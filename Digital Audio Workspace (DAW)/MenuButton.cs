namespace DAW
{
    internal class MenuButton
    {

        protected bool canPlay;

        public MenuButton()
        {
            this.canPlay = false;
        }

        public void SetCanPlay(bool value)
        {
            this.canPlay = value;
        }

        public bool GetCanPlay()
        {
            return this.canPlay;
        }

        public void ChangeCanPlay()
        {
            this.canPlay = !this.canPlay;
        }
    }
}
