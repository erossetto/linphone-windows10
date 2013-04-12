﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Navigation;
using Microsoft.Phone.Controls;
using Microsoft.Phone.Shell;
using System.Threading.Tasks;
using Windows.Storage;
using System.IO;
using System.Text;
using Linphone.Resources;
using Linphone.Model;

namespace Linphone.Views
{
    public partial class Console : BasePage
    {
        public Console()
        {
            InitializeComponent();
            BuildLocalizedApplicationBar();
            Browser.Navigate(new Uri("/Views/logs.html", UriKind.RelativeOrAbsolute));
        }

        private async void Browser_LoadCompleted(object sender, NavigationEventArgs e)
        {
            string logs = await ReadLogs();
            FormatAndDisplayLogs(logs);
        }

        private void FormatAndDisplayLogs(string logs)
        {
            logs = logs.Replace("\r\n", "\n");
            string[] lines = logs.Split('\n');
            bool insertNewLine = false;
            foreach (string line in lines)
            {
                if (line.Length == 0)
                {
                    insertNewLine = false;
                    Browser.InvokeScript("append_nl");
                }
                else
                {
                    if (insertNewLine == true)
                    {
                        Browser.InvokeScript("append_nl");
                    }
                    Browser.InvokeScript("append_text", line);
                    insertNewLine = true;
                }
            }
        }

        private async Task<string> ReadLogs()
        {
            ApplicationSettingsManager appSettings = new ApplicationSettingsManager();
            appSettings.Load();

            byte[] data;
            StorageFolder folder = ApplicationData.Current.LocalFolder;
            StorageFile file = await folder.GetFileAsync(appSettings.LogOption);

            using (Stream s = await file.OpenStreamForReadAsync())
            {
                data = new byte[s.Length];
                await s.ReadAsync(data, 0, (int)s.Length);
            }

            return Encoding.UTF8.GetString(data, 0, data.Length);
        }

        private async void refresh_Click_1(object sender, EventArgs e)
        {
            Browser.InvokeScript("clean");
            string logs = await ReadLogs();
            FormatAndDisplayLogs(logs);
        }

        private void BuildLocalizedApplicationBar()
        {
            ApplicationBar = new ApplicationBar();

            ApplicationBarIconButton appBarRefresh = new ApplicationBarIconButton(new Uri("/Assets/AppBar/refresh.png", UriKind.Relative));
            appBarRefresh.Text = AppResources.Refresh;
            ApplicationBar.Buttons.Add(appBarRefresh);
            appBarRefresh.Click += refresh_Click_1;
        }
    }
}