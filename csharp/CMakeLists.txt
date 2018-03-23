set (REVISION_TARGET Revision_csharp)
set (CSHARP_BUILD_TARGET CSHARP_solution)

set (REVISION_TEMPLATE_FILE ${CMAKE_CURRENT_SOURCE_DIR}/lib/Columbus/Revision.cs)

add_custom_target (
    ${REVISION_TARGET}
    DEPENDS generate_build_info
    COMMAND git checkout ${REVISION_TEMPLATE_FILE}
    COMMAND ${CMAKE_COMMAND} "-DINPUT_FILE_NAME=${REVISION_TEMPLATE_FILE}" "-DOUTPUT_FILE_NAME=${REVISION_TEMPLATE_FILE}" "-DTEMPLATE_VARIABLE_NAME=GIT_HASH" "-DTEMPLATE_VARIABLE_VALUE_FILE=${BUILD_INFO_FILE}" -P ${CMAKE_MODULE_PATH}/ConfigureFile.cmake
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

set_target_properties (${REVISION_TARGET} PROPERTIES FOLDER ${CMAKE_SUPPORT_FOLDER_NAME})

add_custom_target (
  ${CSHARP_BUILD_TARGET}
  COMMAND ${CMAKE_CURRENT_SOURCE_DIR}\\.nuget\\NuGet restore ${CMAKE_CURRENT_SOURCE_DIR}\\All.sln
  COMMAND msbuild All.sln /t:Build  /p:Configuration=$<CONFIG>  /p:Platform=${VS_PLATFORM} /p:COLUMBUS_BIN_DIR=${EXECUTABLE_OUTPUT_PATH} /p:CSHARP_BUILD_DIR=${CMAKE_CURRENT_BINARY_DIR} > ${CMAKE_CURRENT_BINARY_DIR}/CSAN-build.log
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

set_target_properties (${CSHARP_BUILD_TARGET} PROPERTIES FOLDER ${CMAKE_SUPPORT_FOLDER_NAME})

set (CSAN_TARGET CSAN_virtual_target)

add_custom_target (
    ${CSAN_TARGET}
)

set (CSAN_OUTPUT_DIR Columbus/CSAN.dir)

set (CSAN_BINARIES
     CSAN.exe
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
  add_custom_generated_copy_dependency(${CSAN_TARGET} ${CSAN_OUTPUT_DIR} ${EXECUTABLE_OUTPUT_PATH} ${BINARY} ${CSHARP_BUILD_TARGET})
endforeach()

set_visual_studio_project_folder(${CSAN_TARGET} FALSE)