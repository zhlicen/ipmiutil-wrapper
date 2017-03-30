#ifndef WRAPPER_IPMI_UTILS_IPMIUTIL_LOCK_H
#define WRAPPER_IPMI_UTILS_IPMIUTIL_LOCK_H
//ipmiutil supports only one command at one time,
//this mutex should be locked every command 
#include <mutex>
namespace wrapper {
namespace utils {

std::recursive_mutex ipmiutil_mutex{};

}
}


#define COMMAND_LOCK std::lock_guard<std::recursive_mutex> command_lock{wrapper::utils::ipmiutil_mutex};
#endif