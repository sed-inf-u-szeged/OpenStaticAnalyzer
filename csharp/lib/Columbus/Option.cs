namespace Columbus
{
    public delegate bool CallBack(Option o, string[] args);
    public delegate bool DefaultCallBack(Option o);
    public delegate void DelegateOption(string p);

    public struct Option
    {
        /// <summary>
        /// Internal option (not displayed!).
        /// </summary>
        public bool Internal { get; set; }

        /// <summary>
        /// Name of the option, eg. -input
        /// </summary>
        public string Name { get; set; }

        /// <summary>
        /// The number of parameters the option takes.
        /// </summary>
        public int NumberOfParameters { get; set; }

        /// <summary>
        /// The parameter's name (for example: filename in -input:filename)
        /// </summary>
        public string ParameterName { get; set; }

        /// <summary>
        /// The number of the needed option. If 0 is not needed, if the number is equal other option needed number, then just one of them is needed (optional)
        /// </summary>
        public int Needed { get; set; }

        /// <summary>
        /// Type of the option.
        /// </summary>
        public ArgumentOptions Type { get; set; }

        /// <summary>
        /// Callback to process the option.
        /// </summary>
        public CallBack Process { get; set; }
        /// <summary>
        /// Process to be called if the option needs paramater but not set (using the default parameter value). 
        /// </summary>
        public DefaultCallBack DefaultProcess { get; set; }

        /// <summary>
        /// Description of the option.
        /// </summary>
        public string Description { get; set; }

        public override string ToString()
        {
            return Name;
        }
    }
}
