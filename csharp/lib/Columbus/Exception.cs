using System;
using System.Text;

namespace Columbus {

    /// <summary>
    /// Class for exception handling, with location and error message.
    /// </summary>
#if (LIM_INTERNAL)
    internal
#else
    public
#endif
    class ColumbusException : System.Exception
    {

        private string loc;

        /// <summary>
        /// Creates an ColumbusException object.
        /// </summary>
        /// <param name="location">[in] The place where the error is occured.</param>
        /// <param name="message">[in] Errormessage.</param>
        public ColumbusException(string location, string message)
            : base(message) {
            loc = location;
        }

        /// <summary>
        /// Creates an ColumbusException object.
        /// </summary>
        /// <param name="location">[in] The place where the error is occured.</param>
        /// <param name="message">[in] Errormessage.</param>
        /// <param name="innerException">[in] Additional exception information.</param>
        public ColumbusException(string location, string message, System.Exception innerException)
            : base(message, innerException) {
            loc = location;
        }

        /// <summary>
        /// Returns the location of the error.
        /// </summary>
        /// <returns>Location of error.</returns>
        public string Location {
            get {
                return loc;
            }
        }

        /// <summary>
        /// Returns the class of exception.
        /// </summary>
        /// <returns>Class of exception.</returns>
        public virtual string ClassName {
            get {
                return "Columbus.ColumbusException";
            }
        }

        /// <summary>
        /// Returns string representation of the exception.
        /// </summary>
        /// <returns>String representation of the exception.</returns>
        public override string ToString() {
            return ClassName + " @ " + Location + ": " + Message;
        }

    }

    /// <summary>
    /// Class for handling IO exceptions.
    /// </summary>
#if (LIM_INTERNAL)
    internal
#else
    public
#endif
    class ColumbusIOException : ColumbusException {

        /// <summary>
        /// Creates an ColumbusIOException object.
        /// </summary>
        /// <param name="location">[in] The place where the error is occured.</param>
        /// <param name="message">[in] Errormessage.</param>
        public ColumbusIOException(string location, string message)
            : base(location, message) {
        }

        /// <summary>
        /// Creates an ColumbusIOException object.
        /// </summary>
        /// <param name="location">[in] The place where the error is occured.</param>
        /// <param name="message">[in] Errormessage.</param>
        /// <param name="innerException">[in] Additional exception information.</param>
        public ColumbusIOException(string location, string message, System.Exception innerException)
            : base(location, message, innerException) {
        }

        /// <summary>
        /// Returns the class of exception.
        /// </summary>
        /// <returns>Class of exception.</returns>
        public override string ClassName {
            get {
                return "Columbus.ColumbusIOException";
            }
        }

    }

}

