#include "plugin_manager.hpp"
#include <iostream>

// Define the prototype for a function that should exist in the plugin

// that is used to create and return the plugin type in the plugin.
typedef plugin_base* (*create_plugin_t)(void);

// Destroys the plugin type from the plugin before the library is unloaded.
typedef void (*destroy_plugin_t)(void);

plugin_manager::plugin_manager() {}

plugin_manager::~plugin_manager() {}

plugin_base* plugin_manager::load_plugin(const std::wstring& plugin_name) {
    plugin_base* plugin = NULL;
    plugin_map::iterator iter = plugins.find(plugin_name);
    if (iter == plugins.end())
    {
        // Try to load the plugin library
        HMODULE h_module = LoadLibraryW(plugin_name.c_str());
        if (h_module != NULL)
        {
            create_plugin_t create_plugin = (create_plugin_t)GetProcAddress(h_module, "create_plugin");
            if (create_plugin != NULL)
            {
                // Invoke the function to get the plugin from the DLL.
                plugin = create_plugin();
                if (plugin != NULL)
                {
                    plugin->set_name(plugin_name);
                    // Add the plugin and library to the maps.
                    plugins.insert(plugin_map::value_type(plugin_name, plugin));
                    libraries.insert(library_map::value_type(plugin_name, h_module));
                }
                else
                {
                    std::wcerr << "ERROR: Could not load plugin from " << plugin_name << std::endl;
                    // Unload the library.
                    FreeLibrary(h_module);
                }
            }
            else
            {
                std::wcerr << "ERROR: Could not find symbol \"create_plugin\" in " << plugin_name << std::endl;
                FreeLibrary(h_module);
            }
        }
        else
        {
            std::wcerr << "ERROR: Could not load library: " << plugin_name << std::endl;
        }
    }
    else
    {
        std::wcout << "INFO: Library \"" << plugin_name << "\" already loaded." << std::endl;
        plugin = iter->second;
    }
    return plugin;
}

void plugin_manager::unload_plugin(plugin_base*& plugin) {
    if (plugin != NULL)
    {
        library_map::iterator iter = libraries.find(plugin->get_name());
        if (iter != libraries.end())
        {
            // Remove the plugin from our plugin map.
            plugins.erase(plugin->get_name());
            HMODULE h_module = iter->second;
            destroy_plugin_t destroy_plugin = (destroy_plugin_t)GetProcAddress(h_module, "destroy_plugin");
            if (destroy_plugin != NULL)
            {
                destroy_plugin();
            }
            else
            {
                std::wcerr << "ERROR: Unable to find symbol \"destroy_plugin\" in library \"" << plugin->get_name() << std::endl;
            }
            // Unload the library and remove the library from the map.
            FreeLibrary(h_module);
            libraries.erase(iter);
        }
        else
        {
            std::cout << "WARNING: Trying to unload a plugin that is already unloaded or has never been loaded." << std::endl;
        }
        // NULL the plugin
        plugin = NULL;
    }
}
