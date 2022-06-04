#ifndef STORYEXPLORER_H
#define STORYEXPLORER_H

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files
#include <windows.h>
// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <vector>

//cpp headers 
#include "targetver.h"
#include "command_parser.hpp"
#include "eek_parser.hpp"
#include "parser.hpp"


//stuff
#include "resource.h"

std::vector<parser*> parsers;


#endif // !STORYEXPLORER_H
