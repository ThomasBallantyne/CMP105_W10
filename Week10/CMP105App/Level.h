#pragma once

#include <SFML/Graphics.hpp>
#include "Framework/Input.h"
#include "TileMapManager.h"
#include "Player.h"
#include <string>
#include <iostream>


class Level{
public:
	Level(sf::RenderWindow* hwnd, Input* in);
	~Level();

	void handleInput(float dt);
	void update(float dt);
	void render();

private:
	// Default functions for rendering to the screen.
	void beginDraw();
	void endDraw();

	// Default variables for level class.
	sf::RenderWindow* window;
	Input* input;
	TileMapManager tileMapManager;
	Player player;
};