// SPDX-License-Identifier: GPL-3.0-only

using Microsoft.Win32;
using System;
using System.ComponentModel;

namespace VietTypeConfig {
    internal class Settings : INotifyPropertyChanged {
        private const string Subkey = "Software\\VietType";
        private static readonly Guid GUID_SystemConfigCompartment = Guid.Parse("{B2FBD2E7-922F-4996-BE77-21085B91A8F0}");
        private static readonly Guid GUID_TelexConfigCompartment = Guid.Parse("{57335895-0C34-40BA-83F7-72E90A39C222}");
        private static readonly Guid CLSID_TF_ThreadMgr = Guid.Parse("{529a9e6b-6587-4f23-ab9e-9c7d683e3c50}");

        bool default_enabled = false;
        public bool DefaultEnabled {
            get {
                return default_enabled;
            }
            set {
                if (default_enabled != value) {
                    default_enabled = value;
                    OnPropertyChanged(nameof(DefaultEnabled));
                }
            }
        }

        bool oa_uy_tone1 = true;
        public bool OaUy {
            get {
                return oa_uy_tone1;
            }
            set {
                if (oa_uy_tone1 != value) {
                    oa_uy_tone1 = value;
                    OnPropertyChanged(nameof(OaUy));
                }
            }
        }

        bool accept_dd = true;
        public bool AcceptDd {
            get {
                return accept_dd;
            }
            set {
                if (accept_dd != value) {
                    accept_dd = value;
                    OnPropertyChanged(nameof(AcceptDd));
                }
            }
        }

        bool backspace_invalid = true;
        public bool BackspaceInvalid {
            get {
                return backspace_invalid;
            }
            set {
                if (backspace_invalid != value) {
                    backspace_invalid = value;
                    OnPropertyChanged(nameof(BackspaceInvalid));
                }
            }
        }

        bool backconvert_on_backspace = false;
        public bool BackconvertOnBackspace {
            get {
                return backconvert_on_backspace;
            }
            set {
                if (backconvert_on_backspace != value) {
                    backconvert_on_backspace = value;
                    OnPropertyChanged(nameof(BackconvertOnBackspace));
                }
            }
        }


        public event PropertyChangedEventHandler PropertyChanged;
        private void OnPropertyChanged(string propName) {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propName));
        }

        private static bool? ToBool(object v) {
            if (v is int) {
                return (int)v != 0;
            } else {
                return null;
            }
        }

        public static Settings LoadSettings() {
            using (var regKey = Registry.CurrentUser.CreateSubKey(Subkey)) {
                var setting = new Settings();
                setting.DefaultEnabled = ToBool(regKey.GetValue(nameof(default_enabled))) ?? setting.DefaultEnabled;
                setting.OaUy = ToBool(regKey.GetValue(nameof(oa_uy_tone1))) ?? setting.OaUy;
                setting.AcceptDd = ToBool(regKey.GetValue(nameof(accept_dd))) ?? setting.AcceptDd;
                setting.BackspaceInvalid = ToBool(regKey.GetValue(nameof(backspace_invalid))) ?? setting.BackspaceInvalid;
                setting.BackconvertOnBackspace = ToBool(regKey.GetValue(nameof(backconvert_on_backspace))) ?? setting.BackconvertOnBackspace;
                return setting;
            }
        }

        public static void SaveSettings(Settings settings) {
            using (var regKey = Registry.CurrentUser.CreateSubKey(Subkey)) {
                regKey.SetValue(nameof(default_enabled), settings.DefaultEnabled ? 1 : 0);
                regKey.SetValue(nameof(oa_uy_tone1), settings.OaUy ? 1 : 0);
                regKey.SetValue(nameof(accept_dd), settings.AcceptDd ? 1 : 0);
                regKey.SetValue(nameof(backspace_invalid), settings.BackspaceInvalid ? 1 : 0);
                regKey.SetValue(nameof(backconvert_on_backspace), settings.BackconvertOnBackspace ? 1 : 0);

                var threadMgr = Activator.CreateInstance(Type.GetTypeFromCLSID(CLSID_TF_ThreadMgr, true)) as ITfThreadMgr;
                if (threadMgr.Activate(out uint tid) >= 0) {
                    try {
                        if (threadMgr.GetGlobalCompartment(out ITfCompartmentMgr globalMgr) >= 0 &&
                            globalMgr.GetCompartment(GUID_SystemConfigCompartment, out ITfCompartment globalCompartment) >= 0) {
                            if (globalCompartment.GetValue(out object oldGlobal) >= 0) {
                                globalCompartment.SetValue(tid, (oldGlobal as int? ?? 0) + 1);
                            }
                        }
                        if (threadMgr.GetGlobalCompartment(out ITfCompartmentMgr telexMgr) >= 0 &&
                            telexMgr.GetCompartment(GUID_TelexConfigCompartment, out ITfCompartment telexCompartment) >= 0) {
                            if (telexCompartment.GetValue(out object oldTelex) >= 0) {
                                telexCompartment.SetValue(tid, (oldTelex as int? ?? 0) + 1);
                            }
                        }
                    } finally {
                        threadMgr.Deactivate();
                    }
                }
            }
        }
    }
}
