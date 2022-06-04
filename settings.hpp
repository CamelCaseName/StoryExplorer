#ifndef SETTINGS_H
#define SETTINGS_H
#include <string>
#include <typeinfo>
#include <map>

namespace n_settings {
	//type enum for our data points in the settigns vector
	typedef enum class type {
		int_type,
		long_type,
		long_long_type,
		double_type,
		float_type,
		string_type,
		bool_type,
		other_type = 100
	}type;

	//container
	class settings_entry {
	private:
		type data_type;
		const void* data;
	public:
		std::string name;

		//converting this to the value we want, only applicable if our type is int, else we throw
		operator int() {
			if (data_type == type::int_type) return *(int*)data;
			else throw std::bad_cast();
		}
		operator long() {
			if (data_type == type::long_type) return *(long*)data;
			else throw std::bad_cast();
		}
		operator long long() {
			if (data_type == type::long_long_type) return *(long long*)data;
			else throw std::bad_cast();
		}
		operator double() {
			if (data_type == type::double_type) return *(double*)data;
			else throw std::bad_cast();
		}
		operator float() {
			if (data_type == type::float_type) return *(float*)data;
			else throw std::bad_cast();
		}
		operator std::string() {
			if (data_type == type::string_type) return *(std::string*)data;
			else throw std::bad_cast();
		}
		operator bool() {
			if (data_type == type::bool_type) return *(bool*)data;
			else throw std::bad_cast();
		}

		//default constructor
		settings_entry() {
			name = "empty";
			data_type = type::other_type;
			data = nullptr;
		}

		//create settings from type we want
		settings_entry(const std::string& _name, int* _data) {
			name = _name;
			data_type = type::int_type;
			data = (void*)_data;
		}
		settings_entry(const std::string& _name, long* _data) {
			name = _name;
			data_type = type::long_type;
			data = (void*)_data;
		}
		settings_entry(const std::string& _name, long long* _data) {
			name = _name;
			data_type = type::long_long_type;
			data = (void*)_data;
		}
		settings_entry(const std::string& _name, double* _data) {
			name = _name;
			data_type = type::double_type;
			data = (void*)_data;
		}
		settings_entry(const std::string& _name, float* _data) {
			name = _name;
			data_type = type::float_type;
			data = (void*)_data;
		}
		settings_entry(const std::string& _name, const std::string& _data) {
			name = _name;
			data_type = type::string_type;
			data = (void*)&_data;
		}
		settings_entry(const std::string& _name, bool* _data) {
			name = _name;
			data_type = type::bool_type;
			data = (void*)_data;
		}
	};

	//map of all settings, private
	namespace { std::map<std::string, settings_entry> settings_map; }
	//retrieveing
	settings_entry get_setting(const std::string& name);
	//setting
	void set_setting(const std::string& name, const settings_entry& setting);

	//saving
	//reading from save
};
#endif // !SETTINGS_H
