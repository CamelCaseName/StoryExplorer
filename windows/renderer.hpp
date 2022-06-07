#ifndef RENDERER_H
#define RENDERER_H


#include <Windows.h>
//graphics header, linked as library search record
#include <d2d1.h>
#pragma comment(lib, "d2d1")
#include "basewin.hpp"

#include "..\\utils\util.hpp"
using namespace util;

class MainWindow : public BaseWindow<MainWindow> {
	ID2D1Factory* pFactory;
	ID2D1HwndRenderTarget* pRenderTarget;
	ID2D1SolidColorBrush* pBrush;
	D2D1_ELLIPSE ellipse = {};

	void    CalculateLayout();
	HRESULT CreateGraphicsResources();
	void    DiscardGraphicsResources();
	void    OnPaint();
	void    Resize();

public:

	MainWindow() : pFactory(NULL), pRenderTarget(NULL), pBrush(NULL) {
	}

	PCWSTR  ClassName() const { return L"Circle Window Class"; }
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

};

#endif // !RENDERER_H