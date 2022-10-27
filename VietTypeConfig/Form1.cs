using System;
using System.Runtime.InteropServices;
using System.Windows.Forms;

using static VietTypeConfig.VietTypeRegistrar;

namespace VietTypeConfig {
    public partial class Form1 : Form {
        public Form1() {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e) {
            settingsBindingSource.DataSource = Settings.LoadSettings();
            UpdateEnabled();
        }

        private void CloseForm(object sender, EventArgs e) {
            Close();
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e) {
            var settings = settingsBindingSource.DataSource as Settings;
            if (DialogResult == DialogResult.OK && settings != null) {
                try {
                    Settings.SaveSettings(settings);
                } catch (Exception ex) {
                    MessageBox.Show($"Cannot save settings: {ex.Message}", "VietType", MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
            }
        }

        private void btnAbout_Click(object sender, EventArgs e) {
            var message = $"VietType {Version.ProductVersion} ({Version.VcsRevision})\n" +
                "Copyright © 2018 Dinh Ngoc Tu.\n" +
                "VietType is free software, licensed under the GNU General Public License. " +
                "VietType is distributed WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY " +
                "or FITNESS FOR A PARTICULAR PURPOSE.See the included LICENSE file for more details.";
            MessageBox.Show(message, "About VietType", MessageBoxButtons.OK, MessageBoxIcon.Information);
        }

        private void UpdateEnabled() {
            try {
                var activated = VietTypeRegistrar.IsProfileActivated();
                btnEnable.Enabled = activated >= 0;
                btnEnable.Text = (activated == S_OK) ? "&Disable VietType" : "&Enable VietType";
            } catch (Exception ex) {
                btnEnable.Enabled = false;
                MessageBox.Show($"Cannot find VietType library: {ex.Message}", "VietType", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void btnEnable_Click(object sender, EventArgs e) {
            var activated = IsProfileActivated();
            var result = (activated == S_OK) ? DeactivateProfiles() : ActivateProfiles();
            if (result == S_OK) {
                if (activated == S_OK) {
                    MessageBox.Show($"Successfully disabled VietType.", "VietType", MessageBoxButtons.OK, MessageBoxIcon.Information);
                } else {
                    MessageBox.Show($"Successfully enabled VietType. Switch to VietType in the language bar to start using it.", "VietType", MessageBoxButtons.OK, MessageBoxIcon.Information);
                }
            } else {
                var message = Marshal.GetExceptionForHR(result).Message;
                MessageBox.Show($"Cannot configure VietType: {message}", "VietType", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
            UpdateEnabled();
        }
    }
}
