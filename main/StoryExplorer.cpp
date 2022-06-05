// StoryExplorer.cpp : Defines the entry point for the application.
//

#include "StoryExplorer.hpp"

// Forward declarations of functions included in this code module:
bool startup(wchar_t*);
void cleanup();
void display();
std::vector<parser*> parsers;
//global window instance
MainWindow win;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow) {
	UNREFERENCED_PARAMETER(hPrevInstance);


	//test for commands
	//and prepare first image to be displayed
	startup(lpCmdLine);

	if (!win.Create(L"StoryExplorer", WS_OVERLAPPEDWINDOW)) {
		return 0;
	}

	//show window
	ShowWindow(win.Window(), nCmdShow);

	MSG msg = {};
	// Main message loop:
	while (GetMessageW(&msg, nullptr, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}

	//remove and clean all the stuff we put in memory
	cleanup();

	//return (0 or error number/interrupt)
	return (int)msg.wParam;
}

void cleanup() {
	cmd_cleanup();
	
}

bool startup(wchar_t* cmd_line) {
	//create instances of the file parsers we have so far
	parsers.push_back((parser*)(new eek_parser()));

	if (parse(cmd_line)) {

		string file_extension = extension(get_setting("path"));

		//find fitting parser
		for (auto p : parsers) {
			if (p->preferred_extension(file_extension)) {
				//read in file
				string text = read_file_to_string(get_setting("path"));
				//do the parsing
				node_data nodes = p->parse(text);

				return true;
			}
		}
	}

	//catch all return
	return false;
}
