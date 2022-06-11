#include "renderer.hpp"

void main_window::calculate_layout() {
	if (render_target != NULL) {
		D2D1_SIZE_F size = render_target->GetSize();
		x_offset = size.width / 2;
		y_offset = size.height / 2;
		offset_mid = { x_offset, y_offset };

		//update positions

		int i = 0;
		for (auto node : nodes.nodes) {
			node_ellipsi[i++].point = node->position + offset_mid;
		}
	}
}

HRESULT main_window::create_graphics_ressources() {
	HRESULT hr = S_OK;
	if (render_target == NULL) {
		RECT rc;
		GetClientRect(hwnd, &rc);

		D2D1_SIZE_U size = D2D1::SizeU(rc.right, rc.bottom);

		hr = factory->CreateHwndRenderTarget(
			D2D1::RenderTargetProperties(),
			D2D1::HwndRenderTargetProperties(hwnd, size),
			&render_target);

		if (SUCCEEDED(hr)) {
			hr = create_text_ressources();
		}

		if (SUCCEEDED(hr)) {
			hr = render_target->CreateSolidColorBrush(D2D1::ColorF(1.0f, 1.0f, 0), &node_brush);
			hr = render_target->CreateSolidColorBrush(D2D1::ColorF(1.0f, 0, 1.0f), &edge_brush);

		}

		if (SUCCEEDED(hr)) {

			calculate_layout();
		}
	}
	return hr;
}

HRESULT main_window::create_text_ressources() {
	static const wchar_t msc_font_name[] = L"Bahnschrift";
	static const float msc_font_size = 25;
	HRESULT hr;

	// Create a DirectWrite factory.
	hr = DWriteCreateFactory(
		DWRITE_FACTORY_TYPE_SHARED,
		__uuidof(text_factory),
		reinterpret_cast<IUnknown**>(&text_factory)
	);

	if (SUCCEEDED(hr)) {
		// Create a DirectWrite text format object.
		hr = text_factory->CreateTextFormat(
			msc_font_name,
			NULL,
			DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			msc_font_size,
			L"", //locale
			&text_format
		);
	}
	if (SUCCEEDED(hr)) {
		// Center the text horizontally and vertically.
		text_format->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);

		text_format->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
	}

	text_rect.left = 0;
	text_rect.top = 0;
	text_rect.bottom = 80;
	text_rect.right = 300;

	if (SUCCEEDED(hr)) {
		hr = render_target->CreateSolidColorBrush(D2D1::ColorF(0.0f, 0.0f, 0.0f), &text_brush);
	}

	return hr;
}

void main_window::set_nodes(const node_data& _nodes) {
	node_layout_start_time = high_resolution_clock::now();
	nodes = _nodes;

	//do the force directed stuff
	layout_nodes(algorithms::dpcw); //eventually get algo from settings

	for (auto node : nodes.nodes) {
		node_ellipsi.push_back(D2D1_ELLIPSE{ node->position + offset_mid, radius, radius });
	}

	node_layout_stop_time = high_resolution_clock::now();
}

void main_window::layout_nodes(algorithms algo) {
	switch (algo) {
	case algorithms::dpcw:
		do_dpcw_nodes();
		break;
	default:
		break;
	}
}

void main_window::do_dpcw_nodes() {
	float max_edge_weight = 0.0f;
	float min_edge_weight = 0.0f;
	std::vector<std::vector<node*>> clusters;
	std::vector<node*> unconnected_nodes;
	std::vector<float> weights;
	std::unordered_set<node*> nodes_with_edges;
	//get max and min edge weight
	for (auto edge : nodes.edges) {
		max_edge_weight = std::max(max_edge_weight, edge->weight);
		min_edge_weight = std::min(min_edge_weight, edge->weight);
		//save weitghts so we can more easily create a list
		weights.push_back(edge->weight);
		//save ndoes so we can create a cluster of all ndoes not in a cluster yet due to missing edges
		nodes_with_edges.insert(edge->node_1);
		nodes_with_edges.insert(edge->node_2);
	}

	//add all nodes without edges to their own cluster on positon 0
	for (auto node : nodes.nodes) {
		if (nodes_with_edges.count(node) == 0) {
			unconnected_nodes.push_back(node);
		}
	}
	clusters.push_back(unconnected_nodes);

	//assign all ndoes from edges into clusters
	for (auto edge : nodes.edges) {
		if (edge->weight == max_edge_weight) {

		}
	}
}

void main_window::discard_graphics_ressources() {
	safe_release(&render_target);
	safe_release(&node_brush);
}

void main_window::on_paint() {
	drawing_start_time = high_resolution_clock::now();
	HRESULT hr = create_graphics_ressources();
	if (SUCCEEDED(hr)) {
		PAINTSTRUCT ps;
		BeginPaint(hwnd, &ps);

		render_target->BeginDraw();

		render_target->Clear(D2D1::ColorF(D2D1::ColorF::SkyBlue));

		paint_edges();
		paint_nodes();

		draw_debug_text();

		hr = render_target->EndDraw();
		if (FAILED(hr) || hr == D2DERR_RECREATE_TARGET) {
			discard_graphics_ressources();
		}
		EndPaint(hwnd, &ps);
	}
	drawing_stop_time = high_resolution_clock::now();
	duration = duration_cast<microseconds>(drawing_stop_time - drawing_start_time);
}

void main_window::draw_debug_text() {
	if (duration.count() > 0) {
		sprintf_s(
			duration_text, 
			100, 
			"fps: %lli\nframe time: %lli us\nnode layout time: %lli us", 
			(1000000LL / duration.count()), 
			duration.count(), 
			duration_cast<microseconds>(node_layout_stop_time - node_layout_start_time).count());
		std::wstring dt_w = s_to_ws(string(duration_text));
		render_target->DrawTextW(dt_w.c_str(), static_cast<uint32_t>(dt_w.length()), text_format, text_rect, text_brush);
	}
}

void main_window::paint_nodes() {
	int i = 0;
	for (auto node : nodes.nodes) {
		if (static_cast<uint32_t>(node->custom_color)) {
			ID2D1SolidColorBrush* brush_temp;
			render_target->CreateSolidColorBrush(D2D1::ColorF(node->custom_color), &brush_temp);
			if (brush_temp != 0) {
				render_target->FillEllipse(node_ellipsi[i++], brush_temp);
				continue;
			}
		}
		render_target->FillEllipse(node_ellipsi[i++], node_brush);
	}
}

void main_window::paint_edges() {
	for (auto edge : nodes.edges) {
		if (static_cast<uint32_t>(edge->custom_color)) {
			ID2D1SolidColorBrush* brush_temp;
			render_target->CreateSolidColorBrush(D2D1::ColorF(edge->custom_color), &brush_temp);
			if (brush_temp != 0) {
				render_target->DrawLine(edge->node_1->position + offset_mid, edge->node_2->position + offset_mid, brush_temp);
				continue;
			}
		}
		render_target->DrawLine(edge->node_1->position + offset_mid, edge->node_2->position + offset_mid, edge_brush, 2.0f);
	}
}

void main_window::resize() {
	if (render_target != NULL) {
		RECT rc;
		GetClientRect(hwnd, &rc);

		D2D1_SIZE_U size = D2D1::SizeU(rc.right, rc.bottom);

		render_target->Resize(size);
		calculate_layout();
		InvalidateRect(hwnd, NULL, FALSE);
	}
}

LRESULT main_window::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_CREATE:
		if (FAILED(D2D1CreateFactory(
			D2D1_FACTORY_TYPE_SINGLE_THREADED, &factory))) {
			return -1;  // Fail CreateWindowEx.
		}
		//init dpi
		dpi_scale::initialize_dpi_for_window(hwnd);
		return 0;

	case WM_DESTROY:
		discard_graphics_ressources();
		safe_release(&factory);
		PostQuitMessage(0);
		return 0;

	case WM_PAINT:
		on_paint();
		return 0;

	case WM_SIZE:
		resize();
		return 0;
	}
	return DefWindowProcW(hwnd, uMsg, wParam, lParam);
}

//ahhh headers are fun. keep this somewhere in a cpp file, not a header
float dpi_scale::scale = 1.0f;