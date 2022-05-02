#ifndef GRAPHSUPPORT_METADATA_H_
#define GRAPHSUPPORT_METADATA_H_

#include "graph/inc/graph.h"

namespace columbus::rul {
    class TagMetadataStore;
}

namespace columbus::graphsupport {
void addTagMetadataToGraph(columbus::graph::Graph &graph, const columbus::rul::TagMetadataStore &metadata_store);
void readTagMetadataFromGraph(graph::Graph& graph, rul::TagMetadataStore &metadata_store);
} // namespace columbus::graphsupport

#endif
