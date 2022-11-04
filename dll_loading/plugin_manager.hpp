#pragma once

#include "plugin_base.hpp"
#include "plugin_common.hpp"
#include <map>
#include <string>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

class plugin_manager {
public:
    plugin_manager();
    ~plugin_manager();

    plugin_base* load_plugin(const std::wstring& plugin_name);
    void unload_plugin(plugin_base*& plugin);

private:
    typedef std::map<std::wstring, plugin_base*> plugin_map;
    typedef std::map<std::wstring, HMODULE> library_map;

    plugin_map plugins;
    library_map libraries;
};
