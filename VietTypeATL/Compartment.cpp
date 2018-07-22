// Copyright (c) Dinh Ngoc Tu.
// 
// This file is part of VietType.
// 
// VietType is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// VietType is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with VietType.  If not, see <https://www.gnu.org/licenses/>.

// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (c) Microsoft Corporation. All rights reserved

#include "Compartment.h"

VietType::Compartment::Compartment() noexcept {
}

VietType::Compartment::~Compartment() {
}

ITfCompartment* VietType::Compartment::GetCompartment() {
    return _compartment;
}

HRESULT VietType::Compartment::GetCompartmentSource(ITfSource** ppSource) {
    return _compartment->QueryInterface(ppSource);
}

HRESULT VietType::Compartment::GetValue(long* val) {
    HRESULT hr;

    VARIANT v;
    hr = _compartment->GetValue(&v);
    if (hr == S_FALSE) {
        return S_FALSE;
    } else if (hr == S_OK) {
        if (v.vt != VT_I4) {
            return E_FAIL;
        }
        *val = v.lVal;
    }

    return S_OK;
}

HRESULT VietType::Compartment::SetValue(long val) {
    HRESULT hr;

    VARIANT v;
    VariantInit(&v);
    v.vt = VT_I4;
    v.lVal = val;
    hr = _compartment->SetValue(_clientid, &v);
    HRESULT_CHECK_RETURN(hr, L"%s", L"_compartment->SetValue failed");

    return S_OK;
}

HRESULT VietType::Compartment::Initialize(IUnknown* punk, TfClientId clientid, const GUID& guidCompartment, bool global) {
    HRESULT hr;

    CComPtr<ITfCompartmentMgr> compartmentMgr;

    if (global) {
        CComPtr<ITfThreadMgr> threadMgr;
        hr = punk->QueryInterface(&threadMgr);
        HRESULT_CHECK_RETURN(hr, L"%s", L"punk->QueryInterface failed");

        hr = threadMgr->GetGlobalCompartment(&compartmentMgr);
        HRESULT_CHECK_RETURN(hr, L"%s", L"threadMgr->GetGlobalCompartment failed");
    } else {
        hr = punk->QueryInterface(&compartmentMgr);
        HRESULT_CHECK_RETURN(hr, L"%s", L"punk->QueryInterface failed");
    }

    hr = compartmentMgr->GetCompartment(guidCompartment, &_compartment);
    HRESULT_CHECK_RETURN(hr, L"%s", L"compartmentMgr->GetCompartment failed");

    _clientid = clientid;

    return S_OK;
}

HRESULT VietType::Compartment::Uninitialize() {
    _compartment.Release();

    return S_OK;
}
