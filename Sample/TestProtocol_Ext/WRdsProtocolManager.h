// WRdsProtocolManager.h : Declaration of the CWRdsProtocolManager

#pragma once

#ifndef WRDS_PROTOCOL_MANAGER_H
#define WRDS_PROTOCOL_MANAGER_H

#include "resource.h"       // main symbols

#include "stdafx.h"
#include "TestProtocol.h"
#include "WRdsProtocolListener.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

using namespace ATL;


// CWRdsProtocolManager

class ATL_NO_VTABLE CWRdsProtocolManager :
    public CComObjectRootEx<CComMultiThreadModel>,
    public CComCoClass<CWRdsProtocolManager, &CLSID_WRdsProtocolManager>,
    public IWRdsProtocolManager
{
public:
    CWRdsProtocolManager()
    {
    }

DECLARE_REGISTRY_RESOURCEID(106)


BEGIN_COM_MAP(CWRdsProtocolManager)
    COM_INTERFACE_ENTRY2(IUnknown, IWRdsProtocolManager)
    COM_INTERFACE_ENTRY(IWRdsProtocolManager)
END_COM_MAP()

    DECLARE_PROTECT_FINAL_CONSTRUCT()

    HRESULT FinalConstruct()
    {
        return S_OK;
    }

    void FinalRelease()
    {
    }

public:

    // Inherited via IWRdsProtocolManager
    virtual HRESULT __stdcall Initialize(IWRdsProtocolSettings *pIWRdsSettings, PWRDS_SETTINGS pWRdsSettings);

    virtual HRESULT __stdcall CreateListener(WCHAR *wszListenerName, IWRdsProtocolListener **pProtocolListener);

    virtual HRESULT __stdcall NotifyServiceStateChange(WRDS_SERVICE_STATE *pTSServiceStateChange);

    virtual HRESULT __stdcall NotifySessionOfServiceStart(WRDS_SESSION_ID *SessionId);

    virtual HRESULT __stdcall NotifySessionOfServiceStop(WRDS_SESSION_ID *SessionId);

    virtual HRESULT __stdcall NotifySessionStateChange(WRDS_SESSION_ID *SessionId, ULONG EventId);

    virtual HRESULT __stdcall NotifySettingsChange(PWRDS_SETTINGS pWRdsSettings);

    virtual HRESULT __stdcall Uninitialize();

};

OBJECT_ENTRY_AUTO(__uuidof(WRdsProtocolManager), CWRdsProtocolManager)

#endif // WRDS_PROTOCOL_MANAGER_H