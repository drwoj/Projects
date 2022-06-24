using System.Windows.Shapes;
using System.Windows.Media;
using System.Windows.Input;
using System.Windows.Controls;

namespace DAW
{
    internal class RollKey
    {
        double width = 62.5;
        Rectangle rectangle;
        (int, int) coords;
           
        Brush brushMenu = (SolidColorBrush)(new BrushConverter().ConvertFrom("#a6596e"));

        public RollKey(int x, int y, double width, int count)
        {
            this.rectangle = new Rectangle()
            {
                Width = width,
                Height = 30,
                Fill = brushMenu,
                Uid = count.ToString()
            };

            this.width = width;
            this.coords.Item1 = x;
            this.coords.Item2 = y;
        }


        public Rectangle GetRectangle()
        {
            return this.rectangle;
        }

        public double Width
        {
            get { return this.width; }
            set { this.width = value; }
        }

        public void Move(int x, int y)
        {
            this.coords.Item1 = x;
            this.coords.Item2 = y;
        }

        public bool CheckNote(int x, int y)
        {
            if (x == coords.Item1 && y == coords.Item2)
                return true;
            else return false;
        }

        public (int, int) GetCoords()
        {
            return coords;
        }

    }



}
