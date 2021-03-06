// WRdsProtocolLicenseConnection.cpp : Implementation of CWRdsProtocolLicenseConnection
//https://docs.microsoft.com/en-us/windows/win32/api/wtsprotocol/nn-wtsprotocol-iwrdsprotocollicenseconnection
//Please implement this correctly, this is required for Windows licensing!
//TODO: Provide sample implementation

#include "WRdsProtocolLicenseConnection.h"

// CWRdsProtocolLicenseConnection
HRESULT __stdcall CWRdsProtocolLicenseConnection::QueryInterface(REFIID riid, void ** ppvObject) noexcept
{
    HRESULT hResult = E_NOINTERFACE;

    if (!ppvObject)
    {
        hResult = E_POINTER;
    }
    else
    {
        if ((riid == __uuidof(IWRdsProtocolLicenseConnection)) ||
            (riid == IID_IUnknown))
        {
            hResult = S_OK;
            this->AddRef(); // The caller is responsible for release.
            *ppvObject = this;
        }
    }
    return  hResult;
}

HRESULT __stdcall CWRdsProtocolLicenseConnection::RequestLicensingCapabilities(PWRDS_LICENSE_CAPABILITIES ppLicenseCapabilities, ULONG * pcbLicenseCapabilities)
{
    //Required: https://docs.microsoft.com/en-us/windows/win32/api/wtsprotocol/nf-wtsprotocol-iwrdsprotocollicenseconnection-requestclientlicense
    return S_OK;
}

HRESULT __stdcall CWRdsProtocolLicenseConnection::SendClientLicense(PBYTE pClientLicense, ULONG cbClientLicense)
{
    //Required: https://docs.microsoft.com/en-us/windows/win32/api/wtsprotocol/nf-wtsprotocol-iwrdsprotocollicenseconnection-sendclientlicense
    return S_OK;
}

HRESULT __stdcall CWRdsProtocolLicenseConnection::RequestClientLicense(PBYTE Reserve1, ULONG Reserve2, PBYTE ppClientLicense, ULONG * pcbClientLicense)
{
    //Required: https://docs.microsoft.com/en-us/windows/win32/api/wtsprotocol/nf-wtsprotocol-iwrdsprotocollicenseconnection-requestclientlicense
    return S_OK;
}

HRESULT __stdcall CWRdsProtocolLicenseConnection::ProtocolComplete(ULONG ulComplete)
{
    //Required: https://docs.microsoft.com/en-us/windows/win32/api/wtsprotocol/nf-wtsprotocol-iwrdsprotocollicenseconnection-protocolcomplete
    return S_OK;
}
