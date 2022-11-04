#include "parser.hpp"

EXPLORERDLL_API parser::parser() {}
EXPLORERDLL_API parser::~parser() {}

EXPLORERDLL_API n_node::node_data parser::parse(const std::string& text) {
    return n_node::node_data();
}

EXPLORERDLL_API bool parser::is_preferred_extension(const std::string& extension) {
    return false;
}
