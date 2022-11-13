#pragma once

#define EXPLORERDLL_EXPORT
#include "..\\utils\node.hpp"
#include "..\\dll_loading\plugin_common.hpp"
#include "..\\dll_loading\plugin_exports_common.hpp"
#include "..\\layouter\layouter.hpp"
#include "..\\dll_loading\plugin_base.hpp"

class EXPLORERDLL_API dpcw_layouter : public layouter {
private:
public:
	inline const std::string* get_layout_name_short() { return new std::string("dpcw"); }
	plugin_type get_type();
	dpcw_layouter();
	~dpcw_layouter();
	void do_layout();
};

#undef EXPLORERDLL_EXPORT
