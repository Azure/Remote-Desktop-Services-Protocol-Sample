// WRdsProtocolConnection.h : Declaration of the CWRdsProtocolConnection

#pragma once

#ifndef WRDS_PROTOCOL_CONNECTION_H
#define WRDS_PROTOCOL_CONNECTION_H

#include <strsafe.h>

#include "resource.h"       // main symbols
#include "TestProtocol.h"
#include "TestProtocolAPI.h"
#include "stdafx.h"
#include "WRdsProtocolLicenseConnection.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

using namespace ATL;


// CWRdsProtocolConnection

class ATL_NO_VTABLE CWRdsProtocolConnection :
    public CComObjectRootEx<CComMultiThreadModel>,
    public CComCoClass<CWRdsProtocolConnection, &CLSID_WRdsProtocolConnection>,
    public IWRdsProtocolConnection,
    public IWRdsWddmIddProps
{
    IWRdsProtocolConnectionCallback* ConnectionCallback = NULL;
    WCHAR* UserName = NULL;
    WCHAR* Password = NULL;
    WCHAR* Domain = NULL;

public:
    CWRdsProtocolConnection()
    {
       
    }

DECLARE_REGISTRY_RESOURCEID(108)


BEGIN_COM_MAP(CWRdsProtocolConnection)
    COM_INTERFACE_ENTRY2(IUnknown, IWRdsProtocolConnection)
    COM_INTERFACE_ENTRY2(IUnknown, IWRdsWddmIddProps)
    COM_INTERFACE_ENTRY(IWRdsProtocolConnection)
    COM_INTERFACE_ENTRY(IWRdsWddmIddProps)
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

    // Inherited via IWRdsProtocolConnection
    virtual HRESULT __stdcall GetLogonErrorRedirector(IWRdsProtocolLogonErrorRedirector ** ppLogonErrorRedir) override;

    virtual HRESULT __stdcall AcceptConnection(void) override;

    virtual HRESULT __stdcall GetClientData(WRDS_CLIENT_DATA * pClientData) override;

    virtual HRESULT __stdcall GetClientMonitorData(UINT * pNumMonitors, UINT * pPrimaryMonitor) override;

    virtual HRESULT __stdcall GetUserCredentials(WRDS_USER_CREDENTIAL * pUserCreds) override;

    virtual HRESULT __stdcall GetLicenseConnection(IWRdsProtocolLicenseConnection ** ppLicenseConnection) override;

    virtual HRESULT __stdcall AuthenticateClientToSession(WRDS_SESSION_ID * SessionId) override;

    virtual HRESULT __stdcall NotifySessionId(WRDS_SESSION_ID * SessionId, HANDLE_PTR SessionHandle) override;

    virtual HRESULT __stdcall GetInputHandles(HANDLE_PTR * pKeyboardHandle, HANDLE_PTR * pMouseHandle, HANDLE_PTR * pBeepHandle) override;

    virtual HRESULT __stdcall GetVideoHandle(HANDLE_PTR * pVideoHandle) override;

    virtual HRESULT __stdcall ConnectNotify(ULONG SessionId) override;

    virtual HRESULT __stdcall IsUserAllowedToLogon(ULONG SessionId, HANDLE_PTR UserToken, WCHAR * pDomainName, WCHAR * pUserName) override;

    virtual HRESULT __stdcall SessionArbitrationEnumeration(HANDLE_PTR hUserToken, BOOL bSingleSessionPerUserEnabled, ULONG * pSessionIdArray, ULONG * pdwSessionIdentifierCount) override;

    virtual HRESULT __stdcall LogonNotify(HANDLE_PTR hClientToken, WCHAR * wszUserName, WCHAR * wszDomainName, WRDS_SESSION_ID * SessionId, PWRDS_CONNECTION_SETTINGS pWRdsConnectionSettings) override;

    virtual HRESULT __stdcall PreDisconnect(ULONG DisconnectReason) override;

    virtual HRESULT __stdcall DisconnectNotify(void) override;

    virtual HRESULT __stdcall Close(void) override;

    virtual HRESULT __stdcall GetProtocolStatus(WRDS_PROTOCOL_STATUS * pProtocolStatus) override;

    virtual HRESULT __stdcall GetLastInputTime(ULONG64 * pLastInputTime) override;

    virtual HRESULT __stdcall SetErrorInfo(ULONG ulError) override;

    virtual HRESULT __stdcall CreateVirtualChannel(CHAR * szEndpointName, BOOL bStatic, ULONG RequestedPriority, ULONG_PTR * phChannel) override;

    virtual HRESULT __stdcall QueryProperty(GUID QueryType, ULONG ulNumEntriesIn, ULONG ulNumEntriesOut, PWRDS_PROPERTY_VALUE pPropertyEntriesIn, PWRDS_PROPERTY_VALUE pPropertyEntriesOut) override;

    virtual HRESULT __stdcall GetShadowConnection(IWRdsProtocolShadowConnection ** ppShadowConnection) override;

    virtual HRESULT __stdcall NotifyCommandProcessCreated(ULONG SessionId) override;


    // Inherited via IWRdsWddmIddProps
    virtual HRESULT __stdcall GetHardwareId(WCHAR * pDisplayDriverHardwareId, DWORD Count) override;

    virtual HRESULT __stdcall OnDriverLoad(ULONG SessionId, HANDLE_PTR DriverHandle) override;

    virtual HRESULT __stdcall OnDriverUnload(ULONG SessionId) override;

    virtual HRESULT __stdcall EnableWddmIdd(BOOL Enabled) override;

    // Written for TestProtocol
    HRESULT _stdcall SetCredentials(WCHAR* Domain, WCHAR* UserName, WCHAR* Password);

    void SetConnectionCallback(IWRdsProtocolConnectionCallback* ConnectionCallback);

    IWRdsProtocolConnectionCallback* GetConnectionCallback();

};

OBJECT_ENTRY_AUTO(__uuidof(WRdsProtocolConnection), CWRdsProtocolConnection)

#endif // WRDS_PROTOCOL_CONNECTION_H
