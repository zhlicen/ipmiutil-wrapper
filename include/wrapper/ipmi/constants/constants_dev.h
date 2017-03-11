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


// Global consts
typedef consts {
#ifndef DEBUG
	CONST_CHAR(DEBUG_MODE, 0);
#else
	CONST_CHAR(DEBUG_MODE, 1);
#endif
} Global;


// Lan Option Keys
typedef consts{
	CONST_CHAR(ADDRESS, 'N');
	CONST_CHAR(USER_NAME, 'U');
	CONST_CHAR(PASSWORD, 'P');
} LanOptionKeys;


}
}
}
#endif
