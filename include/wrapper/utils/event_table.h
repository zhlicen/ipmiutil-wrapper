#ifndef WRAPPER_IPMI_UTILS_EVENT_TABLE_H
#define WRAPPER_IPMI_UTILS_EVENT_TABLE_H

#include <string>
#include "wrapper/utils/map_table.h"
#include "wrapper/ipmi/constants/constants.h"

namespace wrapper {
namespace utils {

unsigned int make_event(unsigned short event_type, unsigned short event_offset) {
	unsigned int event = event_type;
	event <<= 16;
	event += event_offset;
	return event;
}

class RegisterEventTypes;

using EventTable = MapTable<unsigned int, std::string, RegisterEventTypes>;

class RegisterEventTypes{ 
public:
	// Redfish LogEntryCode
	// IPMI Spec. Table 42-2
	explicit RegisterEventTypes(EventTable::AddFunc add) {
		// add(make_event(0x0, 0x0),  "Assert");
        // add(make_event(0x0, 0x0),  "Deassert");     
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
	}
};



}
}
#endif