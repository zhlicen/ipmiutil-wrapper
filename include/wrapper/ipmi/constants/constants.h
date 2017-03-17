// Constants definition for waRpper user
#ifndef WRAPPER_IPMI_CONSTANTS_CONSTANTS_H
#define WRAPPER_IPMI_CONSTANTS_CONSTANTS_H

// const define macros
#define CONST_CHAR(name, value) static const char name = (value);
#define CONST_BYTE(name, value) static const unsigned char name = (value);
#define CONST_UINT(name, value) static const unsigned int name = (value);
#define CONST_SINT(name, value) static const int name = (value);
#define CONST_USHORT(name, value) static const unsigned short name = (value);
#define CONST_STR(name, value) static constexpr char *name = (char*)(value);
#define CONST_BOOL(name, value) static const bool name = (value);

// consts class
#define consts namespace 

// Parameter prefixes
#ifndef IN
#define IN
#endif 
#ifndef OUT
#define OUT
#endif


namespace wrapper {
namespace ipmi {

using StatusCode = int;

namespace constants {

// IPMI Status Codes
consts StatusCodes{
	CONST_SINT(OK, 0);
};

consts SELRecIDs {
	CONST_USHORT(FIRST_SEL, 0x0000);
	CONST_USHORT(LAST_SEL, 0xFFFF);
};

// SENSOR TYPE
// Table 42-3 in IPMI Spec.
consts SensorTypes {
	CONST_USHORT(reserved, 0x00);
	CONST_USHORT(Temperature, 0x01);
	CONST_USHORT(Voltage, 0x02);
	CONST_USHORT(Current, 0x03);
	CONST_USHORT(Fan, 0x04);
	CONST_USHORT(PlatformChassisIntrusion, 0x05);
	CONST_USHORT(PlatformSecurityViolation, 0x06);
	CONST_USHORT(Processor, 0x07);
	CONST_USHORT(PowerSupply, 0x08);
	CONST_USHORT(PowerUnit, 0x09);
	CONST_USHORT(CoolingDevice, 0x0A);
	CONST_USHORT(FRUSensor, 0x0B);
	CONST_USHORT(Memory, 0x0C);
	CONST_USHORT(DriveSlot, 0x0D);
	CONST_USHORT(POSTMemoryResize, 0x0E);
	CONST_USHORT(SystemFirmware, 0x0F);
	CONST_USHORT(SELDisabled, 0x10);
	CONST_USHORT(Watchdog1, 0x11);
	CONST_USHORT(SystemEvent, 0x12);          /*offset0, 1, 2*/
	CONST_USHORT(CriticalInterrupt, 0x13);    /*offset0, 1, 2*/
	CONST_USHORT(Button, 0x14);               /*offset0, 1, 2*/
	CONST_USHORT(Board, 0x15);
	CONST_USHORT(Microcontroller, 0x16);
	CONST_USHORT(AddinCard, 0x17);
	CONST_USHORT(Chassis, 0x18);
	CONST_USHORT(ChipSet, 0x19);
	CONST_USHORT(OtherFRU, 0x1A);
	CONST_USHORT(CableInterconnect, 0x1B);
	CONST_USHORT(Terminator, 0x1C);
	CONST_USHORT(SystemBootInitiated, 0x1D);
	CONST_USHORT(BootError, 0x01E);
	CONST_USHORT(OSBoot, 0x1F);
	CONST_USHORT(OSCriticalStop, 0x20);
	CONST_USHORT(SlotConnector, 0x21);
	CONST_USHORT(ACPIPowerState, 0x22);
	CONST_USHORT(Watchdog2, 0x23);
	CONST_USHORT(PlatformAlert, 0x24);
	CONST_USHORT(EntityPresence, 0x25);
	CONST_USHORT(MonitorASIC, 0x26);
	CONST_USHORT(LAN, 0x27);
	CONST_USHORT(ManagementSubsystemHealth, 0x28);
	CONST_USHORT(Battery, 0x29);
	CONST_USHORT(SessionAudit, 0x2A);
	CONST_USHORT(VersionChange, 0x2B);
	CONST_USHORT(FRUState, 0x2C);
};

}
}
}
#endif
