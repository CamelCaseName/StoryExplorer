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
			hr = render_target->CreateSolidColorBrush(D2D1::ColorF(1.0f, 1.0f, 0), &node_brush);
			hr = render_target->CreateSolidColorBrush(D2D1::ColorF(1.0f, 0, 1.0f), &edge_brush);

			if (SUCCEEDED(hr)) {
				calculate_layout();
			}
		}
	}
	return hr;
}

void main_window::set_nodes(const node_data& _nodes) {
	nodes = _nodes;
	for (auto node : nodes.nodes) {
		node_ellipsi.push_back(D2D1_ELLIPSE{ node->position + offset_mid, radius, radius });
	}
}

void main_window::discard_graphics_ressources() {
	safe_release(&render_target);
	safe_release(&node_brush);
}

void main_window::on_paint() {
	HRESULT hr = create_graphics_ressources();
	if (SUCCEEDED(hr)) {
		PAINTSTRUCT ps;
		BeginPaint(hwnd, &ps);

		render_target->BeginDraw();

		render_target->Clear(D2D1::ColorF(D2D1::ColorF::SkyBlue));

		paint_edges();
		paint_nodes();

		hr = render_target->EndDraw();
		if (FAILED(hr) || hr == D2DERR_RECREATE_TARGET) {
			discard_graphics_ressources();
		}
		EndPaint(hwnd, &ps);
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