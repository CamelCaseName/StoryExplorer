#ifndef CMDPARSE_H
#define CMDPARSE_H


//cpp headers i think
#include <Windows.h>
#include <vector>
#include <shellapi.h>
#include <fstream>
#include <iostream>
#include <string>
using std::string;
#include "util.hpp"
#include "settings.hpp"
//#include "libs/simdjson.h"

namespace command_parser {
	//method for parsing cmd arguments into our settings
	int parse(wchar_t* cmd);
	int cmd_cleanup();

	//array of arguments
	extern string* argv;
	//amount of arguments
	extern int argc;
};

#endif // !CMDPARSE_H

