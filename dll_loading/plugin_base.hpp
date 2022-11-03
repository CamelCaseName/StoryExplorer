#pragma once
#define EXPLORERDLL_EXPORT

#include "dll_common.h"

class EXPLORERDLL_API plugin_base {
private:
#pragma warning(push)
#pragma warning(disable:4251)
	std::wstring name;
#pragma warning(pop)
public:
	plugin_base(void);
	virtual ~plugin_base(void) = 0;
	inline void set_name(std::wstring& _name) { name = _name; };
	inline std::wstring& get_name(void) { return name; };
};

#undef EXPLORERDLL_EXPORT