// StoryExplorer.cpp : Defines the entry point for the application.
//

#include "StoryExplorer.hpp"

// Forward declarations of functions included in this code module:
bool startup(wchar_t*);
void cleanup();
node_data debug_data();

std::vector<parser*> parsers;
//global window instance
main_window win;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow) {
	UNREFERENCED_PARAMETER(hPrevInstance);


	//test for commands
	//and prepare first image to be displayed
	startup(lpCmdLine);

	if (!win.create(L"StoryExplorer", WS_OVERLAPPEDWINDOW)) {
		return 0;
	}

	//show window
	ShowWindow(win.window(), nCmdShow);

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


				nodes = debug_data();

				//give the renderer our nodes
				win.set_nodes(nodes);

				return true;
			}
		}
	}

	//catch all return
	return false;
}

node_data debug_data() {
	node* t1 = new node(); t1->position = { 10.0f, 0.0f }; t1->weight = 2; t1->custom_color = {};  t1->text = "text"; t1->additional_info = "additional text";
	node* t2 = new node(); t2->position = { 10.0f, 300.0f }; t2->weight = 5; t2->custom_color = {};   t2->text = ""; t2->additional_info = "";
	node* t3 = new node(); t3->position = { -100.0f, 100.0f }; t3->weight = 1; t3->custom_color = {};  t3->text = "text 3"; t3->additional_info = "";
	node* t4 = new node(); t4->position = { 40.0f, 40.0f }; t4->weight = 7; t4->custom_color = {};  t4->text = "text 4"; t4->additional_info = "";
	node* t5 = new node(); t5->position = { 80.0f, 130.0f }; t5->weight = 9; t5->custom_color = {};  t5->text = "text five"; t5->additional_info = "";
	node* t6 = new node(); t6->position = { 250.0f, 100.0f }; t6->weight = 20; t6->custom_color = {};  t6->text = "text 6"; t6->additional_info = "very long additional text here";
	node* t7 = new node(); t7->position = { 100.0f, -200.0f }; t7->weight = 1; t7->custom_color = {};  t7->text = "text saevaen"; t7->additional_info = "additional text";
	node* t8 = new node(); t8->position = { 0.0f, -140.0f }; t8->weight = 1; t8->custom_color = {};  t8->text = "text we need to test length here also"; t8->additional_info = "additional text";

	edge* e1 = new edge(); e1->node_1 = t1; e1->node_2 = t2; e1->weight = 1; e1->text = "text";
	edge* e2 = new edge(); e2->node_1 = t1; e2->node_2 = t6; e2->weight = 5;
	edge* e3 = new edge(); e3->node_1 = t1; e3->node_2 = t3; e3->weight = 10;
	edge* e4 = new edge(); e4->node_1 = t4; e4->node_2 = t5; e4->weight = 1;
	edge* e5 = new edge(); e5->node_1 = t5; e5->node_2 = t6; e5->weight = 7; e5->text = "longer text on an edge";
	edge* e6 = new edge(); e6->node_1 = t6; e6->node_2 = t4; e6->weight = 29;

	node_data d = node_data();
	std::vector<node*> vecn{ t1, t2, t3, t4, t5, t6, t7, t8 };
	std::vector<edge*> vece{ e1, e2, e3, e4, e5, e6};
	d.edges = vece;
	d.nodes = vecn;

	return d;
}
