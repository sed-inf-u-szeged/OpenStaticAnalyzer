using System;

namespace Columbus
{
    /// <summary>
    /// Wrapper around System.Diagnostics.Stopwatch to provide disabling.
    /// If the Enabled property is set to false, Start, Stop and stop will return immediatelly,
    /// Restart will just reset the clock
    /// </summary>
    public class Stopwatch
    {
        private System.Diagnostics.Stopwatch InnerWatch = new System.Diagnostics.Stopwatch();

        /// <summary>
        /// Gets the frequency of the timer as the number of ticks per second. This field
        /// is read-only.
        /// </summary>
        public static readonly long Frequency = System.Diagnostics.Stopwatch.Frequency;

        /// <summary>
        /// Indicates whether the timer is based on a high-resolution performance counter.
        /// This field is read-only.
        /// </summary>
        public static readonly bool IsHighResolution = System.Diagnostics.Stopwatch.IsHighResolution;

        /// <summary>
        /// Gets the current number of ticks in the timer mechanism.
        /// </summary>
        /// <returns>A long integer representing the tick counter value of the underlying timer mechanism.</returns>
        public static long GetTimestamp() { return System.Diagnostics.Stopwatch.GetTimestamp(); }

        /// <summary>
        /// Initializes a new Columbus.CSAN.Util.Stopwatch instance, sets the elapsed time property to zero,
        /// enabled to true, and starts measuring elapsed time.
        /// </summary>
        /// <returns>A Columbus.CSAN.Util.Stopwatch that has just begun measuring elapsed time.</returns>
        public static Stopwatch StartNew()
        {
            var watch = new Stopwatch();
            watch.Start();
            return watch;
        }

        /// <summary>
        /// Indicates that the stopwatch should actually stop, start or restart.
        /// If set to false, those methods will do nothing, restart will reset only.
        /// </summary>
        public bool Enabled { get; set; }

        /// <summary>
        /// Creates a new insance and sets the Enabled property to the parameter given.
        /// The watch will not start measuring time yet.
        /// </summary>
        /// <param name="enabled"></param>
        public Stopwatch(bool enabled)
        {
            Enabled = enabled;
        }

        /// <summary>
        /// Creates a new instance with Enabled set to true - can be used instead of System.Diagnostics.Stopwatch.
        /// The watch will not start measuring time yet.
        /// </summary>
        public Stopwatch() : this(true) { }

        /// <summary>
        /// Gets the total elapsed time measured by the current instance.
        /// </summary>
        public TimeSpan Elapsed { get { return InnerWatch.Elapsed; } }
        
        /// <summary>
        /// Gets the total elapsed time measured by the current instance, in milliseconds.
        /// </summary>
        public long ElapsedMilliseconds { get { return InnerWatch.ElapsedMilliseconds; } }

        /// <summary>
        /// Gets the total elapsed time measured by the current instance, in seconds.
        /// </summary>
        public float ElapsedSeconds { get { return ElapsedMilliseconds / 1000f; } }
        
        /// <summary>
        /// Gets the total elapsed time measured by the current instance, in timer ticks.
        /// </summary>
        public long ElapsedTicks { get { return InnerWatch.ElapsedTicks; } }
       
        /// <summary>
        /// Gets a value indicating whether the System.Diagnostics.Stopwatch timer is running.
        /// </summary>
        public bool IsRunning { get { return InnerWatch.IsRunning; } }

        /// <summary>
        /// Stops time interval measurement and resets the elapsed time to zero.
        /// </summary>
        public void Reset()
        {
            InnerWatch.Reset();
        }

        /// <summary>
        /// Stops time interval measurement, resets the elapsed time to zero, and starts
        /// measuring elapsed time if Enabled is set to true.
        /// </summary>
        public void Restart()
        {
            if (Enabled)
                InnerWatch.Restart();
            else
                InnerWatch.Reset();
        }

        /// <summary>
        /// Starts, or resumes, measuring elapsed time for an interval if Enabled is set
        /// to true.
        /// </summary>
        public void Start()
        {
            if (Enabled)
                InnerWatch.Start();
        }

        /// <summary>
        /// Stops measuring elapsed time for an interval if Enabled is set to true.
        /// </summary>
        public void Stop()
        {
            if (Enabled)
                InnerWatch.Stop();
        }

        /// <summary>
        /// Returns a string that represents the current object.
        /// </summary>
        /// <returns></returns>
        public override string ToString()
        {
            return InnerWatch.ToString();
        }
    }
}
