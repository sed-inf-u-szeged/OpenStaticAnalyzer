namespace Columbus.CSAN.Exceptions
{
    class MsBuildException : System.Exception
    {
        public MsBuildException() : base() { }

        public MsBuildException(string message) : base(message) { }
    }
}
