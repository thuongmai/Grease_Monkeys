#pragma once
#include "Car.h"

class ReverseCar : public Car
{
public:
	ReverseCar(sf::Texture* img);
	ReverseCar(float posX, float posY, float speed, float angle, float brakes, sf::Color color);
	~ReverseCar();

	void update();
	void reset();
};