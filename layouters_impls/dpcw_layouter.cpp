#include "dpcw_layouter.hpp"

EXPLORERDLL_API dpcw_layouter::dpcw_layouter(void) {
	uses_linked = false;
}

EXPLORERDLL_API plugin_type dpcw_layouter::get_type() { return plugin_type::layouter; };

EXPLORERDLL_API dpcw_layouter::~dpcw_layouter(void) {}

EXPLORERDLL_API void dpcw_layouter::do_layout() {

}

dpcw_layouter* instance;

extern "C" EXPLORERDLL_API plugin_base * create_plugin(void) {
	if (instance == NULL) instance = new dpcw_layouter();
	return (plugin_base*)instance;
}

extern "C" EXPLORERDLL_API void delete_plugin(void) {
	if (instance != NULL) delete instance;
}
