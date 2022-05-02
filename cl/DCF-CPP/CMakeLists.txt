set (PROGRAM_NAME DuplicatedCodeFinder_cpp)

set (SOURCES
    src/main.cpp
    src/dcm.cpp
    src/AbstractFilter.cpp
    src/CloneLengthFilter.cpp
    src/ClonePositioned.cpp
    src/CppSerializeAST.cpp
    src/LanguageFactory.cpp
    src/RepeatingLinesFilter.cpp
    src/StatementFilter.cpp

    inc/messages.h

)


if (CMAKE_SYSTEM_NAME STREQUAL Windows)
  set (CLANG_PLATFORM_LIBRARIES
    version
  )

elseif (CMAKE_SYSTEM_NAME STREQUAL Linux)
  set (CLANG_PLATFORM_LIBRARIES
    pthread
    z
    tinfo
    dl
  )
endif ()


add_executable(${PROGRAM_NAME} ${SOURCES})
add_dependencies(${PROGRAM_NAME} DuplicatedCodeFinder clang ${COLUMBUS_GLOBAL_DEPENDENCY})
target_link_libraries(${PROGRAM_NAME}  clangsupport ${CLANG_COMMON_LIBRARIES} ${CLANG_PLATFORM_LIBRARIES} genealogy graphsupport lim2graph graph lim strtable common csi rul io ${COMMON_EXTERNAL_LIBRARIES})
set_visual_studio_project_folder(${PROGRAM_NAME} TRUE)

