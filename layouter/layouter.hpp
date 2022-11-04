#pragma once

//export this to a dll
#define EXPLORERDLL_EXPORT
#include "..\\utils\node.hpp"
#include "..\\dll_loading\plugin_common.hpp"
#include "..\\dll_loading\plugin_base.hpp"

class EXPLORERDLL_API layouter : plugin_base{
private:
public:
	n_node::node_data nodes = {};
	n_node::linked_node_data linked_nodes = {};

	bool uses_linked = false;

	void set_nodes(n_node::node_data& _nodes);

	virtual void do_layout() = 0;

	layouter(void);

	~layouter(void);
};

#undef EXPLORERDLL_EXPORT