#include "command_parser.hpp"


//array of arguments
std::string* command_parser::argv = nullptr;
//amount of arguments
int command_parser::argc = 0;

int command_parser::parse(wchar_t* cmd) {
	//list of strings with the arguments
	wchar_t** argvwch = CommandLineToArgvW(cmd, &argc);

	//do stuff with the arguments
	//rn assume first cmd is a path
	argv = (std::string*)calloc(argc, sizeof(std::string));
	if (argv != nullptr) {
		for (size_t i = 0; i < argc; i++) {
			argv[i] = ws_to_s(std::wstring(argvwch[i]));
		}


		std::ifstream file(argv[0]);
		if (!file.is_open()) {
			std::cout << "File not found" << std::endl;
		}
		//file exists, we can save its location to the settings
	}

	return argc;
}

int command_parser::cleanup() {
	for (size_t i = 0; i < argc; i++) {
		delete& (argv[i]);
	}
	return argc;
}
