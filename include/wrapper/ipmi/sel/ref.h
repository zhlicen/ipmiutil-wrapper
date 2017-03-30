#ifndef WRAPPER_IPMI_SEL_REF_H
#define WRAPPER_IPMI_SEL_REF_H

#include <string>

namespace wrapper {
namespace ipmi {
namespace sel {

extern "C" {
// SEL Entry
typedef struct {
	unsigned short next_rec_id{0};
	unsigned short rec_id{0};
	std::string timestamp{};
	unsigned short sensor_type{0};
	unsigned short sensor_number{0};
	std::string message{};
	bool asserted{false};
	struct {
		unsigned char type{0};
		unsigned char offset{0};
		std::string entry_code_string{};
	} event_entry{};
} SELEntry;

// SEL Info
typedef struct {
	unsigned int total_count{0};
	unsigned int used_count{0};
	std::string last_addition_timestamp{};
	std::string last_erase_timestamp{};
} SELInfo;

}
}
}
}
#endif