#pragma once
//graphics header, linked as library search record
#pragma warning(push, 0)
#include <d2d1.h>
#pragma comment(lib, "d2d1")
#pragma warning(pop)

namespace n_point {
	//a struct definition for the location of a node, to seperate the node definition from the coordinate systen we use
	typedef struct point {
		float x, y;
		//operator overloading for our point
		struct point& operator+=(const point& rhs) { x += rhs.x; y += rhs.y; return *this; }
		struct point& operator+=(const float& k) { x += k; y += k; return *this; }
		struct point& operator-=(const point& rhs) { x -= rhs.x; y -= rhs.y; return *this; }
		struct point& operator-=(const float& k) { x -= k; y -= k; return *this; }

		operator D2D1_POINT_2F() {
			return D2D1_POINT_2F{ x, y };
		}

		float length() {
			return sqrtf(x * x + y * y);
		}

	} point;

	//operator overloading for our point
	inline point operator+(point lhs, const point& rhs) { return { lhs.x + rhs.x, lhs.y + rhs.y }; }
	inline point operator+(point lhs, const float k) { return { lhs.x + k, lhs.y + k }; }
	inline point operator+(const float k, point rhs) { return { k + rhs.x, k + rhs.y }; }
	inline point operator-(point lhs, const point& rhs) { return { lhs.x - rhs.x, lhs.y - rhs.y }; }
	inline point operator-(point lhs, const float k) { return { lhs.x - k, lhs.y - k }; }
	inline point operator-(const float k, point rhs) { return { k - rhs.x, k - rhs.y }; }
	inline point operator*(point lhs, const float k) { return { lhs.x * k, lhs.y * k }; }
	inline point operator*(const float k, point rhs) { return { k * rhs.x, k * rhs.y }; }
	inline point operator/(point lhs, const float k) { return { lhs.x / k, lhs.y / k }; }
	inline point operator/(const float k, point rhs) { return { k / rhs.x, k / rhs.y }; }

	inline point zero() {
		return { 0.0f, 0.0f };
	}
}
