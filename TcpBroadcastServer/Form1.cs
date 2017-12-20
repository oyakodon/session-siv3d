using System;
using System.Windows.Forms;
using System.Collections.Generic;
using System.Linq;

namespace TcpBroadcastServer
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();

            server = new Server();

            server.connectedCount.mChanged += (value) =>
            {
                labConnection.Text = value.ToString();
            };

            server.log.mChanged += (log) =>
            {
                tbLog.Text = log + Environment.NewLine + tbLog.Text;
            };

        }

        private Server server;

        private void btnStart_Click(object sender, EventArgs e)
        {
            btnStart.Enabled = false;
            btnStop.Enabled = true;
            numericUpDown1.Enabled = false;
            checkBox1.Enabled = false;

            tbLog.Text = "";

            server.Start((int)numericUpDown1.Value, !checkBox1.Checked);

        }

        private void btnStop_Click(object sender, EventArgs e)
        {
            btnStart.Enabled = true;
            btnStop.Enabled = false;
            numericUpDown1.Enabled = true;
            checkBox1.Enabled = true;

            labConnection.Text = "-";

            server.Stop();

        }

    }
}
