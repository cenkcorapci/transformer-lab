#include <mtl/runtime/graph.hpp>
#include <mtl/utils/error.hpp>

#include <algorithm>
#include <stdexcept>

namespace mtl::runtime {

std::size_t Graph::add_node(Node node) {
    const std::size_t idx = nodes_.size();
    nodes_.push_back(std::move(node));
    return idx;
}

std::size_t Graph::num_nodes() const noexcept {
    return nodes_.size();
}

void Graph::run() {
    // TODO: replace linear execution with proper topological sort
    for (auto& node : nodes_) {
        if (node.execute) {
            node.execute();
        }
    }
}

} // namespace mtl::runtime
