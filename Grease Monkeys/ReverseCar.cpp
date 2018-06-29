#include "ReverseCar.h"
#include <iostream>

ReverseCar::ReverseCar(sf::Texture* img)
{
	this->image.setTexture(*img);

	this->position = sf::Vector2f(0.0f, 0.0f);
	this->size.x = 116; //100
	this->size.y = 71;  //50
	this->speed = 10;
	this->rotation = 0;
	this->rotationSpeed = 5;
	this->brakes = 10;
	this->carColor = sf::Color::Blue;
	carDirection = NONE;
	blockDirection = NONE;

	image.setPosition(sf::Vector2f(position.x, position.y));
	//sprite.setFillColor(carColor);
	image.setOrigin(size.x / 2, size.y / 2);
	image.setRotation(rotation);

	sprite = sf::RectangleShape(sf::Vector2f(113, 70)); //Real Size 116, 71
	sprite.setPosition(sf::Vector2f(position.x, position.y));
	sprite.setFillColor(carColor);
	//sprite.setOrigin(sprite.getSize().x / 2, sprite.getSize().y / 2);
	sprite.setOrigin(size.x / 2, size.y / 2);
	sprite.setRotation(rotation);

	//Initliaze Accelerate
	accelerationForward = 0;
	accelerationForward = 0;
	isAcceBackward = isAcceForward = false;

	reset();
}
/*
ReverseCar::ReverseCar(float posX, float posY, float speed, float angle, float brakes, sf::Color color)
{
	this->position = sf::Vector2f(posX, posY);
	this->size.x = 100;
	this->size.y = 50;
	this->speed = speed;
	this->rotation = angle;
	this->rotationSpeed = 5;
	this->brakes = brakes;
	this->carColor = color;
	carDirection = NONE;
	blockDirection = NONE;

	//driver = NULL;
	hasDriver = false;

	this->forwardPressed = false;
	this->reversePressed = false;
	this->turnRightPressed = false;
	this->turnLeftPressed = false;

	sprite.setFillColor(carColor);
	sprite.setPosition(sf::Vector2f(position.x, position.y));
	sprite.setSize(sf::Vector2f(size.x, size.y));
	sprite.setRotation(rotation);
	sprite.setOrigin(sprite.getSize().x / 2, sprite.getSize().y / 2);
}
*/
ReverseCar::~ReverseCar() {}


void ReverseCar::update()
{
	//Updates the rotation of the car
	if (turnRightPressed)
	{
		rotation -= rotationSpeed;// *(deltaTime / 1000);
		if (rotation <= -360)
			rotation = 0;
	}
	if (turnLeftPressed)
	{
		rotation += rotationSpeed;// *(deltaTime / 1000);
		if (rotation >= 360)
			rotation = 0;
	}
	sprite.setRotation(rotation);
	image.setRotation(rotation);
	//Updates the position of the car
	//Note: sinf and cosf work in rads so the rotation is converted to rads here
	if ((forwardPressed && blockDirection != FORWARD) || (this->accelerationForward > 0 && blockDirection != FORWARD && !reversePressed))
	{
		if (blockDirection == REVERSE)
		{
			blockDirection = NONE;
			this->accelerationForward = 1;
		}
		float velocity = (float)(speed * this->accelerationForward);
		position.x += cosf(rotation*3.14 / 180) *velocity; // *(deltaTime / 1000);
		position.y += sinf(rotation*3.14 / 180) *velocity; // *(deltaTime / 1000);
		if (forwardPressed && this->accelerationForward < 1 && !reversePressed)
		{
			this->accelerationForward += 0.04;
			this->accelerationReverse = 0;
			isAcceForward = false;
			isAcceBackward = false;
		}
		else if (this->accelerationForward > 0 && !forwardPressed && !reversePressed)
		{
			this->accelerationForward -= 0.02;
			isAcceForward = true;
			isAcceBackward = false;
		}
	}
	if ((reversePressed && blockDirection != REVERSE) || (this->accelerationReverse > 0 && blockDirection != REVERSE && !forwardPressed))
	{
		if (blockDirection == FORWARD)
		{
			blockDirection = NONE;
			accelerationReverse = 1;
		}
		float velocity = (float)(speed * this->accelerationReverse);
		position.x -= cosf(rotation*3.14 / 180) *velocity;// *(deltaTime / 1000);
		position.y -= sinf(rotation*3.14 / 180) * velocity; // *(deltaTime / 1000);
		if (reversePressed && this->accelerationReverse < 1 && !forwardPressed)
		{
			this->accelerationReverse += 0.04;
			this->accelerationForward = 0;
			isAcceBackward = false;
			isAcceForward = false;
		}
		else if (this->accelerationReverse > 0 && !reversePressed && !forwardPressed)
		{
			this->accelerationReverse -= 0.04;
			isAcceBackward = true;
			isAcceForward = false;
		}
	}

	if (blockDirection == FORWARD)
		accelerationForward = 0;
	if (blockDirection == REVERSE)
		accelerationReverse = 0;

	sprite.setPosition(position.x, position.y);
	image.setPosition(position.x, position.y);
}

void ReverseCar::reset()
{
	//driver = NULL;
	hasDriver = false;
	isAcceBackward = false;
	isAcceForward = false;
	this->accelerationForward = 0;
	this->accelerationReverse = 0;

	speed = 10;
	position.x = 300;
	position.y = 5;

	rotation = 0;

	resetKeysPressed();
}