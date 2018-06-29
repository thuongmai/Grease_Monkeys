#include "Player.h"
#include <cmath>
#include <iostream>
using namespace std;

Player::Player(sf::Texture* img)
{
	radius = 20;

	image.setTexture(*img);
	float scale = (radius*2)/img->getSize().y;
	image.setScale(scale, scale);

	inv = new Inventory(sf::Vector2f(800 - 50, 600 - 10), sf::Vector2f(50, 10));
	
	//Set origin to center of sprite
	image.setOrigin(image.getTexture()->getSize().x/2, image.getTexture()->getSize().y / 2);

	reset();
}

Player::~Player() {}

/*
void Player::render()
{

}
*/

//TODO add delta time probably
void Player::update()
{
	if (isInCar)
	{
		posX = car->position.x;
		posY = car->position.y;
	}
	else
	{
		direction.x = destination.x - posX;
		direction.y = destination.y - posY;

		float magnitude = sqrt(pow(direction.x, 2) + pow(direction.y, 2));

		if (magnitude > 5)
		{
			direction.x = direction.x / magnitude;
			direction.y = direction.y / magnitude;

			posX += direction.x * speed;
			posY += direction.y * speed;
		}
	}
	image.setPosition(posX, posY);
}

void Player::enterCar(bool val, Car* Car)
{
	isInCar = val;

	if (!isInCar) //leave car
	{
		car->hasDriver = false;

	    posX -= sinf(car->rotation*3.14 / 180) * ((car->size.x/2) + radius); 
		posY += cosf(car->rotation*3.14 / 180) * ((car->size.y/2) + radius); 
		destination = sf::Vector2f(posX, posY);
	}
	else
	{
		Car->hasDriver = true;
	}

	car = Car;
}

void Player::reset()
{
	isInCar = false;
	car = NULL;

	speed = 5;
	posX = 50;
	posY = 150;
	destination = sf::Vector2f(posX, posY);
	direction = sf::Vector2f(0.0f, 0.0f);
}

Powerup* Player::dropItem(PowerType toDrop) {
	Powerup* dropped = inv->remove(toDrop);
	if (dropped != 0) {
		dropped->position.x = posX;
		dropped->position.y = posY - 25;
	}
	return dropped;
}

void Player::pickItem(Powerup* toPick) {
	inv->add(toPick);
}