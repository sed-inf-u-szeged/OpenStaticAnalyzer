using System;
using System.Text;

namespace Columbus.Lim.Asg {

    /// <summary>
    /// General (base) class for all lim.Exception.
    /// </summary>
#if (LIM_INTERNAL)
    internal
#else
    public
#endif
    class LimException : Columbus.ColumbusException {

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="location">[in] The location of the exception (the "place" where the exception was thrown).</param>
        /// <param name="message">[in] The cause of the exception.</param>
        public LimException(string location, string message)
            : base(location, message) {
        }

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="location">[in] The location of the exception (the "place" where the exception was thrown).</param>
        /// <param name="message">[in] The cause of the exception.</param>
        /// <param name="innerException">[in] Additional exception information.</param>
        public LimException(string location, string message, System.Exception innerException)
            : base(location, message, innerException) {
        }

        /// <summary>
        /// Gives back the name of the lim.LimException class.
        /// </summary>
        /// <returns>Returns the name of the lim.LimException class.</returns>
        public override string ClassName {
            get {
                return "lim.LimException";
            }
        }

    }

    /// <summary>
    /// Thrown by ListIterator if the iterator is invalid.
    /// </summary>
#if (LIM_INTERNAL)
    internal
#else
    public
#endif
    class LimInvalidIteratorException : LimException {

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="location">[in] The location of the exception (the "place" where the exception was thrown).</param>
        /// <param name="message">[in] The cause of the exception.</param>
        public LimInvalidIteratorException(string location, string message)
            : base(location, message) {
        }

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="location">[in] The location of the exception (the "place" where the exception was thrown).</param>
        /// <param name="message">[in] The cause of the exception.</param>
        /// <param name="innerException">[in] Additional exception information.</param>
        public LimInvalidIteratorException(string location, string message, System.Exception innerException)
            : base(location, message, innerException) {
        }

        /// <summary>
        /// Gives back the name of the Lim.LimInvalidIteratorException class.
        /// </summary>
        /// <returns>Returns the name of the Lim.LimInvalidIteratorException class.</returns>
        public override string ClassName {
            get {
                return "lim.LimInvalidIteratorException";
            }
        }

    }

    /// <summary>
    /// Thrown by ListIterator if illegal operation is executed on an iterator.
    /// </summary>
#if (LIM_INTERNAL)
    internal
#else
    public
#endif
    class LimIllegalStateException : LimException {

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="location">[in] The location of the exception (the "place" where the exception was thrown).</param>
        /// <param name="message">[in] The cause of the exception.</param>
        public LimIllegalStateException(string location, string message)
            : base(location, message) {
        }

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="location">[in] The location of the exception (the "place" where the exception was thrown).</param>
        /// <param name="message">[in] The cause of the exception.</param>
        /// <param name="innerException">[in] Additional exception information.</param>
        public LimIllegalStateException(string location, string message, System.Exception innerException)
            : base(location, message, innerException) {
        }

        /// <summary>
        /// Gives back the name of the Lim.IllegalStateException class.
        /// </summary>
        /// <returns>Returns the name of the Lim.IllegalStateException class.</returns>
        public override string ClassName {
            get {
                return "lim.LimIllegalStateException";
            }
        }

    }

    /// <summary>
    /// Thrown by ListIterator if next()(or pervious() ) is called and there is no next (previous) element.
    /// </summary>
#if (LIM_INTERNAL)
    internal
#else
    public
#endif
    class LimNoSuchElementException : LimException {

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="location">[in] The location of the exception (the "place" where the exception was thrown).</param>
        /// <param name="message">[in] The cause of the exception.</param>
        public LimNoSuchElementException(string location, string message)
            : base(location, message) {
        }

        /// <summary>
        /// Constructor.
        /// </summary>
        /// <param name="location">[in] The location of the exception (the "place" where the exception was thrown).</param>
        /// <param name="message">[in] The cause of the exception.</param>
        /// <param name="innerException">[in] Additional exception information.</param>
        public LimNoSuchElementException(string location, string message, System.Exception innerException)
            : base(location, message, innerException) {
        }

        /// <summary>
        /// Gives back the name of the lim.LimNoSuchElementException class.
        /// </summary>
        /// <returns>Returns the name of the lim.LimNoSuchElementException class.</returns>
        public override string ClassName {
            get {
                return "lim.LimNoSuchElementException";
            }
        }

    }

}
