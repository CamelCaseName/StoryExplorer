#include "sugiyama_layouter.hpp"

EXPLORERDLL_API sugiyama_layouter::sugiyama_layouter() {}

EXPLORERDLL_API sugiyama_layouter::~sugiyama_layouter() {}

EXPLORERDLL_API void sugiyama_layouter::do_layout() {

}

EXPLORERDLL_API plugin_type sugiyama_layouter::get_type() { return plugin_type::layouter; };

sugiyama_layouter* instance = NULL;

extern "C" EXPLORERDLL_API plugin_base * create_plugin(void) {
	if (instance == NULL) instance = new sugiyama_layouter();
	return (plugin_base*)instance;
}

extern "C" EXPLORERDLL_API void delete_plugin(void) {
	if (instance != NULL) delete instance;
}