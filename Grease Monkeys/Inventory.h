#pragma once
#include <stdio.h>
#include <vector>
#include "Powerup.h"
#include "Updatable.h"
#include "Renderable.h"

class Inventory : public Updatable, public Renderable {
	std::vector<Powerup*> collection  = std::vector<Powerup*>(3);
	int held = 3;
	sf::Vector2f position;
	sf::Vector2f dimension;
	sf::RectangleShape sprite;

	public:
	Inventory(sf::Vector2f p, sf::Vector2f d);
	sf::RectangleShape getShape();
	Powerup* getPowerup(int);
	void add(Powerup*);
	Powerup* remove(PowerType);
	void update();
	void render();
};