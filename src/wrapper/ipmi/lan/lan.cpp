#include "wrapper/ipmi/constants/constants_dev.h"
#include "wrapper/ipmi/lan/lan.h"
#include "ipmiutil/util/ipmicmd.h"

using namespace  wrapper::ipmi;

void lan::config_lan_option(OUT const lan::LanOption& lan_opt) {
	parse_lan_options(constants::LanOptionKeys::ADDRESS, 
		NON_CONST_CHAR(lan_opt.ip.c_str()), 
		constants::Global::DEBUG_MODE);

	parse_lan_options(constants::LanOptionKeys::PORT,
		NON_CONST_CHAR(lan_opt.port.c_str()),
		constants::Global::DEBUG_MODE);

	parse_lan_options(constants::LanOptionKeys::USER_NAME,
		NON_CONST_CHAR(lan_opt.usr.c_str()),
		constants::Global::DEBUG_MODE);

	parse_lan_options(constants::LanOptionKeys::PASSWORD,
		NON_CONST_CHAR(lan_opt.pwd.c_str()),
		constants::Global::DEBUG_MODE);
}
