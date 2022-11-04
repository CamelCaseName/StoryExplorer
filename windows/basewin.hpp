#pragma once

template <class DERIVED_TYPE>
class base_window {
public:
	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
		DERIVED_TYPE* pThis = NULL;

		if (uMsg == WM_NCCREATE) {
			CREATESTRUCT* pCreate = (CREATESTRUCT*)lParam;
			pThis = (DERIVED_TYPE*)pCreate->lpCreateParams;
			SetWindowLongPtrW(hwnd, GWLP_USERDATA, (LONG_PTR)pThis);

			pThis->hwnd = hwnd;
		}
		else {
			pThis = (DERIVED_TYPE*)GetWindowLongPtrW(hwnd, GWLP_USERDATA);
		}
		if (pThis) {
			return pThis->HandleMessage(uMsg, wParam, lParam);
		}
		else {
			return DefWindowProcW(hwnd, uMsg, wParam, lParam);
		}
	}

	base_window() : hwnd(NULL) {}

	BOOL create(
		PCWSTR lpWindowName,
		DWORD dwStyle,
		DWORD dwExStyle = 0,
		int x = CW_USEDEFAULT,
		int y = CW_USEDEFAULT,
		int nWidth = CW_USEDEFAULT,
		int nHeight = CW_USEDEFAULT,
		HWND hWndParent = 0,
		HMENU hMenu = 0
	) {
		WNDCLASS wc = { 0 };

		wc.lpfnWndProc = DERIVED_TYPE::WindowProc;
		wc.hInstance = GetModuleHandleW(NULL);
		wc.hIcon = LoadIconW(wc.hInstance, L"StoryExplorer.ico");
		wc.hCursor = LoadCursorW(nullptr, IDC_ARROW);
		wc.lpszClassName = class_name();

		RegisterClassW(&wc);

		hwnd = CreateWindowExW(
			dwExStyle, class_name(), lpWindowName, dwStyle, x, y,
			nWidth, nHeight, hWndParent, hMenu, GetModuleHandleW(NULL), this
		);

		return (hwnd ? TRUE : FALSE);
	}

	HWND window() const { return hwnd; }

protected:

	virtual PCWSTR  class_name() const = 0;
	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) = 0;

	HWND hwnd;
};
