// dllmain.h : Declaration of module class.

#ifndef DLLMAIN_H
#define DLLMAIN_H

#include "stdafx.h"
#include "resource.h"
#include "TestProtocol.h"

class CTestProtocolModule : public ATL::CAtlDllModuleT< CTestProtocolModule >
{
public :
    DECLARE_LIBID(LIBID_TestProtocolLib)
    DECLARE_REGISTRY_APPID_RESOURCEID(IDR_TESTPROTOCOL, "{f1d4c579-c0e3-4e35-a55a-cf6a4979310d}")
};

extern class CTestProtocolModule _AtlModule;

#endif // DLLMAIN_H