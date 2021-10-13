namespace Columbus.CSAN.Utils
{
    public class WatchBag
    {
        /// <summary>
        /// Main stopwatch, runs during the whole analysis.
        /// </summary>
        public Stopwatch MainWatch { get; } = new Stopwatch();
        /// <summary>
        /// Stopwatch for roughly measuring time being spent in Roslyn's code. Started before every
        /// major roslyn method call, eg. getting semantic models, and stopped right after the call returned.
        /// </summary>
        public Stopwatch RoslynWatch { get; } = new Stopwatch();
        /// <summary>
        /// Stopwatch for measuring C# language asg building time. CrossEdges are not included however.
        /// </summary>
        public Stopwatch CSSIWatch { get; } = new Stopwatch();
        /// <summary>
        /// Stopwatch for measuring LIM asg building time. C# asg's crossedges are also included, because those
        /// are not taking much time, and are filled from LIM visitors.
        /// </summary>
        public Stopwatch LIMWatch { get; } = new Stopwatch();
    }
}
