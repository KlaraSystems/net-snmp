/*
 * While Darwin 10 (aka, Mac OS X 10.6 Snow Leopard) is "BSD-like", it differs
 * substantially enough to not warrant pretending it is a BSD flavor.
 * This first section are the vestigal BSD remnants.
 */
/* Portions of this file are subject to the following copyright(s).  See
 * the Net-SNMP's COPYING file for more details and other copyrights
 * that may apply:
 */
/*
 * Portions of this file are copyrighted by:
 * Copyright (C) 2007 Apple, Inc. All rights reserved.
 * Use is subject to license terms specified in the COPYING file
 * distributed with the Net-SNMP package.
 */

/*
 * BSD systems use a different method of looking up sockaddr_in values 
 */
/* #define NEED_KLGETSA 1 */

#define CHECK_RT_FLAGS 1

/*
 * this is not good enough before freebsd3! 
 */
/* #undef HAVE_NET_IF_MIB_H */

/*
 * This section adds the relevant definitions from generic.h
 * (a file we don't include here)
 */

/*
 * udp_inpcb list symbol, e.g. for mibII/udpTable.c
 */
#define INP_NEXT_SYMBOL inp_next

/*
 * This section defines Mac OS X 10.5 (and later) specific additions.
 */
#define darwin 10
#ifndef darwin10
#   define darwin10 darwin
#endif

/*
 * Mac OS X should only use the modern API and definitions.
 */
#ifndef NETSNMP_NO_LEGACY_DEFINITIONS
#define NETSNMP_NO_LEGACY_DEFINITIONS 1
#endif

/*
 * use new host resources files as well
 */
#define NETSNMP_INCLUDE_HOST_RESOURCES
#define NETSNMP_INCLUDE_HRSWINST_REWRITES
#define NETSNMP_INCLUDE_HRSWRUN_REWRITES
#undef NETSNMP_INCLUDE_HRSWRUN_WRITE_SUPPORT
#define NETSNMP_CAN_GET_DISK_LABEL 1

/*
 * Enabling this restricts the compiler to mostly public APIs.
 */
#ifndef __APPLE_API_STRICT_CONFORMANCE
#define __APPLE_API_STRICT_CONFORMANCE 1
#endif
#ifndef __APPLE_API_UNSTABLE
#define __APPLE_API_UNSTABLE 1
#endif

/*
 * Although Darwin does have an fstab.h file, getfsfile etc. always return null.
 * At least, as of 5.3.
 */
#undef HAVE_FSTAB_H

#define SWAPFILE_DIR "/private/var/vm"
#define SWAPFILE_PREFIX "swapfile"

/*
 * These apparently used to be in netinet/tcp_timers.h, but went away in
 * 10.4.2. Define them here til we find out a way to get the real values.
 */
#define TCPTV_MIN       (  1*PR_SLOWHZ)         /* minimum allowable value */
#define TCPTV_REXMTMAX  ( 64*PR_SLOWHZ)         /* max allowable REXMT value */

/*
 * Because Mac OS X is built on Mach, it does not provide a BSD-compatible
 * VM statistics API.
 */
#define USE_MACH_HOST_STATISTICS 1

/*
 * This tells code that manipulates IPv6 that the structures are unified,
 * i.e., IPv4 and IPv6 use the same structs.
 * This should eventually be replaced with a configure directive.
 */
/* #define USE_UNIFIED_IPV6_STRUCTS 1 */
#undef STRUCT_in6pcb_HAS_inp_vflag

/*
 * utility macro used in several darwin specific files
 */
#define SNMP_CFRelease(x) do { if (x) { CFRelease(x); x = NULL; } } while(0)

/*
 * Mac OS X runs on both PPC and Intel hardware,
 *   which handle udpTable index values differently
 */
#include <TargetConditionals.h>
#ifdef TARGET_RT_LITTLE_ENDIAN
#define UDP_ADDRESSES_IN_HOST_ORDER 1
#endif

