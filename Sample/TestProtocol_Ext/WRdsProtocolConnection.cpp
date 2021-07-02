// WRdsProtocolConnection.cpp : Implementation of CWRdsProtocolConnection
// Please take time to implement most of these functions

#include "WRdsProtocolConnection.h"

HRESULT __stdcall CWRdsProtocolConnection::QueryInterface(REFIID riid, void ** ppvObject) noexcept
{
    HRESULT hResult = E_NOINTERFACE;

    if (!ppvObject)
    {
        hResult = E_POINTER;
    }
    else
    {
        if ((riid == __uuidof(IWRdsProtocolConnection)) ||
            (riid == __uuidof(IWRdsWddmIddProps)) ||
            (riid == IID_IUnknown))
        {
            hResult = S_OK;
            this->AddRef(); // The caller is responsible for release.
            *ppvObject = this;
        }
    }
    return  hResult;
}

HRESULT __stdcall CWRdsProtocolConnection::GetLogonErrorRedirector(IWRdsProtocolLogonErrorRedirector ** ppLogonErrorRedir)
{
    //Optional: gets errors from winlogon that the remote client can handle
    //https://docs.microsoft.com/en-us/windows/win32/api/wtsprotocol/nn-wtsprotocol-iwrdsprotocollogonerrorredirector
    ppLogonErrorRedir = NULL;
    return S_OK;
}

HRESULT __stdcall CWRdsProtocolConnection::AcceptConnection(void)
{
    //A hook to allow preprocessing to happen
    //https://docs.microsoft.com/en-us/windows/win32/api/wtsprotocol/nf-wtsprotocol-iwrdsprotocolconnection-acceptconnection
    return S_OK;
}

HRESULT __stdcall CWRdsProtocolConnection::GetClientData(WRDS_CLIENT_DATA * pClientData)
{
    //https://docs.microsoft.com/en-us/windows/win32/api/wtsprotocol/nf-wtsprotocol-iwrdsprotocolconnection-getclientdata
    errno_t copyReturnValue;

    // Some sample values
    (*pClientData).fEnableWindowsKey = 1;
    (*pClientData).fInheritAutoLogon = 1;
    (*pClientData).fNoAudioPlayback = 1;

    //This is what gets returned when a user will run "qwinsta" and is mandatory
    WCHAR* protocolName = L"TL-Ext";
    copyReturnValue = wcsncpy_s((*pClientData).ProtocolName, protocolName, wcslen(protocolName));

    return S_OK;
}

HRESULT __stdcall CWRdsProtocolConnection::GetClientMonitorData(UINT * pNumMonitors, UINT * pPrimaryMonitor)
{
    //Optional
    //https://docs.microsoft.com/en-us/windows/win32/api/wtsprotocol/nf-wtsprotocol-iwrdsprotocolconnection-getclientmonitordata
    return S_OK;
}

HRESULT __stdcall CWRdsProtocolConnection::GetUserCredentials(WRDS_USER_CREDENTIAL * pUserCreds)
{
    //Return user credentials to pass to winlogon if not using kerberos or other secure mechanisms
    //These can also be passed in from GetClientData
    //Be really really careful about relying on this, and cleaning up plain-text passwords
    //Highly suggested to rely on kerberos/AD/AAD that are significantly more secure
    errno_t copyReturnValue;
  
    copyReturnValue = wcsncpy_s((*pUserCreds).Domain, this->Domain, wcslen(this->Domain));
    if (copyReturnValue != 0)
    {
        return ERROR;
    }

    copyReturnValue = wcsncpy_s((*pUserCreds).UserName, this->UserName, wcslen(this->UserName));
    if (copyReturnValue != 0)
    {
        return ERROR;
    }

    copyReturnValue = wcsncpy_s((*pUserCreds).Password, this->Password, wcslen(this->Password));
    if (copyReturnValue != 0)
    {
        return ERROR;
    }
    
    return S_OK;
}
 
HRESULT __stdcall CWRdsProtocolConnection::GetLicenseConnection(IWRdsProtocolLicenseConnection ** ppLicenseConnection)
{
    //Required: https://docs.microsoft.com/en-us/windows/win32/api/wtsprotocol/nf-wtsprotocol-iwrdsprotocolconnection-getlicenseconnection
    HRESULT hr;

    CComObject<CWRdsProtocolLicenseConnection>* pLicenseConnection = NULL;
    hr = CComObject<CWRdsProtocolLicenseConnection>::CreateInstance(&pLicenseConnection);
    if (FAILED(hr)) 
    {
        return E_FAIL;
    }

    *ppLicenseConnection = pLicenseConnection;

    return S_OK;
} 

HRESULT __stdcall CWRdsProtocolConnection::AuthenticateClientToSession(WRDS_SESSION_ID * SessionId)
{
    //Optional
    //https://docs.microsoft.com/en-us/windows/win32/api/wtsprotocol/nf-wtsprotocol-iwrdsprotocolconnection-authenticateclienttosession
    return E_NOTIMPL;
}

HRESULT __stdcall CWRdsProtocolConnection::NotifySessionId(WRDS_SESSION_ID * SessionId, HANDLE_PTR SessionHandle)
{
    //Optional: https://docs.microsoft.com/en-us/windows/win32/api/wtsprotocol/nf-wtsprotocol-iwrdsprotocolconnection-notifysessionid
    //This returns the session ID when the connection gets a new session
    //Note: You can receive multiple session IDs per connection
    return S_OK;
}
 
HRESULT __stdcall CWRdsProtocolConnection::GetInputHandles(HANDLE_PTR * pKeyboardHandle, HANDLE_PTR * pMouseHandle, HANDLE_PTR * pBeepHandle)
{
    //TODO: Provide sample implementation
    //https://docs.microsoft.com/en-us/windows/win32/api/wtsprotocol/nf-wtsprotocol-iwrdsprotocolconnection-getinputhandles
    pKeyboardHandle = NULL;
    pMouseHandle = NULL;
    pBeepHandle = NULL;
    return S_OK;
}

HRESULT __stdcall CWRdsProtocolConnection::GetVideoHandle(HANDLE_PTR * pVideoHandle)
{
    //TODO: Double check this
    //Not required if using IDD
    //https://docs.microsoft.com/en-us/windows/win32/api/wtsprotocol/nf-wtsprotocol-iwrdsprotocolconnection-getvideohandle
    return S_OK;
}

HRESULT __stdcall CWRdsProtocolConnection::ConnectNotify(ULONG SessionId)
{
    //https://docs.microsoft.com/en-us/windows/win32/api/wtsprotocol/nf-wtsprotocol-iwrdsprotocolconnection-connectnotify
    //Optional, this is returned when the session is "connected".
    //In IDD this is when the IDD driver creation has started
    return S_OK;
}

HRESULT __stdcall CWRdsProtocolConnection::IsUserAllowedToLogon(ULONG SessionId, HANDLE_PTR UserToken, WCHAR * pDomainName, WCHAR * pUserName)
{
    //Optional: https://docs.microsoft.com/en-us/windows/win32/api/wtsprotocol/nf-wtsprotocol-iwrdsprotocolconnection-isuserallowedtologon
    return S_OK;
}

HRESULT __stdcall CWRdsProtocolConnection::SessionArbitrationEnumeration(HANDLE_PTR hUserToken, BOOL bSingleSessionPerUserEnabled, ULONG * pSessionIdArray, ULONG * pdwSessionIdentifierCount)
{
    //https://docs.microsoft.com/en-us/windows/win32/api/wtsprotocol/nf-wtsprotocol-iwrdsprotocolconnection-sessionarbitrationenumeration
    // Optional, this provides mechanism to determine how to arbitrate a user with multiple sessions or if there are not enough licenses
    // E_NOTIMPL results in default session arbitration 
    return E_NOTIMPL;
}

HRESULT __stdcall CWRdsProtocolConnection::LogonNotify(HANDLE_PTR hClientToken, WCHAR * wszUserName, WCHAR * wszDomainName, WRDS_SESSION_ID * SessionId, PWRDS_CONNECTION_SETTINGS pWRdsConnectionSettings)
{
    // Optional: https://docs.microsoft.com/en-us/windows/win32/api/wtsprotocol/nf-wtsprotocol-iwrdsprotocolconnection-logonnotify
    // This is returned when winlogon says the user has been logged on
    return S_OK;
}

HRESULT __stdcall CWRdsProtocolConnection::PreDisconnect(ULONG DisconnectReason)
{
    // Optional: https://docs.microsoft.com/en-us/windows/win32/api/wtsprotocol/nf-wtsprotocol-iwrdsprotocolconnection-predisconnect
    // Happens when the terminal/session is about to get disconnected
    return S_OK;
}


HRESULT __stdcall CWRdsProtocolConnection::DisconnectNotify(void)
{
    //https://docs.microsoft.com/en-us/windows/win32/api/wtsprotocol/nf-wtsprotocol-iwrdsprotocolconnection-disconnectnotify
    // DisconnectNotify is called when the terminal disconnects, it doesn't always mean
    // that the connection itself is being disconnected 
    return S_OK;
}

HRESULT __stdcall CWRdsProtocolConnection::Close(void)
{
    IWRdsProtocolConnectionCallback* localConnectionCallback = NULL;

    if (this->Domain != NULL)
    {
        delete[] this->Domain;
        this->Domain = NULL;
    }
    if (this->UserName != NULL)
    {
        delete[] this->UserName;
        this->UserName = NULL;
    }
    if (this->Password != NULL)
    {
        delete[] this->Password;
        this->Password = NULL;
    }

    localConnectionCallback = GetConnectionCallback();
    if (NULL != localConnectionCallback)
    {
        localConnectionCallback->Release();
        localConnectionCallback = NULL;
    }

    return S_OK;
}

HRESULT __stdcall CWRdsProtocolConnection::GetProtocolStatus(WRDS_PROTOCOL_STATUS * pProtocolStatus)
{
    //Optional: https://docs.microsoft.com/en-us/windows/win32/api/wtsprotocol/nf-wtsprotocol-iwrdsprotocolconnection-getprotocolstatus
    WTS_PROTOCOL_COUNTERS* EmptyProtocolCounters = new WTS_PROTOCOL_COUNTERS;
    WTS_CACHE_STATS* EmptyCacheStats = new WTS_CACHE_STATS;

    (*pProtocolStatus).Output = *EmptyProtocolCounters;
    (*pProtocolStatus).Input = *EmptyProtocolCounters;
    (*pProtocolStatus).Cache = *EmptyCacheStats;
    (*pProtocolStatus).AsyncSignal = 0;
    (*pProtocolStatus).AsyncSignalMask = 0;

    return S_OK;
}

HRESULT __stdcall CWRdsProtocolConnection::GetLastInputTime(ULONG64 * pLastInputTime)
{
    //Required: How to determine if the user is idle
    //https://docs.microsoft.com/en-us/windows/win32/api/wtsprotocol/nf-wtsprotocol-iwrdsprotocolconnection-getlastinputtime
    //This is useful for policies about idle time to save cost
    *pLastInputTime = 0;
    return S_OK;
}

HRESULT __stdcall CWRdsProtocolConnection::SetErrorInfo(ULONG ulError)
{
    //https://docs.microsoft.com/en-us/windows/win32/api/wtsprotocol/nf-wtsprotocol-iwrdsprotocolconnection-seterrorinfo
    //Optional: Set why the connection is being terminated
    return E_NOTIMPL;
}

HRESULT __stdcall CWRdsProtocolConnection::CreateVirtualChannel(CHAR * szEndpointName, BOOL bStatic, ULONG RequestedPriority, ULONG_PTR * phChannel)
{
    //Optional: https://docs.microsoft.com/en-us/windows/win32/api/wtsprotocol/nf-wtsprotocol-iwrdsprotocolconnection-createvirtualchannel
    return E_NOTIMPL;
}

HRESULT __stdcall CWRdsProtocolConnection::QueryProperty(GUID QueryType, ULONG ulNumEntriesIn, ULONG ulNumEntriesOut, PWRDS_PROPERTY_VALUE pPropertyEntriesIn, PWRDS_PROPERTY_VALUE pPropertyEntriesOut)
{
    /*
    if (QueryType == SupportedProperty_GUID) 
    {
        // Set value
        return S_OK;
    }
    */
    //Optional: https://docs.microsoft.com/en-us/windows/win32/api/wtsprotocol/nf-wtsprotocol-iwrdsprotocolconnection-queryproperty
    return E_NOTIMPL;
}

HRESULT __stdcall CWRdsProtocolConnection::GetShadowConnection(IWRdsProtocolShadowConnection ** ppShadowConnection)
{
    //Optional: https://docs.microsoft.com/en-us/windows/win32/api/wtsprotocol/nf-wtsprotocol-iwrdsprotocolconnection-getshadowconnection
    return E_NOTIMPL;
}

HRESULT __stdcall CWRdsProtocolConnection::NotifyCommandProcessCreated(ULONG SessionId)
{
    //Optional: https://docs.microsoft.com/en-us/windows/win32/api/wtsprotocol/nf-wtsprotocol-iwrdsprotocolconnection-notifycommandprocesscreated
    //When winlogon has been created
    return S_OK;
}

HRESULT __stdcall CWRdsProtocolConnection::GetHardwareId(WCHAR * pDisplayDriverHardwareId, DWORD Count)
{
    // Required for IDD graphics drivers
    // https://docs.microsoft.com/en-us/windows/win32/api/wtsprotocol/nf-wtsprotocol-iwrdswddmiddprops-gethardwareid
    // Return your valid graphics driver here, this is defined in the driver's INF file.
    WCHAR* DefaultDisplayDriverHardwareId;
    DefaultDisplayDriverHardwareId = L"SampleGPU_IndirectDisplay_v14_SimpleAutoRemoteConfig";
    HRESULT hr = StringCchCopyW(
        pDisplayDriverHardwareId,
        Count,
        DefaultDisplayDriverHardwareId
    );
    
    return S_OK;
}

HRESULT __stdcall CWRdsProtocolConnection::OnDriverLoad(ULONG SessionId, HANDLE_PTR DriverHandle)
{
    //Optional: Called when the IDD driver has been loaded
    //https://docs.microsoft.com/en-us/windows/win32/api/wtsprotocol/nf-wtsprotocol-iwrdswddmiddprops-ondriverload
    return S_OK;
}

HRESULT __stdcall CWRdsProtocolConnection::OnDriverUnload(ULONG SessionId)
{
    //Optional: Called when the IDD driver has been unloaded
    //https://docs.microsoft.com/en-us/windows/win32/api/wtsprotocol/nf-wtsprotocol-iwrdswddmiddprops-ondriverunload
    return S_OK;
}

HRESULT __stdcall CWRdsProtocolConnection::EnableWddmIdd(BOOL Enabled)
{
    //Required: https://docs.microsoft.com/en-us/windows/win32/api/wtsprotocol/nf-wtsprotocol-iwrdswddmiddprops-enablewddmidd
    //Termsrv tells the stack whether to use IDD or XDDM, modern windows systems will always return true
    //If this returns true, it will load IDD drivers
    //If this returns false, it will load XDDM drivers (legacy)
    return S_OK;
}


HRESULT _stdcall CWRdsProtocolConnection::SetCredentials(WCHAR* Domain, WCHAR* UserName, WCHAR* Password)
{
    //Optional, this is not part of the interface and provided as a helper method
    //This is not secure, please use kerberos or other modern authentication mechanisms
    //Handle credentials with care such as using ZeroMemory
    size_t len;
    size_t result;
    
    len = wcslen(Domain) + 1;
    this->Domain = new WCHAR[len];
    result = StringCchCopyW(this->Domain, len, Domain);

    len = wcslen(UserName) + 1;
    this->UserName = new WCHAR[len];
    result = StringCchCopyW(this->UserName, len, UserName);

    len = wcslen(Password) + 1;
    this->Password = new WCHAR[len];
    result = StringCchCopyW(this->Password, len, Password);

    return S_OK;
}

void CWRdsProtocolConnection::SetConnectionCallback(IWRdsProtocolConnectionCallback* ConnectionCallback)
{
    //https://docs.microsoft.com/en-us/windows/win32/api/wtsprotocol/nn-wtsprotocol-iwtsprotocolconnectioncallback
    this->ConnectionCallback = ConnectionCallback;
}

IWRdsProtocolConnectionCallback* CWRdsProtocolConnection::GetConnectionCallback()
{
    //https://docs.microsoft.com/en-us/windows/win32/api/wtsprotocol/nn-wtsprotocol-iwtsprotocolconnectioncallback
    return this->ConnectionCallback;
}