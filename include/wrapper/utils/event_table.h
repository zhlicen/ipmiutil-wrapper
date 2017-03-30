#ifndef WRAPPER_IPMI_UTILS_EVENT_TABLE_H
#define WRAPPER_IPMI_UTILS_EVENT_TABLE_H

#include <string>
#include "wrapper/utils/map_table.h"
#include "wrapper/ipmi/constants/constants.h"

namespace wrapper {
namespace utils {

unsigned int make_event(unsigned char event_type, unsigned char event_offset);
unsigned int make_sensor_specific_event(unsigned short sensor_type, 
	unsigned char event_type, unsigned char event_offset);


// Generic
unsigned int make_event(unsigned char event_type, unsigned char event_offset) {
	unsigned int event = event_type;
	event <<= 8;
	event += event_offset;
	return event;
}

// Sensor Specific
unsigned int make_sensor_specific_event(unsigned short sensor_type, 
	unsigned char event_type, unsigned char event_offset) {
	unsigned int event = sensor_type;
	event = (unsigned int) event  << 16;
	unsigned short event_body = event_type;
	event_body = (unsigned short)(event_body << 8);
	event_body = (unsigned short)(event_body + event_offset);
	event += event_body;
	return event;
}

class RegisterEventTypes;

using EventTable = MapTable<unsigned int, std::string, RegisterEventTypes>;

class RegisterEventTypes{ 
public:
	
	explicit RegisterEventTypes(EventTable::AddFunc add) {
		// add(make_event(0x0, 0x0),  "Assert");
        // add(make_event(0x0, 0x0),  "Deassert");   
		// Redfish LogEntryCode
		// IPMI Spec. Table 42-2
        add(make_event(0x01, 0x00),  "Lower Non-critical - going low");   
        add(make_event(0x01, 0x01),  "Lower Non-critical - going high");   
        add(make_event(0x01, 0x02),  "Lower Critical - going low");    
        add(make_event(0x01, 0x03),  "Lower Critical - going high");    
        add(make_event(0x01, 0x04),  "Lower Non-recoverable - going low");     
        add(make_event(0x01, 0x05),  "Lower Non-recoverable - going high");     
        add(make_event(0x01, 0x06),  "Upper Non-critical - going low");      
        add(make_event(0x01, 0x07),  "Upper Non-critical - going high");      
        add(make_event(0x01, 0x08),  "Upper Critical - going low");    
        add(make_event(0x01, 0x09),  "Upper Critical - going high");      
        add(make_event(0x01, 0x0A),  "Upper Non-recoverable - going low");   
        add(make_event(0x01, 0x0B),  "Upper Non-recoverable - going high");        
        add(make_event(0x02, 0x00),  "Transition to Idle");
        add(make_event(0x02, 0x01),  "Transition to Active");      
        add(make_event(0x02, 0x02),  "Transition to Busy");        
        add(make_event(0x03, 0x00),  "State Deasserted");       
        add(make_event(0x03, 0x01),  "State Asserted");     
        add(make_event(0x04, 0x00),  "Predictive Failure deasserted");       
        add(make_event(0x04, 0x01),  "Predictive Failure asserted");             
        add(make_event(0x05, 0x00),  "Limit Not Exceeded");              
        add(make_event(0x05, 0x01),  "Limit Exceeded");                
        add(make_event(0x06, 0x00),  "Performance Met");        
        add(make_event(0x06, 0x01),  "Performance Lags");
        add(make_event(0x07, 0x00),  "Transition to OK");
        add(make_event(0x07, 0x01),  "Transition to Non-Critical from OK");
        add(make_event(0x07, 0x02),  "Transition to Critical from less severe");
        add(make_event(0x07, 0x03),  "Transition to Non-recoverable from less severe");
        add(make_event(0x07, 0x04),  "Transition to Non-Critical from more severe");
        add(make_event(0x07, 0x05),  "Transition to Critical from Non-recoverable");
        add(make_event(0x07, 0x06),  "Transition to Non-recoverable");
        add(make_event(0x07, 0x07),  "Monitor");
        add(make_event(0x07, 0x08),  "Informational");
        add(make_event(0x08, 0x00),  "Device Removed / Device Absent");        
        add(make_event(0x08, 0x01),  "Device Inserted / Device Present");
        add(make_event(0x09, 0x00),  "Device Disabled");        
        add(make_event(0x09, 0x01),  "Device Enabled");        
        add(make_event(0x0A, 0x00),  "Transition to Running");        
        add(make_event(0x0A, 0x1),  "Transition to In Test");        
        add(make_event(0x0A, 0x02),  "Transition to Power Off");
        add(make_event(0x0A, 0x03),  "Transition to On Line");        
        add(make_event(0x0A, 0x04),  "Transition to Off Line");        
        add(make_event(0x0A, 0x05),  "Transition to Off Duty");
        add(make_event(0x0A, 0x06),  "Transition to Degraded");        
        add(make_event(0x0A, 0x07),  "Transition to Power Save");        
        add(make_event(0x0A, 0x08),  "Install Error");        
        add(make_event(0x0B, 0x00),  "Fully Redundant");        
        add(make_event(0x0B, 0x01),  "Redundancy Lost");        
        add(make_event(0x0B, 0x02),  "Redundancy Degraded");        
        add(make_event(0x0B, 0x03),  "Non-redundant:Sufficient Resources from Redundant");        
        add(make_event(0x0B, 0x04),  "Non-redundant:Sufficient Resources from Insufficient Resources");        
        add(make_event(0x0B, 0x05),  "Non-redundant:Insufficient Resources");
        add(make_event(0x0B, 0x06),  "Redundancy Degraded from Fully Redundant");
        add(make_event(0x0B, 0x07),  "Redundancy Degraded from Non-redundant");
        add(make_event(0x0C, 0x00),  "D0 Power State");
        add(make_event(0x0C, 0x01),  "D1 Power State");        
        add(make_event(0x0C, 0x02),  "D2 Power State");
        add(make_event(0x0C, 0x03),  "D3 Power State");


		// IPMI Spec. Table 42-3
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::reserved,
			0x6f, 0x00), "reserved");

		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::Temperature,
			0x6f, 0x00), "Presence");

		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::Voltage,
			0x6f, 0x00), "Presence");

		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::Current,
			0x6f, 0x00), "Presence");

		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::Fan,
			0x6f, 0x00), "Presence");

		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::PlatformChassisIntrusion,
			0x6f, 0x00), "Generic Chassis Instruction");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::PlatformChassisIntrusion,
			0x6f, 0x01), "Drive Bay instruction");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::PlatformChassisIntrusion,
			0x6f, 0x02), "I/O Card area intrusion");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::PlatformChassisIntrusion,
			0x6f, 0x03), "Processor area intrusion");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::PlatformChassisIntrusion,
			0x6f, 0x04), "LAN Leash Lost ");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::PlatformChassisIntrusion,
			0x6f, 0x05), "Unauthorized dock/undock");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::PlatformChassisIntrusion,
			0x6f, 0x06), "FAN area intrusion ");

		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::PlatformSecurityViolation,
			0x6f, 0x00), "Secure Mode");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::PlatformSecurityViolation,
			0x6f, 0x01), "Pre-boot Password Violation - user password");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::PlatformSecurityViolation,
			0x6f, 0x02), "Pre-boot Password Violation attempt - setup password");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::PlatformSecurityViolation,
			0x6f, 0x03), "Pre-boot Password Violation - network boot password");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::PlatformSecurityViolation,
			0x6f, 0x04), "Other pre-boot Password Violation");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::PlatformSecurityViolation,
			0x6f, 0x05), "Out-of-band Access Password Violation");

		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::Processor,
			0x6f, 0x00), "IERR");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::Processor,
			0x6f, 0x01), "Thermal Trip");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::Processor,
			0x6f, 0x02), "FRB1/BIST failure");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::Processor,
			0x6f, 0x03), "FRB2/Hang in POST failure ");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::Processor,
			0x6f, 0x04), "FRB3/Processor Startup/Initialization failure");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::Processor,
			0x6f, 0x05), "Configuration Error");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::Processor,
			0x6f, 0x06), "SM BIOS Uncorrectable CPU-complex Error");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::Processor,
			0x6f, 0x07), "Processor Presence detected");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::Processor,
			0x6f, 0x08), "Processor disabled");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::Processor,
			0x6f, 0x09), "Terminator Presence Detected");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::Processor,
			0x6f, 0x0A), "Processor Automatically Throttled ");

		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::PowerSupply,
			0x6f, 0x00), "Presence detected");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::PowerSupply,
			0x6f, 0x01), "Power Supply Failure detected");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::PowerSupply,
			0x6f, 0x02), "Predictive Failure");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::PowerSupply,
			0x6f, 0x03), "Power Supply input lost (AC/DC)");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::PowerSupply,
			0x6f, 0x04), "Power Supply input lost or out-of-range");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::PowerSupply,
			0x6f, 0x05), "Power Supply input out-of-range, but present");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::PowerSupply,
			0x6f, 0x06), "Configuration error");

		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::PowerUnit,
			0x6f, 0x00), "Power Off / Power Down");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::PowerUnit,
			0x6f, 0x01), "Power Cycle");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::PowerUnit,
			0x6f, 0x02), "240VA Power Down");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::PowerUnit,
			0x6f, 0x03), "Interlock Power Down");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::PowerUnit,
			0x6f, 0x04), "AC lost");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::PowerUnit,
			0x6f, 0x05), "Soft Power Control Failure");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::PowerUnit,
			0x6f, 0x06), "Power Unit Failure detected");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::PowerUnit,
			0x6f, 0x07), "Predictive Failure");

		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::Memory,
			0x6f, 0x00), "Correctable ECC / other correctable memory error");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::Memory,
			0x6f, 0x01), "Uncorrectable ECC / other uncorrectable memory error");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::Memory,
			0x6f, 0x02), "Parity");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::Memory,
			0x6f, 0x03), "Memory Scrub Failed");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::Memory,
			0x6f, 0x04), "Memory Device Disabled");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::Memory,
			0x6f, 0x05), "Correctable ECC / other correctable memory error logging limit reached");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::Memory,
			0x6f, 0x06), "Presence detected");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::Memory,
			0x6f, 0x07), "Configuration error");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::Memory,
			0x6f, 0x08), "Spare");

		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::SystemFirmware,
			0x6f, 0x00), "System Firmware Error");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::SystemFirmware,
			0x6f, 0x01), "System Firmware Hang");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::SystemFirmware,
			0x6f, 0x02), "System Firmware Progress");

		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::SELDisabled,
			0x6f, 0x00), "Correctable Memory Error Logging Disabled");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::SELDisabled,
			0x6f, 0x01), "Event Type Logging Disabled");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::SELDisabled,
			0x6f, 0x02), "Log Area Reset/Cleared");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::SELDisabled,
			0x6f, 0x03), "All Event Logging Disabled");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::SELDisabled,
			0x6f, 0x04), "SEL Full");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::SELDisabled,
			0x6f, 0x05), "SEL Almost Full");

		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::Watchdog1,
			0x6f, 0x00), "BIOS Watchdog Reset");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::Watchdog1,
			0x6f, 0x01), "OS Watchdog Reset");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::Watchdog1,
			0x6f, 0x02), "OS Watchdog Shut Down");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::Watchdog1,
			0x6f, 0x03), "OS Watchdog Power Down");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::Watchdog1,
			0x6f, 0x04), "OS Watchdog Power Cycle");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::Watchdog1,
			0x6f, 0x05), "OS Watchdog NMI / Diagnostic Interrupt");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::Watchdog1,
			0x6f, 0x06), "OS Watchdog Expired, status only");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::Watchdog1,
			0x6f, 0x07), "OS Watchdog pre-timeout Interrupt, non-NMI");

		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::SystemEvent,
			0x6f, 0x00), "System Reconfigured");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::SystemEvent,
			0x6f, 0x01), "OEM System Boot Event");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::SystemEvent,
			0x6f, 0x02), "Undetermined system hardware failure");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::SystemEvent,
			0x6f, 0x03), "Entry added to Auxiliary Log");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::SystemEvent,
			0x6f, 0x04), "PEF Action");

		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::CriticalInterrupt,
			0x6f, 0x0), "Front Panel NMI / Diagnostic Interrupt");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::CriticalInterrupt,
			0x6f, 0x01), "Bus Timeout");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::CriticalInterrupt,
			0x6f, 0x02), "I/O channel check NMI");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::CriticalInterrupt,
			0x6f, 0x03), "Software NMI");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::CriticalInterrupt,
			0x6f, 0x04), "PCI PERR");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::CriticalInterrupt,
			0x6f, 0x05), "PCI SERR");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::CriticalInterrupt,
			0x6f, 0x06), "EISA Fail Safe Timeout");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::CriticalInterrupt,
			0x6f, 0x07), "Bus Correctable Error");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::CriticalInterrupt,
			0x6f, 0x08), "Bus Uncorrectable Error");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::CriticalInterrupt,
			0x6f, 0x09), "Fatal NMI (port 61h, bit 7)");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::CriticalInterrupt,
			0x6f, 0x0A), "Bus Fatal Error");

		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::Button,
			0x6f, 0x00), "Power Button pressed");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::Button,
			0x6f, 0x01), "Sleep Button pressed");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::Button,
			0x6f, 0x02), "Reset Button pressed");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::Button,
			0x6f, 0x03), "FRU latch open");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::Button,
			0x6f, 0x04), "FRU service request button");

		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::ChipSet,
			0x6f, 0x00), "Soft Power Control Failure");
		
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::SystemBootInitiated,
			0x6f, 0x00), "Initiated by power up");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::SystemBootInitiated,
			0x6f, 0x01), "Initiated by hard reset");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::SystemBootInitiated,
			0x6f, 0x02), "Initiated by warm reset");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::SystemBootInitiated,
			0x6f, 0x03), "User requested PXE boot");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::SystemBootInitiated,
			0x6f, 0x04), "Automatic boot to diagnostic");

		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::BootError,
			0x6f, 0x00), "No bootable media");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::BootError,
			0x6f, 0x01), "Non-bootable diskette left in drive");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::BootError,
			0x6f, 0x02), "PXE Server not found");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::BootError,
			0x6f, 0x03), "Invalid boot sector");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::BootError,
			0x6f, 0x04), "Timeout waiting for user selection of boot source");

		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::OSBoot,
			0x6f, 0x00), "A: boot completed");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::OSBoot,
			0x6f, 0x01), "C: boot completed");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::OSBoot,
			0x6f, 0x02), "PXE boot completed");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::OSBoot,
			0x6f, 0x03), "Diagnostic boot completed");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::OSBoot,
			0x6f, 0x04), "CD-ROM boot completed");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::OSBoot,
			0x6f, 0x05), "ROM boot completed");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::OSBoot,
			0x6f, 0x06), "boot completed - boot device not specified");

		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::OSCriticalStop,
			0x6f, 0x00), "Stop during OS load / initialization");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::OSCriticalStop,
			0x6f, 0x01), "Run-time Stop");

		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::SlotConnector,
			0x6f, 0x00), "Fault Status asserted");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::SlotConnector,
			0x6f, 0x01), "Identify Status asserted");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::SlotConnector,
			0x6f, 0x02), "Slot / Connector Device installed/attached");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::SlotConnector,
			0x6f, 0x03), "Slot / Connector Ready for Device Installation");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::SlotConnector,
			0x6f, 0x04), "Slot/Connector Ready for Device Removal");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::SlotConnector,
			0x6f, 0x05), "Slot Power is Off");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::SlotConnector,
			0x6f, 0x06), "Slot / Connector Device Removal Request");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::SlotConnector,
			0x6f, 0x07), "Interlock asserted");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::SlotConnector,
			0x6f, 0x08), "Slot is Disabled");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::SlotConnector,
			0x6f, 0x09), "Slot holds spare device");

		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::ACPIPowerState,
			0x6f, 0x00), "S0 / G0 working");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::ACPIPowerState,
			0x6f, 0x01), "S1 sleeping with system h/w & processor context maintained");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::ACPIPowerState,
			0x6f, 0x02), "S2 sleeping, processor context lost");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::ACPIPowerState,
			0x6f, 0x03), "S3 sleeping, processor & h/w context lost, memory retained.");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::ACPIPowerState,
			0x6f, 0x04), "S4 non-volatile sleep / suspend-to disk");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::ACPIPowerState,
			0x6f, 0x05), "S5 / G2 soft-off");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::ACPIPowerState,
			0x6f, 0x06), "S4 / S5 soft-off, particular S4 / S5 state cannot be determined");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::ACPIPowerState,
			0x6f, 0x07), "G3 / Mechanical Off");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::ACPIPowerState,
			0x6f, 0x08), "Sleeping in an S1, S2, or S3 states ");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::ACPIPowerState,
			0x6f, 0x09), "G1 sleeping");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::ACPIPowerState,
			0x6f, 0x0A), "S5 entered by override");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::ACPIPowerState,
			0x6f, 0x0B), "Legacy ON state");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::ACPIPowerState,
			0x6f, 0x0C), "Legacy OFF state");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::ACPIPowerState,
			0x6f, 0x0E), "Uknown");

		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::Watchdog2,
			0x6f, 0x00), "Timer expired, status only");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::Watchdog2,
			0x6f, 0x01), "Hard Reset");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::Watchdog2,
			0x6f, 0x02), "Power Down");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::Watchdog2,
			0x6f, 0x03), "Power Cycle");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::Watchdog2,
			0x6f, 0x04), "reserved");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::Watchdog2,
			0x6f, 0x05), "reserved");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::Watchdog2,
			0x6f, 0x06), "reserved");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::Watchdog2,
			0x6f, 0x07), "reserved");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::Watchdog2,
			0x6f, 0x08), "Timer interrupt");

		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::PlatformAlert,
			0x6f, 0x00), "platform generated page");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::PlatformAlert,
			0x6f, 0x01), "platform generated LAN alert");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::PlatformAlert,
			0x6f, 0x02), "Platform Event Trap generated, formatted per IPMI PET specification");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::PlatformAlert,
			0x6f, 0x03), "platform generated SNMP trap, OEM format");

		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::EntityPresence,
			0x6f, 0x00), "Entity Present");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::EntityPresence,
			0x6f, 0x01), "Entity Absent");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::EntityPresence,
			0x6f, 0x02), "Entity Disabled");

		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::LAN,
			0x6f, 0x00), "LAN Heartbeat Lost");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::LAN,
			0x6f, 0x01), "LAN Heartbeat");

		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::ManagementSubsystemHealth,
			0x6f, 0x00), "sensor access degraded or unavailable");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::ManagementSubsystemHealth,
			0x6f, 0x01), "controller access degraded or unavailable");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::ManagementSubsystemHealth,
			0x6f, 0x02), "management controller off-line");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::ManagementSubsystemHealth,
			0x6f, 0x03), "management controller unavailable");

		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::Battery,
			0x6f, 0x00), "battery low");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::Battery,
			0x6f, 0x01), "battery failed");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::Battery,
			0x6f, 0x02), "battery presence detected");
	
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::SessionAudit,
			0x6f, 0x00), "Session Activated");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::SessionAudit,
			0x6f, 0x01), "Session Deactivated");

		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::VersionChange,
			0x6f, 0x00), "Hardware change detected with associated Entity");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::VersionChange,
			0x6f, 0x01), "Firmware or software change detected with associated Entity");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::VersionChange,
			0x6f, 0x02), "Hardware incompatibility detected with associated Entity");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::VersionChange,
			0x6f, 0x03), "Firmware or software incompatibility detected with associated Entity");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::VersionChange,
			0x6f, 0x04), "Entity is of an invalid or unsupported hardware version");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::VersionChange,
			0x6f, 0x05), "Entity contains an invalid or unsupported firmware or software version");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::VersionChange,
			0x6f, 0x06), "Hardware Change detected with associated Entity was successful");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::VersionChange,
			0x6f, 0x07), "Software or F/W Change detected with associated Entity was successful");

		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::FRUState,
			0x6f, 0x00), "FRU Not Installed");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::FRUState,
			0x6f, 0x01), "FRU Inactive");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::FRUState,
			0x6f, 0x02), "FRU Activation Requested");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::FRUState,
			0x6f, 0x03), "FRU Activation In Progress");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::FRUState,
			0x6f, 0x04), "FRU Active");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::FRUState,
			0x6f, 0x05), "FRU Deactivation Requested");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::FRUState,
			0x6f, 0x06), "FRU Deactivation In Progress");
		add(make_sensor_specific_event(
			ipmi::constants::SensorTypes::FRUState,
			0x6f, 0x07), "FRU Communication Lost");
	}
};



}
}
#endif