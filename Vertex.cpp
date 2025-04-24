#include "Vertex.h"

void Vertex::setPosition(float x, float y) {
	position = Position(x, y);
}

void Vertex::setColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a) {
	color = Color(r, g, b, a);
}
