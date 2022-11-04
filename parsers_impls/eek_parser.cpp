#include "eek_parser.hpp"
using namespace eek_classes;

EXPLORERDLL_API eek_parser::eek_parser() {}
EXPLORERDLL_API eek_parser::~eek_parser() {}


EXPLORERDLL_API n_node::node_data eek_parser::parse(const string& text) {
	UNREFERENCED_PARAMETER(text);
	json j = json::parse("{\"numbah\":42,\"hello\":0.21,\"ttt\":\"test1\",\"vec\":[1,2,3,4]}");
	//test t = {};
	auto t = j.get<test>();
	return eek_parser::data;
}


EXPLORERDLL_API plugin_type eek_parser::get_type() { return plugin_type::parser; };

EXPLORERDLL_API bool eek_parser::is_preferred_extension(const string& extension) {
	if (extension == "story" || extension == "character") {
		return true;
	}
	return false;
}



eek_parser* instance = NULL;

extern "C" EXPLORERDLL_API plugin_base * create_plugin(void) {
	if (instance == NULL) instance = new eek_parser();
	return (plugin_base*)instance;
}

extern "C" EXPLORERDLL_API void delete_plugin(void) {
	if (instance != NULL) delete instance;
}
