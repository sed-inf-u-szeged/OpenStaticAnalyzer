{ 
  'includes' : {
      'osa.gyp'
  },
  'targets': [
    {
      'target_name': 'javascriptAddon',
      'sources': [ 'addon.cc', 'Factory.h', 'Factory.cc',
 'inc/SystemWrapper.h' , 'src/SystemWrapper.cc', 'inc/CommentWrapper.h' , 'src/CommentWrapper.cc', 'inc/ModuleDeclarationWrapper.h' , 'src/ModuleDeclarationWrapper.cc', 'inc/VariableDeclaratorWrapper.h' , 'src/VariableDeclaratorWrapper.cc', 'inc/PropertyWrapper.h' , 'src/PropertyWrapper.cc', 'inc/SpreadElementWrapper.h' , 'src/SpreadElementWrapper.cc', 'inc/SuperWrapper.h' , 'src/SuperWrapper.cc', 'inc/TemplateElementWrapper.h' , 'src/TemplateElementWrapper.cc', 'inc/CatchClauseWrapper.h' , 'src/CatchClauseWrapper.cc', 'inc/FunctionWrapper.h' , 'src/FunctionWrapper.cc', 'inc/SwitchCaseWrapper.h' , 'src/SwitchCaseWrapper.cc', 'inc/ClassBodyWrapper.h' , 'src/ClassBodyWrapper.cc', 'inc/MethodDefinitionWrapper.h' , 'src/MethodDefinitionWrapper.cc', 'inc/ProgramWrapper.h' , 'src/ProgramWrapper.cc', 'inc/IdentifierWrapper.h' , 'src/IdentifierWrapper.cc', 'inc/ExportNamedDeclarationWrapper.h' , 'src/ExportNamedDeclarationWrapper.cc', 'inc/ImportDeclarationWrapper.h' , 'src/ImportDeclarationWrapper.cc', 'inc/ArrayExpressionWrapper.h' , 'src/ArrayExpressionWrapper.cc', 'inc/ArrowFunctionExpressionWrapper.h' , 'src/ArrowFunctionExpressionWrapper.cc', 'inc/AssignmentExpressionWrapper.h' , 'src/AssignmentExpressionWrapper.cc', 'inc/AwaitExpressionWrapper.h' , 'src/AwaitExpressionWrapper.cc', 'inc/BinaryExpressionWrapper.h' , 'src/BinaryExpressionWrapper.cc', 'inc/CallExpressionWrapper.h' , 'src/CallExpressionWrapper.cc', 'inc/ClassExpressionWrapper.h' , 'src/ClassExpressionWrapper.cc', 'inc/ConditionalExpressionWrapper.h' , 'src/ConditionalExpressionWrapper.cc', 'inc/FunctionExpressionWrapper.h' , 'src/FunctionExpressionWrapper.cc', 'inc/LogicalExpressionWrapper.h' , 'src/LogicalExpressionWrapper.cc', 'inc/MemberExpressionWrapper.h' , 'src/MemberExpressionWrapper.cc', 'inc/MetaPropertyWrapper.h' , 'src/MetaPropertyWrapper.cc', 'inc/NewExpressionWrapper.h' , 'src/NewExpressionWrapper.cc', 'inc/ObjectExpressionWrapper.h' , 'src/ObjectExpressionWrapper.cc', 'inc/SequenceExpressionWrapper.h' , 'src/SequenceExpressionWrapper.cc', 'inc/TaggedTemplateExpressionWrapper.h' , 'src/TaggedTemplateExpressionWrapper.cc', 'inc/TemplateLiteralWrapper.h' , 'src/TemplateLiteralWrapper.cc', 'inc/ThisExpressionWrapper.h' , 'src/ThisExpressionWrapper.cc', 'inc/UnaryExpressionWrapper.h' , 'src/UnaryExpressionWrapper.cc', 'inc/UpdateExpressionWrapper.h' , 'src/UpdateExpressionWrapper.cc', 'inc/YieldExpressionWrapper.h' , 'src/YieldExpressionWrapper.cc', 'inc/BooleanLiteralWrapper.h' , 'src/BooleanLiteralWrapper.cc', 'inc/NullLiteralWrapper.h' , 'src/NullLiteralWrapper.cc', 'inc/NumberLiteralWrapper.h' , 'src/NumberLiteralWrapper.cc', 'inc/RegExpLiteralWrapper.h' , 'src/RegExpLiteralWrapper.cc', 'inc/StringLiteralWrapper.h' , 'src/StringLiteralWrapper.cc', 'inc/AssignmentPropertyWrapper.h' , 'src/AssignmentPropertyWrapper.cc', 'inc/ArrayPatternWrapper.h' , 'src/ArrayPatternWrapper.cc', 'inc/AssignmentPatternWrapper.h' , 'src/AssignmentPatternWrapper.cc', 'inc/ObjectPatternWrapper.h' , 'src/ObjectPatternWrapper.cc', 'inc/RestElementWrapper.h' , 'src/RestElementWrapper.cc', 'inc/BlockStatementWrapper.h' , 'src/BlockStatementWrapper.cc', 'inc/BreakStatementWrapper.h' , 'src/BreakStatementWrapper.cc', 'inc/ContinueStatementWrapper.h' , 'src/ContinueStatementWrapper.cc', 'inc/DebuggerStatementWrapper.h' , 'src/DebuggerStatementWrapper.cc', 'inc/EmptyStatementWrapper.h' , 'src/EmptyStatementWrapper.cc', 'inc/ExpressionStatementWrapper.h' , 'src/ExpressionStatementWrapper.cc', 'inc/ForInStatementWrapper.h' , 'src/ForInStatementWrapper.cc', 'inc/ForStatementWrapper.h' , 'src/ForStatementWrapper.cc', 'inc/IfStatementWrapper.h' , 'src/IfStatementWrapper.cc', 'inc/LabeledStatementWrapper.h' , 'src/LabeledStatementWrapper.cc', 'inc/ReturnStatementWrapper.h' , 'src/ReturnStatementWrapper.cc', 'inc/SwitchStatementWrapper.h' , 'src/SwitchStatementWrapper.cc', 'inc/ThrowStatementWrapper.h' , 'src/ThrowStatementWrapper.cc', 'inc/TryStatementWrapper.h' , 'src/TryStatementWrapper.cc', 'inc/WhileStatementWrapper.h' , 'src/WhileStatementWrapper.cc', 'inc/WithStatementWrapper.h' , 'src/WithStatementWrapper.cc', 'inc/ClassDeclarationWrapper.h' , 'src/ClassDeclarationWrapper.cc', 'inc/ExportSpecifierWrapper.h' , 'src/ExportSpecifierWrapper.cc', 'inc/FunctionDeclarationWrapper.h' , 'src/FunctionDeclarationWrapper.cc', 'inc/ExportAllDeclarationWrapper.h' , 'src/ExportAllDeclarationWrapper.cc', 'inc/ExportDefaultDeclarationWrapper.h' , 'src/ExportDefaultDeclarationWrapper.cc', 'inc/VariableDeclarationWrapper.h' , 'src/VariableDeclarationWrapper.cc', 'inc/ForOfStatementWrapper.h' , 'src/ForOfStatementWrapper.cc', 'inc/DoWhileStatementWrapper.h' , 'src/DoWhileStatementWrapper.cc', 'inc/ImportDefaultSpecifierWrapper.h' , 'src/ImportDefaultSpecifierWrapper.cc', 'inc/ImportNamespaceSpecifierWrapper.h' , 'src/ImportNamespaceSpecifierWrapper.cc', 'inc/ImportSpecifierWrapper.h' , 'src/ImportSpecifierWrapper.cc',  ],  
          'include_dirs': [                                       
             '../../',                                            
             '<(source_dir)/inc',                                 
             '<(source_dir)/lib',                                 
             '<(bin_dir)/3rdparty/install/include',                 
      ],                                                                                                             
      'conditions': [                                          
         ['OS=="linux"', {
               "cflags_cc!": [ "-fno-rtti" ],
               "cflags_cc": [ "-fPIC", "-isystem <(bin_dir)/3rdparty/install/include" ],
         }],
         ['OS=="win"',                                    
           {                                                
             'msvs_settings': {                             
               'VCCLCompilerTool': {                        
                 'DisableSpecificWarnings': [ '4530', '4482', '4577', 4541 ],
               },                                           
               'VCLinkerTool': {                            
                 'IgnoreDefaultLibraryNames': ['MSVCRT']    
               }                                            
             },                                             
             'configurations': {                            
               'Release': {                                 
                 'defines': [                               
                    'NDEBUG',                          
                  ],                                    
               },                                      
               'Debug': {                              
                 'defines': [                          
                   'DEBUG',                            
                  ],                                    
               },                                      
             },                                        
           },                                          
         ],                                            
      ],                                                    
      'link_settings': {                                                                                                 
        'conditions': [                                                                                                  
          ['OS=="win"', {                                                                                              
              'library_dirs': [                                                                                          
                '<(bin_dir)/lib/<(configuration)',
                '<(bin_dir)/3rdparty/install/lib'
              ],                                                                                                         
              'libraries': [                                                                                             
                '-lstrtable.lib', '-lcommon.lib', '-lcsi.lib', '-ljavascript.lib', '-lio.lib', '-lboost_iostreams.lib', '-lz.lib'
              ]                                                                                                          
          }],                                                                                                            
          ['OS=="linux"', {                                                                                            
          'libraries': [                                                                                                 
            '-L<(bin_dir)/lib','-L<(bin_dir)/3rdparty/install/lib','-ljavascript','-lstrtable','-lcommon','-lcsi','-lio','-lboost_iostreams','-lz'
          ]}],                                                                                                           
        ],                                                                                                               
      }                                                                                                                  
    },                                                                                                               
    {                                                         
      'target_name': 'action_after_build',                    
      'type': 'none',                                         
      'dependencies': ['javascriptAddon'],                            
      'copies': [                                             
        {                                                     
          'files': [ '<(PRODUCT_DIR)/javascriptAddon.node' ],         
          'destination': '<(bin_dir)/bin'
        }                                                     
      ]                                                       
    }                                                         
  ]                                                                                                                  
}
