#pragma once
#include "Model.h"
#include "View.h"
#include "GameState.h"

class Controller 
{
public:
	Model* model;
	View* view;

	Controller(Model*, View*);
	~Controller();

	void inputs();
	bool isMouseClicked(sf::Event event, sf::RectangleShape button);
	int countCollisionTried; //TEST
};