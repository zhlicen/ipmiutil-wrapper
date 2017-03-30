#ifndef WRAPPER_IPMI_SEL_LAN_H
#define WRAPPER_IPMI_SEL_LAN_H

#include <string>
#include "wrapper/ipmi/constants/constants.h"
#include "wrapper/ipmi/sel/ref.h"
#include "wrapper/ipmi/lan/ref.h"

namespace wrapper {
namespace ipmi {
namespace sel {

StatusCode get_sel_info(IN const lan::LanOption& lan_opt, IN OUT SELInfo& sel_info);

StatusCode get_log_entry(IN const lan::LanOption& lan_opt, IN unsigned short rec_id, OUT SELEntry& sel_entry);

StatusCode clear_entries(IN const lan::LanOption& lan_opt);

}
}
}

#endif