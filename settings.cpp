#include "settings.hpp"
using namespace n_settings;

void n_settings::add_setting(const string& name, const settings_entry& setting) {
	settings_map[name] = setting;
}

settings_entry n_settings::get_setting(const string& name) {
	return settings_map[name];
}
