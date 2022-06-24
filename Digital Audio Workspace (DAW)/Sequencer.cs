using Microsoft.Win32;
using System;
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.Threading;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;

namespace DAW
{
    internal class Sequencer
    {
        int count;
        int bars;
        string path;
        ConcurrentDictionary<int, ConcurrentDictionary<int, byte>> notes = new();
        Dictionary<int, string> sounds = new();
        Dictionary<int, Mutex> mutexes = new();   

        public Sequencer(string p)
        {
            this.count = 2;
            this.bars = 8;
            this.notes.TryAdd(0, new ConcurrentDictionary<int, byte>());
            this.notes.TryAdd(1, new ConcurrentDictionary<int, byte>());
            this.path = p;
            sounds.TryAdd(0, p+"/Samples/Drums/Kick.Mp3");
            sounds.TryAdd(1, p +"/Samples/Drums/Snare.Mp3");
            this.mutexes.TryAdd(0, new Mutex());
            this.mutexes.TryAdd(1, new Mutex());
        }

        ~Sequencer()
        {
            foreach (var item in this.mutexes.Values)
            {
                item.Dispose();
            }
        }

        public void AddSample(StackPanel panel) {
            StackPanel sp = new StackPanel
            {
                Orientation = Orientation.Horizontal,
                Uid = Convert.ToString(this.count)
            };
           
            this.notes.TryAdd(this.count, new ConcurrentDictionary<int, byte>());
            this.Sounds.TryAdd(this.count, path+"/Samples/Drums/Default.Mp3");
            this.mutexes.TryAdd(this.count, new Mutex());

            Button btn = new Button
            {
                Margin = new Thickness(10, 0, 30, 0),
                Width = 80,
                Height = 30,
                Content = "Sample",
                Uid = Convert.ToString(this.count)             
            };

            this.count++;
            btn.Click += LoadSample_Click;     
            sp.Children.Add(btn);
            for (int i = 0; i < this.bars; i++)
                sp.Children.Add(new CheckBox {Uid = Convert.ToString(i)} );
            
            panel.Children.Add(sp);

           
        }

        public void RemoveSample(StackPanel panel)
        {
            if (this.count > 0)
            { 
                this.count--;
                this.notes.TryRemove(this.count, out _);
                panel.Children.RemoveAt(this.count);
                this.sounds.Remove(this.count, out _);
                this.mutexes.Remove(this.count, out _);
            }
        }        

        public void AddBars(StackPanel panel)
        {
            if (this.bars < 20)
            {
                

                for (int i = 0; i < this.count; i++)
                {
                    StackPanel child = VisualTreeHelper.GetChild(panel, i) as StackPanel;
                    child.Children.Add(new CheckBox { Uid = Convert.ToString(bars) });
                }
                this.bars++;
            }

        }

        public void RemoveBars(StackPanel panel)
        {

            if (this.bars > 1)
            {
                
                for (int i = 0; i < this.count; i++)
                {
                    StackPanel child = VisualTreeHelper.GetChild(panel, i) as StackPanel;
                    child.Children.RemoveAt(this.bars);
                    this.RemoveNote(i, this.bars);

                }
                this.bars--;

            }
           
        }

        public void AddNote(int key, int value)
        {
            this.notes[key].TryAdd(value, 0);
        }

        public void RemoveNote(int key, int value)
        {
            this.notes[key].TryRemove(value, out _);
        }

        public bool CheckNote(int key, int value)
        {
         return this.notes[key].ContainsKey(value);
        }

        private void LoadSample_Click(object sender, RoutedEventArgs e)
        {
            OpenFileDialog ofd = new OpenFileDialog();
            ofd.Filter = "All Media Files|*.wav; *.mp3";
            ofd.DefaultExt = ".wav";

            bool? result = ofd.ShowDialog();

            if (result == true)
            {
                string filePath = ofd.FileName;
                string fileName = System.IO.Path.GetFileNameWithoutExtension(ofd.FileName);
                Button btn = sender as Button;
                btn.Content = fileName;
                int index = int.Parse(btn.Uid);

                this.mutexes[index].WaitOne();
                this.sounds[index] = filePath;
                this.mutexes[index].ReleaseMutex();
            }
        }

        public void Acquire(int index)
        {
            this.mutexes[index].WaitOne();
        }

        public void Release(int index)
        {
            this.mutexes[index].ReleaseMutex();
        }

        public int Count
        {
            get { return this.count; }
        }

        public int Bars
        {
            get { return this.bars; }
        }

        public Dictionary<int, string> Sounds
        {
            get { return this.sounds; }
        }
    }
}
