// WRdsProtocolListener.h : Declaration of the CWRdsProtocolListener

#pragma once

#ifndef WRDS_PROTOCOL_LISTENER_H
#define WRDS_PROTOCOL_LISTENER_H

#include "resource.h"       // main symbols

#include "stdafx.h"
#include "WRdsProtocolConnection.h"

#include "TestProtocol.h"
#include "TestProtocolAPI.h"


#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

using namespace ATL;


class ATL_NO_VTABLE CWRdsProtocolListener :
    public CComObjectRootEx<CComMultiThreadModel>,
    public CComCoClass<CWRdsProtocolListener, &CLSID_WRdsProtocolListener>,
    public IWRdsProtocolListener
{
    IWRdsProtocolListenerCallback * pListenerCallback = NULL;
    HANDLE threadHandle = NULL;

public:
    CWRdsProtocolListener()
    {
    }

DECLARE_REGISTRY_RESOURCEID(107)


BEGIN_COM_MAP(CWRdsProtocolListener)
    COM_INTERFACE_ENTRY2(IUnknown, IWRdsProtocolListener)
    COM_INTERFACE_ENTRY(IWRdsProtocolListener)
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
    // Inherited via IWRdsProtocolListener
    virtual HRESULT __stdcall GetSettings(WRDS_LISTENER_SETTING_LEVEL WRdsListenerSettingLevel, PWRDS_LISTENER_SETTINGS pWRdsListenerSettings) override;

    virtual HRESULT __stdcall StartListen(IWRdsProtocolListenerCallback * pCallback) override;

    virtual HRESULT __stdcall StopListen(void) override;

};

OBJECT_ENTRY_AUTO(__uuidof(WRdsProtocolListener), CWRdsProtocolListener)

#endif // WRDS_PROTOCOL_LISTENER_H