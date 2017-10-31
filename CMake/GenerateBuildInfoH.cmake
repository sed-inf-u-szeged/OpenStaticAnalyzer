
file(STRINGS ${BINARY_DIR}/BuildInfo.txt BUILD_NUMBER)

file(WRITE ${BINARY_DIR}/BuildInfo.h
  "#ifndef _BUILD_INFO_H_\n"
  "#define _BUILD_INFO_H_\n"
  "#define REVISION_NUMBER \"${BUILD_NUMBER}\"\n"
  "#endif\n"
)
