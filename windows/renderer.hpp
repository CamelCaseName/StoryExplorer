#ifndef RENDERER_H
#define RENDERER_H

#define NOMINMAX
#include <Windows.h>
//set for some aspects of the dpcw
#include <unordered_set>
//stopwatch functions
#include <chrono>
//timer classes
#include <thread>
//#include <agents.h> //cant get it to work
//graphics header, linked as library search record
#include <d2d1.h>
#pragma comment(lib, "d2d1")
//needed for text rendering
#include <dwrite.h>
#include <dwrite_1.h>
#include <dwrite_2.h>
#include <dwrite_3.h>
#pragma comment(lib, "dwrite")
//basic widnow stuff
#include "basewin.hpp"

#include "..\\utils\node.hpp"
#include "..\\utils\util.hpp"
#include "../layouter/layouter.hpp"
using namespace util;
using namespace n_node;
using namespace std;
using namespace std::chrono;

#pragma warning(push)
#pragma warning(disable:4455) //disable operator literal suffix warning, THE ENDINGS FUCKING ARE IN THE STD NAMESPACE; HOW MORE RESERVED CAN THEY BE
using std::chrono::operator""s;
using std::chrono::operator""ms;
using std::chrono::operator""us;
using std::chrono::operator""ns;
constexpr int debug_buffer_size = 1000;

typedef std::unordered_map<linked_node*, int>& layer_map;
typedef std::unordered_map<linked_node*, int> layer_map_i;

enum class algorithms {
	dpcw, //the good thing
	sugiyama, //layered graph
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
	node_data nodes = { }; //"flat" representation
	linked_node_data linked_nodes = { }; //"blown up" representation with a complete tree 
	const float radius = 7.0f;
	const milliseconds target_frame_time_ms = 10ms;
	const algorithms current_algorithm = algorithms::dpcw;
	float x_offset = 0.0f;
	float y_offset = 0.0f;
	int layout_iterations = 0;
	point offset_mid = {};
	steady_clock::time_point drawing_start_time;
	steady_clock::time_point drawing_stop_time;
	steady_clock::time_point node_layout_start_time;
	steady_clock::time_point node_layout_stop_time;
	std::wstring debug_text;
	microseconds duration;
	bool nodes_updated_main = false;
	bool force_update = true;//used for fixed 30/60fps updating of the graph
	char* duration_text = (char*)calloc(debug_buffer_size, sizeof(char*));
	thread fps_update;
	thread node_layout_update;
	class layouter* current_layouter = nullptr;
	std::vector<class layouter*> layouter_impls;

	void calculate_layout();
	void update_node_ellipsi();
	HRESULT create_graphics_ressources();
	HRESULT create_text_ressources();
	void discard_graphics_ressources();
	void layout_nodes(algorithms algo);
	void do_dpcw_nodes();
	void do_sugiyama_nodes();
	void on_paint();
	void draw_debug_text();
	void paint_nodes();
	void paint_edges();
	void thread_master();
	void resize(); 
	void sugiyama_extend_links(linked_node_data& linked_nodes, layer_map layers);
	int sugiyama_edge_span(linked_node_edge* _edge, layer_map _layers);
	void do_force_directed_layout(const node_data& data, int max_iterations);
	int sugiyama_edge_span(linked_node* _node1, linked_node* _node2, layer_map _layers);
	void sugiyama_set_layer(layer_map _layers, linked_node* node, int _layer_index);
	linked_node* sugiyama_insert_dummy_vertices(linked_node* goal, int edge_span, layer_map _layers);

public:

	main_window() : factory(NULL), render_target(NULL), node_brush(NULL) {
	}

	//todo move impls to their respective dll and simplify interface here
	void fps_updater(milliseconds target_frametime);
	void node_layout_updater(milliseconds target_frametime);
	bool nodes_updated() { return nodes_updated_main; }
	void set_nodes(const node_data& _nodes);
	void layout_nodes();
	inline void set_layouters(const std::vector<class layouter*> _layouters) { layouter_impls = _layouters; }
	PCWSTR  class_name() const { return L"Story Explorer Window Class"; }
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

};

#pragma warning(pop)
#endif // !RENDERER_H