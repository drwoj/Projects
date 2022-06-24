using System.Collections.Generic;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;

namespace DAW
{
    internal class PresetPiano : IRollPlayer
    {
        private Brush brushWhite = (SolidColorBrush)(new BrushConverter().ConvertFrom("#ffffff"));
        public void InitNoteNames(Grid grid)
        {
            grid.Children.Clear();
            int n = 7;
            int row = 0;

            List<TextBlock> temp = new(88);
            temp.Add(new TextBlock() { Text = "C8", TextAlignment = TextAlignment.Center, Foreground = brushWhite, VerticalAlignment = VerticalAlignment.Center });
            for (int i = 0; i < 7; i++)
            {
                temp.Add(new TextBlock() { Text = "H" + n, TextAlignment = TextAlignment.Center, Foreground = brushWhite, VerticalAlignment = VerticalAlignment.Center });
                temp.Add(new TextBlock() { Text = "A" + n + "#", TextAlignment = TextAlignment.Center, Foreground = brushWhite, VerticalAlignment = VerticalAlignment.Center });
                temp.Add(new TextBlock() { Text = "A" + n, TextAlignment = TextAlignment.Center, Foreground = brushWhite, VerticalAlignment = VerticalAlignment.Center });
                temp.Add(new TextBlock() { Text = "G" + n + "#", TextAlignment = TextAlignment.Center, Foreground = brushWhite, VerticalAlignment = VerticalAlignment.Center });
                temp.Add(new TextBlock() { Text = "G" + n, TextAlignment = TextAlignment.Center, Foreground = brushWhite, VerticalAlignment = VerticalAlignment.Center });
                temp.Add(new TextBlock() { Text = "F" + n + "#", TextAlignment = TextAlignment.Center, Foreground = brushWhite, VerticalAlignment = VerticalAlignment.Center });
                temp.Add(new TextBlock() { Text = "F" + n, TextAlignment = TextAlignment.Center, Foreground = brushWhite, VerticalAlignment = VerticalAlignment.Center });
                temp.Add(new TextBlock() { Text = "E" + n, TextAlignment = TextAlignment.Center, Foreground = brushWhite, VerticalAlignment = VerticalAlignment.Center });
                temp.Add(new TextBlock() { Text = "D" + n + "#", TextAlignment = TextAlignment.Center, Foreground = brushWhite, VerticalAlignment = VerticalAlignment.Center });
                temp.Add(new TextBlock() { Text = "D" + n, TextAlignment = TextAlignment.Center, Foreground = brushWhite, VerticalAlignment = VerticalAlignment.Center });
                temp.Add(new TextBlock() { Text = "C" + n + "#", TextAlignment = TextAlignment.Center, Foreground = brushWhite, VerticalAlignment = VerticalAlignment.Center });
                temp.Add(new TextBlock() { Text = "C" + n, TextAlignment = TextAlignment.Center, Foreground = brushWhite, VerticalAlignment = VerticalAlignment.Center });

                n--;
            }
            temp.Add(new TextBlock() { Text = "H0", TextAlignment = TextAlignment.Center, Foreground = brushWhite, VerticalAlignment = VerticalAlignment.Center });
            temp.Add(new TextBlock() { Text = "A0#", TextAlignment = TextAlignment.Center, Foreground = brushWhite, VerticalAlignment = VerticalAlignment.Center });
            temp.Add(new TextBlock() { Text = "A0", TextAlignment = TextAlignment.Center, Foreground = brushWhite, VerticalAlignment = VerticalAlignment.Center });

            foreach (var item in temp)
            {
                grid.Children.Add(item);
                Grid.SetRow(item, row);
                Grid.SetColumn(item, 0);
                row++;

            }

        }

        public void SetPlayer(Dictionary<int, string> notes)
        {
            notes.Clear();
            int n = 7;
            for (int i = 0; i < 7; i++)
            {
                notes.TryAdd((i * 12) + 1, "H" + n);
                notes.TryAdd((i * 12) + 2, "A" + n + "#");
                notes.TryAdd((i * 12) + 3, "A" + n);
                notes.TryAdd((i * 12) + 4, "G" + n + "#");
                notes.TryAdd((i * 12) + 5, "G" + n);
                notes.TryAdd((i * 12) + 6, "F" + n + "#");
                notes.TryAdd((i * 12) + 7, "F" + n);
                notes.TryAdd((i * 12) + 8, "E" + n);
                notes.TryAdd((i * 12) + 9, "D" + n + "#");
                notes.TryAdd((i * 12) + 10, "D" + n);
                notes.TryAdd((i * 12) + 11, "C" + n + "#");
                notes.TryAdd((i * 12) + 12, "C" + n);
                n--;
            }
            notes.TryAdd(0, "C8");
            notes.TryAdd(85, "H0");
            notes.TryAdd(86, "A0" + "#");
            notes.TryAdd(87, "A0");
        }
    }
}
