using Microsoft.CodeAnalysis.CSharp;

namespace Columbus.CSAN.Metrics.Complexity
{
    delegate void Callback();

    /// <summary>
    /// Method: NL metrics expresses the complexity of the method with the depth of 
    /// maximum embeddedness of branches and cycles to be found in it. When calculating 
    /// metrics the following instructions are taken into account: if, for, while, do-while, switch, conditional statement (?:). 
    /// The following language elements do not enhance the value in themselves; 
    /// however, if additional embeddednesses can be found in their block, they are considered: else, case label 
    /// (label that belongs to the switch instruction), default label (default label that belongs to the switch instruction), try, catch, finally [3].
    /// </summary>
    sealed class NL : AbstractNL
    {

        public static int Calculate(CSharpSyntaxNode node)
        {
            MethodVisitor mv = new MethodVisitor(node, false);
            mv.Visit(node);
            return mv.result;
        }

        
    }
}
