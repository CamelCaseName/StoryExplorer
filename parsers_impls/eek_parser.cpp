#include "eek_parser.hpp"
using namespace eek_classes;

node_data eek_parser::parse(string text) {
	json j = json::parse("{\"numbah\":42,\"hello\":0.21,\"ttt\":\"test1\",\"vec\":[1,2,3,4]}");
	//test t = {};
	auto t = j.get<test>();
	return eek_parser::data;
}

bool eek_parser::is_preferred_extension(const string& extension) {
	if (extension == "story" || extension == "character") {
		return true;
	}
	return false;
}
