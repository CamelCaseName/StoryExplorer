#pragma once

#include <string>
#include <vector>
#include <math.h>
#include "..\\utils\point.hpp"
#include "..\\utils\color.hpp"
#include "..\\utils\node.hpp"

#define EXPLORERDLL_EXPORT
#include "..\\dll_loading\plugin_common.hpp"
#include "..\\dll_loading\plugin_base.hpp"


class EXPLORERDLL_API parser : plugin_base {
private:
public:
	const plugin_type type;
	parser();
	~parser();
	//pure virtual parse method definition to enable inheritance and have the framework still work with the rest
	virtual n_node::node_data parse(const std::string& text) = 0;
	//string with the file extenstion this parser wants to work with. can also be a custom key
	virtual bool is_preferred_extension(const std::string& extension) = 0;
};
 
#undef EXPLORERDLL_EXPORT
