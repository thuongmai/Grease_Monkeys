#include "Updatable.h"
#include "Renderable.h" 
#include "Car.h"
#include "RegularCar.h"

class Enemy : public Updatable//, public Renderable
{
public:
	sf::Sprite image;
	float radius;
	Car* car;
	sf::Vector2f destination;


	Enemy(sf::Texture* img, Car* Car);
	~Enemy();

	void update();
	void SetTargetDestination(sf::Vector2f target);
};