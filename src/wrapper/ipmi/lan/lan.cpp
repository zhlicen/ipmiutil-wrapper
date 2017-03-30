#include <string.h>
#include "wrapper/ipmi/constants/constants_dev.h"
#include "wrapper/ipmi/lan/lan.h"
#include "ipmiutil/util/ipmicmd.h"

using namespace  wrapper::ipmi;

void lan::config_lan_option(IN const lan::LanOption& lan_opt) {
	static lan::LanOption saved_option{};
	if(saved_option == lan_opt) {
		return;
	}
	saved_option = lan_opt;
	ipmi_close();
	const int IP_LEN = 15;
	const int PORT_LEN = 5;
	const int MAX_USERNAME = 80;
	const int MAX_PWD = 20;
	char ip[IP_LEN + 1] = {0}; 
	char port[PORT_LEN + 1] = {0}; 
	char usr[MAX_USERNAME + 1] = {0};  
	char pwd[MAX_PWD + 1] = {0}; 
	strncpy(ip, lan_opt.ip.c_str(), IP_LEN);
	strncpy(port, lan_opt.port.c_str(), PORT_LEN);
	strncpy(usr, lan_opt.usr.c_str(), MAX_USERNAME);
	strncpy(pwd, lan_opt.pwd.c_str(), MAX_PWD);	
	char priv_level_admin[] = { "4" };
	parse_lan_options(constants::LanOptionKeys::ADDRESS, 
		ip, 
		constants::Global::DEBUG_MODE);

	parse_lan_options(constants::LanOptionKeys::PORT,
		port,
		constants::Global::DEBUG_MODE);

	parse_lan_options(constants::LanOptionKeys::USER_NAME,
		usr,
		constants::Global::DEBUG_MODE);

	parse_lan_options(constants::LanOptionKeys::PASSWORD,
		pwd,
		constants::Global::DEBUG_MODE);

	parse_lan_options(constants::LanOptionKeys::PRIV_LEVEL, 
		priv_level_admin, 
		0); /*admin priv to clear*/
}
