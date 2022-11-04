#pragma once
#define EXPLORERDLL_EXPORT
#include "plugin_common.hpp"
#include "plugin_base.hpp"

extern "C" EXPLORERDLL_API plugin_base * create_plugin(void);
extern "C" EXPLORERDLL_API void delete_plugin(void);

#undef EXPLORERDLL_EXPORT