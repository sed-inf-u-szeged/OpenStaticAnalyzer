using System;

namespace Columbus.CSAN.Exceptions
{
    public class UnexpectedEnumValueException : Exception
    {
        public UnexpectedEnumValueException(Enum enumValue) : base($"Unexpected value '{enumValue}' for enum '{enumValue.GetType()}'")
        {
        }
    }
}
