#ifndef WRAPPER_IPMI_LAN_LAN_H
#define WRAPPER_IPMI_LAN_LAN_H

#include "wrapper/ipmi/constants/constants.h"
#include "wrapper/ipmi/lan/ref.h"

namespace wrapper {
namespace ipmi {
namespace lan{

void config_lan_option(IN const LanOption& lan_opt);

}
}
}
#endif
