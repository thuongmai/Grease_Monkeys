#include "Enemy.h"

#include <iostream>
using namespace std;

Enemy::Enemy(sf::Texture* img, Car* Car)
{
	image.setTexture(*img);
	radius = 20;
	float scale = (radius * 2) / img->getSize().y;
	image.setScale(scale, scale);
	image.setOrigin(image.getTexture()->getSize().x / 2, image.getTexture()->getSize().y / 2);

	car = Car;
	car->hasDriver = true;

	destination = sf::Vector2f(0,0);
}

Enemy::~Enemy()
{

}

void Enemy::SetTargetDestination(sf::Vector2f target)
{
	destination = target;
}

void Enemy::update()
{
	//dot/cross product angle
	car->resetKeysPressed();

	//car direction
	sf::Vector2f facing = sf::Vector2f (-cosf((car->rotation+180)*3.14 / 180), -sinf((car->rotation+180)*3.14 / 180)); 
	
	//destination direction
	sf::Vector2f target = sf::Vector2f( destination.x - car->position.x, destination.y - car->position.y);

	//sf::Vector3f crossproduct;
	//crossproduct.x = (target.y*0) - (0*facing.y);
	//crossproduct.y = (0*facing.x) - (target.x*0);
	//crossproduct.z = (target.x*facing.y) - (target.y*facing.x);
	//cout << "Difference: " << (target.x*facing.y) - (target.y*facing.x) << endl;

	//Turn towards destination
	if ((target.x*facing.y) - (target.y*facing.x) > 10)
	{
		car->turnRightPressed = true;
	}
	else if ((target.x*facing.y) - (target.y*facing.x) < -10)
	{
		car->turnLeftPressed = true;
	}
	
	int dX, dY;
	dX = target.x - facing.x;
	dY = target.y - facing.y;
	int mag = sqrt((dX*dX) + (dY*dY));
	if (mag > 10)
	{
		car->forwardPressed = true;
	}

	image.setPosition(sf::Vector2f(car->position.x, car->position.y));
}