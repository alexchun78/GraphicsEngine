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

struct UV {
	float u;
	float v;
};

typedef struct vertex_tag
{
	union {
		Position _position;
		float _asArray[2];
	};

	union {
		Color _color;
		GLubyte _asColorArray[4];
	};

	union {
		UV _uv;
		float _asUV[2];
	};

	void SetPosition(float x, float y)
	{
		_position.x = x;
		_position.y = y;
	}

	void SetColor(GLubyte r,GLubyte g,GLubyte b,GLubyte a)
	{
		_color.r = r;
		_color.g = g;
		_color.b = b;
		_color.a = a;
	}

	void SetUV(float u,float v)
	{
		_uv.u = u;
		_uv.v = v;
	}
} Vertex;