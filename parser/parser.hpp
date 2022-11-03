#ifndef PARSER_ABSTRACT_H
#define PARSER_ABSTRACT_H

#include <string>
using std::string;
#include <vector>
#include <math.h>
#include "..\\utils\point.hpp"
#include "..\\utils\color.hpp"
#include "..\\utils\node.hpp"
#include "..\\main\StoryExplorer.hpp"
using namespace n_point;
using namespace n_node;

class parser {
public:
	//pure virtual parse method definition to enable inheritance and have the framework still work with the rest
	virtual n_node::node_data parse(string text) = 0;
	//string with the file extenstion this parser wants to work with. can also be a custom key
	virtual bool is_preferred_extension(const string& extension) = 0;
private:
	n_node::node_data data;
};
 
#endif // !PARSER_ABSTRACT_H
