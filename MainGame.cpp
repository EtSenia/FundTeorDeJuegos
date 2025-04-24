#include "MainGame.h"

void MainGame::init()
{
	if(SDL_Init(SDL_INIT_AUDIO | SDL_INIT_EVENTS )) {
		std::cout << "SDL_Init succeeded\n";
	}
	else {
		std::cout << "SDL_Init failed: " << SDL_GetError() << "\n";
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	this->window = SDL_CreateWindow("GameName", this->width, this->height, SDL_WINDOW_OPENGL);
	if (!window) {
		SDL_Quit();
	}

	SDL_GLContext glContext = SDL_GL_CreateContext(window);


	GLenum error = glewInit();
	glViewport(0, 0, width, height);
}

void MainGame::processInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_EVENT_QUIT) {
			gameState = GameState::EXIT;
		}

		if (event.type == SDL_EVENT_KEY_DOWN || event.type == SDL_EVENT_KEY_UP) {
		}

		switch (event.type) {
		case SDL_EVENT_MOUSE_MOTION:
			//std::cout << "Posicion x: " << event.motion.x << " Posicion y: " << event.motion.x << "\n";
			break;

		case SDL_EVENT_MOUSE_BUTTON_DOWN:
			std::cout << event.type;
			break;
		}
	}
}

MainGame::MainGame()
{
	width = 1920;
	height = 1080;
	gameState = GameState::MENU;
	window = nullptr;
}

MainGame::~MainGame()
{
}

void MainGame::run()
{


	init();
	glClearColor(1, 0, 0, 1);
	this->s.init(-1, -1, 1, 1);
	update();
}
void MainGame::update()
{
	while (gameState != GameState::EXIT) {
		processInput();
		draw();
	}
}

void MainGame::draw()
{
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	s.draw();

	SDL_GL_SwapWindow(window);
}
