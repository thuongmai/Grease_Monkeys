#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>

#include "Model.h"
#include "Renderable.h"
#include "GameState.h"
#include "Map.h"

class View 
{
public:
	Model* model;
	
	sf::RenderWindow window;
	std::vector<Renderable*> renderables();
	GameState gameState;

	View(Model* m);
	~View();

	void render();
	void scrollScreen();

	sf::Texture pauseButtonTexture;
	sf::RectangleShape playButton, pauseButton, quitButton;

	sf::Font font;
	sf::Text playButtonText, titleText, quitButtonText;

	Map* stage;
	sf::View view;
	sf::Vector2f positionView;

	sf::RectangleShape healthBar;
};