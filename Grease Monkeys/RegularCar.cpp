#include "RegularCar.h"
#include <iostream>

RegularCar::RegularCar(sf::Texture* img)
{
	this->image.setTexture(*img);
	this->position = sf::Vector2f(0.0f, 0.0f);
	this->size.x = 121; //100
	this->size.y = 70; //50
	this->speed = 5;
	this->rotation = 0;
	this->rotationSpeed = 2;
	this->brakes = 10;
	this->carColor = sf::Color::Magenta;
	carDirection = NONE;
	blockDirection = NONE;

	image.setPosition(sf::Vector2f(position.x, position.y));
	//sprite.setFillColor(carColor);
	image.setOrigin(size.x/2, size.y/2);
	image.setRotation(rotation);
	
	sprite = sf::RectangleShape(sf::Vector2f(117, 69)); //Real Size 121, 70
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
RegularCar::RegularCar(float posX, float posY, float speed, float angle, float brakes, sf::Color color)
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
}*/

RegularCar::~RegularCar() {}


void RegularCar::update()
{
	//Updates the rotation of the car
	if (turnRightPressed)
	{
		rotation += rotationSpeed;// *(deltaTime / 1000);
		if (rotation >= 360)
			rotation = 0;
	}
	if (turnLeftPressed)
	{
		rotation -= rotationSpeed;// *(deltaTime / 1000);
		if (rotation <= -360)
			rotation = 0;
	}
	sprite.setRotation(rotation);
	image.setRotation(rotation);
	//Updates the position of the car
	//Note: sinf and cosf work in rads so the rotation is converted to rads here
	//FORWARD
	if ((forwardPressed && blockDirection != FORWARD) || (this->accelerationForward > 0 && blockDirection != FORWARD && !reversePressed))
	{
		if (blockDirection == REVERSE)
		{
			blockDirection = NONE;
			this->accelerationForward = 1;
		}
		float velocity = (float)(speed * this->accelerationForward);
		position.x -= (float)(cosf(rotation*3.14 / 180) *velocity); // *(deltaTime / 1000);
		position.y -= (float)(sinf(rotation*3.14 / 180) *velocity); // *(deltaTime / 1000);
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
	//Revese
	if ((reversePressed && blockDirection != REVERSE) || (this->accelerationReverse > 0 && blockDirection != REVERSE && !forwardPressed))
	{
		if (blockDirection == FORWARD)
		{
			blockDirection = NONE;
			accelerationReverse = 1;
		}
		float velocity = (float)(speed * this->accelerationReverse);
		position.x += (float)(cosf(rotation*3.14 / 180) * velocity);// *(deltaTime / 1000);
		position.y += (float)(sinf(rotation*3.14 / 180) * velocity); // *(deltaTime / 1000);
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

void RegularCar::reset()
{
	//driver = NULL;
	hasDriver = false;
	isAcceBackward = false;
	isAcceForward = false;
	this->accelerationForward = 0;
	this->accelerationReverse = 0;

	speed = 5;
	position.x = 300;
	position.y = 5;

	rotation = 0;
	blockDirection = NONE;
	resetKeysPressed();
}