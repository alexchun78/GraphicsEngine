#include "MainGame.h"
#include "Errors.h"
#include "ImageLoader.h"
#include <iostream>
#include <string>

MainGame::MainGame() : m_screenWidth(1024), m_screenHeight(768), 
m_time(0.0f), m_window(NULL),
m_gameState(GameState::PLAY),
m_maxFps(60.0f)
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

	m_sprites.push_back(new Sprite());
	m_sprites.back()->Init(-1.0f, -1.0f, 1.0f, 1.0f, "Textures/jimmyJump_pack/PNG/CharacterRight_Standing.png");
	m_sprites.push_back(new Sprite());
	m_sprites.back()->Init(0.0f, -1.0f, 1.0f, 1.0f, "Textures/jimmyJump_pack/PNG/CharacterRight_Standing.png");
	m_sprites.push_back(new Sprite());
	m_sprites.back()->Init(-1.0f, 0.0f, 1.0f, 1.0f, "Textures/jimmyJump_pack/PNG/CharacterRight_Standing.png");
	//m_playerTexture = ImageLoader::loadPNG("Textures/jimmyJump_pack/PNG/CharacterRight_Standing.png");

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

	// 4. set up glew --> 이건 옵션이다. 
	glewExperimental = true; // 대부분은 필요 없지만, 가끔 이상한 충돌 버그가 발생할 때 해결책이다.
	GLenum error = glewInit(); // 그래픽 하드웨어 등을 세팅해줌
	if (error != GLEW_OK)
	{
		FatalError("it could not be initialize glew!");
	}

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	glClearColor(0.0f, 0.0f, 1.0f, 1.0);

	// check the opengl version
	std::printf("*** opengl version : %s ***\n", glGetString(GL_VERSION));

	// Set VSYNC : vertical Sync를 켜주는 기능, 기본은 켜져있는 상태임
	SDL_GL_SetSwapInterval(1);

	// Shader 초기화
	InitShaders();

}

void MainGame::InitShaders()
{
	m_colorProgram.CompileShaders("Shaders/colorShading.vert", "Shaders/colorShading.frag");
	m_colorProgram.AddAttibutes("vertexPosition");
	m_colorProgram.AddAttibutes("vertexColor");
	m_colorProgram.AddAttibutes("vertexUV");
	m_colorProgram.LinkShader();
}

void MainGame::GameLoop()
{
	while (m_gameState != GameState::EXIT)
	{
		//float startTicks = SDL_GetTicks();
		ProcessInput();
		m_time += 0.01; 
		DrawGame();
		CalcFPS();

		// print only once every 10 frames
		static int frameCounter = 0;
		frameCounter++;
		if (frameCounter == 10) {
			std::cout << m_fps << std::endl;
			frameCounter = 0;
		}

		float frameTicks = SDL_GetTicks();

		// limit the FPS to the max FPS
		if (1000.0f / m_maxFps > frameTicks) {
			SDL_Delay(1000.0f / m_maxFps - frameTicks);
		}
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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // | 한 개는 다른 요소들을 combine 시키는 용도이다. 

	m_colorProgram.Use();
	glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, m_playerTexture._id); -> resource manager에서 관리
	GLint textureLocation = m_colorProgram.GetUniformLocation("mySampler");
	glUniform1i(textureLocation, 0);

	GLint timeLocation = m_colorProgram.GetUniformLocation("time");
	glUniform1f(timeLocation, m_time);

	for (int i = 0; i < m_sprites.size(); ++i)
	{
		m_sprites[i]->Draw();
	}

	glBindTexture(GL_TEXTURE_2D, 0);

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

void MainGame::CalcFPS() {
	static const int NUM_SAMPLES = 10;
	static float frameTimes[NUM_SAMPLES];
	static int curFrame = 0;

	static float prevTicks = SDL_GetTicks();

	static float curTicks;
	curTicks = SDL_GetTicks();

	m_frameTime = curTicks - prevTicks;
	frameTimes[curFrame % NUM_SAMPLES] = m_frameTime;

	prevTicks = curTicks;

	curFrame++;
	int count;
	if (curFrame < NUM_SAMPLES)
	{
		count = curFrame;
	}
	else {
		count = NUM_SAMPLES;
	}

	float frameTimeAverage = 0;
	for (int i = 0; i < count; i++)
	{
		frameTimeAverage += frameTimes[i];
	}
	frameTimeAverage /= count;

	if (frameTimeAverage != 0) {
		m_fps = 1000 / frameTimeAverage;
	}
	else
	{
		m_fps = 60.0f;
	}
}