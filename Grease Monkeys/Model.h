#pragma once
#include <vector>
#include <fstream>
#include "Updatable.h"

#include "Player.h"

#include "Car.h"
#include "RegularCar.h"
#include "ReverseCar.h"
#include "BrokenWheelCar.h"
#include "NoBrakesCar.h"
#include "Enemy.h"

#include <iostream>
#include <ctime>

class Model
{
public:
	Model();
	~Model();

	Player* player;
	sf::Texture playerTexture;
	sf::Texture* carTextures;
	sf::Texture enemyTexture;
	std::vector<Car*> car;
	std::vector<Enemy*> enemies;
	std::vector<Powerup*> powerups;

	int mapRows, mapCols;
	int* mapData;

	std::vector<Updatable*> updatables;
	void update();
	void reset();
	void chooseCarNumber(sf::Keyboard::Key);
	int carIndex;

	int carOverlappedIndex;
	bool isCarOverlapped();
	float countTime;

	sf::RectangleShape wallLeft, wallRight, wallUp, wallDown;
	//////////////////// 
	void normalize(sf::Vector2f);
	float dot(sf::Vector2f, sf::Vector2f);
	float distance(float, float, float, float);
	void project(sf::Vector2f&, sf::VertexArray, float&, float&);
	bool collision(sf::RectangleShape, sf::RectangleShape);
	bool hitTheWall(sf::RectangleShape);

	sf::VertexArray one;
	sf::VertexArray two;

private:
	void loadTextures();
};