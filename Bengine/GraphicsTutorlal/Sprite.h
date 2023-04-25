#ifndef SPRITE_H
#define SPRITE_H

#include <GL/glew.h>
// for 2D
class Sprite 
{
public:
	Sprite();
	~Sprite();

	void Init(float x, float y, float width, float height);

	void Draw();

private:
	float m_x;
	float m_y;
	float m_width;
	float m_height;
	GLuint m_vboID;
};

#endif //SPRITE_H