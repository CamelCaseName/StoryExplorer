#ifndef NODE_H
#define NODE_H

#include <vector>
#include <string>

#include "color.hpp"
#include "point.hpp"

using namespace n_point;
using std::string;

namespace n_node {
	//a struct defining a node, 
	typedef struct node {
		point position = {};
		float weight = 1;
		color custom_color = {};
		string text;
		string additional_info;
	} node;

	typedef struct linked_node {
		node self = {};
		std::vector<linked_node*> parents;
		std::vector<linked_node*> children;
	} linked_node;

	//a struct defining an edge
	typedef struct edge {
		float weight = 1;
		node* node_1 = {};
		node* node_2 = {};
		color custom_color = {};
		string text;
	} edge;

	//a struct for containign all nodes and edges to pass to the renderer in the end
	typedef struct node_data {
		std::vector<node*> nodes;
		std::vector<edge*> edges;
	} node_data;

	typedef struct linked_node_data {
		std::vector<linked_node*> nodes;

		//todo, incomplete lol
		/*operator node_data() {
			std::vector<node*> _nodes;
			std::vector<edge*> _edges;
			for (auto l_node : nodes) {
				_nodes.push_back(&l_node->self);
				for (auto child : l_node->children) {

				}
			}
		}*/
	} linked_node_data;
}


#endif // !NODE_H