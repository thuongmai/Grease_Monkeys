#include "Model.h"
#include <time.h>
bool circleHit(float x, float y, float c, float x1, float y1, float c1) {
	if (((x - x1)*(x - x1) + (y - y1)*(y - y1)) < ((c + c1)*(c + c1))) {
		return true;
	}
	return false;
}

Model::Model() : one(sf::LinesStrip, 4), two(sf::LinesStrip, 4)
{
	srand(time(0));
	countTime = 0;
	carIndex = 0;

	std::ifstream fileHndl;

	fileHndl.open("Assets/mapData.txt");

	fileHndl >> mapCols;
	fileHndl >> mapRows;

	mapData = new int[mapRows * mapCols];
	for (int i = 0; i < mapRows; i++) {
		for (int j = 0; j < mapCols; j++) {
			fileHndl >> mapData[j + i * mapCols];
		}
	}

	//init textures
	loadTextures();

	//init player and empty cars
	player = new Player(&playerTexture);

	car.push_back(new RegularCar(&carTextures[0]));
	car.push_back(new ReverseCar(&carTextures[1]));
	car.push_back(new BrokenWheelCar(&carTextures[2]));
	car.push_back(new NoBrakesCar(&carTextures[3]));

	enemies.push_back(new Enemy(&enemyTexture, car[0]));

	std::srand(time(0));
	powerups.push_back(new Powerup(Damage, rand() % (mapCols * 32), rand() % (mapRows * 32)));
	powerups.push_back(new Powerup(Shield, rand() % (mapCols * 32), rand() % (mapRows * 32)));
	powerups.push_back(new Powerup(Repair, rand() % (mapCols * 32), rand() % (mapRows * 32)));
	reset();

	//Set up Wall
	wallUp.setPosition(sf::Vector2f(0, 0));
	wallUp.setSize(sf::Vector2f((float)(mapCols * 32), (float)(mapRows * 1)));
	wallLeft.setPosition(sf::Vector2f(0, 0));
	wallLeft.setSize(sf::Vector2f((float)(mapCols * 1), (float)(mapRows * 32)));
	wallDown.setPosition(sf::Vector2f(0, (float)(mapRows * 31)));
	wallDown.setSize(sf::Vector2f((float)(mapCols * 32), (float)(mapRows * 1)));
	wallRight.setPosition(sf::Vector2f((float)(mapCols * 31), 0));
	wallRight.setSize(sf::Vector2f((float)mapCols, (float)mapRows * 32));
}

Model::~Model() {}

void Model::update()
{
	player->update();
	enemies[0]->SetTargetDestination(sf::Vector2f(player->posX, player->posY));
	enemies[0]->update();
	for (int i = 0; i < car.size(); i++)
	{
		car[i]->update();
		if (car[i]->health <= 0) {
			if (carIndex == i) carIndex = 0;
			car.erase(car.begin() + i);
		}
	}

	for (int i = 0; i < powerups.size(); i++)
	{
		if (powerups[i] != 0) {
			powerups[i]->update();
			if (circleHit(player->posX, player->posY, player->radius, powerups[i]->position.x, powerups[i]->position.y, 5.f)) player->inv->add(powerups[i]);
		}
	}

}

void Model::reset()
{
	player->reset();
	/*for (int i = 0; i < car.size(); i++)
	{
		car[i]->reset();
		car[i]->position.x = rand() % (mapCols * 31);
		car[i]->position.y = rand() % (mapRows * 31);
	}*/
	car.clear();

	car.push_back(new RegularCar(&carTextures[0]));
	car.push_back(new ReverseCar(&carTextures[1]));
	car.push_back(new BrokenWheelCar(&carTextures[2]));
	car.push_back(new NoBrakesCar(&carTextures[3]));

	car[0]->position.x = 300;
	car[0]->position.y = 300;

	car[1]->position.x = 500;
	car[1]->position.y = 300;

	car[2]->position.x = 400;
	car[2]->position.y = 500;

	car[3]->position.x = 600;
	car[3]->position.y = 200;

	enemies.clear();
	enemies.push_back(new Enemy(&enemyTexture, car[0]));

	while (isCarOverlapped() && countTime < 50)
	{
		car[carOverlappedIndex]->position.x = rand() % (mapCols * 31);
		car[carOverlappedIndex]->position.y = rand() % (mapRows * 31);
		car[carOverlappedIndex]->update();
		countTime++;
		//std::cout << "---------------Count Time: " << countTime << std::endl;
	}
}

bool Model::isCarOverlapped()
{
	for (int i = 0; i < car.size() - 1; i++) {
		for (int j = i + 1; j < car.size(); j++) {
			//if (car[i]->collide(car[j]))
			if (collision(car[i]->sprite, car[j]->sprite))
			{
				//std::cout << "Car " << i << " [" << car[i]->position.x << " " << car[i]->position.y << " " << car[i]->size.x << " " << car[i]->size.y << " ] "
				//<< " Overlap car " << j << " [" << car[j]->position.x << " " << car[j]->position.y << " " << car[j]->size.x << " " << car[j]->size.y << " ] " << std::endl;
				carOverlappedIndex = j;
				//std::cout << "Reset random position for car " << carOverlappedIndex << std::endl;
				//std::cout << "Distance from Car " << i << " to Player: " << car[i]->distanceToPlayer(player->sprite) << std::endl;
				return true;
			}
			//std::cout << "Car " << i << " [" << car[i]->position.x << " " << car[i]->position.y << " " << car[i]->size.x << " " << car[i]->size.y << " ] "
			//<< " Passed car " << j << " [" << car[j]->position.x << " " << car[j]->position.y << " " << car[j]->size.x << " " << car[j]->size.y << " ] " << std::endl;
			//std::cout << "Distance from Car " << i << " to Player: " << car[i]->distanceToPlayer(player->sprite) << std::endl;
			//std::cout << "Distance from Car " << j << " to Player: " << car[j]->distanceToPlayer(player->sprite) << std::endl;
		}
	}
	return false;
}

bool Model::hitTheWall(sf::RectangleShape player)
{
	if (collision(player, wallUp))
		std::cout << "^^^^ Wall UP" << std::endl;
	if (collision(player, wallDown))
		std::cout << "^^^^ Wall DOWN" << std::endl;
	if (collision(player, wallLeft))
		std::cout << "^^^^ Wall LEFT" << std::endl;
	if (collision(player, wallRight))
		std::cout << "^^^^ Wall RIGHT" << std::endl;

	if (collision(player, wallUp)
		|| collision(player, wallDown)
		|| collision(player, wallLeft)
		|| collision(player, wallRight))
		return true;
	return false;
}

void Model::chooseCarNumber(sf::Keyboard::Key key)
{
	switch (key)
	{
	case sf::Keyboard::Key::Num1:
		carIndex = 0;
		break;
	case sf::Keyboard::Key::Num2:
		carIndex = 1;
		break;
	case sf::Keyboard::Key::Num3:
		carIndex = 2;
		break;
	case sf::Keyboard::Key::Num4:
		carIndex = 3;
		break;
	}
}


void Model::loadTextures()
{
	playerTexture.loadFromFile("Assets/monkey.png");

	carTextures = new sf::Texture[4];
	carTextures[0].loadFromFile("Assets/car_blue_5.png");
	carTextures[1].loadFromFile("Assets/car_black_2.png");
	carTextures[2].loadFromFile("Assets/car_green_1.png");
	carTextures[3].loadFromFile("Assets/car_red_4.png");

	enemyTexture.loadFromFile("Assets/bad_monkey.png");
}


/////////////////////REFERENCE: http://en.sfml-dev.org/forums/index.php?topic=12604.0 /////////////////////////////

void Model::project(sf::Vector2f& axis, sf::VertexArray _rectangle, float& min, float& max)
{
	//sf::Vector2f temp = sf::Vector2f(_rectangle[0].position.x, _rectangle[0].position.y);
	float _dot = dot(axis, _rectangle[0].position);
	min = _dot;
	max = _dot;
	for (int i = 0; i < 4; i++)
	{
		_dot = dot(_rectangle[i].position, axis);

		if (_dot < min)
			min = _dot;
		else if (_dot > max)
			max = _dot;
	}

}
float Model::distance(float minA, float maxA, float minB, float maxB)
{
	if (minB > maxA) return minB - maxA;
	else return minA - maxB;
}
float Model::dot(sf::Vector2f vector1, sf::Vector2f vector2)
{
	return vector1.x * vector2.x + vector1.y * vector2.y;
}
void Model::normalize(sf::Vector2f vector) {
	const float magnitude = sqrt(vector.x * vector.y + vector.y * vector.y);
	if (magnitude == 0)
		return;
	vector.x = vector.x / magnitude;
	vector.y = vector.y / magnitude;
}

bool Model::collision(sf::RectangleShape s1, sf::RectangleShape s2)
{

	sf::Transform transform = s1.getTransform();
	sf::FloatRect rect = s1.getLocalBounds();
	one[0].position = transform.transformPoint(sf::Vector2f(rect.left, rect.top));
	one[1].position = transform.transformPoint(sf::Vector2f(rect.left + rect.width, rect.top));
	one[2].position = transform.transformPoint(sf::Vector2f(rect.left + rect.width, rect.top + rect.height));
	one[3].position = transform.transformPoint(sf::Vector2f(rect.left, rect.top + rect.height));
	for (int i = 0; i < 4; i++)
	{
		one[i].color = sf::Color::Red;
	}

	transform = s2.getTransform();
	rect = s2.getLocalBounds();

	two[0].position = transform.transformPoint(sf::Vector2f(rect.left, rect.top));
	two[1].position = transform.transformPoint(sf::Vector2f(rect.left + rect.width, rect.top));
	two[2].position = transform.transformPoint(sf::Vector2f(rect.left + rect.width, rect.top + rect.height));
	two[3].position = transform.transformPoint(sf::Vector2f(rect.left, rect.top + rect.height));
	for (int i = 0; i < 4; i++)
	{
		one[i].color = sf::Color::Green;
	}

	sf::Vector2f axis;
	float minA;
	float minB;
	float maxA;
	float maxB;


	// Test one
	axis.x = one[1].position.x - one[0].position.x;
	axis.y = one[1].position.y - one[0].position.y;
	normalize(axis);

	project(axis, one, minA, maxA);
	project(axis, two, minB, maxB);

	if (distance(minA, maxA, minB, maxB)>0.f)
		return false;


	// Test two
	axis.x = one[3].position.x - one[0].position.x;
	axis.y = one[3].position.y - one[0].position.y;
	normalize(axis);

	project(axis, one, minA, maxA);
	project(axis, two, minB, maxB);

	if (distance(minA, maxA, minB, maxB)>0.f)
		return false;


	// Test three
	axis.x = two[1].position.x - two[0].position.x;
	axis.y = two[1].position.y - two[0].position.y;
	normalize(axis);

	project(axis, one, minA, maxA);
	project(axis, two, minB, maxB);

	if (distance(minA, maxA, minB, maxB)>0.f)
		return false;


	// Test four
	axis.x = two[3].position.x - two[0].position.x;
	axis.y = two[3].position.y - two[0].position.y;
	normalize(axis);

	project(axis, one, minA, maxA);
	project(axis, two, minB, maxB);

	if (distance(minA, maxA, minB, maxB)>0.f)
		return false;

	return true;
}
