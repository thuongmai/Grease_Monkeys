#pragma once
#include "Updatable.h"
#include "Renderable.h"
#include "GameState.h"

//#include "Player.h"

class Car : public Updatable//, public Renderable
{
public:
	sf::Sprite image;
	sf::RectangleShape sprite;

	sf::Vector2f position;
	sf::Vector2u size;
	float speed, brakes, rotationSpeed;
	double accelerationForward, accelerationReverse;
	float rotation;
	sf::Color carColor;

	bool forwardPressed, reversePressed;
	bool turnRightPressed, turnLeftPressed;

	bool hasDriver;
	//Player* driver;

	Car();
	~Car();

	//void render();
	virtual void update() = 0;
	virtual void reset() = 0;

	Direction carDirection;
	Direction blockDirection;

	void changeCarColour(sf::Texture* color);
	void resetKeysPressed();

	bool isNoBrakesCarHit;
	bool isAcceForward, isAcceBackward;

	int health;
	int shield;
	int damage;
};