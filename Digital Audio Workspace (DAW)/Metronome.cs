using System.Media;
using System.Threading;

namespace DAW
{
    internal class Metronome : MenuButton
    {
        SoundPlayer player = new SoundPlayer();
        double bpm;
        int count;
 

        public Metronome(string path)
        {
            this.bpm = 0;
            count = 0;
            this.player.SoundLocation = path+"/Samples/Drums/Metronome.wav";
            this.player.Load();
        }

        public void Play()
        {
            Thread t = new(() =>
            {
                this.player.Play();
            });

            
            t.Start();
        }

        public void Stop()
        {
            this.player.Stop();
        }

        public void SetBpm(double value)
        {
            this.bpm = value;
        }

        public double GetBpm() 
        { 
            return this.bpm; 
        }

        public void IncCount()
        {
            this.count++;
        }

        public int GetCount()
        {
            return this.count;
        }

        public void ResetCount()
        {
            this.count = 0;
        }
    }
}
