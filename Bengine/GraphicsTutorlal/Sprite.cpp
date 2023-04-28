#include "Sprite.h"

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

	float vertexData[12]; // 6*2 -> 사각형에 두개의 삼각형, x,y좌표

	// first triangle
	vertexData[0] = x + width;
	vertexData[1] = y + height;

	vertexData[2] = x;
	vertexData[3] = y + height;

	vertexData[4] = x;
	vertexData[5] = y;

	// second triangle
	vertexData[6] = x;
	vertexData[7] = y;

	vertexData[8] = x + width ;
	vertexData[9] = y;

	vertexData[10] = x + width;
	vertexData[11] = y + height;

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
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glDrawArrays(GL_TRIANGLES, 0, 6);

	//glDisableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
