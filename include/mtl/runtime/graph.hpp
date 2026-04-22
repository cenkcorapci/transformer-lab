#pragma once

#include <mtl/core/tensor.hpp>

#include <cstddef>
#include <functional>
#include <memory>
#include <string>
#include <vector>

namespace mtl::runtime {

/// A node in the computation graph.
///
/// TODO: implement automatic differentiation (reverse-mode AD).
/// TODO: add graph fusion passes.
struct Node {
    std::string              name;
    std::vector<std::size_t> inputs;   ///< indices into Graph::nodes_
    std::vector<std::size_t> outputs;

    /// Operation kernel to execute (placeholder type).
    std::function<void()> execute;
};

/// Directed acyclic computation graph.
///
/// TODO: implement topological sort and schedule execution.
/// TODO: add constant folding and dead-node elimination passes.
class Graph {
public:
    Graph()  = default;
    ~Graph() = default;

    Graph(const Graph&)            = delete;
    Graph& operator=(const Graph&) = delete;
    Graph(Graph&&) noexcept        = default;
    Graph& operator=(Graph&&) noexcept = default;

    std::size_t add_node(Node node);

    [[nodiscard]] std::size_t num_nodes() const noexcept;

    /// Execute all nodes in topological order.
    void run();

private:
    std::vector<Node> nodes_;
};

} // namespace mtl::runtime
