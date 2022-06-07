#ifndef POINT_H
#define POINT_H
//graphics header, linked as library search record
#include <d2d1.h>
#pragma comment(lib, "d2d1")

namespace n_point {
	//a struct definition for the location of a node, to seperate the node definition from the coordinate systen we use
	typedef struct point {
		double x, y;
		//operator overloading for our point
		struct point& operator+=(const point& rhs) { x += rhs.x; y += rhs.y; return *this; }
		struct point& operator+=(const double& k) { x += k; y += k; return *this; }
		struct point& operator-=(const point& rhs) { x -= rhs.x; y -= rhs.y; return *this; }
		struct point& operator-=(const double& k) { x -= k; y -= k; return *this; }
	} point;

	//operator overloading for our point
	inline point operator+(point lhs, const point& rhs) { return lhs += rhs; }
	inline point operator+(point lhs, const double k) { return lhs += k; }
	inline point operator+(const double k, point rhs) { return rhs += k; }
	inline point operator-(point lhs, const point& rhs) { return lhs -= rhs; }
	inline point operator-(point lhs, const double k) { return lhs -= k; }
	inline point operator-(const double k, point rhs) { return rhs -= k; }



	namespace n_dpi {
		inline float InitializeDPIScale(HWND hwnd) {
			float dpi = static_cast<float>(GetDpiForWindow(hwnd));
			return dpi / 96.0f;
		}

		inline point PixelsToDipsX(const point& p, float dpi_scale) {
			return { p.x / dpi_scale, p.y / dpi_scale };
		}
	}
}


#endif // !POINT_H
