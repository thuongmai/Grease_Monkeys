#pragma once
#include <SFML/System.hpp>

#include "Updatable.h"
#include "Renderable.h" 
#include "Inventory.h"
#include "Car.h"

class Player : public Updatable//, public Renderable
{
public:
	sf::Sprite image;

	int speed;
	float posX;
	float posY;
	float radius;
	Inventory* inv;

	sf::Vector2f direction;
	sf::Vector2f destination;

	bool isInCar;
	Car* car;

	Player(sf::Texture* img);
	~Player();

	//void render();
	void update();
	void reset();
	void enterCar(bool val, Car* car);
	Powerup* dropItem(PowerType);
	void pickItem(Powerup*);
};