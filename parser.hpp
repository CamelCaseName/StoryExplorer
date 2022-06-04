#ifndef PARSER_ABSTRACT_H
#define PARSER_ABSTARCT_H

#include <string>
#include <vector>
#include <math.h>
#include "point.hpp"

#pragma pack(1)
typedef struct color {
	uint8_t a;
	uint8_t r;
	uint8_t g;
	uint8_t b;

	operator int() {
		//return a << 24 || r << 16 || g << 8 || r;
		return *(int*)this;
	}

	color operator=(int num) {
		/*a = (num & (0xff << 24)) >> 24;
		r = (num & (0xff << 16)) >> 16;
		g = (num & (0xff << 8)) >> 8;
		b = num & 0xff;*/
		*(int*)this = num;
		return *this;
	}

} color;

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
