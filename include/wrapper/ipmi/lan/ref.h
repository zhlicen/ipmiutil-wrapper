#ifndef WRAPPER_IPMI_LAN_REF_H
#define WRAPPER_IPMI_LAN_REF_H

#include <string>

namespace wrapper {
namespace ipmi {
namespace lan{


typedef struct {
	std::string ip;
	std::string port;
	std::string usr;
	std::string pwd;
} LanOption;


}
}
}

#endif