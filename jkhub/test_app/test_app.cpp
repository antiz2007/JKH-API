// test_app.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>


#include "../jkhub/api_public.h"

typedef int (*APICALL)(apiImport_t *apiIn, apiExport_t *apiOut); 

APICALL pGetModuleAPI;

static apiImport_t derp = {0};
static apiExport_t derp2 = {0};

int _tmain(int argc, _TCHAR* argv[])
{
	// just a test app to run the actual API so I don't have to get the game involved
	HMODULE module = GetModuleHandle(argv[1]);
	pGetModuleAPI = (APICALL)GetProcAddress(module, "GetModuleAPI");

	pGetModuleAPI(&derp, &derp2);
	derp2.Connect(8, "something generic");

	return 0;
}

