namespace Columbus.CSAN.Metrics.Complexity
{
    internal struct HalsteadMetrics
    {
        public HalsteadMetrics(uint distinctOperands, uint distinctOperators, uint totalOperands, uint totalOperators)
        {
            TotalOperands = totalOperands;
            TotalOperators = totalOperators;
            DistinctOperands = distinctOperands;
            DistinctOperators = distinctOperators;
        }

        public uint DistinctOperands { get; private set; }

        public uint DistinctOperators { get; private set; }

        public uint TotalOperands { get; private set; }

        public uint TotalOperators { get; private set; }

    }
}
