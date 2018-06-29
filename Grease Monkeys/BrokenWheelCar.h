#pragma once
#include "Car.h"

class BrokenWheelCar : public Car
{
public:
	bool onlyLeft;

	BrokenWheelCar(sf::Texture* img);
	//BrokenWheelCar(float posX, float posY, float speed, float angle, float brakes, sf::Color color);
	~BrokenWheelCar();

	void update();
	void reset();
};