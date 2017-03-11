/*
 * Copyright (c) 2004 Kontron Canada, Inc.  All Rights Reserved.
 *
 * Base on code from
 * Copyright (c) 2003 Sun Microsystems, Inc.  All Rights Reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * Redistribution of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *
 * Redistribution in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 *
 * Neither the name of Sun Microsystems, Inc. or the names of
 * contributors may be used to endorse or promote products derived
 * from this software without specific prior written permission.
 *
 * This software is provided "AS IS," without a warranty of any kind.
 * ALL EXPRESS OR IMPLIED CONDITIONS, REPRESENTATIONS AND WARRANTIES,
 * INCLUDING ANY IMPLIED WARRANTY OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE OR NON-INFRINGEMENT, ARE HEREBY EXCLUDED.
 * SUN MICROSYSTEMS, INC. ("SUN") AND ITS LICENSORS SHALL NOT BE LIABLE
 * FOR ANY DAMAGES SUFFERED BY LICENSEE AS A RESULT OF USING, MODIFYING
 * OR DISTRIBUTING THIS SOFTWARE OR ITS DERIVATIVES.  IN NO EVENT WILL
 * SUN OR ITS LICENSORS BE LIABLE FOR ANY LOST REVENUE, PROFIT OR DATA,
 * OR FOR DIRECT, INDIRECT, SPECIAL, CONSEQUENTIAL, INCIDENTAL OR
 * PUNITIVE DAMAGES, HOWEVER CAUSED AND REGARDLESS OF THE THEORY OF
 * LIABILITY, ARISING OUT OF THE USE OF OR INABILITY TO USE THIS SOFTWARE,
 * EVEN IF SUN HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
 */

#ifndef IPMI_KONTRONOEM_H
#define IPMI_KONTRONOEM_H


#define IPMI_BUF_SIZE  1024
#ifdef HAVE_LANPLUS
#include "../lib/lanplus/lanplus_defs.h"
#endif

#define TRUE   1
#define FALSE  0

#define IPMI_NETFN_APP           0x06
#define IPMI_NETFN_STORAGE       0x0a
#define IPMI_NETFN_PICMG         0x2C

#define IPMI_BMC_SLAVE_ADDR             0x20

#define BMC_GET_DEVICE_ID               0x1
#define GET_FRU_INFO         0x10
#define GET_FRU_DATA         0x11

#pragma pack(1)
struct fru_info {
        uint16_t size;
        uint8_t access:1;
};
struct fru_header {
        uint8_t version;
        struct {
                uint8_t internal;
                uint8_t chassis;
                uint8_t board;
                uint8_t product;
                uint8_t multi;
        } offset;
        uint8_t pad;
        uint8_t checksum;
};
#pragma pack()

/* the ERRs are defined in ipmicmd.h */
int ipmi_kontronoem_main(void *intf, int argc, char **argv);

#endif /* IPMI_KONTRONOEM_H */
