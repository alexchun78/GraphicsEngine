#ifndef MAINGAME_H
#define MAINGAME_H

#include <SDL/SDL.h>
#include <GL/glew.h>

enum class GameState
{
	PLAY,
	EXIT
};

class MainGame
{
public:
	MainGame();
	~MainGame();

	void Run();

private:
	void InitSystems();
	void GameLoop();
	void ProcessInput();

private:
	SDL_Window* m_window;
	int m_screenWidth;
	int m_screenHeight;
	GameState m_gameState;
};

#endif //MAINGAME_H