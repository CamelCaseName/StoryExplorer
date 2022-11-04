#include "layouter.hpp"

EXPLORERDLL_API layouter::layouter() {}

EXPLORERDLL_API layouter::~layouter() {}

EXPLORERDLL_API void layouter::set_nodes(n_node::node_data& _nodes) {
	nodes = _nodes;
	if (uses_linked) {
		linked_nodes = (n_node::linked_node_data)_nodes;
	}
}