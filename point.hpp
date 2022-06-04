#ifndef POINT_H
#define POINT_H


//a struct definition for the location of a node, to seperate the node definition from the coordinate systen we use
typedef struct point {
	double x, y;
	//operator overloading for our point
	struct point& operator+=(const point& rhs) { x += rhs.x; y += rhs.y; return *this; }
	struct point& operator+=(const double& k) { x += k; y += k; return *this; }
	struct point& operator-=(const point& rhs) { x -= rhs.x; y -= rhs.y; return *this; }
	struct point& operator-=(const double& k) { x -= k; y -= k; return *this; }
}point;

//operator overloading for our point
point operator+(point lhs, const point& rhs) { return lhs += rhs; }
point operator+(point lhs, const double k) { return lhs += k; }
point operator+(const double k, point rhs) { return rhs += k; }
point operator-(point lhs, const point& rhs) { return lhs -= rhs; }
point operator-(point lhs, const double k) { return lhs -= k; }
point operator-(const double k, point rhs) { return rhs -= k; }

#endif // !POINT_H
