
#include "wrapper/ipmi/constants/constants_dev.h"
#include "wrapper/ipmi/sel/sel.h"
#include "ipmiutil/util/ipmicmd.h"
#include "wrapper/utils/sensor_table.h"
#include "wrapper/utils/event_table.h"

using namespace std;
using namespace wrapper::ipmi;
using namespace wrapper::utils;

// ipmiutil implementation re-write
namespace ipmiutil_rw {

extern "C" {
	#include <time.h>
	#include <string.h>
	#define MAX_BUFFER_SIZE        255

	// [Re-use] Based on ipmiutil - ievents.c - fmt_time()
	void fmt_time(time_t etime, char *buf, int bufsz) {
		time_t t = etime;
		if (bufsz < 20) printf("fmt_time: buffer size should be >= 18\n");
		strncpy(buf, "0000-00-00T00:00:00", bufsz);
		// A redfish format
		strftime(buf, bufsz, "%Y-%m-%dT%H:%M:%S", gmtime(&t));
		return;
	}

	void get_time_str(uchar *time_bytes, char *buf, int bufsz) {
		time_t event_time = time_bytes[0] + (time_bytes[1] << 8) +
			(time_bytes[2] << 16) + (time_bytes[3] << 24);
		fmt_time(event_time, buf, bufsz);
	}

	// [Re-write] Based on ipmiutil - isel.c - ClearSEL()
	int clear_sel(void)
	{ 
		parse_lan_options('V', (char*)"4", 0); /*admin priv to clear*/
		uchar responseData[MAX_BUFFER_SIZE];
		int responseLength = MAX_BUFFER_SIZE;
		int status;
		uchar inputData[6];
		uchar completionCode;
		ushort cmd;

		cmd = RESERVE_SEL;  /*0x0A42*/
		status = ipmi_cmd(cmd, inputData, 0, responseData,
			&responseLength, &completionCode, constants::Global::DEBUG_MODE);

		if (status == ACCESS_OK && completionCode == 0) {
			cmd = CLEAR_SEL;  /*0x0A47*/
			inputData[0] = responseData[0];  /*Reservation ID [0]*/
			inputData[1] = responseData[1];  /*Reservation ID [1]*/
			inputData[2] = 'C';
			inputData[3] = 'L';
			inputData[4] = 'R';
			inputData[5] = 0xAA;   /* initiate erase */
			status = ipmi_cmd(cmd, inputData, 6, responseData,
				&responseLength, &completionCode, constants::Global::DEBUG_MODE);
			/* The reservation is cancelled by the CLEAR_SEL cmd */
		}
		if (status == ACCESS_OK) {
			if (completionCode) {
				printf("ClearSEL: cmd = %x, completion code=%x\n",
					cmd, completionCode);
				status = completionCode;
			}
			else {
				/* Successful, done. */
				printf("ClearSEL: Log Cleared successfully\n");
			}
		}
		else {
			printf("ClearSEL: cmd = %x, error status = %d\n",
				cmd, status);
		}
		return(status);
	}  /* ClearSEL()*/

	#define REC_SIZE        16    /*SEL Record Size, see IPMI 1.5 Table 26-1 */
	#define MIN_FREE       128    /*=8*16, minimal bytes of free SEL space */
	// [Re-write] Based on ipmiutil - isel.c - ReadSELinfo()
	int get_sel_info(sel::SELInfo& sel_info)
	{
		uint vfree, vused, vtotal, vsize;
		vsize = REC_SIZE;
		uchar responseData[MAX_BUFFER_SIZE];
		int responseLength = MAX_BUFFER_SIZE;
		int status;
		uchar completionCode;
		uchar inputData[6];
		uchar b;
		char *strb;
		char time_add[20] = { 0 };
		char time_erase[20] = { 0 };

		status = ipmi_cmd(GET_SEL_INFO, inputData, 0, responseData,
			&responseLength, &completionCode, constants::Global::DEBUG_MODE);
		if (constants::Global::DEBUG_MODE) printf("GetSelInfo status = %x, cc = %x\n",
			status, completionCode);

		if ((status == ACCESS_OK) && (completionCode == 0)) {
			vfree = responseData[3] + (responseData[4] << 8); // in Bytes
			vused = responseData[1] + (responseData[2] << 8); // in Entries/Allocation Units
			get_time_str(responseData + 5, time_add, sizeof(time_add));
			get_time_str(responseData + 9, time_erase, sizeof(time_erase));
			vtotal = vused + (vfree / vsize); // vsize from AllocationInfo
			b = responseData[13];
			if (b & 0x80) strb = (char*)" overflow"; /*SEL overflow occurred*/
			else strb = (char*)"";
			if (b & 0x1) {         // Get SEL Allocation Info supported
				status = ipmi_cmd(GET_SEL_ALLOCATION_INFO, inputData, 0,
					responseData, &responseLength,
					&completionCode, constants::Global::DEBUG_MODE);
				if (constants::Global::DEBUG_MODE) printf("GetSelInfo status = %x, cc = %x\n",
					status, completionCode);
				if ((status == ACCESS_OK) && (completionCode == 0)) {
					vsize = responseData[2] + (responseData[3] << 8);
					if (vsize == 0) vsize = REC_SIZE;
					vtotal = responseData[0] + (responseData[1] << 8);
				}
			}

			printf("SEL %s Size = %d records (Used=%d, Free=%d)\n",
				strb, vtotal, vused, vfree / vsize);
			sel_info.total_count = vtotal;
			sel_info.used_count = vused;
			sel_info.last_addition_timestamp = time_add;
			sel_info.last_erase_timestamp = time_erase;
			//successful, done
			return(0);
		}
		else {
			vfree = MIN_FREE * 2; /*sane values to avoid SEL full warning*/
			vused = 0;
			vtotal = vused + (vfree / vsize);
			sel_info.total_count = vtotal;
			sel_info.used_count = vused;
			sel_info.last_addition_timestamp = time_add;
			sel_info.last_erase_timestamp = time_erase;
			return(1);
		}
	}  /*end ReadSELinfo()*/

	#pragma pack(1)
	typedef struct
	{
		ushort             record_id;
		uchar              record_type;
		uint               timestamp;
		ushort             generator_id;    /*slave_addr/channel*/
		uchar              evm_rev;         //event message revision
		uchar              sensor_type;
		uchar              sensor_number;
		uchar              event_trigger;
		uchar              event_data1;
		uchar              event_data2;
		uchar              event_data3;
	} SEL_RECORD;
	#pragma pack()

	#define RECORD_BASE     2     //base value to the SEL record in IMB resp data

	// [Re-write] Reference to ipmiutil - isel.c - GetSelEntry()
	int read_sel_entry(unsigned short rec_id, sel::SELEntry& sel_entry) {
		SEL_RECORD selBuf;
		SEL_RECORD *selRecord = &selBuf;
		uchar responseData[MAX_BUFFER_SIZE];
		int responseLength = MAX_BUFFER_SIZE;
		int status;
		uchar inputData[6];
		uchar completionCode;
		char* cpRecordID;	 
		ushort inRecordID;   //save the input record id
		
		inRecordID = rec_id;
		if (!selRecord) {
			if (constants::Global::DEBUG_MODE)
				printf("GetSelEntry: error, output buffer is NULL\n");
			return -3;
		}

		//set the reservation id to zero
		inputData[0] = 0;
		inputData[1] = 0;

		//set the record id to get
		cpRecordID = (char*)&inRecordID;
		inputData[2] = cpRecordID[0];
		inputData[3] = cpRecordID[1];

		//set the offset to the record to value zero
		inputData[4] = 0;

		//set the number of byte to read.  0xFF means read the entire record
		inputData[5] = (char)0xFF;

		status = ipmi_cmd(GET_SEL_ENTRY, inputData, 6, responseData,
			&responseLength, &completionCode, constants::Global::DEBUG_MODE);

		if (status == ACCESS_OK) {
			if (completionCode) {
				if (completionCode == 0xCB && inRecordID == 0)
					printf("Firmware Log (SEL) is empty\n");
				else
					printf("GetSelEntry[%x]: completion code=%x\n",
						inRecordID, completionCode); // responseData[0]);
			}
			else {
				//successful, done

				//save the next SEL record id
				cpRecordID[0] = responseData[0];
				cpRecordID[1] = responseData[1];
				
				//save the SEL record content
				//(note that selRecord structure must be pragma_pack'd)
				memcpy(selRecord, &responseData[RECORD_BASE], 16);
				sel_entry.next_rec_id = inRecordID;
				sel_entry.rec_id = selRecord->record_id;
				//non-OEM
				if (selRecord->record_type < 0xc0) {
			
					
					
					sel_entry.sensor_number = selRecord->sensor_number;
					sel_entry.sensor_type = selRecord->sensor_type;
					char time[20] = { 0 };
					get_time_str((uchar*)&selRecord->timestamp, time, sizeof(time));
					sel_entry.timestamp = time;
				
					//event trigger byte[7] 0 - asserted 1 - deasserted
					bool asserted = ((selRecord->event_trigger & 0x80) == 0);
					//event type[6-4]
					sel_entry.event_entry.type =
						(int)(selRecord->event_trigger & 0x7F);
					//event offset event_data1[3-0]
					sel_entry.event_entry.offset =
						(int)(selRecord->event_data1 & 0x0F);

					//build message string
					string sensor_name = "Unknown Sensor";
					try {
						sensor_name = 
							SensorTable::get_instance()->look_up(sel_entry.sensor_type);
					}
					catch (...) {
						printf("Unable to get sensor name for sensor 0x%02x\n", sel_entry.sensor_type);
					}
					sel_entry.message += sensor_name + " ";
					sel_entry.message += std::to_string(sel_entry.sensor_number);
					sel_entry.message += constants::SELStrings::SAPERATOR;
					string event_desc = "Unknow Event";
					unsigned int event = make_event(sel_entry.event_entry.type, sel_entry.event_entry.offset);
					try {
						event_desc =
							EventTable::get_instance()->look_up(event);
					}
					catch (...) {
						printf("Unable to get sensor name for event 0x%04x\n", event);
					}
					sel_entry.message += event_desc;
					sel_entry.message += constants::SELStrings::SAPERATOR;
					if (asserted) {
						sel_entry.message += constants::SELStrings::ASSERTED;
					}
					else {
						sel_entry.message += constants::SELStrings::DEASSERTED;
					}
				}
				else {
					sel_entry.timestamp = "0000-00-00T00:00:00";
					sel_entry.message = "OEM";
				}
				//sel_entry.event_entry
				if (rec_id == 0 || rec_id == selRecord->record_id)
				{
					/* We return success if the input record is
					begin-of-SEL (value 0), or
					input and output record id matches.
					*/
					
					return 0;
				}
				else
				{
					/* If last record, inRecordID will be -1 from
					response data, so return -1 as normal EOF.
					(fix to bug 279)
					*/
					if (rec_id == 0xFFFF) return(-1);
					/* If not last record, this is an error. */
					if (constants::Global::DEBUG_MODE)
						printf("GetSelEntry: input id  %d != output id %d \n", inRecordID, selRecord->record_id);
					
					return -4;
				}
			}
		}
		return status;
	}
}
}




StatusCode sel::get_sel_info(OUT SELInfo& sel_info) {
	return ipmiutil_rw::get_sel_info(sel_info);
}


StatusCode sel::get_log_entry(IN unsigned short rec_id, OUT SELEntry& sel_entry) {
	return ipmiutil_rw::read_sel_entry(rec_id, sel_entry);
}



StatusCode sel::clear_entries() {
	return ipmiutil_rw::clear_sel();
}
