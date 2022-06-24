using Microsoft.Win32;
using NAudio.Wave;
using System;
using System.Threading;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Threading;
using System.Windows.Shapes;
using System.Text.RegularExpressions;

namespace DAW
{
    public partial class MainWindow : Window
    {

        double bpm = 0;
        private static string path = System.IO.Path.GetDirectoryName(System.Reflection.Assembly.GetExecutingAssembly().Location);
        DispatcherTimer timer = new();
        Metronome metronome = new(path);
        MenuButton playButton = new();
        WaveOutEvent wo;
        PianoKeyboard pianoKeyboard = new();
        Sequencer sequencer = new Sequencer(path);
        PianoRoll pianoRoll = new();
        Context context = new(new PresetPiano());
        Presets presets = new();
        Brush brushBackground = (SolidColorBrush)(new BrushConverter().ConvertFrom("#272537"));
        Brush brushOrange = (SolidColorBrush)(new BrushConverter().ConvertFrom("#feb662"));
        Brush brushWhite = (SolidColorBrush)(new BrushConverter().ConvertFrom("#ffffff"));
        Brush brushBlack = (SolidColorBrush)(new BrushConverter().ConvertFrom("#000000"));
        Brush brushMenu = (SolidColorBrush)(new BrushConverter().ConvertFrom("#a6596e"));

        public MainWindow()
        {
            InitializeComponent();
            timer.Interval = TimeSpan.FromMilliseconds(6000);
            timer.Tick += timer_Tick;
            context.SetGrid(NotesGrid);
            context.SetInstrument();
            PresetsCombo.ItemsSource = presets.GetPresets();
            PresetsCombo.Text = presets.CurrentPreset;
        }
           

        private void OnlyNumbers(object sender, TextCompositionEventArgs e)
        {
            Regex regex = new Regex("[^0-9]+");
            e.Handled = regex.IsMatch(e.Text);
        }
        private void Play(int n)
        {
           Thread t = new(() =>
            {
                sequencer.Acquire(n);
                string sound = sequencer.Sounds[n];
                sequencer.Release(n);
                AudioFileReader w = new(sound);
                WasapiOut o = new();
                o.Init(w);
                o.Play();
                var time = new AudioFileReader(sound).TotalTime;
                Thread.Sleep(time);
                o.Dispose();
                w.Dispose();
            });

            
            t.Start();
        }
        private void playPiano(string note)
        {
            Thread t = new(() =>
            {
                string sound = pianoKeyboard.GetSound(note);
                AudioFileReader source = new(path + "/Samples/Instruments/Piano/" + sound + ".wav");
                pianoKeyboard.NewDevice(note);
                pianoKeyboard.Init(note, source);
                pianoKeyboard.Play(note);
               
            });

            t.Start();
        }

        private void PlayRoll(int note, double duration)
        {
            Thread t = new(() =>
            {
                string sound = context.GetSound(note);
                AudioFileReader source = new(path + "/Samples/Instruments/"+presets.CurrentPreset+"/" + sound + ".wav");
                WasapiOut o = new();
                o.Init(source);
                o.Play();

                var time = timer.Interval * duration/62.5;
                
                Thread.Sleep(time);
                o.Dispose();
                source.Dispose();
            });


            t.Start();
        }
        private void Metronome_Click(object sender, RoutedEventArgs e)
        {
            
            Button btn = sender as Button;
            metronome.ChangeCanPlay();
            metronome.GetCanPlay();

            if (metronome.GetCanPlay())
            {
                btn.Background = brushOrange;
                if(!playButton.GetCanPlay())
                    timer.Start();                
            }
            else
            {
                btn.Background = brushBackground;
                if(!playButton.GetCanPlay())
                    timer.Stop();
                    metronome.ResetCount();
            }
         

        }
        private void Play_Click(object sender, RoutedEventArgs e)
        {
            Button btn = sender as Button;
            playButton.ChangeCanPlay();
           
            if (playButton.GetCanPlay())
            {
                btn.Background = brushOrange;
                if (!metronome.GetCanPlay())
                    timer.Start();
            }
            else
            {
                btn.Background = brushBackground;
                if (!metronome.GetCanPlay())
                {
                    timer.Stop();
                    metronome.ResetCount(); 
                }        
            }
        }
        private void timer_Tick(object sender, EventArgs e)
        {

            if (metronome.GetCount()%4==0 && metronome.GetCanPlay())
                metronome.Play();

            if (playButton.GetCanPlay())
            {
                for (int i = 0; i < sequencer.Count; i++)
                    if (sequencer.CheckNote(i, metronome.GetCount() % sequencer.Bars))
                        Play(i);

                for (int i = 0; i < context.Count; i++)
                {
                    double duration = pianoRoll.ShouldPlay(metronome.GetCount() % (pianoRoll.Bars*4), i);

                    if (duration!=-1)
                        PlayRoll(i, duration);
                }

            }
            
            metronome.IncCount();
        }
        private void Bpm_changed(object sender, EventArgs e)
        {
            bpm = (double)(15000 / (double)Bpm.Value);

            timer.Interval = TimeSpan.FromMilliseconds(bpm);
            metronome.SetBpm(bpm);
        }

        private void RollBars_changed(object sender, EventArgs e)
        {
            int updated = (int)RollBars.Value;
            int old = pianoRoll.Bars;
            int delta = updated - old;
            pianoRoll.Bars = updated;
            if (delta >= 0)
            {
                PianoRollGrid.Width += delta * 250;
                PianoRollCanva.Width += delta * 250;
                for (int i = 0; i < delta * 4; i++)
                    PianoRollGrid.ColumnDefinitions.Add(new ColumnDefinition());
            }
            else
            {
                PianoRollGrid.Width += delta * 250; //delta is negative so we just add
                PianoRollCanva.Width += delta * 250;
                PianoRollGrid.ColumnDefinitions.RemoveRange(PianoRollGrid.ColumnDefinitions.Count-5, 4);
            }

        }
        private void Drum_checked(object sender, RoutedEventArgs e)
        {
            CheckBox chk = sender as CheckBox;
            Panel panel = chk.Parent as Panel;

            int note = int.Parse(chk.Uid);
            int sample = int.Parse(panel.Uid);

            sequencer.AddNote(sample, note);
        }   
        private void Drum_unchecked(object sender, RoutedEventArgs e)
        {
            CheckBox chk = sender as CheckBox;
            Panel panel = chk.Parent as Panel;
           
            int note = int.Parse(chk.Uid);
            int sample = int.Parse(panel.Uid);

            sequencer.RemoveNote(sample, note);  
        }
        private void AddSample_Click(object sender, RoutedEventArgs e)
        {
            sequencer.AddSample(drumPanel);
        }
        private void DeleteSample_Click(object sender, RoutedEventArgs e)
        {
            sequencer.RemoveSample(drumPanel);
        }
        private void AddBars_Click(object sender, RoutedEventArgs e)
        {
            sequencer.AddBars(drumPanel);
        }
        private void DeleteBars_Click(object sender, RoutedEventArgs e)
        {
            sequencer.RemoveBars(drumPanel);
        }
        private void LoadSample_Click(object sender, RoutedEventArgs e)
        {
            OpenFileDialog ofd = new OpenFileDialog();
            ofd.Filter = "All Media Files|*.wav; *.mp3";
            ofd.DefaultExt = ".wav";

            bool?result = ofd.ShowDialog();

            if (result == true)
            {
                string filePath = ofd.FileName;
                string fileName = System.IO.Path.GetFileNameWithoutExtension(ofd.FileName);
                Button btn = sender as Button;
                btn.Content = fileName;

                int index = int.Parse(btn.Uid);
                sequencer.Acquire(index);
                sequencer.Sounds[index] = filePath;
                sequencer.Release(index);
            }

     
        }
        private void PianoPlay(object sender, RoutedEventArgs e)
        {

            Button btn = sender as Button;
            string note = btn.Name.Remove(0,1);
            if (pianoKeyboard.CheckNote(note))
            {
                string sound = pianoKeyboard.GetSound(note);
                AudioFileReader source = new(path +"/Samples/Instruments/Piano/"+ sound + ".wav");
                wo = new();
                wo.Init(source);               
                wo.Play();
  
            }
        }  
        private void PianoKeyPlay(object sender, KeyEventArgs e)
        {

            string note = e.Key.ToString();
            if (note.Length > 1)
                note = note.Remove(0, 1);

            if (pianoKeyboard.CheckNote(note) && !pianoKeyboard.isPlaying(note))
            {
                pianoKeyboard.AddPlaying(note);
                playPiano(note);
                Button btn = (Button)FindName("_" + note);
                btn.Background = brushOrange;

            }

        }
        private void PianoStop(object sender, RoutedEventArgs e)
        {
            
            wo.Stop();
            wo.Dispose();
            wo = null;
            
        }
        private void PianoKeyStop(object sender, KeyEventArgs e)
        {
            string note = e.Key.ToString();
            if (note.Length > 1)
                note = note.Remove(0, 1);

            if (pianoKeyboard.CheckNote(note))
            {

                pianoKeyboard.Stop(note);
                pianoKeyboard.RemovePlaying(note);
                Button btn = (Button)FindName("_" + note);

                if (pianoKeyboard.IsBlack(note))
                    btn.Background = brushBlack;
                else btn.Background = brushWhite;
            }
        }
        private void AddToRoll(object sender, MouseButtonEventArgs e)
        {

            Point p = Mouse.GetPosition(PianoRollCanva);
            int x = (int)(p.X / 62.5);
            int y = (int)(p.Y / 30);

            if (pianoRoll.CheckNotes(x, y))
            {
                pianoRoll.SetLastWidth(pianoRoll.UpdateWidth(x, y));
                return;
            }

            double width = pianoRoll.GetLastWidth();
           
            var key = new RollKey(x, y, width, pianoRoll.Count);
            key.GetRectangle().MouseMove +=DragRectangle; ;
            key.GetRectangle().MouseRightButtonDown += RemoveRectangle;
            key.GetRectangle().PreviewMouseWheel += ChangeRectangleSize;

            HitTestResult result = VisualTreeHelper.HitTest(PianoRollCanva, p);

            Grid.SetRow(key.GetRectangle(), y);
            Grid.SetColumn(key.GetRectangle(), x);
            Canvas.SetLeft(key.GetRectangle(), x * 62.5);
            Canvas.SetTop(key.GetRectangle(), y * 30);

            PianoRollCanva.Children.Add(key.GetRectangle());
            pianoRoll.AddNote(pianoRoll.Count, key);
        }
        private void ChangeRectangleSize(object sender, MouseWheelEventArgs e)
        {
            
            if (Keyboard.IsKeyDown(Key.LeftCtrl))
            {
                PianoRollScroll.ScrollToVerticalOffset(PianoRollScroll.VerticalOffset);
                Rectangle rect = (Rectangle)sender;
                rect.Width += e.Delta / 12;
                pianoRoll.SetWidth(int.Parse(rect.Uid), rect.Width);
                pianoRoll.SetLastWidth(rect.Width);
            }
        }

        private void DragRectangle(object sender, MouseEventArgs e)
        {
            if (e.MiddleButton == MouseButtonState.Pressed)
            {
                Rectangle rect = (Rectangle)sender;
                DragDrop.DoDragDrop(rect, new DataObject(DataFormats.Serializable, rect), DragDropEffects.Move);
            }
        }       
        private void Canvas_Drop(object sender, DragEventArgs e)
        {
            Rectangle r = (Rectangle)e.Data.GetData(DataFormats.Serializable);
            Point p = e.GetPosition(PianoRollCanva);
            int x = (int)(p.X / 62.5);
            int y = (int)(p.Y / 30);

            if (!pianoRoll.CheckNotes(x, y))
            {
                Grid.SetRow(r, y);
                Grid.SetColumn(r, x);
                Canvas.SetLeft(r, x * 62.5);
                Canvas.SetTop(r, y * 30);
                pianoRoll.Move(int.Parse(r.Uid), x, y);
            }
          
        }
        private void RemoveRectangle(object sender, MouseButtonEventArgs e)
        {
            Rectangle rect = (Rectangle)sender;
            PianoRollCanva.Children.Remove(rect);
            pianoRoll.RemoveNote(int.Parse(rect.Uid));
        }

        private void ChangePreset(object sender, SelectionChangedEventArgs e)
        {
            presets.CurrentPreset = PresetsCombo.SelectedItem.ToString();
            int index = PresetsCombo.SelectedIndex;
            context.SetPreset(presets.PresetsObject[index]);
            context.SetInstrument();
        }
    
    }
}

//  #272537 tlo
//  #feb662 pomaranczowy
//  #f9f871 zolty
//  #a6596e menu
//  #623f5d fioletowy
