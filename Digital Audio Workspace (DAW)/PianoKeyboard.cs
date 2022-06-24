using NAudio.Wave;
using System.Collections.Generic;

namespace DAW
{
    internal class PianoKeyboard
    {
        readonly Dictionary<string, string> notes = new();
        Dictionary<string, WaveOutEvent> devices = new();
        HashSet<string> blackKeys = new HashSet<string>();
        HashSet<string> arePlaying = new HashSet<string>();

       public PianoKeyboard()
        {
            notes.TryAdd("Q", "C4"); 
            notes.TryAdd("2", "C4#");
            notes.TryAdd("W", "D4");
            notes.TryAdd("3", "D4#");
            notes.TryAdd("E", "E4");
            notes.TryAdd("R", "F4");
            notes.TryAdd("5", "F4#");
            notes.TryAdd("T","G4");
            notes.TryAdd("6","G4#");
            notes.TryAdd("Y","A4");
            notes.TryAdd("7", "A4#");
            notes.TryAdd("U", "H4");
            notes.TryAdd("Z", "C5"); 
            notes.TryAdd("S", "C5#");
            notes.TryAdd("X", "D5");
            notes.TryAdd("D", "D5#");
            notes.TryAdd("C", "E5");
            notes.TryAdd("V", "F5");
            notes.TryAdd("G", "F5#");
            notes.TryAdd("B","G5");
            notes.TryAdd("H","G5#");
            notes.TryAdd("N","A5");
            notes.TryAdd("J", "A5#");
            notes.TryAdd("M", "H5");


            blackKeys.Add("2");
            blackKeys.Add("3");
            blackKeys.Add("5");
            blackKeys.Add("6");
            blackKeys.Add("7");
            blackKeys.Add("S");
            blackKeys.Add("D");
            blackKeys.Add("G");
            blackKeys.Add("H");
            blackKeys.Add("J");
        }

        public bool CheckNote(string key)
        {
            return this.notes.ContainsKey(key);
        }

        public string GetSound(string key)
        {
            return this.notes[key];
        }


        public void NewDevice(string key)
        {
            this.devices[key] = new();
        }

        public void Init(string key, AudioFileReader source)
        {
            this.devices[key].Init(source);
        }

        public void Play(string key)
        {
            this.devices[key].Play();
        }

        public void Stop(string key)
        {
            this.devices[key].Stop();
            this.devices[key].Dispose();
            this.devices[key] = null;
        }

        public bool IsBlack(string key)
        {
            return this.blackKeys.Contains(key);
        }
        
        public void AddPlaying(string key)
        {
            this.arePlaying.Add(key);
        }

        public void RemovePlaying(string key)
        {
            this.arePlaying.Remove(key);
        }

        public bool isPlaying(string key)
        {
            return this.arePlaying.Contains(key);
        }
    }
}
