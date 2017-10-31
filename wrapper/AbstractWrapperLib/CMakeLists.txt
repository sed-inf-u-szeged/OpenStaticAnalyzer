set (LIBNAME abstractwrapper)

set (SOURCES
    src/abstractwrapper/AbstractArchive.cpp
    src/abstractwrapper/AbstractCompiler.cpp
    src/abstractwrapper/AbstractLinker.cpp
    src/abstractwrapper/AbstractWrapper.cpp
    src/paramsup/ArmccParamsup.cpp
    src/paramsup/ArParamsup.cpp
    src/paramsup/ClParamsup.cpp
    src/paramsup/GccParamsup.cpp
    src/paramsup/LibParamsup.cpp
    src/paramsup/ParamsupCommon.cpp
    
    inc/abstractwrapper/AbstractArchive.h
    inc/abstractwrapper/AbstractCompiler.h
    inc/abstractwrapper/AbstractLinker.h
    inc/abstractwrapper/AbstractWrapper.h
    inc/messages.h
    inc/paramsup/ArmccParamsup.h
    inc/paramsup/ArParamsup.h
    inc/paramsup/ClParamsup.h
    inc/paramsup/GccParamsup.h
    inc/paramsup/LibParamsup.h
    inc/paramsup/ParamsupCommon.h 
)

add_library (${LIBNAME} STATIC ${SOURCES})
add_dependencies (${LIBNAME} boost)
set_visual_studio_project_folder(${LIBNAME} TRUE)

