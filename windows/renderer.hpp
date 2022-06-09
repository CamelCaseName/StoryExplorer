#ifndef RENDERER_H
#define RENDERER_H


#include <Windows.h>
//graphics header, linked as library search record
#include <d2d1.h>
#pragma comment(lib, "d2d1")
#include "basewin.hpp"

#include "..\\utils\node.hpp"
#include "..\\utils\util.hpp"
using namespace util;
using namespace n_node;


class main_window : public base_window<main_window> {
private:
	ID2D1Factory* factory;
	ID2D1HwndRenderTarget* render_target;
	ID2D1SolidColorBrush* node_brush;
	ID2D1SolidColorBrush* edge_brush;
	std::vector<D2D1_ELLIPSE> node_ellipsi;
	node_data nodes = { };
	const float radius = 7.0f;
	float x_offset = 0.0f;
	float y_offset = 0.0f;
	point offset_mid = {};
	

	void    calculate_layout();
	HRESULT create_graphics_ressources();
	void    discard_graphics_ressources();
	void    on_paint();
	void paint_nodes();
	void paint_edges();
	void    resize();

public:

	main_window() : factory(NULL), render_target(NULL), node_brush(NULL) {
	}

	void set_nodes(const node_data& _nodes);
	PCWSTR  class_name() const { return L"Circle Window Class"; }
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

};

#endif // !RENDERER_H