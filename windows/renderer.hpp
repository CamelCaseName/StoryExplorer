#ifndef RENDERER_H
#define RENDERER_H

#define NOMINMAX
#include <Windows.h>
#include <unordered_set>
#include <chrono>
//graphics header, linked as library search record
#include <d2d1.h>
#pragma comment(lib, "d2d1")
//needed for text rendering
#include <dwrite.h>
#include <dwrite_1.h>
#include <dwrite_2.h>
#include <dwrite_3.h>
#pragma comment(lib, "dwrite")
//base widnow stuff
#include "basewin.hpp"

#include "..\\utils\node.hpp"
#include "..\\utils\util.hpp"
using namespace util;
using namespace n_node;
using namespace std;
using namespace std::chrono;

enum class algorithms {
	dpcw //the good thing
};


class main_window : public base_window<main_window> {
private:
	ID2D1Factory* factory;
	IDWriteFactory* text_factory;
	IDWriteTextFormat* text_format;
	D2D1_RECT_F text_rect = {};
	ID2D1HwndRenderTarget* render_target;
	ID2D1SolidColorBrush* node_brush;
	ID2D1SolidColorBrush* text_brush;
	ID2D1SolidColorBrush* edge_brush;
	std::vector<D2D1_ELLIPSE> node_ellipsi;
	node_data nodes = { };
	const float radius = 7.0f;
	float x_offset = 0.0f;
	float y_offset = 0.0f;
	int layout_iterations = 0;
	point offset_mid = {};
	steady_clock::time_point drawing_start_time;
	steady_clock::time_point drawing_stop_time;
	steady_clock::time_point node_layout_start_time;
	steady_clock::time_point node_layout_stop_time;
	microseconds duration;
	char* duration_text = (char*)calloc(100, sizeof(char*));


	void calculate_layout();
	void update_node_ellipsi();
	HRESULT create_graphics_ressources();
	HRESULT create_text_ressources();
	void discard_graphics_ressources();
	void layout_nodes(algorithms algo);
	void do_dpcw_nodes();
	void do_force_directed_layout(const node_data& nodes, int max_iterations = 1);
	void on_paint();
	void draw_debug_text();
	void paint_nodes();
	void paint_edges();
	void resize();

public:

	main_window() : factory(NULL), render_target(NULL), node_brush(NULL) {
	}

	void set_nodes(const node_data& _nodes);
	PCWSTR  class_name() const { return L"Circle Window Class"; }
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

};

#endif // !RENDERER_H