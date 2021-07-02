// WRdsProtocolListener.cpp : Implementation of CWRdsProtocolListener

#include "WRdsProtocolListener.h"

// CWRdsProtocolListener

HRESULT __stdcall CWRdsProtocolListener::QueryInterface(REFIID riid, void ** ppvObject) noexcept
{
    HRESULT hResult = E_NOINTERFACE;

    if (!ppvObject)
    {
        hResult = E_POINTER;
    }
    else
    {
        if ((riid == __uuidof(IWRdsProtocolListener)) ||
            (riid == IID_IUnknown))
        {
            hResult = S_OK;
            this->AddRef(); // The caller is responsible for release.
            *ppvObject = this;
        }
    }
    return  hResult;
}

HRESULT __stdcall CWRdsProtocolListener::GetSettings(WRDS_LISTENER_SETTING_LEVEL WRdsListenerSettingLevel, PWRDS_LISTENER_SETTINGS pWRdsListenerSettings)
{
    //Optional: https://docs.microsoft.com/en-us/windows/win32/api/wtsprotocol/nf-wtsprotocol-iwrdsprotocollistener-getsettings
    return E_NOTIMPL;
}

HRESULT __stdcall CWRdsProtocolListener::StartListen(IWRdsProtocolListenerCallback * pCallback)
{
    //Required: https://docs.microsoft.com/en-us/windows/win32/api/wtsprotocol/nf-wtsprotocol-iwrdsprotocollistener-startlisten
    //Called when listener is enabled/termsrv is started
    this->pListenerCallback = pCallback;
    // Note: From documentation: The protocol must add a reference
    //       to this object and release it when StopListen is called.
    pCallback->AddRef();

    // For validation purposes only
    //When we start the listener, create a thread that waits until the command for a sample connection
    //This is defined in TestProtocolAPI.cpp
    this->threadHandle = CreateThread(NULL, 0, &WaitToConnect, this->pListenerCallback, 0, NULL);
    if (this->threadHandle == NULL)
    {
        return ERROR;
    }

    return S_OK;
}

HRESULT __stdcall CWRdsProtocolListener::StopListen(void)
{
    //Required: https://docs.microsoft.com/en-us/windows/win32/api/wtsprotocol/nf-wtsprotocol-iwrdsprotocollistener-stoplisten
    //Called when termsrv is being shutdown (such as machine is shutting down) or listener is stopped
    if(this->threadHandle != NULL)
    {
        CloseHandle(this->threadHandle);
        this->threadHandle = NULL;
    }
    if (NULL != this->pListenerCallback)
    {
        this->pListenerCallback->Release();
        this->pListenerCallback = NULL;
    }

    return S_OK;
}
