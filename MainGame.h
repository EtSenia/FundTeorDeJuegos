#pragma once
#include <SDL3/SDL.h>
#include <GL/glew.h>
#include <iostream>
#include "Sprite.h"

enum class GameState {
	PLAY, EXIT, MENU
};

class MainGame {
	unsigned short int width;
	unsigned short int height;
	SDL_Window* window;
	void init();
	void processInput();
	Sprite s;
public:
	MainGame();
	~MainGame();
	GameState gameState;
	void run();
	void update();
	void draw();
};