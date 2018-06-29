#pragma once
#include <SFML/System.hpp>
#include "Updatable.h"
#include "Renderable.h"

enum PowerType {Repair, Shield, Damage};

class Powerup : public Updatable, public Renderable {
	PowerType type;
	sf::Time duration;
	sf::CircleShape sprite;
public:
	sf::Vector2f position;
	bool isHeld;
	Powerup(PowerType, float, float);
	void update();
	void render();
	PowerType getType();
	sf::CircleShape getShape();
};