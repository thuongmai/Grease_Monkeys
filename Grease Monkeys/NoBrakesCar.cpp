#include "NoBrakesCar.h"
#include <iostream>

NoBrakesCar::NoBrakesCar(sf::Texture* img)
{
	this->image.setTexture(*img);
	this->position = sf::Vector2f(0.0f, 0.0f);
	this->size.x = 131; //100
	this->size.y = 70;  //50
	this->speed = 15;
	this->rotation = 0;
	this->rotationSpeed = 10;
	this->brakes = 10;
	this->carColor = sf::Color::Red;
	carDirection = NONE;
	blockDirection = NONE;

	image.setPosition(sf::Vector2f(position.x, position.y));
	image.setScale(1, 1);
	image.setOrigin(size.x / 2, size.y / 2);
	image.setRotation(rotation);

	sprite = sf::RectangleShape(sf::Vector2f(130, 68)); //Real Size (131, 70)
	sprite.setPosition(sf::Vector2f(position.x, position.y));
	sprite.setFillColor(sf::Color::Transparent);
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
NoBrakesCar::NoBrakesCar(float posX, float posY, float speed, float angle, float brakes, sf::Color color)
{
	this->position = sf::Vector2f(posX, posY);
	this->size.x = 100;
	this->size.y = 50;
	this->speed = speed;
	this->rotation = angle;
	this->rotationSpeed = 7;
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
NoBrakesCar::~NoBrakesCar() {}


void NoBrakesCar::update()
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
	if ((forwardPressed || hasDriver) && blockDirection != FORWARD && !reversePressed && !isNoBrakesCarHit)
	{
		isAcceForward = true;
		if (blockDirection == REVERSE)
			blockDirection = NONE;
		float velocity = (float)(speed * this->accelerationForward);
		position.x -= cosf(rotation*3.14 / 180) *velocity; // *(deltaTime / 1000);
		position.y -= sinf(rotation*3.14 / 180) *velocity; // *(deltaTime / 1000);
		if (this->accelerationForward < 1)
			this->accelerationForward += 0.02;
	}
	if (reversePressed && blockDirection != REVERSE)
	{
		//No reversing?
		std::cout << "**************************************** "<< std::endl;
		isAcceForward = false;
		if (blockDirection == FORWARD)
			blockDirection = NONE;
		accelerationForward = 0;
		isNoBrakesCarHit = false;
		position.x += cosf(rotation*3.14 / 180) *speed;// *(deltaTime / 1000);
		position.y += sinf(rotation*3.14 / 180) * speed; // *(deltaTime / 1000);
	}
		
	sprite.setPosition(position.x, position.y);
	image.setPosition(position.x, position.y);
}

void NoBrakesCar::reset()
{
	//driver = NULL;
	hasDriver = false;
	isAcceBackward = false;
	isAcceForward = false;
	this->accelerationForward = 0;
	this->accelerationReverse = 0;
	speed = 15;
	rotationSpeed = 10;
	position.x = 300;
	position.y = 5;

	rotation = 0;
	isNoBrakesCarHit = false;
	resetKeysPressed();
}