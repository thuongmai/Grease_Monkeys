#include "Car.h"
#include <iostream>

Car::Car()
{
	this->position = sf::Vector2f(0.0f, 0.0f);
	this->size = sf::Vector2u(100, 50);
	this->speed = 5;
	this->rotation = 0;
	this->rotationSpeed = 5;
	this->brakes = 10;
	carDirection = NONE;
	blockDirection = NONE;

	sprite = sf::RectangleShape(sf::Vector2f(size.x, size.y));
	sprite.setPosition(sf::Vector2f(position.x, position.y));
	sprite.setFillColor(carColor);
	sprite.setOrigin(sprite.getSize().x / 2, sprite.getSize().y / 2);
	sprite.setRotation(rotation);

	image.setPosition(sf::Vector2f(position.x, position.y));

	image.setOrigin(size.x / 2, size.y / 2);
	image.setRotation(rotation);

	//driver = NULL;
	hasDriver = false;

	speed = 5;
	position.x = 300;
	position.y = 5;

	isNoBrakesCarHit = false;
	resetKeysPressed();
	damage = 2;
	health = 100;
	shield = 0;
}

Car::~Car() {}

//Can be used to change the car's colour
void Car::changeCarColour(sf::Texture* color)
{
	this->image.setTexture(*color);
}

void Car::resetKeysPressed()
{
	this->forwardPressed = false;
	this->reversePressed = false;
	this->turnRightPressed = false;
	this->turnLeftPressed = false;
}