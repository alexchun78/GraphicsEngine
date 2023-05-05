#pragma once
#include <GL/glew.h>
struct Position {
	float x;
	float y;
};

struct Color {
	GLubyte r;
	GLubyte g;
	GLubyte b;
	GLubyte a;
};

typedef struct vertex_tag
{
	union {
		Position _position;
		float _asArray[2];
	};

	union {
		Color _color;
		float _asColorArray[4];
	};
} Vertex;