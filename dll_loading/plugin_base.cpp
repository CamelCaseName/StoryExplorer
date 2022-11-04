#include "plugin_base.hpp"
#include "plugin_base.hpp"

EXPLORERDLL_API plugin_base::plugin_base(void) {}
EXPLORERDLL_API plugin_base::~plugin_base(void) {}
EXPLORERDLL_API	void plugin_base::set_name(const std::wstring& _name) { name = _name; };
EXPLORERDLL_API const std::wstring& plugin_base::get_name(void) { return name; };

