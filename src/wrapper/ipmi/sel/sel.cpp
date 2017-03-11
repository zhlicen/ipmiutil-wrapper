#include "wrapper/ipmi/constants/constants_dev.h"
#include "wrapper/ipmi/sel/sel.h"

using namespace wrapper::ipmi;


// [Re-write] Reference to ipmiutil - isel.c - ReadSELinfo()
StatusCode sel::get_sel_info(OUT SELInfo& sel_info) {
	return constants::StatusCodes::OK;
}

// [Re-write] Reference to ipmiutil - isel.c - ReadSEL()
StatusCode sel::get_log_entry(IN unsigned int rec_id, OUT SELEntry& sel_entry) {
	return constants::StatusCodes::OK;
}

// [Reuse] Reference to ipmiutil - isel.c - ClearSEL()
extern int ClearSEL(void);
StatusCode sel::clear_entries() {
	return ClearSEL();
}
