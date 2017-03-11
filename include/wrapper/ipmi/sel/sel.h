#ifndef WRAPPER_IPMI_SEL_LAN_H
#define WRAPPER_IPMI_SEL_LAN_H

#include <string>
#include "wrapper/ipmi/constants/constants.h"
#include "wrapper/ipmi/sel/ref.h"

namespace wrapper {
namespace ipmi {
namespace sel {

StatusCode get_sel_info(OUT SELInfo& sel_info);

StatusCode get_log_entry(IN unsigned int rec_id, OUT SELEntry& sel_entry);

StatusCode clear_entries();

}
}
}

#endif