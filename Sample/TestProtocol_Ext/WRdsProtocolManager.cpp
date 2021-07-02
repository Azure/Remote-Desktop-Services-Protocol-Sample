// WRdsProtocolManager.cpp : Implementation of CWRdsProtocolManager
//https://docs.microsoft.com/en-us/windows/win32/api/wtsprotocol/nn-wtsprotocol-iwrdsprotocolmanager
//Most of these methods are optional and are a result of being inside svchost

#include "WRdsProtocolManager.h"

// CWRdsProtocolManager

// Inherited via IWRdsProtocolManager
HRESULT __stdcall CWRdsProtocolManager::QueryInterface(REFIID riid, void ** ppvObject) noexcept
{
    HRESULT hResult = E_NOINTERFACE;

    if (!ppvObject)
    {
        hResult = E_POINTER;
    }
    else
    {
        if ((riid == __uuidof(IWRdsProtocolManager)) ||
            (riid == IID_IUnknown))
        {
            hResult = S_OK;
            this->AddRef(); // The caller is responsible for release.
            *ppvObject = this;
        }
    }
    return  hResult;
}

HRESULT CWRdsProtocolManager::Initialize(IWRdsProtocolSettings *pIWRdsSettings, PWRDS_SETTINGS pWRdsSettings)
{

    return S_OK;
}

HRESULT CWRdsProtocolManager::CreateListener(WCHAR *wszListenerName, IWRdsProtocolListener **pProtocolListener)
{
    HRESULT hr;
    CComObject<CWRdsProtocolListener> * newListener = NULL;

    hr = CComObject<CWRdsProtocolListener>::CreateInstance(&newListener);
    if (FAILED(hr) || NULL == newListener)
    {
        return ERROR;
    }
    *pProtocolListener = newListener;
    // Released by caller (termsrv)
    (*pProtocolListener)->AddRef();

    return S_OK;
}

HRESULT CWRdsProtocolManager::NotifyServiceStateChange(WRDS_SERVICE_STATE *pTSServiceStateChange)
{
    return S_OK;
}

HRESULT CWRdsProtocolManager::NotifySessionOfServiceStart(WRDS_SESSION_ID *SessionId)
{
    return E_NOTIMPL;
}

HRESULT CWRdsProtocolManager::NotifySessionOfServiceStop(WRDS_SESSION_ID *SessionId)
{
    return E_NOTIMPL;
}

HRESULT CWRdsProtocolManager::NotifySessionStateChange(WRDS_SESSION_ID *SessionId, ULONG EventId)
{
    return E_NOTIMPL;
}

HRESULT CWRdsProtocolManager::NotifySettingsChange(PWRDS_SETTINGS pWRdsSettings)
{
    return E_NOTIMPL;
}

HRESULT CWRdsProtocolManager::Uninitialize()
{
    return S_OK;
}
