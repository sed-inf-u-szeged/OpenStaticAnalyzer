if (CMAKE_HOST_SYSTEM_NAME STREQUAL "Windows")
    set (OPENSSL_LIBRARIES libssl.lib libcrypto.lib crypt32.lib)
else ()
    set (OPENSSL_LIBRARIES ssl crypto dl pthread)
endif ()

set (CSAN_BINARIES
     Columbus.dll
     CSAN${EXE}
     CSAN.dll
     CSAN.dll.config
     CSharp.dll
     Humanizer.dll
     LIM.dll
     Microsoft.Bcl.AsyncInterfaces.dll
     Microsoft.Build.Locator.dll
     Microsoft.CodeAnalysis.CSharp.dll
     Microsoft.CodeAnalysis.CSharp.Workspaces.dll
     Microsoft.CodeAnalysis.dll
     Microsoft.CodeAnalysis.VisualBasic.dll
     Microsoft.CodeAnalysis.VisualBasic.Workspaces.dll
     Microsoft.CodeAnalysis.Workspaces.dll
     Microsoft.CodeAnalysis.Workspaces.MSBuild.dll
     System.Composition.AttributedModel.dll
     System.Composition.Convention.dll
     System.Composition.Hosting.dll
     System.Composition.Runtime.dll
     System.Composition.TypedParts.dll
     CSAN.deps.json
     CSAN.runtimeconfig.json
)
