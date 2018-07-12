set (PACKAGE_LANG CSharp)
set (OSA_TARGET_NAME OSA-${PACKAGE_LANG})

add_subdirectory (doc/usersguide)

add_custom_target (
    ${OSA_TARGET_NAME}
)

set_visual_studio_project_folder(${OSA_TARGET_NAME} FALSE)

if (CMAKE_SYSTEM_NAME STREQUAL Windows)

  file (MAKE_DIRECTORY
        ${OSA_PACKAGE_DIR}/${PACKAGE_LANG}/Demo
        ${OSA_PACKAGE_DIR}/${PACKAGE_LANG}/${CMAKE_SYSTEM_NAME}Tools
  )

  # These functions copy the SOURCE file into different directories of the OpenStaticAnalyzer package.
  # The second parameter is optional. You can set the name of the target, which will be used for generating the SOURCE.
  # The third parameter is also optional. You can set a different name for the SOURCE on which the file will be created in the tools directory.
  function (add_custom_generated_copy_dependency_to_root_dir SOURCE)
    add_custom_generated_copy_dependency(${OSA_TARGET_NAME} ${EXECUTABLE_OUTPUT_PATH} ${OSA_PACKAGE_DIR}/${PACKAGE_LANG} ${ARGV})
  endfunction ()

  function (add_custom_generated_copy_dependency_to_tools_dir SOURCE)
    add_custom_generated_copy_dependency(${OSA_TARGET_NAME} ${EXECUTABLE_OUTPUT_PATH} ${OSA_PACKAGE_DIR}/${PACKAGE_LANG}/${CMAKE_SYSTEM_NAME}Tools ${ARGV})
  endfunction ()

  add_custom_generated_copy_dependency_to_root_dir (OpenStaticAnalyzerCSharp${EXE})

  add_custom_generated_copy_dependency_to_tools_dir (rules_csharp.csv OpenStaticAnalyzerCSharp)
  add_custom_generated_copy_dependency_to_tools_dir (DuplicatedCodeFinder_csharp${EXE} DuplicatedCodeFinder_csharp DuplicatedCodeFinder${EXE})
  add_custom_generated_copy_dependency_to_tools_dir (DCF.rul DuplicatedCodeFinder_csharp_copy_DCF.rul)
  add_custom_generated_copy_dependency_to_tools_dir (FxCop2Graph${EXE})
  add_custom_generated_copy_dependency_to_tools_dir (FxCop.rul FxCop2Graph)
  add_custom_generated_copy_dependency_to_tools_dir (GraphDump${EXE})
  add_custom_generated_copy_dependency_to_tools_dir (GraphMerge${EXE})
  add_custom_generated_copy_dependency_to_tools_dir (LIM2Metrics${EXE})
  add_custom_generated_copy_dependency_to_tools_dir (MET.rul LIM2Metrics)
  add_custom_generated_copy_dependency_to_tools_dir (MetricHunter_csharp${EXE} MetricHunter_csharp MetricHunter${EXE})
  add_custom_generated_copy_dependency_to_tools_dir (MetricHunter_CSHARP.threshold MetricHunter_csharp_copy_MetricHunter_CSHARP.threshold MetricHunter.threshold)


  set (CSAN_BINARIES
       CSAN${EXE}
       Columbus.dll
       CSharp.dll
       LIM.dll
       Microsoft.CodeAnalysis.dll
       Microsoft.CodeAnalysis.CSharp.dll
       Microsoft.CodeAnalysis.CSharp.Workspaces.dll
       Microsoft.CodeAnalysis.VisualBasic.dll
       Microsoft.CodeAnalysis.VisualBasic.Workspaces.dll
       Microsoft.CodeAnalysis.Workspaces.dll
       Microsoft.CodeAnalysis.Workspaces.Desktop.dll
       System.Collections.Immutable.dll
       System.Composition.AttributedModel.dll
       System.Composition.Convention.dll
       System.Composition.Hosting.dll
       System.Composition.Runtime.dll
       System.Composition.TypedParts.dll
       System.Reflection.Metadata.dll
  )

  foreach (BINARY ${CSAN_BINARIES})
    add_custom_generated_copy_dependency_to_tools_dir (${BINARY} CSAN_virtual_target)
  endforeach() 


  add_custom_generated_copy_dependency(
      ${OSA_TARGET_NAME}
      doc/usersguide
      ${OSA_PACKAGE_DIR}/${PACKAGE_LANG}
      UsersGuide.html
      ${OSA_TARGET_NAME}-UG
  )

  
  set (DEMO_SCRIPTS_AND_FILES
      analyze${SCRIPT_EXT}
      softfilter
      hardfilter
  )

  add_prefix(DEMO_SCRIPTS_AND_FILES ${CMAKE_CURRENT_SOURCE_DIR}/demo/)

  add_custom_copy_list_target (
      ${OSA_TARGET_NAME}
      DemoFiles
      DEMO_SCRIPTS_AND_FILES
      ${OSA_PACKAGE_DIR}/${PACKAGE_LANG}/Demo
  )  
  
  add_custom_extract_target (
      ${OSA_TARGET_NAME}
      ${CMAKE_CURRENT_SOURCE_DIR}/demo/log4net-1.2.13.zip 
      ${OSA_PACKAGE_DIR}/${PACKAGE_LANG}/Demo
      ${OSA_PACKAGE_DIR}/${PACKAGE_LANG}/Demo/log4net-1.2.13
  )
  
  copy_licenses()

endif()
