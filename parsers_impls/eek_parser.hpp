#pragma once

#include <vector>
#include <string>

#define EXPLORERDLL_EXPORT
#include "..\\dll_loading\plugin_common.hpp"
#include "..\\dll_loading\plugin_base.hpp"
#include "..\\dll_loading\plugin_exports_common.hpp"
#include "..\\parser\parser.hpp"
#include "..\\utils\json.hpp"

using json = nlohmann::json;
//todo https://github.com/nlohmann/json#specializing-enum-conversion this for the eek enums, mabye rip them from dnspy automatically?

//classes used by house party in their story files
namespace eek_classes {
	typedef struct test {
		int numbah = 0;
		float hello = 0;
		std::string ttt;
		std::vector<int> vec;
	}test;

	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(test, numbah, hello, ttt, vec)
}


class EXPLORERDLL_API eek_parser : parser {
private:
	n_node::node_data data;
public:
	eek_parser();
	~eek_parser();
	n_node::node_data parse(const string& text);
	plugin_type get_type();
	bool is_preferred_extension(const string& extension);
};

//hp classes

#undef EXPLORERDLL_EXPORT
