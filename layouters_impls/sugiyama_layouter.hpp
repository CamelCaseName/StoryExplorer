#pragma once

#define EXPLORERDLL_EXPORT
#include "..\\utils\node.hpp"
#include "..\\dll_loading\plugin_common.hpp"
#include "..\\dll_loading\plugin_exports_common.hpp"
#include "..\\layouter\layouter.hpp"
#include "..\\dll_loading\plugin_base.hpp"

class EXPLORERDLL_API sugiyama_layouter : public layouter {
private:
public:
    sugiyama_layouter();
    ~sugiyama_layouter();
    void do_layout();
};

#undef EXPLORERDLL_EXPORT
