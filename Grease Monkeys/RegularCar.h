#pragma once
#include "Car.h"

class RegularCar : public Car
{
public:
	RegularCar(sf::Texture* img);
	RegularCar(float posX, float posY, float speed, float angle, float brakes, sf::Color color);
	~RegularCar();

	void update();
	void reset();
};