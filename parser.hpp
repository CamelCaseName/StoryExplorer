#ifndef PARSER_ABSTRACT_H
#define PARSER_ABSTARCT_H

#include <string>
#include <vector>
#include <math.h>
#include "point.hpp"
#include "color.hpp"


//a struct defining a node, 
typedef struct node {
	point position;
	double weight;
	color custom_color;
	std::string text;
	std::string additional_info;
} node;

//a struct defining an edge
typedef struct edge {
	double weight;
	node node_1;
	node node_2;
	color custom_color;
	std::string text;
} edge;

//a struct for containign all nodes and edges to pass to the renderer in the end
typedef struct node_data {
	std::vector<node*> nodes;
	std::vector<edge*> edges;
} node_data;


class parser {
public:
	virtual node_data parse(std::string) = 0;
private:
	node_data data;
};

#endif // !PARSER_ABSTRACT_H
