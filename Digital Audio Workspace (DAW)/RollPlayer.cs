
using System.Collections.Generic;
using System.Windows.Media;
using System.Windows;
using System.Windows.Controls;

namespace DAW
{
    public interface IRollPlayer
    {
        void InitNoteNames(Grid grid);
        void SetPlayer(Dictionary<int, string> dict);
        
           
    }
}
