

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.01.0622 */
/* at Mon Jan 18 19:14:07 2038
 */
/* Compiler settings for TestProtocol.idl:
    Oicf, W1, Zp8, env=Win64 (32b run), target_arch=AMD64 8.01.0622 
    protocol : all , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */



/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 500
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif /* __RPCNDR_H_VERSION__ */


#ifndef __TestProtocol_h__
#define __TestProtocol_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __WRdsProtocolManager_FWD_DEFINED__
#define __WRdsProtocolManager_FWD_DEFINED__

#ifdef __cplusplus
typedef class WRdsProtocolManager WRdsProtocolManager;
#else
typedef struct WRdsProtocolManager WRdsProtocolManager;
#endif /* __cplusplus */

#endif 	/* __WRdsProtocolManager_FWD_DEFINED__ */


#ifndef __WRdsProtocolListener_FWD_DEFINED__
#define __WRdsProtocolListener_FWD_DEFINED__

#ifdef __cplusplus
typedef class WRdsProtocolListener WRdsProtocolListener;
#else
typedef struct WRdsProtocolListener WRdsProtocolListener;
#endif /* __cplusplus */

#endif 	/* __WRdsProtocolListener_FWD_DEFINED__ */


#ifndef __WRdsProtocolConnection_FWD_DEFINED__
#define __WRdsProtocolConnection_FWD_DEFINED__

#ifdef __cplusplus
typedef class WRdsProtocolConnection WRdsProtocolConnection;
#else
typedef struct WRdsProtocolConnection WRdsProtocolConnection;
#endif /* __cplusplus */

#endif 	/* __WRdsProtocolConnection_FWD_DEFINED__ */


#ifndef __WRdsProtocolLicenseConnection_FWD_DEFINED__
#define __WRdsProtocolLicenseConnection_FWD_DEFINED__

#ifdef __cplusplus
typedef class WRdsProtocolLicenseConnection WRdsProtocolLicenseConnection;
#else
typedef struct WRdsProtocolLicenseConnection WRdsProtocolLicenseConnection;
#endif /* __cplusplus */

#endif 	/* __WRdsProtocolLicenseConnection_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "wtsprotocol.h"
#include "shobjidl.h"

#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __TestProtocolLib_LIBRARY_DEFINED__
#define __TestProtocolLib_LIBRARY_DEFINED__

/* library TestProtocolLib */
/* [version][helpstring][uuid] */ 


EXTERN_C const IID LIBID_TestProtocolLib;

EXTERN_C const CLSID CLSID_WRdsProtocolManager;

#ifdef __cplusplus

class DECLSPEC_UUID("23b3ed19-0299-45bd-b235-0c0c9bab40a4")
WRdsProtocolManager;
#endif

EXTERN_C const CLSID CLSID_WRdsProtocolListener;

#ifdef __cplusplus

class DECLSPEC_UUID("9f790faf-8f95-47fa-bb72-19150220585a")
WRdsProtocolListener;
#endif

EXTERN_C const CLSID CLSID_WRdsProtocolConnection;

#ifdef __cplusplus

class DECLSPEC_UUID("549085ba-495f-4b6f-b4a2-f0886ff5e29e")
WRdsProtocolConnection;
#endif

EXTERN_C const CLSID CLSID_WRdsProtocolLicenseConnection;

#ifdef __cplusplus

class DECLSPEC_UUID("73c7a2a4-7950-41ae-b2b7-c4e53708b616")
WRdsProtocolLicenseConnection;
#endif
#endif /* __TestProtocolLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


