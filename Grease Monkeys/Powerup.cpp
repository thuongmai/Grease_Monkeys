#include "Powerup.h"

Powerup::Powerup(PowerType t, float x, float y) {
	type = t;
	sprite = sf::CircleShape(5);
	if (type == Shield) sprite.setFillColor(sf::Color::Blue);
	if (type == Damage) sprite.setFillColor(sf::Color::Red);
	if (type == Repair) sprite.setFillColor(sf::Color::Green);
	position.x = x;
	position.y = y;
	sprite.setPosition(position);
	isHeld = false;
}
void Powerup::update() {
	sprite.setPosition(position);
}
void Powerup::render() {
	//view->window.draw(sprite);
}

sf::CircleShape Powerup::getShape() { return this->sprite; }

PowerType Powerup::getType() { return type; }