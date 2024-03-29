set (PROGRAM_NAME PAN)

set (SOURCES
    src/main.cpp
    src/PBuilder.cpp
    src/plloc.cpp
    src/PVisitor.cpp
    src/VisitorImport.cpp
    src/VisitorType.cpp
    
    inc/messages.h
    inc/PBuilder.h
    inc/PlLOC.h
    inc/PVisitor.h
    inc/VisitorImport.h
    inc/VisitorType.h     
)



function (add_version_config VERSION)
  string (FIND ${VERSION} "." DOT_POSITION)
  string (SUBSTRING ${VERSION} 0 ${DOT_POSITION} PROGRAM_VERSION)
  set (VERSIONED_PROGRAM_NAME ${PROGRAM_NAME}${PROGRAM_VERSION})
  add_executable(${VERSIONED_PROGRAM_NAME} ${SOURCES})
  add_dependencies(${VERSIONED_PROGRAM_NAME} ${COLUMBUS_GLOBAL_DEPENDENCY})
  target_link_libraries(${VERSIONED_PROGRAM_NAME} python python${VERSION} common strtable csi io ${COMMON_EXTERNAL_LIBRARIES})
  target_compile_definitions(${VERSIONED_PROGRAM_NAME} PUBLIC Py_NO_ENABLE_SHARED ${ARGN})

  if (CMAKE_SYSTEM_NAME STREQUAL Linux)
    if (NOT ${PROGRAM_VERSION} STREQUAL "2")
      target_include_directories(${VERSIONED_PROGRAM_NAME} PUBLIC ${COLUMBUS_3RDPARTY_INSTALL_DIR}/include/python${VERSION})
    endif ()
    target_link_libraries(${VERSIONED_PROGRAM_NAME} pthread util dl rt)
  elseif (CMAKE_SYSTEM_NAME STREQUAL Windows)
    target_link_libraries(${VERSIONED_PROGRAM_NAME} version ws2_32)
  endif ()

  set_visual_studio_project_folder(${VERSIONED_PROGRAM_NAME} FALSE)
endfunction()

add_version_config(2.7)
add_version_config(3.8 PY3)
