
set (CLANG_COMMON_LIBRARIES
  clangMetrics
  clangTooling
  clangFrontend
  clangRewriteFrontend
  clangSerialization
  clangParse
  clangSema
  clangEdit
  clangLex
  clangAnalysis
  clangRewrite
  clangASTMatchers
  clangAST
  clangDriver
  clangBasic

  LLVMMCParser
  LLVMMC
  LLVMProfileData
  LLVMBitReader
  LLVMBitstreamReader
  LLVMCore
  LLVMSupport
  LLVMOption
  LLVMDemangle
  LLVMBinaryFormat
  LLVMRemarks
  LLVMFrontendOpenMP
)

if (CMAKE_SYSTEM_NAME STREQUAL Windows)
  list (APPEND CLANG_COMMON_LIBRARIES version)
elseif (CMAKE_SYSTEM_NAME STREQUAL Linux)
  list (APPEND CLANG_COMMON_LIBRARIES pthread z tinfo dl)
elseif (CMAKE_SYSTEM_NAME STREQUAL Darwin)
  list (APPEND CLANG_COMMON_LIBRARIES pthread z dl curses)
endif ()
