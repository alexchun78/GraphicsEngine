#include "MainGame.h"

MainGame::MainGame()
{
	m_window = NULL;
	m_screenWidth = 1024;
	m_screenHeight = 768;
}
MainGame::~MainGame()
{}

void MainGame::Run()
{
	InitSystems();
}

void MainGame::InitSystems()
{
	SDL_Init(SDL_INIT_EVERYTHING);

	m_window = SDL_CreateWindow("Game Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
		m_screenWidth, m_screenHeight, SDL_WINDOW_OPENGL);

}