// WRdsProtocolLicenseConnection.h : Declaration of the CWRdsProtocolLicenseConnection

#pragma once

#ifndef WRDS_PROTOCOL_LICENSE_CONNECTION_H
#define WRDS_PROTOCOL_LICENSE_CONNECTION_H

#include "resource.h" // main symbols
#include "stdafx.h"

#include "TestProtocol.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

using namespace ATL;


// CWRdsProtocolLicenseConnection

class ATL_NO_VTABLE CWRdsProtocolLicenseConnection :
    public CComObjectRootEx<CComMultiThreadModel>,
    public CComCoClass<CWRdsProtocolLicenseConnection, &CLSID_WRdsProtocolLicenseConnection>,
    public IWRdsProtocolLicenseConnection
{
public:
    CWRdsProtocolLicenseConnection()
    {
    }

DECLARE_REGISTRY_RESOURCEID(109)


BEGIN_COM_MAP(CWRdsProtocolLicenseConnection)
    COM_INTERFACE_ENTRY2(IUnknown, IWRdsProtocolLicenseConnection)
    COM_INTERFACE_ENTRY(IWRdsProtocolLicenseConnection)
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

    // Inherited via IWRdsProtocolLicenseConnection
    virtual HRESULT __stdcall RequestLicensingCapabilities(PWRDS_LICENSE_CAPABILITIES ppLicenseCapabilities, ULONG * pcbLicenseCapabilities) override;

    virtual HRESULT __stdcall SendClientLicense(PBYTE pClientLicense, ULONG cbClientLicense) override;

    virtual HRESULT __stdcall RequestClientLicense(PBYTE Reserve1, ULONG Reserve2, PBYTE ppClientLicense, ULONG * pcbClientLicense) override;

    virtual HRESULT __stdcall ProtocolComplete(ULONG ulComplete) override;

};

OBJECT_ENTRY_AUTO(__uuidof(WRdsProtocolLicenseConnection), CWRdsProtocolLicenseConnection)

#endif // WRDS_PROTOCOL_LICENSE_CONNECTION_H