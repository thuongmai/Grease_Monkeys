#pragma once
#include "Car.h"

class NoBrakesCar : public Car
{
public:
	NoBrakesCar(sf::Texture* img);
	NoBrakesCar(float posX, float posY, float speed, float angle, float brakes, sf::Color color);
	~NoBrakesCar();

	void update();
	void reset();
};