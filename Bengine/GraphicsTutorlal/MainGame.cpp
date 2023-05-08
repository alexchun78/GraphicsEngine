#include "MainGame.h"
#include "Errors.h"
#include "ImageLoader.h"
#include <iostream>
#include <string>

MainGame::MainGame() : m_screenWidth(1024), m_screenHeight(768), 
m_time(0.0f), m_window(NULL),
m_gameState(GameState::PLAY)
{
	//m_window = NULL;
	//m_screenWidth = 1024;
	//m_screenHeight = 768;
	//m_gameState = GameState::PLAY;
	//m_time = 0.0f;
}

MainGame::~MainGame()
{}

void MainGame::Run()
{
	InitSystems();

	m_sprite.Init(-1.0f, -1.0f, 2.0f, 2.0f);

	m_playerTexture = ImageLoader::loadPNG("Textures/jimmyJump_pack/PNG/CharacterRight_Standing.png");

	GameLoop();
}

void MainGame::InitSystems()
{
	// 1. initialize SDL
	SDL_Init(SDL_INIT_EVERYTHING);

	// 2. open a SDL window 
	m_window = SDL_CreateWindow("Game Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
		m_screenWidth, m_screenHeight, SDL_WINDOW_OPENGL);
	if (m_window == NULL)
	{
		FatalError("SDL Window could not be created!");
	}

	// 3. set up our OpenGLcontext
	SDL_GLContext glContext = SDL_GL_CreateContext(m_window);
	if (glContext == NULL)
	{
		FatalError("SDL_GL Context could not be created!");
	}

	// 4. set up glew --> �̰� �ɼ��̴�. 
	glewExperimental = true; // ��κ��� �ʿ� ������, ���� �̻��� �浹 ���װ� �߻��� �� �ذ�å�̴�.
	GLenum error = glewInit(); // �׷��� �ϵ���� ���� ��������
	if (error != GLEW_OK)
	{
		FatalError("it could not be initialize glew!");
	}

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	glClearColor(0.0f, 0.0f, 1.0f, 1.0);

	// Shader �ʱ�ȭ
	InitShaders();

}

void MainGame::InitShaders()
{
	m_colorProgram.CompileShaders("Shaders/colorShading.vert", "Shaders/colorShading.frag");
	m_colorProgram.AddAttibutes("vertexPosition");
	m_colorProgram.AddAttibutes("vertexColor");
	m_colorProgram.LinkShader();
}

void MainGame::GameLoop()
{
	while (m_gameState != GameState::EXIT)
	{
		ProcessInput();
		m_time += 0.01; 
		DrawGame();
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

void MainGame::DrawGame()
{
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // | �� ���� �ٸ� ��ҵ��� combine ��Ű�� �뵵�̴�. 

	m_colorProgram.Use();

	GLuint timeLocation = m_colorProgram.GetUniformLocation("time");
	glUniform1f(timeLocation, m_time);

	m_sprite.Draw();

	m_colorProgram.UnUse();
	//glEnableClientState(GL_COLOR_ARRAY);
	//glBegin(GL_TRIANGLES);
	//glColor3f(1.0f, 0.0f, 0.0f);
	//glVertex2f(0, 0);
	//glVertex2f(0, 500);
	//glVertex2f(500, 500);
	//glEnd();

	SDL_GL_SwapWindow(m_window);
}