#ifndef WRAPPER_IPMI_SEL_REF_H
#define WRAPPER_IPMI_SEL_REF_H

#include <string>

namespace wrapper {
namespace ipmi {
namespace sel{

// SEL Entry
typedef struct {
	unsigned int next_rec_id;
	unsigned int rec_id;
	std::string timestamp;
	int sensor_type;
	int sensor_number;
	std::string message;
	struct {
		int type;
		int offset;
	} event_entry;
} SELEntry;

// SEL Info
typedef struct {
	unsigned int total_count;
	unsigned int used_count;
	std::string last_addition_timestamp;
	std::string last_erase_timestamp;
} SELInfo;

}
}
}

#endif