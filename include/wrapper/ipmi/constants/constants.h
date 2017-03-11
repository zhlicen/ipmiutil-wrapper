// Constants definition for waRpper user
#ifndef WRAPPER_IPMI_CONSTANTS_CONSTANTS_H
#define WRAPPER_IPMI_CONSTANTS_CONSTANTS_H

// const define macros
#define CONST_CHAR(name, value) static const char name = (value);
#define CONST_BYTE(name, value) static const unsigned char name = (value);
#define CONST_UINT(name, value) static const unsigned int name = (value);
#define CONST_SINT(name, value) static const int name = (value);
#define CONST_STR(name, value) static const char *name = (value);
#define CONST_BOOL(name, value) static const bool name = (value);

// consts class
#define consts struct

// Parameter prefixes
#ifndef IN
#define IN
#endif 
#ifndef OUT
#define OUT
#endif


namespace wrapper {
namespace ipmi {

using StatusCode = int;

namespace constants {

// IPMI Status Codes
typedef consts{
	CONST_SINT(OK, 0);
} StatusCodes;

typedef consts{
	CONST_UINT(FIRST_SEL, 0x0000);
	CONST_UINT(LAST_SEL, 0xFFFF);
} SELRecIDs;

}
}
}
#endif
