#ifndef EEK_PARSER_H
#define EEK_PARSER_H
#include <vector>
#include <string>
#include "parser.hpp"
#include "..\\utils\json.hpp"
using json = nlohmann::json;
//todo https://github.com/nlohmann/json#specializing-enum-conversion this for the eek enums, mabye rip them from dnspy automatically?

//classes used by house party in their story files
namespace eek_classes {
	struct test {
		int numbah = 0;
		float hello = 0;
		std::string ttt;
		std::vector<int> vec;
	};

	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(test, numbah, hello, ttt, vec)
}


class eek_parser : parser {
public:
	node_data parse(string text);
	bool preferred_extension(const string& extension);
private:
	node_data data;
};

//hp classes

#endif // !EEK_PARSER_H
