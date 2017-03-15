#ifndef WRAPPER_IPMI_SEL_REF_H
#define WRAPPER_IPMI_SEL_REF_H

#include <string>

namespace wrapper {
namespace ipmi {
namespace sel{

// SEL Entry
typedef struct {
	unsigned short next_rec_id;
	unsigned short rec_id;
	std::string timestamp;
	unsigned short sensor_type;
	unsigned short sensor_number;
	std::string message;
	struct {
		unsigned short type;
		unsigned short offset;
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