#ifndef WRAPPER_IPMI_UTILS_SENSOR_TABLE_H
#define WRAPPER_IPMI_UTILS_SENSOR_TABLE_H

#include <string>
#include "wrapper/utils/map_table.h"
#include "wrapper/ipmi/constants/constants.h"

namespace wrapper {
namespace utils {

class RegisterSensorTypes;

using SensorTable = MapTable<unsigned short, std::string, RegisterSensorTypes>;

class RegisterSensorTypes{ 
public:
	explicit RegisterSensorTypes(SensorTable::AddFunc add) {
		add(ipmi::constants::SensorTypes::reserved, "reserved");
		add(ipmi::constants::SensorTypes::Temperature, "Temperature");
		add(ipmi::constants::SensorTypes::Voltage, "Voltage");
		add(ipmi::constants::SensorTypes::Current, "Current");
		add(ipmi::constants::SensorTypes::Fan, "Fan");
		add(ipmi::constants::SensorTypes::PlatformChassisIntrusion, "Platform Chassis Intrusion");
		add(ipmi::constants::SensorTypes::PlatformSecurityViolation, "Platform Security Violation");
		add(ipmi::constants::SensorTypes::Processor, "Processor");
		add(ipmi::constants::SensorTypes::PowerSupply, "Power Supply");
		add(ipmi::constants::SensorTypes::PowerUnit, "PowerUnit");
		add(ipmi::constants::SensorTypes::CoolingDevice, "Cooling Device");
		add(ipmi::constants::SensorTypes::FRUSensor, "FRU Sensor");
		add(ipmi::constants::SensorTypes::Memory, "Memory");
		add(ipmi::constants::SensorTypes::DriveSlot, "DriveSlot");
		add(ipmi::constants::SensorTypes::POSTMemoryResize, "POST Memory Resize");
		add(ipmi::constants::SensorTypes::SystemFirmware, "System Firmware");
		add(ipmi::constants::SensorTypes::SELDisabled, "SEL Disabled");
		add(ipmi::constants::SensorTypes::Watchdog1, "Watchdog 1");
		add(ipmi::constants::SensorTypes::SystemEvent, "System Event");                /*offset0, 1, 2*/
		add(ipmi::constants::SensorTypes::CriticalInterrupt, "Critical Interrupt");    /*offset0, 1, 2*/
		add(ipmi::constants::SensorTypes::Button, "Button");                           /*offset0, 1, 2*/
		add(ipmi::constants::SensorTypes::Board, "Board");
		add(ipmi::constants::SensorTypes::Microcontroller, "Microcontroller");
		add(ipmi::constants::SensorTypes::AddinCard, "Add-in Card");
		add(ipmi::constants::SensorTypes::Chassis, "Chassis");
		add(ipmi::constants::SensorTypes::ChipSet, "Chip Set");
		add(ipmi::constants::SensorTypes::OtherFRU, "Other FRU");
		add(ipmi::constants::SensorTypes::CableInterconnect, "Cable / Interconnect");
		add(ipmi::constants::SensorTypes::Terminator, "Terminator");
		add(ipmi::constants::SensorTypes::SystemBootInitiated, "System Boot Initiated");
		add(ipmi::constants::SensorTypes::BootError, "Boot Error");
		add(ipmi::constants::SensorTypes::OSBoot, "OS Boot");
		add(ipmi::constants::SensorTypes::OSCriticalStop, "OS Critical Stop");
		add(ipmi::constants::SensorTypes::SlotConnector, "Slot / Connector");
		add(ipmi::constants::SensorTypes::ACPIPowerState, "ACPI Power State");
		add(ipmi::constants::SensorTypes::Watchdog2, "Watchdog 2");
		add(ipmi::constants::SensorTypes::PlatformAlert, "Platform Alert");
		add(ipmi::constants::SensorTypes::EntityPresence, "Entity Presence");
		add(ipmi::constants::SensorTypes::MonitorASIC, "MonitorASIC");
		add(ipmi::constants::SensorTypes::LAN, "LAN");
		add(ipmi::constants::SensorTypes::ManagementSubsystemHealth, "Management Subsystem Health");
		add(ipmi::constants::SensorTypes::Battery, "Battery");
	}
};



}
}
#endif