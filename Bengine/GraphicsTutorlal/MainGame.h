#ifndef MAINGAME_H
#define MAINGAME_H

#include <SDL/SDL.h>
#include <GL/glew.h>
#include "Sprite.h"

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
	void DrawGame();

private:
	SDL_Window* m_window;
	int m_screenWidth;
	int m_screenHeight;
	GameState m_gameState;

	Sprite m_sprite;
};

#endif //MAINGAME_H