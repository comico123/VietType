// SPDX-License-Identifier: GPL-3.0-only

// VietTypeATL.cpp : Implementation of DLL Exports.

#include "stdafx.h"
#include "resource.h"
#include "dllmain.h"

using namespace ATL;

// Used to determine whether the DLL can be unloaded by OLE.
_Use_decl_annotations_ STDAPI DllCanUnloadNow(void) {
    return _AtlModule.DllCanUnloadNow();
}

// Returns a class factory to create an object of the requested type.
_Use_decl_annotations_ STDAPI DllGetClassObject(_In_ REFCLSID rclsid, _In_ REFIID riid, _Outptr_ LPVOID* ppv) {
    return _AtlModule.DllGetClassObject(rclsid, riid, ppv);
}

// DllRegisterServer - Adds entries to the system registry.
STDAPI DllRegisterServer(void) {
    return S_OK;
}

// DllUnregisterServer - Removes entries from the system registry.
STDAPI DllUnregisterServer(void) {
    return S_OK;
}

// DllInstall - Adds/Removes entries to the system registry per user per machine.
STDAPI DllInstall(BOOL bInstall, _In_opt_ LPCWSTR pszCmdLine) {
    return S_OK;
}
