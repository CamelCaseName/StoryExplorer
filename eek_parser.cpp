#include "eek_parser.hpp"

node_data eek_parser::parse(string text) {
	return eek_parser::data;
}

bool eek_parser::preferred_extension(const string& extension) {
	if (extension == "story" || extension == "character") {
		return true;
	}
	return false;
}
