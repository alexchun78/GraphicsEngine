#ifndef MAINGAME_H
#define MAINGAME_H

#include <SDL/SDL.h>
#include <GL/glew.h>
#include <vector>
#include "GLSLProgram.h"
#include "GLTexture.h"


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
	void InitShaders();
	void GameLoop();
	void ProcessInput();
	void DrawGame();
	void CalcFPS();


private:
	SDL_Window* m_window;
	int m_screenWidth;
	int m_screenHeight;
	GameState m_gameState;

	GLSLProgram m_colorProgram;
	
	// [NOTE] Sprite�� �����Ͱ� �ƴϸ�, push_back �� ������ �Ҹ��ڰ� �ҷ����� glDeleteBuffer�� ����Ǿ� �����Ͱ� �������. 
	std::vector<Sprite*> m_sprites;
	//Sprite m_sprite;

	float m_fps;
	float m_maxFps;
	float m_frameTime;

	float m_time;
};

#endif //MAINGAME_H