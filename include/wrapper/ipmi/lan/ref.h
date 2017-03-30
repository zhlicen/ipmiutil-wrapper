#ifndef WRAPPER_IPMI_LAN_REF_H
#define WRAPPER_IPMI_LAN_REF_H

#include <string>

namespace wrapper {
namespace ipmi {
namespace lan{

extern "C" {
	
typedef struct lanOption{
	bool operator==(const lanOption& other){
		return (other.ip == ip && other.port == port 
		&& other.usr == usr && other.pwd == pwd);
	}
	std::string ip;
	std::string port;
	std::string usr;
	std::string pwd;
} LanOption;

}

}
}
}

#endif