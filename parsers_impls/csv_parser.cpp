#include "csv_parser.hpp"

EXPLORERDLL_API csv_parser::csv_parser() {}

EXPLORERDLL_API csv_parser::~csv_parser() {}

EXPLORERDLL_API n_node::node_data csv_parser::parse(const string& text) {
    return n_node::node_data();
}

EXPLORERDLL_API bool csv_parser::is_preferred_extension(const string& extension) {
    return false;
}

csv_parser* instance = NULL;

extern "C" EXPLORERDLL_API plugin_base * create_plugin(void) {
	if (instance == NULL) instance = new csv_parser();
	return (plugin_base*)instance;
}

extern "C" EXPLORERDLL_API void delete_plugin(void) {
	if (instance != NULL) delete instance;
}
