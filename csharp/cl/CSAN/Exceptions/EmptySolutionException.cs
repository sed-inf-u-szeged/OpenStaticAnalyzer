using System;

namespace Columbus.CSAN.Exceptions
{
    public class EmptySolutionException : Exception
    {
        public EmptySolutionException(string message) : base(message)
        {
        }
    }
}
