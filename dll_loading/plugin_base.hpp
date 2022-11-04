#pragma once
#define EXPLORERDLL_EXPORT

#include "plugin_common.hpp"
#include <string>

enum EXPLORERDLL_API plugin_type {
	none,
	parser,
	layouter,
	other = 100
};

class EXPLORERDLL_API plugin_base {
private:
#pragma warning(push)
#pragma warning(disable:4251)
	std::wstring name;
#pragma warning(pop)
public:
	const plugin_type type;
	plugin_base(void);
	~plugin_base(void);
	void set_name(const std::wstring& _name);
	const std::wstring& get_name(void);
};


#undef EXPLORERDLL_EXPORT