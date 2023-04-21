#include "MainGame.h"
#include <iostream>
MainGame::MainGame()
{
	m_window = NULL;
	m_screenWidth = 1024;
	m_screenHeight = 768;
	m_gameState = GameState::PLAY;
}
MainGame::~MainGame()
{}

void MainGame::Run()
{
	InitSystems();
	GameLoop();
}

void MainGame::InitSystems()
{
	SDL_Init(SDL_INIT_EVERYTHING);

	m_window = SDL_CreateWindow("Game Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
		m_screenWidth, m_screenHeight, SDL_WINDOW_OPENGL);

}

void MainGame::GameLoop()
{
	while (m_gameState != GameState::EXIT)
	{
		ProcessInput();
	}
}

void MainGame::ProcessInput()
{
	SDL_Event evnt;

	while (SDL_PollEvent(&evnt)) 
	{
		switch (evnt.type) 
		{
		case SDL_QUIT:
			m_gameState = GameState::EXIT;
			break;
		case SDL_MOUSEMOTION:
			std::cout << evnt.motion.x << " " << evnt.motion.y << std::endl;
		}
	}
}