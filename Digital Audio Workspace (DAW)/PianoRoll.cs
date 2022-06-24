using System.Collections.Concurrent;
using System.Collections.Generic;
using System.Threading;

namespace DAW
{
    internal class PianoRoll
    {
        Dictionary<int, RollKey> notes = new();
        Dictionary<int, Dictionary<int, double>> graph = new();
        int count = 0;
        double lastWidth = 62.5;
        int bars = 4;


        public PianoRoll()
        {
            for(int i=0; i<88; i++)
                graph.TryAdd(i, new Dictionary<int, double>());
        }
        public void AddNote(int key, RollKey rollKey)
        {
            this.count++;
            try
            {
                this.notes.Add(key, rollKey);
            }
            catch 
            {
                this.count--;
                return;
            }
            this.graph[rollKey.GetCoords().Item2].Add(rollKey.GetCoords().Item1, rollKey.Width);

            
        }

        public void RemoveNote(int key)
        {
            this.count--;
            RollKey temp; 
            try
            {
                temp = this.notes[key];
            }
            catch
            {
                this.count++;
                return;
            }
            this.graph[temp.GetCoords().Item2].Remove(temp.GetCoords().Item1);
            this.notes.Remove(key);
           
            
        }

        public RollKey GetKey(int key)
        {
            return this.notes[key];
        }

        public int Count
        {
            get => this.count;
        }

        public void Move(int n, int x, int y)
        {
            var temp = this.notes[n];
            this.graph[temp.GetCoords().Item2].Remove(temp.GetCoords().Item1);
            this.notes[n].Move(x, y);
            temp = this.notes[n];
            this.graph[temp.GetCoords().Item2].Add(temp.GetCoords().Item1, temp.Width);
        }

        public void SetWidth(int n, double x)
        {
            var temp = this.notes[n];
            this.notes[n].Width = x;
            this.graph[temp.GetCoords().Item2][temp.GetCoords().Item1] = x;
        }

        public double GetWidth(int n)
        {
            return notes[n].Width;
        }

        public void SetLastWidth(double x)
        {
            lastWidth = x;
        }

        public double GetLastWidth()
        {
            return lastWidth;
        }


        public bool CheckNotes(int x, int y)
        {
            foreach (var item in notes.Values)
                if (item.CheckNote(x, y))
                    return true;
            
            return false;
        }

        public double ShouldPlay(int x, int y) // returns info and duration
        {
            
            if (this.graph[y].ContainsKey(x))
                return this.graph[y][x];
            return -1;               
        }

        public int Bars
        {
            get { return this.bars; }
            set { this.bars = value; }
        }

        public double UpdateWidth(int x, int y)
        {
            return this.graph[y][x];
        }

    }

}
