#pragma once

#ifndef TEST_PROTOCOL_API_H
#define TEST_PROTOCOL_API_H

#include <unordered_set>

#include "stdafx.h"
#include "TestProtocol.h"
#include "WRdsProtocolConnection.h"
#include "wtsdefs.h"

using namespace ATL;
using namespace std;

#define MAX_STR_SIZE 256

typedef struct _CONNECTION_CONFIG
{
    WCHAR Domain[MAX_STR_SIZE];
    WCHAR UserName[MAX_STR_SIZE];
    WCHAR Password[MAX_STR_SIZE];
}   CONNECTION_CONFIG, *PCONNECTION_CONFIG;

typedef struct _CONNECTION_OUTPUT
{
    ULONG ulConnectionId;
    WCHAR ActivityId[MAX_STR_SIZE];
}   CONNECTION_OUTPUT, *PCONNECTION_OUTPUT;


DWORD WINAPI WaitToConnect(LPVOID lpParameter);

HRESULT CreateTestConnection(
    IWRdsProtocolListenerCallback* pListenerCallback,
    PCONNECTION_CONFIG pConnectionConfig,
    PCONNECTION_OUTPUT pConnectionOutput
);

#endif // TEST_PROTOCOL_API_H
