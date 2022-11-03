#pragma once
#include "..\\utils\node.hpp"

class layouter {
private:
public:
	n_node::node_data nodes = {};
	n_node::linked_node_data linked_nodes = {};
	bool uses_linked = false;
	inline void set_nodes(n_node::node_data& _nodes) {
		nodes = _nodes;
		if (uses_linked) {
			linked_nodes = (n_node::linked_node_data)_nodes;
		}
	}

	virtual void do_layout() = 0;
};