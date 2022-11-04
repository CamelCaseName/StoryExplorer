#pragma once

#include <string>

#define EXPLORERDLL_EXPORT
#include "..\\dll_loading\plugin_common.hpp"
#include "..\\dll_loading\plugin_base.hpp"
#include "..\\dll_loading\plugin_exports_common.hpp"
#include "..\\parser\parser.hpp"

class EXPLORERDLL_API csv_parser : parser {
private:
	n_node::node_data data;
public:
	csv_parser();
	~csv_parser();
	n_node::node_data parse(const string& text);
	bool is_preferred_extension(const string& extension);
};

#undef EXPLORERDLL_EXPORT
