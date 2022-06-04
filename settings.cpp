#include "settings.hpp"
using namespace n_settings;

void n_settings::set_setting(const std::string& name, const settings_entry& setting) {
	settings_map.insert({name, setting});
}

settings_entry n_settings::get_setting(const std::string& name) {
	return settings_map[name];
}
