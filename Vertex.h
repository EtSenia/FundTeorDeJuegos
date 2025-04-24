#pragma once
#include <GL/glew.h>

struct Position {
	float x;
	float y;

	Position(float x, float y) : x(x), y(y) {}
};

struct Color {
	GLubyte r;
	GLubyte g;
	GLubyte b;
	GLubyte a;

	Color(GLubyte r, GLubyte g, GLubyte b, GLubyte a) : r(r), g(g), b(b), a(a) {}
};

struct Vertex
{	
	Position position;
	Color color;
	void setPosition(float x, float y);
	void setColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a);
	Vertex(float _x = 0, float _y = 0, GLubyte r = 0, GLubyte g = 0, GLubyte b = 0, GLubyte a = 255) : position(_x, _y), color(r,g,b,a) {}
};

