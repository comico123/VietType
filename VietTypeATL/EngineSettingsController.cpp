// SPDX-FileCopyrightText: Copyright (c) 2018 Dinh Ngoc Tu
// SPDX-License-Identifier: GPL-3.0-only

#include "EngineSettingsController.h"
#include "EngineController.h"

namespace VietType {

static constexpr TF_PRESERVEDKEY PK_Toggle = {VK_OEM_3, TF_MOD_ALT}; // Alt-`

_Check_return_ HRESULT EngineSettingsController::Initialize(
    _In_ EngineController* ec, _In_ ITfThreadMgr* threadMgr, _In_ TfClientId clientid) {
    HRESULT hr;

    _ec = ec;

    hr = CreateInitialize(
        &_default_enabled,
        HKEY_CURRENT_USER,
        Globals::ConfigKeyName.c_str(),
        L"default_enabled",
        KEY_QUERY_VALUE,
        threadMgr,
        clientid);
    HRESULT_CHECK_RETURN(hr, L"%s", L"CreateInitialize(_default_enabled) failed");

    hr = CreateInitialize(
        &_backconvert_on_backspace,
        HKEY_CURRENT_USER,
        Globals::ConfigKeyName.c_str(),
        L"backconvert_on_backspace",
        KEY_QUERY_VALUE,
        threadMgr,
        clientid);
    HRESULT_CHECK_RETURN(hr, L"%s", L"CreateInitialize(_backconvert_on_backspace) failed");

    hr = CreateInitialize(
        &_pk_toggle,
        HKEY_CURRENT_USER,
        Globals::ConfigKeyName.c_str(),
        L"pk_toggle",
        KEY_QUERY_VALUE,
        threadMgr,
        clientid);
    HRESULT_CHECK_RETURN(hr, L"%s", L"CreateInitialize(_pk_toggle) failed");

    hr = CreateInitialize(
        &_show_composing_attr,
        HKEY_CURRENT_USER,
        Globals::ConfigKeyName.c_str(),
        L"show_composing_attr",
        KEY_QUERY_VALUE,
        threadMgr,
        clientid);
    HRESULT_CHECK_RETURN(hr, L"%s", L"CreateInitialize(_show_composing_attr) failed");

    hr = CreateInitialize(
        &_tc_oa_uy_tone1,
        HKEY_CURRENT_USER,
        Globals::ConfigKeyName.c_str(),
        L"oa_uy_tone1",
        KEY_QUERY_VALUE,
        threadMgr,
        clientid);
    HRESULT_CHECK_RETURN(hr, L"%s", L"CreateInitialize(_tc_oa_uy_tone1) failed");

    hr = CreateInitialize(
        &_tc_accept_dd,
        HKEY_CURRENT_USER,
        Globals::ConfigKeyName.c_str(),
        L"accept_dd",
        KEY_QUERY_VALUE,
        threadMgr,
        clientid);
    HRESULT_CHECK_RETURN(hr, L"%s", L"CreateInitialize(_tc_accept_dd) failed");

    hr = CreateInitialize(
        &_tc_backspace_invalid,
        HKEY_CURRENT_USER,
        Globals::ConfigKeyName.c_str(),
        L"backspace_invalid",
        KEY_QUERY_VALUE,
        threadMgr,
        clientid);
    HRESULT_CHECK_RETURN(hr, L"%s", L"CreateInitialize(_tc_backspace_invalid) failed");

    hr = CreateInitialize(
        &_tc_optimize_multilang,
        HKEY_CURRENT_USER,
        Globals::ConfigKeyName.c_str(),
        L"optimize_multilang",
        KEY_QUERY_VALUE,
        threadMgr,
        clientid);
    HRESULT_CHECK_RETURN(hr, L"%s", L"CreateInitialize(_tc_optimize_multilang) failed");

    hr = CreateInitialize(
        &_tc_autocorrect,
        HKEY_CURRENT_USER,
        Globals::ConfigKeyName.c_str(),
        L"autocorrect",
        KEY_QUERY_VALUE,
        threadMgr,
        clientid);
    HRESULT_CHECK_RETURN(hr, L"%s", L"CreateInitialize(_tc_optimize_multilang) failed");

    return S_OK;
}

HRESULT EngineSettingsController::Uninitialize() {
    HRESULT hr;

    hr = _tc_autocorrect->Uninitialize();
    HRESULT_CHECK_RETURN(hr, L"%s", L"_tc_autocorrect->Uninitialize failed");
    _tc_autocorrect.Release();

    hr = _tc_optimize_multilang->Uninitialize();
    HRESULT_CHECK_RETURN(hr, L"%s", L"_tc_optimize_multilang->Uninitialize failed");
    _tc_optimize_multilang.Release();

    hr = _tc_backspace_invalid->Uninitialize();
    HRESULT_CHECK_RETURN(hr, L"%s", L"_tc_backspace_invalid->Uninitialize failed");
    _tc_backspace_invalid.Release();

    hr = _tc_accept_dd->Uninitialize();
    HRESULT_CHECK_RETURN(hr, L"%s", L"_tc_accept_dd->Uninitialize failed");
    _tc_accept_dd.Release();

    hr = _tc_oa_uy_tone1->Uninitialize();
    HRESULT_CHECK_RETURN(hr, L"%s", L"_tc_oa_uy_tone1->Uninitialize failed");
    _tc_oa_uy_tone1.Release();

    hr = _show_composing_attr->Uninitialize();
    HRESULT_CHECK_RETURN(hr, L"%s", L"_show_composing_attr->Uninitialize failed");
    _show_composing_attr.Release();

    hr = _pk_toggle->Uninitialize();
    HRESULT_CHECK_RETURN(hr, L"%s", L"_pk_toggle->Uninitialize failed");
    _pk_toggle.Release();

    hr = _backconvert_on_backspace->Uninitialize();
    HRESULT_CHECK_RETURN(hr, L"%s", L"_backconvert_on_backspace->Uninitialize failed");
    _backconvert_on_backspace.Release();

    hr = _default_enabled->Uninitialize();
    HRESULT_CHECK_RETURN(hr, L"%s", L"_default_enabled->Uninitialize failed");
    _default_enabled.Release();

    return S_OK;
}

HRESULT EngineSettingsController::LoadTelexSettings(Telex::TelexConfig& cfg) {
    HRESULT hr;

    DWORD oa_uy_tone1 = true;
    hr = _tc_oa_uy_tone1->GetValueOrDefault(&oa_uy_tone1, _ec->GetEngine().GetConfig().oa_uy_tone1);
    HRESULT_CHECK_RETURN(hr, L"%s", L"_tc_oa_uy_tone1->GetValueOrDefault failed");
    cfg.oa_uy_tone1 = static_cast<bool>(oa_uy_tone1);

    DWORD accept_dd = true;
    hr = _tc_accept_dd->GetValueOrDefault(&accept_dd, _ec->GetEngine().GetConfig().accept_separate_dd);
    HRESULT_CHECK_RETURN(hr, L"%s", L"_tc_accept_dd->GetValueOrDefault failed");
    cfg.accept_separate_dd = static_cast<bool>(accept_dd);

    DWORD backspace_invalid = true;
    hr = _tc_backspace_invalid->GetValueOrDefault(
        &backspace_invalid, _ec->GetEngine().GetConfig().backspaced_word_stays_invalid);
    HRESULT_CHECK_RETURN(hr, L"%s", L"_tc_backspace_invalid->GetValueOrDefault failed");
    cfg.backspaced_word_stays_invalid = static_cast<bool>(backspace_invalid);

    DWORD optimize_multilang = 1;
    hr = _tc_optimize_multilang->GetValueOrDefault(
        &optimize_multilang, static_cast<DWORD>(_ec->GetEngine().GetConfig().optimize_multilang));
    HRESULT_CHECK_RETURN(hr, L"%s", L"_tc_optimize_multilang->GetValueOrDefault failed");
    cfg.optimize_multilang = optimize_multilang;

    DWORD autocorrect = true;
    hr = _tc_autocorrect->GetValueOrDefault(&autocorrect, static_cast<DWORD>(_ec->GetEngine().GetConfig().autocorrect));
    HRESULT_CHECK_RETURN(hr, L"%s", L"_tc_autocorrect->GetValueOrDefault failed");
    cfg.autocorrect = autocorrect;

    return S_OK;
}

void EngineSettingsController::IsDefaultEnabled(_Out_ DWORD* pde) const {
    std::ignore = _default_enabled->GetValueOrDefault(pde, 0);
}

void EngineSettingsController::IsBackconvertOnBackspace(_Out_ DWORD* pde) const {
    std::ignore = _backconvert_on_backspace->GetValueOrDefault(pde, 0);
}

void EngineSettingsController::GetPreservedKeyToggle(_Out_ TF_PRESERVEDKEY* pde) const {
    ULONGLONG val;
    HRESULT hr = _pk_toggle->GetValue(&val);
    if (SUCCEEDED(val)) {
        *pde = TF_PRESERVEDKEY{static_cast<UINT>(val & UINT_MAX), static_cast<UINT>((val >> 32) & UINT_MAX)};
    } else {
        *pde = PK_Toggle;
    }
}

void EngineSettingsController::IsShowingComposingAttr(_Out_ DWORD* pde) const {
    std::ignore = _show_composing_attr->GetValueOrDefault(pde, 1);
}

} // namespace VietType
