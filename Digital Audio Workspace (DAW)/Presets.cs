using System.IO;
using System.Collections.Generic;

namespace DAW
{
    internal class Presets
    {

        private List<string> presets = new();
        private string currentPreset;
        private List<IRollPlayer> presetsObject = new();
        public Presets()
        {
            currentPreset = "piano";
            this.Init();
        }
        public List<string> GetPresets()
        {
            return this.presets;
        }

        public void AddPreset(string value)
        {
            this.presets.Add(value);
        }

        public string CurrentPreset
        {
            get { return this.currentPreset; }
            set { this.currentPreset = value; }
        }

        private void Init()
        {
            string path = Directory.GetCurrentDirectory() + "/Samples/Instruments/";
            string[] dirs = Directory.GetDirectories(path);

            foreach (var item in dirs)
            {
                string name = Path.GetFileName(item);
                this.presets.Add(name);
            }

            presetsObject.Add(new PresetChoir());
            presetsObject.Add(new PresetFlute());
            presetsObject.Add(new PresetOrgans());
            presetsObject.Add(new PresetPiano());
            presetsObject.Add(new PresetSaxophone());
            

        }

        public List<IRollPlayer> PresetsObject
        {
            get { return presetsObject; }
        }

    }
}
