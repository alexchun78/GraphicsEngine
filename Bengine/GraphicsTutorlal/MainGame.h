#ifndef MAINGAME_H
#define MAINGAME_H

#include <SDL/SDL.h>
#include <GL/glew.h>
class MainGame
{
public:
	MainGame();
	~MainGame();

	void Run();

	void InitSystems();

private:
	SDL_Window* m_window;
	int m_screenWidth;
	int m_screenHeight;
};

#endif //MAINGAME_H