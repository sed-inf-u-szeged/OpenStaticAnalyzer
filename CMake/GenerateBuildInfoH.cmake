
set (PREVIOUS_VERSION_FILE ${BINARY_DIR}/BuildInfo.txt)
set (CURRENT_VERSION_FILE ${BINARY_DIR}/BuildInfo-temp.txt)
file(STRINGS ${CURRENT_VERSION_FILE} CURRENT_BUILD_NUMBER)

function (update_version_files)
  file(WRITE ${PREVIOUS_VERSION_FILE} ${CURRENT_BUILD_NUMBER})
  file(WRITE ${BINARY_DIR}/BuildInfo.h
    "#ifndef _BUILD_INFO_H_\n"
    "#define _BUILD_INFO_H_\n"
    "#define REVISION_NUMBER \"${CURRENT_BUILD_NUMBER}\"\n"
    "#endif\n"
  )
endfunction ()


if (EXISTS ${PREVIOUS_VERSION_FILE})
  file(STRINGS ${PREVIOUS_VERSION_FILE} PREVIOUS_BUILD_NUMBER)
  if (NOT ${PREVIOUS_BUILD_NUMBER} STREQUAL ${CURRENT_BUILD_NUMBER})
    update_version_files()
  endif ()
else()
  update_version_files()
endif ()
