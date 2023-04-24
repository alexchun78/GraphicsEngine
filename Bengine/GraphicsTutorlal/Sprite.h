#ifndef SPRITE_H
#define SPRITE_H

// for 2D
class Sprite 
{
public:
	Sprite();
	~Sprite();

	void Init(int x, int y, int width, int height);
	void Draw();

private:
	int m_x;
	int m_y;
	int m_width;
	int m_height;
};

#endif //SPRITE_H