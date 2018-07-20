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

#include "Utilities.h"
#include "Compartment.h"

HRESULT VietType::IsContextEmpty(ITfContext * context, TfClientId clientid, bool * isempty) {
    HRESULT hr;

    SmartComObjPtr<Compartment> compEmpty;
    hr = compEmpty.CreateInstance();
    HRESULT_CHECK_RETURN(hr, L"%s", L"compEmpty.CreateInstance failed");

    hr = compEmpty->Initialize(context, clientid, GUID_COMPARTMENT_EMPTYCONTEXT);
    HRESULT_CHECK_RETURN(hr, L"%s", L"compEmpty->Initialize failed");

    long contextEmpty;
    hr = compEmpty->GetValue(&contextEmpty);
    HRESULT_CHECK_RETURN(hr, L"%s", L"compDisabled->GetValue failed");

    *isempty = hr == S_OK && contextEmpty;
    return hr;
}
