#ifndef STORYEXPLORER_H
#define STORYEXPLORER_H

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files
#pragma warning(push, 0)
#include <windows.h>
//graphics header, linked as library search record
#include <d2d1.h>
#pragma comment(lib, "d2d1")
#pragma warning(pop)
// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <vector>


//define to get rid of the deprecationw arning as there is no suitable alternative, even in c++20
#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING //doesnt work but whatever, standard says so. will also disable warning 4996 for the codecvt lib

//cpp headers 
#include "..\\targetver.h"
#include "..\\cmd_parser\command_parser.hpp"
#include "..\\windows\renderer.hpp"
#include "..\\settings\settings.hpp"
#include "..\\utils\util.hpp"
#include "..\\dll_loading\plugin_manager.hpp"
#include "..\\layouter\layouter.hpp"
#include "..\\parser\parser.hpp"


using namespace command_parser;
using namespace n_settings;
using namespace util;
using std::string;


#endif // !STORYEXPLORER_H
