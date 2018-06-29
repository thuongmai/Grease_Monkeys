#include "Inventory.h"

Inventory::Inventory(sf::Vector2f p, sf::Vector2f d) { position = p; dimension = d; sprite.setPosition(position); sprite.setFillColor(sf::Color::Yellow), sprite.setSize(dimension); }

void Inventory::add(Powerup* toAdd) {
	//if (held >= collection.size())
	//	return;
	toAdd->isHeld = true;
	if (toAdd->getType() == Shield) {
		toAdd->position.x = position.x + dimension.x/4;
		toAdd->position.y = position.y;
	}
	if (toAdd->getType() == Damage) {
		toAdd->position.x = position.x + 2*dimension.x/4;
		toAdd->position.y = position.y;
	}
	if (toAdd->getType() == Repair) {
		toAdd->position.x = position.x + 3*dimension.x/4;
		toAdd->position.y = position.y;
	}
	collection[toAdd->getType()] = toAdd;
	//held++;
}

Powerup* Inventory::getPowerup(int i) { return collection[i]; }

Powerup* Inventory::remove(PowerType type) {
	Powerup* toReturn = collection[type];
	collection[type] = 0;
	if(toReturn != 0)
	toReturn->isHeld = false;
	return toReturn;
	//held--;
}

void Inventory::update() {

}

void Inventory::render() {

}

sf::RectangleShape Inventory::getShape() { return this->sprite; }