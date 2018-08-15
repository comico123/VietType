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
#include "CompositionManager.h"
#include "EngineController.h"
#include "EditSessions.h"

HRESULT VietType::IsContextEmpty(_In_ ITfContext* context, _In_ TfClientId clientid, _Out_ bool* isempty) {
    HRESULT hr;

    CComPtr<Compartment> compEmpty;
    hr = CreateInstance2(&compEmpty);
    HRESULT_CHECK_RETURN(hr, L"%s", L"CreateInstance2(&compEmpty) failed");

    hr = compEmpty->Initialize(context, clientid, GUID_COMPARTMENT_EMPTYCONTEXT);
    HRESULT_CHECK_RETURN(hr, L"%s", L"compEmpty->Initialize failed");

    long contextEmpty;
    hr = compEmpty->GetValue(&contextEmpty);
    HRESULT_CHECK_RETURN(hr, L"%s", L"compDisabled->GetValue failed");

    *isempty = hr == S_OK && contextEmpty;
    return hr;
}

HRESULT VietType::OnNewContext(_In_ ITfContext *context, _In_ VietType::CompositionManager* compositionManager, _In_ VietType::EngineController* controller) {
    HRESULT hr;

    bool isempty;
    hr = VietType::IsContextEmpty(context, compositionManager->GetClientId(), &isempty);
    HRESULT_CHECK_RETURN(hr, L"%s", L"VietType::IsContextEmpty failed");
    if (isempty) {
        controller->SetBlocked(VietType::EngineController::BlockedKind::Blocked);
        return S_OK;
    }

    TF_STATUS st;
    hr = context->GetStatus(&st);
    if (SUCCEEDED(hr)) {
        DBG_DPRINT(
            L"d=%c%c%c s=%c%c%c",
            (st.dwDynamicFlags & TF_SD_LOADING) ? L'L' : L'_',
            (st.dwDynamicFlags & TF_SD_READONLY) ? L'R' : L'_',
            (st.dwDynamicFlags & TS_SD_UIINTEGRATIONENABLE) ? L'U' : L'_',
            (st.dwStaticFlags & TF_SS_DISJOINTSEL) ? L'D' : L'_',
            (st.dwStaticFlags & TF_SS_REGIONS) ? L'R' : L'_',
            (st.dwStaticFlags & TF_SS_TRANSITORY) ? L'T' : L'_');
    } else DBG_HRESULT_CHECK(hr, L"%s", L"context->GetStatus failed");

    if (!controller->IsEditBlockedPending()) {
        controller->SetEditBlockedPending();
        hr = VietType::CompositionManager::RequestEditSession(
            VietType::EditSessions::EditBlocked,
            compositionManager,
            context,
            controller);
        controller->ResetEditBlockedPending();
        if (FAILED(hr)) {
            DBG_HRESULT_CHECK(hr, L"%s", L"CompositionManager::RequestEditSession failed");
            controller->SetBlocked(VietType::EngineController::BlockedKind::Free);
        }
    }

    return S_OK;
}
