using Microsoft.CodeAnalysis.CSharp;

namespace Columbus.CSAN.Metrics.Complexity
{
    /// <summary>
    /// NLE metrics expresses the complexity of the method with the depth of maximum embeddedness of 
    /// branches and cycles to be found in it, where in the if-else-if structure the additional if instruction 
    /// does not enhance the value of the metrics. When calculating metrics, the following instructions are taken 
    /// into account: if, for, while, do-while, switch, conditional statement (?:). The following language elements
    /// do not enhance the value: else, else if (i.e. in the if-else-if structure the use of else-if does not 
    /// enhance further the value of the metrics), case label (label that belongs to switch instruction), 
    /// default label (default label that belongs to switch instruction), try, catch, finally.
    /// </summary>
    sealed class NLE : AbstractNL
    {
        public static int Calculate(CSharpSyntaxNode node)
        {
            MethodVisitor mv = new MethodVisitor(node, true);
            mv.Visit(node);
            return mv.result;
        }
    }
}
