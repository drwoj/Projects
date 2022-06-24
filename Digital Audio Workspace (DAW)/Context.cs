using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Controls;

namespace DAW
{
    internal class Context
    {
        private IRollPlayer player;
        private readonly Dictionary<int, string> notes = new();
        Grid grid;
        private int count;
        public Context(IRollPlayer player)
        {
            this.player = player;
        }
        
        public Context()
        { }

        public string GetSound(int key)
        {
            return this.notes[key];
        }

        public void SetPreset(IRollPlayer value)
        {
            this.player = value;
        }

        public void SetGrid(Grid value)
        {
            this.grid = value;
        }

        public void SetInstrument()
        {
            this.player.SetPlayer(notes);
            this.player.InitNoteNames(grid);
            this.count = notes.Count();
        }

        public int Count
        {
            get {return this.count; }
        }
    }
}
