set (PROGRAM_NAME JANLink)

set (SOURCES
    src/main.cpp
    src/Linker.cpp
    src/LinkerBase.cpp
    src/LinkerHelper.cpp
    src/VisitorLinker.cpp
    src/VisitorStrMap.cpp

    inc/Linker.h
    inc/messages.h 
    inc/LinkerBase.h
    inc/LinkerHelper.h
    inc/VisitorLinker.h
    inc/VisitorStrMap.h
)


add_executable(${PROGRAM_NAME} ${SOURCES} )
add_dependencies(${PROGRAM_NAME} ${COLUMBUS_GLOBAL_DEPENDENCY})
target_link_libraries(${PROGRAM_NAME} java strtable common csi io ${COMMON_EXTERNAL_LIBRARIES})
set_visual_studio_project_folder(${PROGRAM_NAME} TRUE)
