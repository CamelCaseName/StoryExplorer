#ifndef PARSER_ABSTRACT_H
#define PARSER_ABSTRACT_H

#include <string>
using std::string;
#include <vector>
#include <math.h>
#include "..\\utils\color.hpp"
#include "..\\utils\point.hpp"
#include "..\\main\StoryExplorer.hpp"


//a struct defining a node, 
typedef struct node {
	point position;
	double weight;
	color custom_color;
	string text;
	string additional_info;
} node;

//a struct defining an edge
typedef struct edge {
	double weight;
	node node_1;
	node node_2;
	color custom_color;
	string text;
} edge;

//a struct for containign all nodes and edges to pass to the renderer in the end
typedef struct node_data {
	std::vector<node*> nodes;
	std::vector<edge*> edges;
} node_data;


class parser {
public:
	//pure virtual parse method definition to enable inheritance and have the framework still work with the rest
	virtual node_data parse(string text) = 0;
	//string with the file extenstion this parser wants to work with. can also be a custom key
	virtual bool preferred_extension(const string& extension) = 0;
private:
	node_data data;
};
 
#endif // !PARSER_ABSTRACT_H
