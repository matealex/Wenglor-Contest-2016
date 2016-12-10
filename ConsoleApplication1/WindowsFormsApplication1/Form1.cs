using System;
using System.Drawing;
using System.Runtime.InteropServices;
using System.Threading;
using System.Windows.Forms;

namespace WenglorGUIApplication
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        [DllImport("ImageOperations.dll", EntryPoint = "readOperationFile")]
        public static extern void readOperationFile();

        [DllImport("ImageOperations.dll", EntryPoint = "processImage")]
        public static extern void processImage(int imageNumber);

        private void button2_Click(object sender, EventArgs e)
        {
            new Thread(() =>
            {
                readOperationFile();

                for (var i = 1; i <= 10; i++)
                {
                    pictureBox1.Image = Image.FromFile(".\\Input Files\\Input-" + i + ".bmp");
                    processImage(i);
                    pictureBox2.Image = Image.FromFile(".\\Output Files\\Output-" + i + ".bmp");
                    Thread.Sleep(3000);
                }

                MessageBox.Show("Done");
            }).Start();
        }
    }
}