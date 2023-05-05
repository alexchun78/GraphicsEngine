#include "Sprite.h"
#include "Vertex.h"

#include <cstddef>

Sprite::Sprite()
{
	m_vboID = 0;
}

Sprite::~Sprite()
{
	if (m_vboID != 0)
	{
		glDeleteBuffers(1, &m_vboID);
	}
}


void Sprite::Init(float x, float y, float width, float height)
{
	m_x = x;
	m_y = y;
	m_width = width;
	m_height = height;

	if (m_vboID == 0)
	{
		glGenBuffers(1, &m_vboID);
	}

	//float vertexData[12]; // 6*2 -> 사각형에 두개의 삼각형, x,y좌표
	Vertex vertexData[6];

	// first triangle
	vertexData[0]._position.x = x + width;
	vertexData[0]._position.y = y + height;

	vertexData[1]._position.x = x;
	vertexData[1]._position.y = y + height;

	vertexData[2]._position.x = x;
	vertexData[2]._position.y = y;

	// second triangle
	vertexData[3]._position.x = x;
	vertexData[3]._position.y = y;

	vertexData[4]._position.x = x + width ;
	vertexData[4]._position.y = y;

	vertexData[5]._position.x = x + width;
	vertexData[5]._position.y = y + height;

	// color
	for (int i = 0; i < 6; ++i)
	{
		vertexData[i]._color.r = 255;
		vertexData[i]._color.g = 0;
		vertexData[i]._color.b = 255;
		vertexData[i]._color.a = 255;
	}

	vertexData[1]._color.r = 0;
	vertexData[1]._color.g = 0;
	vertexData[1]._color.b = 255;
	vertexData[1]._color.a = 255;


	vertexData[4]._color.r = 0;
	vertexData[4]._color.g = 255;
	vertexData[4]._color.b = 0;
	vertexData[4]._color.a = 255;
	glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Sprite::Draw()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_vboID);

	// vertex attribute 활성화
	//glEnableVertexAttribArray(0);

	// vertex data에서 시작 vertex의 위치를 알려준다.
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex,_position));
	// vertex data에서 시작 color의 위치를 알려준다. -> color는 Normalize를 자동으로 해주기 위해 GL_TRUE로 해준다
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex,_color));

	glDrawArrays(GL_TRIANGLES, 0, 6);

	//glDisableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
