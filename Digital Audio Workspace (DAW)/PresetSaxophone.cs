using System.Collections.Generic;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;

namespace DAW
{
    internal class PresetSaxophone : IRollPlayer // A2 - F5
    {
        private Brush brushWhite = (SolidColorBrush)(new BrushConverter().ConvertFrom("#ffffff"));
        public void InitNoteNames(Grid grid)
        {
            grid.Children.Clear();

            int n = 4;
            int row = 0;

            List<TextBlock> temp = new(35);
            temp.Add(new TextBlock() { Text = "F5", TextAlignment = TextAlignment.Center, Foreground = brushWhite, VerticalAlignment = VerticalAlignment.Center });

            temp.Add(new TextBlock() { Text = "E5", TextAlignment = TextAlignment.Center, Foreground = brushWhite, VerticalAlignment = VerticalAlignment.Center });

            temp.Add(new TextBlock() { Text = "D5#", TextAlignment = TextAlignment.Center, Foreground = brushWhite, VerticalAlignment = VerticalAlignment.Center });

            temp.Add(new TextBlock() { Text = "D5", TextAlignment = TextAlignment.Center, Foreground = brushWhite, VerticalAlignment = VerticalAlignment.Center });

            temp.Add(new TextBlock() { Text = "C#5", TextAlignment = TextAlignment.Center, Foreground = brushWhite, VerticalAlignment = VerticalAlignment.Center });

            temp.Add(new TextBlock() { Text = "C5", TextAlignment = TextAlignment.Center, Foreground = brushWhite, VerticalAlignment = VerticalAlignment.Center });




            for (int i = 0; i < 2; i++)
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



            temp.Add(new TextBlock() { Text = "H2", TextAlignment = TextAlignment.Center, Foreground = brushWhite, VerticalAlignment = VerticalAlignment.Center });

            temp.Add(new TextBlock() { Text = "A2#", TextAlignment = TextAlignment.Center, Foreground = brushWhite, VerticalAlignment = VerticalAlignment.Center });

            temp.Add(new TextBlock() { Text = "A2", TextAlignment = TextAlignment.Center, Foreground = brushWhite, VerticalAlignment = VerticalAlignment.Center });

            temp.Add(new TextBlock() { Text = "G2#", TextAlignment = TextAlignment.Center, Foreground = brushWhite, VerticalAlignment = VerticalAlignment.Center });

            temp.Add(new TextBlock() { Text = "G2", TextAlignment = TextAlignment.Center, Foreground = brushWhite, VerticalAlignment = VerticalAlignment.Center });

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

            int n = 4;
            for (int i = 0; i < 2; i++)
            {
                notes.TryAdd((i * 12) + 6, "H" + n);
                notes.TryAdd((i * 12) + 7, "A" + n + "#");
                notes.TryAdd((i * 12) + 8, "A" + n);
                notes.TryAdd((i * 12) + 9, "G" + n + "#");
                notes.TryAdd((i * 12) + 10, "G" + n);
                notes.TryAdd((i * 12) + 11, "F" + n + "#");
                notes.TryAdd((i * 12) + 12, "F" + n);
                notes.TryAdd((i * 12) + 13, "E" + n);
                notes.TryAdd((i * 12) + 14, "D" + n + "#");
                notes.TryAdd((i * 12) + 15, "D" + n);
                notes.TryAdd((i * 12) + 16, "C" + n + "#");
                notes.TryAdd((i * 12) + 17, "C" + n);
                n--;
            }
            notes.TryAdd(0, "F5");
            notes.TryAdd(1, "E5");
            notes.TryAdd(2, "D5#");
            notes.TryAdd(3, "D5");
            notes.TryAdd(4, "C5#");
            notes.TryAdd(5, "C5");
            notes.TryAdd(30, "H2");
            notes.TryAdd(31, "A2" + "#");
            notes.TryAdd(32, "A2");
            notes.TryAdd(33, "G2#");
            notes.TryAdd(34, "G2");
        }
    }
}
