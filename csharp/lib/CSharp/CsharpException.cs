using System;
using System.Text;

namespace Columbus.Csharp.Asg {

    /// <summary>
    /// General (base) class for all csharp.Exception.
    /// </summary>
#if (CSHARP_INTERNAL)
    internal
#else
    public
#endif
    class CsharpException : Columbus.ColumbusException {

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="location">[in] The location of the exception (the "place" where the exception was thrown).</param>
        /// <param name="message">[in] The cause of the exception.</param>
        public CsharpException(string location, string message)
            : base(location, message) {
        }

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="location">[in] The location of the exception (the "place" where the exception was thrown).</param>
        /// <param name="message">[in] The cause of the exception.</param>
        /// <param name="innerException">[in] Additional exception information.</param>
        public CsharpException(string location, string message, System.Exception innerException)
            : base(location, message, innerException) {
        }

        /// <summary>
        /// Gives back the name of the csharp.CsharpException class.
        /// </summary>
        /// <returns>Returns the name of the csharp.CsharpException class.</returns>
        public override string ClassName {
            get {
                return "csharp.CsharpException";
            }
        }

    }

    /// <summary>
    /// Thrown by ListIterator if the iterator is invalid.
    /// </summary>
#if (CSHARP_INTERNAL)
    internal
#else
    public
#endif
    class CsharpInvalidIteratorException : CsharpException {

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="location">[in] The location of the exception (the "place" where the exception was thrown).</param>
        /// <param name="message">[in] The cause of the exception.</param>
        public CsharpInvalidIteratorException(string location, string message)
            : base(location, message) {
        }

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="location">[in] The location of the exception (the "place" where the exception was thrown).</param>
        /// <param name="message">[in] The cause of the exception.</param>
        /// <param name="innerException">[in] Additional exception information.</param>
        public CsharpInvalidIteratorException(string location, string message, System.Exception innerException)
            : base(location, message, innerException) {
        }

        /// <summary>
        /// Gives back the name of the Csharp.CsharpInvalidIteratorException class.
        /// </summary>
        /// <returns>Returns the name of the Csharp.CsharpInvalidIteratorException class.</returns>
        public override string ClassName {
            get {
                return "csharp.CsharpInvalidIteratorException";
            }
        }

    }

    /// <summary>
    /// Thrown by ListIterator if illegal operation is executed on an iterator.
    /// </summary>
#if (CSHARP_INTERNAL)
    internal
#else
    public
#endif
    class CsharpIllegalStateException : CsharpException {

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="location">[in] The location of the exception (the "place" where the exception was thrown).</param>
        /// <param name="message">[in] The cause of the exception.</param>
        public CsharpIllegalStateException(string location, string message)
            : base(location, message) {
        }

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="location">[in] The location of the exception (the "place" where the exception was thrown).</param>
        /// <param name="message">[in] The cause of the exception.</param>
        /// <param name="innerException">[in] Additional exception information.</param>
        public CsharpIllegalStateException(string location, string message, System.Exception innerException)
            : base(location, message, innerException) {
        }

        /// <summary>
        /// Gives back the name of the Csharp.IllegalStateException class.
        /// </summary>
        /// <returns>Returns the name of the Csharp.IllegalStateException class.</returns>
        public override string ClassName {
            get {
                return "csharp.CsharpIllegalStateException";
            }
        }

    }

    /// <summary>
    /// Thrown by ListIterator if next()(or pervious() ) is called and there is no next (previous) element.
    /// </summary>
#if (CSHARP_INTERNAL)
    internal
#else
    public
#endif
    class CsharpNoSuchElementException : CsharpException {

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="location">[in] The location of the exception (the "place" where the exception was thrown).</param>
        /// <param name="message">[in] The cause of the exception.</param>
        public CsharpNoSuchElementException(string location, string message)
            : base(location, message) {
        }

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="location">[in] The location of the exception (the "place" where the exception was thrown).</param>
        /// <param name="message">[in] The cause of the exception.</param>
        /// <param name="innerException">[in] Additional exception information.</param>
        public CsharpNoSuchElementException(string location, string message, System.Exception innerException)
            : base(location, message, innerException) {
        }

        /// <summary>
        /// Gives back the name of the csharp.CsharpNoSuchElementException class.
        /// </summary>
        /// <returns>Returns the name of the csharp.CsharpNoSuchElementException class.</returns>
        public override string ClassName {
            get {
                return "csharp.CsharpNoSuchElementException";
            }
        }

    }

}
