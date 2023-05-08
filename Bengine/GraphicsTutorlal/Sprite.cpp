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

	//float vertexData[12]; // 6*2 -> �簢���� �ΰ��� �ﰢ��, x,y��ǥ
	Vertex vertexData[6];

	// first triangle
	vertexData[0].SetPosition(x + width, y + height);
	vertexData[0].SetUV(1.0f, 1.0f);
	vertexData[1].SetPosition(x, y + height);
	vertexData[1].SetUV(0.0f, 1.0f);
	vertexData[2].SetPosition(x, y);
	vertexData[2].SetUV(0.0f, 0.0f);

	// second triangle
	vertexData[3].SetPosition(x, y);
	vertexData[3].SetUV(0.0f, 0.0f);
	vertexData[4].SetPosition(x + width, y);
	vertexData[4].SetUV(1.0f, 0.0f);
	vertexData[5].SetPosition(x + width, y + height);
	vertexData[5].SetUV(1.0f, 1.0f);

	// color
	for (int i = 0; i < 6; ++i)
		vertexData[i].SetColor(255, 0, 255, 255);

	vertexData[1].SetColor(0, 0, 255, 255);
	vertexData[4].SetColor(0, 255, 0, 255);

	glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Sprite::Draw()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_vboID);

	// vertex attribute Ȱ��ȭ
	//glEnableVertexAttribArray(0);

	// vertex data���� ���� vertex�� ��ġ�� �˷��ش�.
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex,_position));
	// vertex data���� ���� color�� ��ġ�� �˷��ش�. -> color�� Normalize�� �ڵ����� ���ֱ� ���� GL_TRUE�� ���ش�
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex,_color));
	// vertex data���� ���� UV�� ��ġ�� �˷��ش�.
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, _uv));

	glDrawArrays(GL_TRIANGLES, 0, 6);

	//glDisableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
