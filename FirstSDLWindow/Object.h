#pragma once
#include <SDL_rect.h>

struct Color {
	unsigned char r, g, b, a;	// RGB and alpha for opacity
	Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
	Color& operator= (const Color& in);
};

struct vector {		// 2D collection of X and Y values
	float x = 0;
	float y = 0;
	vector(float x = 0, float y = 0) {
		this->x = x;
		this->y = y;
	}
	vector& operator= (const vector& in) {
		x = in.x;
		y = in.y;
		return *this;
	}
	vector operator+ (const vector& in) {
		return vector(in.x + x, in.y + y);
	}
	vector operator- (const vector& in) {
		return vector(x - in.x, y - in.y);
	}
	vector operator* (const float& in) {
		return vector(x * in, y * in);
	}
	vector operator/ (const vector& in) {
		return vector(x / in.x, y / in.y);
	}
	float dot(const vector& in) {	// Dot product
		return x * in.x + y * in.y;
	}
	float comparitiveDistance(const vector& in) {	// Do not use this if you are looking for the actual distance between two points
		vector diff = *this - in;
		return diff.dot(diff);
	}
};

struct AxisAlignedBoundingBox {
	vector* center;	// Pointer so that we can keep track of the rapidly changing positions
	float radi[2];	// 1/2 of width and length
	SDL_Rect toSDLRect();
	vector min();	// Returns the top-left point
	vector max();	// Returns the bottom-right point
};


class Object {	// I'm making all of this public for ease
public:
	vector pos;
	vector vel;
	vector acc;
	bool isVisible;
	bool isStatic;
	Color color = Color(255, 255, 255, 255);	// Automatically set to white
	size_t id;
	int mass;		// This is probably always going to be 1, but we can change this for fun

	bool isCircle;
	float radius;

	// Tracking when we previously collided
	size_t lastCollisionFrame = 0;
	size_t lastOverlapFrame = 0;

	// Colliders
	AxisAlignedBoundingBox* AABB;

	int createAABB();	// Returns 1 on a successful creation, 0 on failure
	int destroyAABB();	// Returns 1 on a successful deletion
	Object(float x, float y, size_t ident);
	Object(float x, float y, float radius, size_t ident);
};
