#pragma once
#include <cstdint>
//graphics header, linked as library search record


#pragma warning(push, 0)
#include <d2d1.h>
#pragma comment(lib, "d2d1")
#pragma warning(pop)

#pragma pack(push)
#pragma pack(1)
typedef struct color {
	uint8_t a;
	uint8_t r;
	uint8_t g;
	uint8_t b;

	operator int() {
		//return a << 24 || r << 16 || g << 8 || r;
		return *(int*)this;
	}

	inline color operator=(int num) {
		/*a = (num & (0xff << 24)) >> 24;
		r = (num & (0xff << 16)) >> 16;
		g = (num & (0xff << 8)) >> 8;
		b = num & 0xff;*/
		*(int*)this = num;
		return *this;
	}

	inline operator D2D1_COLOR_F() {
		return { static_cast<float>(r / 255),static_cast<float>(g / 255),static_cast<float>(b / 255),static_cast<float>(a / 255) };
	}

} color;
#pragma pack(pop)
