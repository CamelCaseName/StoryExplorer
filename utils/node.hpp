#ifndef NODE_H
#define NODE_H

#include <algorithm>
#include <vector>
#include <iterator>
#include <string>
#include <fstream>
#include <istream>
#include <iostream>
#include <unordered_map>

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

	inline std::ostream& operator<<(std::ostream& str, const node& n) {
		str << "P: ( " << n.position.x << "| " << n.position.y << " ) W: " << n.weight << " T: " << n.text;
	}

	typedef struct linked_node {
		node self = {};
		std::vector<linked_node*> neighbors;
	} linked_node;

	//a struct defining an edge
	typedef struct edge {
		float weight = 1;
		node* node_1 = {};
		node* node_2 = {};
		color custom_color = {};
		string text;
	} edge;


	typedef struct linked_node_data {
		std::vector<linked_node*> nodes;
		linked_node root;

		//convert to a flat structure
		/*operator node_data() {
			std::vector<node*> _nodes;
			std::vector<edge*> _edges;
			for (auto l_node : nodes) {
				_nodes.push_back(&l_node->self);
				for (auto neighbor : l_node->neighbors) {

				}
			}
		}*/
	} linked_node_data;

	//a struct for containign all nodes and edges to pass to the renderer in the end
	typedef struct node_data {
		std::vector<node*> nodes;
		std::vector<edge*> edges;

		operator linked_node_data() {
			//object to return
			linked_node_data _data = {};
			//map of the already used nodesd and their linked counterparts so we can easily link them when we go through the edges
			auto node_lookup = std::unordered_map<node*, linked_node*>();
			std::vector<linked_node*> all_linked_nodes;

			for (auto _node : this->nodes) {
				//create new linked node and add our current data to it
				auto _linked_node = new linked_node();
				_linked_node->self = *_node;

				//add it to the list of all nodes
				node_lookup.insert({ _node, _linked_node });
				all_linked_nodes.push_back(_linked_node);
			}

			//now that we have all the cool new nodes, we can go ahead 
			//and go through all the edges and add the references in the linked nodes
			for (auto _edge : this->edges) {
				node_lookup[_edge->node_1]->neighbors.push_back(node_lookup[_edge->node_2]);
			}

			std::vector<linked_node*> linked_to_nodes;

			//set root to some random node. we should not ever see this being used, 
			//because a real tree alsways has a root e.g. a node that is not linked to. but let's be safe
			//for this we set the ndoe witht he most children as the root node. we also have to add it to our new root node if it is not in the diff, if we encounter a cycle
			linked_node* current_root = node_lookup[nodes[0]];
			//do sanity checks and see if all nodes are linked to somehow, else we add a definite root node which links too all unlinked nodes
			//get a list of all nodes which we link to
			for (auto _node : this->nodes) {
				for (auto _node2 : node_lookup[_node]->neighbors) {
					linked_to_nodes.push_back(_node2);
				}

				//if we have a node with more neighboors, use it as the 
				if (current_root->neighbors.size() < node_lookup[_node]->neighbors.size()) {
					current_root = node_lookup[_node];
				}
			}

			//compare the list of nodes which we link to and the ones we dont link to
			//list to hold the difference
			std::vector<linked_node*> diff;
			//sort the inputs
			std::sort(linked_to_nodes.begin(), linked_to_nodes.end());
			std::sort(all_linked_nodes.begin(), all_linked_nodes.end());
			//compute difference
			std::set_difference(all_linked_nodes.begin(), all_linked_nodes.end(), linked_to_nodes.begin(), linked_to_nodes.end(), std::inserter(diff, diff.begin()));


			if (diff.size() > 0) {
				//if we have any nodes not yet linked to we create a master root thing and link to them. 
				//this wil also link our new root to the old root of all nots that have been linked to
				auto _root_node = new linked_node();
				//add self node
				node l = {};
				l.text = "ROOT";
				l.additional_info = "can be safely ignored";
				_root_node->self = l;

				//add all neighbors
				for (auto _linked_node : diff) {
					_root_node->neighbors.push_back(_linked_node);
				}

				//add our old root ~if we need~
				_root_node->neighbors.push_back(current_root);

				_data.root = *_root_node;
				delete _root_node;
			}


			//now that we have constructed the linked tree thing we can go ahead and move it into our data, then return
			_data.nodes = all_linked_nodes;

			return _data;
		}
	} node_data;

}


#endif // !NODE_H