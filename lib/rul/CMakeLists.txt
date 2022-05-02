set (LIBNAME rul)

set (SOURCES
    src/RulHandler.cpp
    src/RulMD.cpp
    src/RulMDString.cpp
    src/RulTags.cpp
    src/RulTagStore.cpp
    src/RulTagMetadataStore.cpp

    inc/messages.h
    inc/RulHandler.h
    inc/RulHandlerException.h
    inc/RulMD.h
    inc/RulMDString.h
    inc/RulTags.h
    inc/RulTagString.h
    inc/RulTagStore.h
    inc/RulTagMetadata.h
    inc/RulTagMetadataStore.h
)

add_library (${LIBNAME} STATIC ${SOURCES})
target_link_libraries (${LIBNAME} common io xerces-c md4c-html md4c)

if (CMAKE_SYSTEM_NAME STREQUAL Linux)
  target_link_libraries (${LIBNAME} pthread)
endif()

set_visual_studio_project_folder(${LIBNAME} TRUE)
