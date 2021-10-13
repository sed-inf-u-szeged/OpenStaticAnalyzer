set (LIBNAME yamlcpp)

set (SOURCES

  include/yaml-cpp/anchor.h
  include/yaml-cpp/binary.h
  include/yaml-cpp/dll.h
  include/yaml-cpp/emitfromevents.h
  include/yaml-cpp/emitter.h
  include/yaml-cpp/emitterdef.h
  include/yaml-cpp/emittermanip.h
  include/yaml-cpp/emitterstyle.h
  include/yaml-cpp/eventhandler.h
  include/yaml-cpp/exceptions.h
  include/yaml-cpp/mark.h
  include/yaml-cpp/null.h
  include/yaml-cpp/ostream_wrapper.h
  include/yaml-cpp/parser.h
  include/yaml-cpp/stlemitter.h
  include/yaml-cpp/traits.h
  include/yaml-cpp/yaml.h

  include/yaml-cpp/contrib/anchordict.h
  include/yaml-cpp/contrib/graphbuilder.h


  include/yaml-cpp/node/convert.h
  include/yaml-cpp/node/emit.h
  include/yaml-cpp/node/impl.h
  include/yaml-cpp/node/iterator.h
  include/yaml-cpp/node/node.h
  include/yaml-cpp/node/parse.h
  include/yaml-cpp/node/ptr.h
  include/yaml-cpp/node/type.h

  include/yaml-cpp/node/detail/impl.h
  include/yaml-cpp/node/detail/iterator.h
  include/yaml-cpp/node/detail/iterator_fwd.h
  include/yaml-cpp/node/detail/memory.h
  include/yaml-cpp/node/detail/node.h
  include/yaml-cpp/node/detail/node_data.h
  include/yaml-cpp/node/detail/node_iterator.h
  include/yaml-cpp/node/detail/node_ref.h

  src/binary.cpp
  src/collectionstack.h
  src/convert.cpp
  src/directives.cpp
  src/directives.h
  src/emit.cpp
  src/emitfromevents.cpp
  src/emitter.cpp
  src/emitterstate.cpp
  src/emitterstate.h
  src/emitterutils.cpp
  src/emitterutils.h
  src/exceptions.cpp
  src/exp.cpp
  src/exp.h
  src/indentation.h
  src/memory.cpp
  src/node.cpp
  src/nodebuilder.cpp
  src/nodebuilder.h
  src/nodeevents.cpp
  src/nodeevents.h
  src/node_data.cpp
  src/null.cpp
  src/ostream_wrapper.cpp
  src/parse.cpp
  src/parser.cpp
  src/ptr_vector.h
  src/regeximpl.h
  src/regex_yaml.cpp
  src/regex_yaml.h
  src/scanner.cpp
  src/scanner.h
  src/scanscalar.cpp
  src/scanscalar.h
  src/scantag.cpp
  src/scantag.h
  src/scantoken.cpp
  src/setting.h
  src/simplekey.cpp
  src/singledocparser.cpp
  src/singledocparser.h
  src/stream.cpp
  src/stream.h
  src/streamcharsource.h
  src/stringsource.h
  src/tag.cpp
  src/tag.h
  src/token.h

  src/contrib/graphbuilder.cpp
  src/contrib/graphbuilderadapter.cpp
  src/contrib/graphbuilderadapter.h
  src/contrib/yaml-cpp.natvis
)

add_library (${LIBNAME} STATIC ${SOURCES})
add_dependencies (${LIBNAME} boost)
set_visual_studio_project_folder(${LIBNAME} TRUE)
