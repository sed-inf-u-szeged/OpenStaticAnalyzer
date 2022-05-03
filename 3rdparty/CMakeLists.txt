include(ExternalProject)
set(BUILD_SHARED_LIBS OFF)

# All the external static library names should follow this naming convention:
# Linux:
#   lib<name>.a
# Windows:
#   <name>.lib

file (MAKE_DIRECTORY ${COLUMBUS_3RDPARTY_INSTALL_DIR}/bin)
file (MAKE_DIRECTORY ${COLUMBUS_3RDPARTY_INSTALL_DIR}/lib)
file (MAKE_DIRECTORY ${COLUMBUS_3RDPARTY_INSTALL_DIR}/include)

# Disable warnings during building 3rdparty code
if (CMAKE_CXX_COMPILER_ID MATCHES GNU|Clang)
  add_compile_options("-w")
endif()

########################### zlib #########################

ExternalProject_Add(zlib
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/zlib
    PATCH_COMMAND git clean -x -d -f
          COMMAND git reset --hard
          COMMAND git apply --ignore-whitespace ${CMAKE_CURRENT_SOURCE_DIR}/CMake/zlib.patch
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${COLUMBUS_3RDPARTY_INSTALL_DIR} -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} -DCMAKE_C_FLAGS=${CMAKE_C_FLAGS}  -DCMAKE_C_COMPILER=${CMAKE_C_COMPILER}
    LOG_CONFIGURE 1
    LOG_BUILD 1
    LOG_INSTALL 1
)

# This extra rename step is needed on windows to rename the library to be compatible with the CMake library naming convention.
if (CMAKE_SYSTEM_NAME STREQUAL Windows)
  ExternalProject_Add_Step (zlib rename
    DEPENDEES BUILD INSTALL
    COMMAND ${CMAKE_COMMAND} -E rename ${COLUMBUS_3RDPARTY_INSTALL_DIR}/lib/zlibstatic$<$<CONFIG:Debug>:d>.lib ${COLUMBUS_3RDPARTY_INSTALL_DIR}/lib/z.lib
    LOG 1
  )
endif()


########################### boost ########################

if (CMAKE_CXX_COMPILER_ID STREQUAL MSVC)
  set (BOOST_TOOLSET toolset=msvc-14.1)
elseif (CMAKE_CXX_COMPILER_ID MATCHES GNU|Clang)
  set (BOOST_EXTRA_CXX_COMPILER_FLAGS cxxflags=-fPIC)
  set (BOOST_EXTRA_C_COMPILER_FLAGS cflags=-fPIC)
  if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set (BOOST_TOOLSET toolset=gcc-${CMAKE_CXX_COMPILER_VERSION})
  elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set (BOOST_TOOLSET toolset=clang-${CMAKE_CXX_COMPILER_VERSION})
  endif()
endif ()

ExternalProject_Add(boost
    DEPENDS zlib
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/boost
    BUILD_IN_SOURCE 1
    CONFIGURE_COMMAND ${COMMAND_PREFIX}bootstrap${SCRIPT_EXT}
    BUILD_COMMAND ${COMMAND_PREFIX}b2 ${BOOST_EXTRA_CXX_COMPILER_FLAGS} ${BOOST_EXTRA_C_COMPILER_FLAGS} ${BOOST_TOOLSET} --reconfigure --build-dir=${CMAKE_CURRENT_BINARY_DIR}/boost-prefix --prefix=${COLUMBUS_3RDPARTY_INSTALL_DIR} -j8 --with-filesystem --with-system --with-date_time --with-iostreams --with-graph --with-regex --with-thread --with-math --layout=system variant=$<$<CONFIG:Debug>:debug>$<$<CONFIG:Release>:release>  runtime-link=static architecture=x86  threading=multi address-model=64 link=static  -sZLIB_INCLUDE=${COLUMBUS_3RDPARTY_INSTALL_DIR}/include -sZLIB_LIBPATH=${COLUMBUS_3RDPARTY_INSTALL_DIR}/lib -sZLIB_BINARY=z -sNO_ZLIB=0 -sNO_BZIP2=1   headers
          COMMAND ${COMMAND_PREFIX}b2 ${BOOST_EXTRA_CXX_COMPILER_FLAGS} ${BOOST_EXTRA_C_COMPILER_FLAGS} ${BOOST_TOOLSET} --reconfigure --build-dir=${CMAKE_CURRENT_BINARY_DIR}/boost-prefix --prefix=${COLUMBUS_3RDPARTY_INSTALL_DIR} -j8 --with-filesystem --with-system --with-date_time --with-iostreams --with-graph --with-regex --with-thread --with-math --layout=system variant=$<$<CONFIG:Debug>:debug>$<$<CONFIG:Release>:release>  runtime-link=static architecture=x86  threading=multi address-model=64 link=static  -sZLIB_INCLUDE=${COLUMBUS_3RDPARTY_INSTALL_DIR}/include -sZLIB_LIBPATH=${COLUMBUS_3RDPARTY_INSTALL_DIR}/lib -sZLIB_BINARY=z -sNO_ZLIB=0 -sNO_BZIP2=1   install
    INSTALL_COMMAND ${CMAKE_COMMAND} -E echo "No sepearate installation step is needed."
    LOG_CONFIGURE 1
    LOG_BUILD 1
    LOG_INSTALL 1
)

# This extra rename step is needed on windows to rename the libraries to be compatible with the CMake library naming convention.
if (CMAKE_SYSTEM_NAME STREQUAL Windows)
  set (BOOST_LIBRARY_NAMES_TO_RENAME
    iostreams
    graph
    date_time
    chrono
    math_c99
    math_c99f
    math_c99l
    math_tr1
    math_tr1f
    math_tr1l
    regex
    system
    filesystem
    thread
  )

  foreach (LIB ${BOOST_LIBRARY_NAMES_TO_RENAME})
    set (BOOST_RENAME_COMMAND ${BOOST_RENAME_COMMAND} COMMAND ${CMAKE_COMMAND} -E rename "${COLUMBUS_3RDPARTY_INSTALL_DIR}/lib/libboost_${LIB}.lib" "${COLUMBUS_3RDPARTY_INSTALL_DIR}/lib/boost_${LIB}.lib")
  endforeach()
  
  ExternalProject_Add_Step (boost rename
    DEPENDEES BUILD INSTALL
    ${BOOST_RENAME_COMMAND}
    LOG 1
  )
endif ()


########################### xerces-c #########################

if (CMAKE_SYSTEM_NAME STREQUAL Linux)
  ExternalProject_Add( xerces-c
      URL https://archive.apache.org/dist/xerces/c/3/sources/xerces-c-3.1.4.tar.gz
      URL_HASH MD5=21bb097b711a513275379b59757cba4c 
      BUILD_IN_SOURCE 1
      CONFIGURE_COMMAND ./reconf
                COMMAND ./configure --disable-shared -disable-network --disable-transcoder-icu --prefix=${COLUMBUS_3RDPARTY_INSTALL_DIR} --disable-dependency-tracking
      BUILD_COMMAND make -j8 all
      INSTALL_COMMAND make install
      LOG_DOWNLOAD 1
      LOG_UPDATE 1
      LOG_CONFIGURE 1
      LOG_BUILD 1
      LOG_INSTALL 1
  )

elseif (CMAKE_SYSTEM_NAME STREQUAL Windows)
  
  ExternalProject_Add( xerces-c
      URL https://archive.apache.org/dist/xerces/c/3/sources/xerces-c-3.1.4.zip
      URL_HASH MD5=6fcd8ec268f6bfe11d8ce2cd7d25a185
      BUILD_IN_SOURCE 1
      CONFIGURE_COMMAND ${CMAKE_COMMAND} -E echo "No configuration is required."
      BUILD_COMMAND msbuild projects/Win32/VC14/xerces-all/xerces-all.sln /m /t:XercesLib "/p:Configuration=Static $<CONFIG>" /p:Platform=${VS_PLATFORM} /p:PlatformToolset=${CMAKE_VS_PLATFORM_TOOLSET}
      INSTALL_COMMAND ${CMAKE_COMMAND} "-DCOPY_SOURCE=${CMAKE_CURRENT_BINARY_DIR}/xerces-c-prefix/src/xerces-c/src/xercesc/" "-DCOPY_TARGET=${COLUMBUS_3RDPARTY_INSTALL_DIR}/include/xercesc" -DCOPY_PATTERN=*.hpp -P ${CMAKE_CURRENT_SOURCE_DIR}/CMake/SearchAndCopyFiles.cmake
              COMMAND ${CMAKE_COMMAND} "-DCOPY_SOURCE=${CMAKE_CURRENT_BINARY_DIR}/xerces-c-prefix/src/xerces-c/src/xercesc/" "-DCOPY_TARGET=${COLUMBUS_3RDPARTY_INSTALL_DIR}/include/xercesc" -DCOPY_PATTERN=*.c -P ${CMAKE_CURRENT_SOURCE_DIR}/CMake/SearchAndCopyFiles.cmake
              COMMAND ${CMAKE_COMMAND} -E copy "Build/Win64/VC14/Static $<CONFIG>/xerces-c_static_3$<$<CONFIG:Debug>:d>.lib" ${COLUMBUS_3RDPARTY_INSTALL_DIR}/lib/xerces-c.lib
      LOG_DOWNLOAD 1
      LOG_CONFIGURE 1
      LOG_BUILD 1
      LOG_INSTALL 1
  )
endif ()

########################### PMD #########################

set (PMD_PACKAGE_VERSION pmd-bin-6.32.0)
set (PMD_DIST_PACKAGE ${CMAKE_CURRENT_SOURCE_DIR}/PMD/pmd-dist/target/${PMD_PACKAGE_VERSION}.zip)
set (PMD_PACKAGE ${COLUMBUS_3RDPARTY_INSTALL_DIR}/PMD.zip)
if (CMAKE_SYSTEM_NAME STREQUAL Windows)
  set (MVNW_POSTFIX .cmd)
endif ()

add_custom_command (
  OUTPUT ${PMD_PACKAGE}
  COMMAND ${COMMAND_PREFIX}mvnw${MVNW_POSTFIX} package -DskipTests -Dmaven.test.skip=true -Dmaven.javadoc.skip=true -Dmaven.source.skip=true -pl pmd-dist,pmd-core,pmd-java > ${CMAKE_CURRENT_BINARY_DIR}/PMD-build.log 2>&1
  COMMAND ${CMAKE_COMMAND} -E chdir ${CMAKE_CURRENT_SOURCE_DIR}/PMD/pmd-dist/target/ ${CMAKE_COMMAND} -E remove_directory PMD
  COMMAND ${CMAKE_COMMAND} -E chdir ${CMAKE_CURRENT_SOURCE_DIR}/PMD/pmd-dist/target/ ${CMAKE_COMMAND} -E tar xf ${PMD_DIST_PACKAGE}
  COMMAND ${CMAKE_COMMAND} -E chdir ${CMAKE_CURRENT_SOURCE_DIR}/PMD/pmd-dist/target/ ${CMAKE_COMMAND} -E rename ${PMD_PACKAGE_VERSION} PMD
  COMMAND ${CMAKE_COMMAND} -E chdir ${CMAKE_CURRENT_SOURCE_DIR}/PMD/pmd-dist/target/ ${CMAKE_COMMAND} -E tar cf ${PMD_DIST_PACKAGE} --format=zip PMD
  COMMAND ${CMAKE_COMMAND} -E copy ${PMD_DIST_PACKAGE} ${PMD_PACKAGE}
  COMMENT "Building PMD"
  DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/PMD
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/PMD
)

add_custom_target (
  PMD
  DEPENDS ${PMD_PACKAGE}
)

set_target_properties (PMD PROPERTIES FOLDER "ExternalProjectTargets/pmd")


########################### SpotBugs #########################

ExternalProject_Add( spotbugs
    URL https://repo.maven.apache.org/maven2/com/github/spotbugs/spotbugs/4.2.2/spotbugs-4.2.2.tgz
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ${CMAKE_COMMAND} -P ${CMAKE_MODULE_PATH}/AddExecutablePermission.cmake ${CMAKE_CURRENT_BINARY_DIR}/spotbugs-prefix/src/spotbugs/bin/spotbugs
    INSTALL_COMMAND ${CMAKE_COMMAND} -E chdir ${CMAKE_CURRENT_BINARY_DIR}/spotbugs-prefix/src ${CMAKE_COMMAND} -E tar cf ${COLUMBUS_3RDPARTY_INSTALL_DIR}/spotbugs.zip --format=zip spotbugs
    LOG_DOWNLOAD 1
    LOG_INSTALL 1
)


########################### python27 #########################
if (CMAKE_SYSTEM_NAME STREQUAL Linux)

  ExternalProject_Add( python2.7
      DEPENDS zlib
      SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/python2
      CONFIGURE_COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/python2/configure --enable-optimizations --disable-shared --prefix=${COLUMBUS_3RDPARTY_INSTALL_DIR}
      BUILD_COMMAND make -j8 altbininstall inclinstall
      INSTALL_COMMAND ${CMAKE_COMMAND} -E echo "No install step is required as the build step installs the library."
      LOG_CONFIGURE 1
      LOG_BUILD 1
      LOG_INSTALL 1
  )
elseif (CMAKE_SYSTEM_NAME STREQUAL Windows)

  ExternalProject_Add( python2.7
      DEPENDS zlib
      SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/python2
      BUILD_IN_SOURCE 1
      CONFIGURE_COMMAND ""
      BUILD_COMMAND msbuild PCbuild/pythoncore.vcxproj /m /t:Build /p:Configuration=$<CONFIG> /p:Platform=${VS_PLATFORM} /p:PlatformToolset=${CMAKE_VS_PLATFORM_TOOLSET}
      INSTALL_COMMAND ${CMAKE_COMMAND} -E copy_directory Include ${COLUMBUS_3RDPARTY_INSTALL_DIR}/include/python2.7
              COMMAND ${CMAKE_COMMAND} -E copy "PC/pyconfig.h" ${COLUMBUS_3RDPARTY_INSTALL_DIR}/include/python2.7/pyconfig.h
              COMMAND ${CMAKE_COMMAND} -E copy "PCbuild/amd64/python27$<$<CONFIG:Debug>:_d>.lib" ${COLUMBUS_3RDPARTY_INSTALL_DIR}/lib/python2.7.lib
      LOG_CONFIGURE 1
      LOG_BUILD 1
      LOG_INSTALL 1
  )

endif ()

########################### python38 #########################
if (CMAKE_SYSTEM_NAME STREQUAL Linux)

  ExternalProject_Add( python3.8
      DEPENDS zlib
      SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/python3
      CONFIGURE_COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/python3/configure --enable-optimizations --disable-shared --prefix=${COLUMBUS_3RDPARTY_INSTALL_DIR} --without-pymalloc
      BUILD_COMMAND make -j8 altbininstall inclinstall
      INSTALL_COMMAND ${CMAKE_COMMAND} -E echo "No install step is required as the build step installs the library."
      LOG_CONFIGURE 1
      LOG_BUILD 1
      LOG_INSTALL 1
  )
elseif (CMAKE_SYSTEM_NAME STREQUAL Windows)

  ExternalProject_Add( python3.8
      DEPENDS zlib
      SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/python3
      BUILD_IN_SOURCE 1
      CONFIGURE_COMMAND ""
      BUILD_COMMAND msbuild PCbuild/pythoncore.vcxproj /m /t:Build /p:Configuration=$<CONFIG> /p:Platform=${VS_PLATFORM} /p:PlatformToolset=${CMAKE_VS_PLATFORM_TOOLSET}
      INSTALL_COMMAND ${CMAKE_COMMAND} -E copy_directory Include ${COLUMBUS_3RDPARTY_INSTALL_DIR}/include/python3.8
              COMMAND ${CMAKE_COMMAND} -E copy "PC/pyconfig.h" ${COLUMBUS_3RDPARTY_INSTALL_DIR}/include/python3.8/pyconfig.h
              COMMAND ${CMAKE_COMMAND} -E copy "PCbuild/${PYTHON_PLATFORM_NAME}/python38$<$<CONFIG:Debug>:_d>.lib" ${COLUMBUS_3RDPARTY_INSTALL_DIR}/lib/python3.8.lib
      LOG_CONFIGURE 1
      LOG_BUILD 1
      LOG_INSTALL 1
  )
endif ()

###################### cppcheck ############################

if (CMAKE_SYSTEM_NAME STREQUAL Linux OR CMAKE_SYSTEM_NAME STREQUAL Darwin)
  ExternalProject_Add( cppcheck
      SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/cppcheck
      CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${COLUMBUS_3RDPARTY_INSTALL_DIR} -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
      LOG_CONFIGURE 1
      LOG_BUILD 1
      LOG_INSTALL 1
  )

elseif (CMAKE_SYSTEM_NAME STREQUAL Windows)

  ExternalProject_Add( cppcheck
      SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/cppcheck
      CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${COLUMBUS_3RDPARTY_INSTALL_DIR} -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
      LOG_CONFIGURE 1
      LOG_BUILD 1
      LOG_INSTALL 1
  )

endif()

###################### openssl ############################

if (CMAKE_HOST_SYSTEM_NAME STREQUAL "Windows")
    ExternalProject_Add( openssl
        URL https://www.openssl.org/source/openssl-1.1.0h.tar.gz
        CONFIGURE_COMMAND perl ../openssl/Configure --prefix=${COLUMBUS_3RDPARTY_INSTALL_DIR} --openssldir=ssl VC-WIN64A ${DEBUG_BUILD} -no-shared
        BUILD_COMMAND nmake
        INSTALL_COMMAND nmake install
        LOG_CONFIGURE 1
        LOG_BUILD 1
        LOG_INSTALL 1
        LOG_DOWNLOAD 1
    )

  else ()
    ExternalProject_Add( openssl
        URL https://www.openssl.org/source/openssl-1.1.0h.tar.gz
        CONFIGURE_COMMAND ../openssl/config --prefix=${COLUMBUS_3RDPARTY_INSTALL_DIR} --openssldir=ssl ${DEBUG_BUILD} -no-shared
        BUILD_COMMAND make
        INSTALL_COMMAND make install
        LOG_CONFIGURE 1
        LOG_BUILD 1
        LOG_INSTALL 1
        LOG_DOWNLOAD 1
    )
  
endif ()

###################### llvm/clang ############################

if (CMAKE_SYSTEM_NAME STREQUAL Linux)

  ExternalProject_Add( clang
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/clang/llvm
    CMAKE_ARGS -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} -DCMAKE_INSTALL_PREFIX=${COLUMBUS_3RDPARTY_INSTALL_DIR} -DCMAKE_EXE_LINKER_FLAGS=${CMAKE_EXE_LINKER_FLAGS} -DLLVM_ENABLE_RTTI=ON -DLLVM_OPTIMIZED_TABLEGEN=ON -DLLVM_ENABLE_SPHINX=ON "-DLLVM_ENABLE_PROJECTS=clang\\$<SEMICOLON>clang-tools-extra" -DCMAKE_CXX_STANDARD=${CMAKE_CXX_STANDARD} -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER} -DCMAKE_C_COMPILER=${CMAKE_C_COMPILER}
    BUILD_COMMAND ${CMAKE_COMMAND} --build <BINARY_DIR> --config $<CONFIG> --parallel ${PHYSICAL_CORES} -t install-llvm-libraries-stripped -t install-clang-libraries-stripped -t install-clang-headers -t install-llvm-headers -t install-clang-tidy-stripped -t install-clang-resource-headers
    INSTALL_COMMAND ""
    LOG_CONFIGURE 1
    LOG_BUILD 1
    LOG_INSTALL 1
  )

elseif (CMAKE_SYSTEM_NAME STREQUAL Windows)

  ExternalProject_Add( clang
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/clang/llvm
    CMAKE_GENERATOR Ninja
    CMAKE_ARGS -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} -DCMAKE_INSTALL_PREFIX=${COLUMBUS_3RDPARTY_INSTALL_DIR} -DLLVM_USE_CRT_DEBUG=MTd -DLLVM_USE_CRT_RELEASE=MT -DLLVM_ENABLE_RTTI=ON  "-DLLVM_ENABLE_PROJECTS=clang\\$<SEMICOLON>clang-tools-extra" -DCMAKE_CXX_STANDARD=${CMAKE_CXX_STANDARD} -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER} -DCMAKE_C_COMPILER=${CMAKE_C_COMPILER}  -DCMAKE_GENERATOR_TOOLSET=
    BUILD_COMMAND ${CMAKE_COMMAND} --build <BINARY_DIR> --config $<CONFIG> --parallel ${PHYSICAL_CORES} -t install-llvm-libraries-stripped -t install-clang-libraries-stripped -t install-clang-headers -t install-llvm-headers -t install-clang-tidy-stripped -t install-clang-resource-headers
    INSTALL_COMMAND ""
	LOG_CONFIGURE 1
    LOG_BUILD 1
    LOG_INSTALL 1
  )

endif()


######################## miniz #################################
add_subdirectory(miniz)
