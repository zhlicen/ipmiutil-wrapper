// Constants definition for developer only
#ifndef WRAPPER_IPMI_CONSTANTS_CONSTANTS_DEV_H
#define WRAPPER_IPMI_CONSTANTS_CONSTANTS_DEV_H

#include "wrapper/ipmi/constants/constants.h"
using StatusCode = int;

// Unsafe, for ccapatible with C interfaces
#define NON_CONST_CHAR(val) const_cast<char*>(val)



namespace wrapper {
namespace ipmi {
namespace constants {

extern "C" {

// Global consts
consts Global {
#ifndef DEBUG
	CONST_CHAR(DEBUG_MODE, 1);
#else
	CONST_CHAR(DEBUG_MODE, 1);
#endif
}


// Lan Option Keys
consts LanOptionKeys {
	CONST_CHAR(ADDRESS, 'N');
	CONST_CHAR(PORT, 'p');
	CONST_CHAR(USER_NAME, 'U');
	CONST_CHAR(PASSWORD, 'P');
	CONST_CHAR(PRIV_LEVEL, 'V');
}


// SEL Strings
consts SELStrings {
	CONST_STR(SAPERATOR, ", ");
	CONST_STR(ASSERTED, "Asserted");
	CONST_STR(DEASSERTED, "Deasserted");
}

}

}
}
}
#endif
