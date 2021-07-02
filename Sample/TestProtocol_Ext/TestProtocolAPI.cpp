#include "TestProtocolAPI.h"



DWORD WINAPI WaitToConnect(LPVOID lpParameter)
{
    IWRdsProtocolListenerCallback* pListenerCallback;

    pListenerCallback = (IWRdsProtocolListenerCallback*)lpParameter;
    CONNECTION_CONFIG newConnectionConfig;
    //These need to be changed to real values for your system!
    swprintf_s(newConnectionConfig.UserName, MAX_STR_SIZE, L"testuser");
    swprintf_s(newConnectionConfig.Password, MAX_STR_SIZE, L"DontUseThis1");
    swprintf_s(newConnectionConfig.Domain, MAX_STR_SIZE, L"");

    CONNECTION_OUTPUT newConnectionOutput;
    //Wait for the presence of a file to simulate a remote connection
    //For real protocols this would usually happen when a TCP/UDP socket connection is recieved
    bool retval = PathFileExistsW(L"C:\\TestProtocol\\createconnection.txt");
    while(!retval)
    {
        Sleep(5000);
        retval = PathFileExistsW(L"C:\\TestProtocol\\createconnection.txt");
    }

    CreateTestConnection(pListenerCallback, &newConnectionConfig, &newConnectionOutput);

    return TRUE;
}

HRESULT CreateTestConnection(
    IWRdsProtocolListenerCallback* pListenerCallback,
    PCONNECTION_CONFIG pConnectionConfig,
    PCONNECTION_OUTPUT pConnectionOutput
)
{
    HRESULT hr;
    ULONG ulConnectionId;
    WRDS_CONNECTION_SETTINGS WRdsConnectionSettings;
    IWRdsProtocolConnectionCallback* localConnectionCallback = NULL;

    ZeroMemory(&WRdsConnectionSettings, sizeof(WRdsConnectionSettings));

    CComObject<CWRdsProtocolConnection>* pConnection = NULL;
    hr = CComObject<CWRdsProtocolConnection>::CreateInstance(&pConnection);
    if (FAILED(hr))
    {
        return E_FAIL;
    }
    if (NULL == pConnection)
    {
        return E_POINTER;
    }

    // Set credentials
    pConnection->SetCredentials(pConnectionConfig->Domain, pConnectionConfig->UserName, pConnectionConfig->Password);

    // Connections will fail if these aren't set
    WRdsConnectionSettings.WRdsConnectionSettingLevel = WRDS_CONNECTION_SETTING_LEVEL_1;
    WRdsConnectionSettings.WRdsConnectionSetting.WRdsConnectionSettings1.WRdsListenerSettings.WRdsListenerSettingLevel = WRDS_LISTENER_SETTING_LEVEL_1;
    WRdsConnectionSettings.WRdsConnectionSetting.WRdsConnectionSettings1.WRdsListenerSettings.WRdsListenerSetting.WRdsListenerSettings1.pSecurityDescriptor = NULL;
    // Inform termsrv that there is a new connection
    hr = pListenerCallback->OnConnected(pConnection, &WRdsConnectionSettings, &localConnectionCallback);
    if (FAILED(hr))
    {
        return E_FAIL;
    }

    hr = localConnectionCallback->GetConnectionId(&ulConnectionId);
    if (FAILED(hr))
    {
        return E_FAIL;
    }
    pConnectionOutput->ulConnectionId = ulConnectionId;
    pConnection->SetConnectionCallback(localConnectionCallback);

    hr = localConnectionCallback->OnReady();
    if (FAILED(hr))
    {
        return E_FAIL;
    }

    return S_OK;
}

