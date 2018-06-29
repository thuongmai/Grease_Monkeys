#include "Controller.h"

Controller::Controller(Model* m, View* v)
{
	this->model = m;
	this->view = v;
}

Controller::~Controller() {}

void Controller::inputs()
{
	sf::Event event;

	while (view->window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			view->window.close();
			break;

		case sf::Event::MouseButtonPressed:
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				if (view->gameState == START)
				{
					//PLAY AND RESUME BUTTON
					if (isMouseClicked(event, view->playButton))
					{
						view->gameState = PLAY;
					}
					//QUIT BUTTON
					if (isMouseClicked(event, view->quitButton))
					{
						view->window.close();
					}
				}

				else if (view->gameState == PLAY)
				{
					//PAUSE BUTTON
					if (isMouseClicked(event, view->pauseButton))
					{
						view->gameState = PAUSE;
					}
					else
					{
						//model->player->destination = static_cast<sf::Vector2f>(sf::Mouse::getPosition(view->window));
						model->player->destination = static_cast<sf::Vector2f>(view->window.mapPixelToCoords((sf::Mouse::getPosition(view->window))));
					}
				}

				else if (view->gameState == PAUSE)
				{
					//PLAY AND RESUME BUTTON
					if (isMouseClicked(event, view->playButton))
					{
						view->gameState = PLAY;
					}
					//QUIT BUTTON
					if (isMouseClicked(event, view->quitButton))
					{
						view->gameState = START;
						model->reset();
					}
				}
			}
			break;

		case sf::Event::KeyPressed:
			if (view->gameState == PLAY)
			{
				//change active car for testing purposes
				model->car[model->carIndex]->resetKeysPressed();
				model->chooseCarNumber(event.key.code);

				if (event.key.code == sf::Keyboard::Key::Space)
					if (view->gameState == PLAY)
					{

						model->car[model->carIndex]->resetKeysPressed();

						//change active car for testing purposes
						model->chooseCarNumber(event.key.code);

						if (event.key.code == sf::Keyboard::Key::Space)
						{
							if (model->player->isInCar)
							{
								model->player->enterCar(false, NULL);
							}
							else
							{
								//see if player can enter car
								int inRange = -1;

								float dX, dY, distance;
								for (int i = 0; i < model->car.size(); i++)
								{
									dX = (model->car[i]->position.x - model->player->posX);
									dY = (model->car[i]->position.y - model->player->posY);

									distance = sqrt((dX*dX) + (dY*dY));

									if (distance < model->car[i]->size.y + model->player->radius)
									{
										inRange = i;
									}
								}

								if (inRange > -1)
								{
									model->player->enterCar(true, model->car[inRange]);
									model->carIndex = inRange;
								}
							}
						}
					}
				break;
			}
		}

		if (view->gameState == PLAY)
		{
			//model->car[model->carIndex]->keyboardHandler(event.key.code);
			//Check for overlapping?
			/*
			if (model->isCarOverlapped())
			{
			model->car[model->carIndex]->blockDirection = model->car[model->carIndex]->carDirection;
			std::cout << "Run Car Overllapped()---" << model->car[model->carIndex]->carDirection << std::endl;
			}
			else
			{
			//model->car[model->carIndex]->blockDirection = NONE;
			std::cout << "--- Vertice top left: " << model->car[model->carIndex]->position.x
			<< ":" << model->car[model->carIndex]->position.y << " " << model->car[model->carIndex]->rotation << std::endl;
			view->testerBallPosition.x = model->car[model->carIndex]->sprite.getPosition().x;
			view->testerBallPosition.y = model->car[model->carIndex]->sprite.getPosition().y;
			view->testerBall.setPosition(sf::Vector2f(view->testerBallPosition.x, view->testerBallPosition.y));
			}*/

			//Keyboard controls are for car
			model->car[model->carIndex]->resetKeysPressed();
			for (int i = 0; i < model->car.size(); i++)
			{
				//model->car[i]->sprite.setOrigin(0, 0);
			}

			//sf::Vector2f transformThis = model->car[model->carIndex]->sprite.getTransform().transformPoint(sf::Vector2f(model->car[model->carIndex]->position.x, model->car[model->carIndex]->position.y));

			//std::cout << "Get Transform: " << transformThis.x << " " << transformThis.y<<std::endl;
			//std::cout << "- " << model->car[model->carIndex]->position.x << " " << model->car[model->carIndex]->position.y << std::endl;

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
			{
				model->car[model->carIndex]->turnLeftPressed = true;
				//model->car[model->carIndex]->keyboardHandler(sf::Keyboard::Key::Left);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
			{
				model->car[model->carIndex]->reversePressed = true;
				if ((model->isCarOverlapped() || model->hitTheWall(model->car[model->carIndex]->sprite)) && model->car[model->carIndex]->blockDirection != FORWARD)
				{
					std::cout << "HIT BACK " << countCollisionTried << std::endl;
					countCollisionTried++;
					model->car[model->carIndex]->blockDirection = REVERSE;
					for (int i = 0; i < model->car.size(); i++) {
						Car* currentCar = model->car[model->carIndex];
						Car* targetCar = model->car[i];
						if (model->collision(currentCar->sprite, targetCar->sprite)) {
							if (currentCar->shield <= 0) {
								model->car[model->carIndex]->health -= model->car[i]->damage;
							}
							if (currentCar->shield > 0) {
								int remainderDamage = targetCar->damage - currentCar->shield;
								currentCar->shield -= targetCar->damage;
								if (remainderDamage > 0)
									currentCar->health -= remainderDamage;
							}
						}
					}
				}
				//model->car[model->carIndex]->keyboardHandler(sf::Keyboard::Key::Down);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
			{
				model->car[model->carIndex]->forwardPressed = true;
				/*
				if (model->isCarOverlapped() && model->car[model->carIndex]->blockDirection != REVERSE)
				{
				std::cout << "HIT" << std::endl;
				model->car[model->carIndex]->blockDirection = FORWARD;
				}*/
				//if (model->car[model->carIndex]->collision(model->car[model->carIndex]->sprite, model->car[1]->sprite))
				if ((model->isCarOverlapped() || model->hitTheWall(model->car[model->carIndex]->sprite)) && model->car[model->carIndex]->blockDirection != REVERSE)
				{
					model->car[model->carIndex]->blockDirection = FORWARD;
					std::cout << "HIT FRONT " << countCollisionTried << std::endl;
					countCollisionTried++;
				}

				//model->car[model->carIndex]->keyboardHandler(sf::Keyboard::Key::Up);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
			{
				model->car[model->carIndex]->turnRightPressed = true;

				//model->car[model->carIndex]->keyboardHandler(sf::Keyboard::Key::Right);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z))
			{
				Powerup* current = model->player->dropItem(Repair);
				if (current != 0) {

					int inRange = -1;

					float dX, dY, distance;
					for (int i = 0; i < model->car.size(); i++)
					{
						dX = (model->car[i]->position.x - current->position.x);
						dY = (model->car[i]->position.y - current->position.y);

						distance = sqrt((dX*dX) + (dY*dY));

						if (distance < model->car[i]->size.y)
						{
							inRange = i;
						}
					}

					if (inRange > -1)
					{
						model->car[inRange]->health = 100;
						for (int i = 0; i < model->powerups.size(); i++) {
							if (&(*current) == &(*(model->powerups[i]))) {
								model->powerups.erase(model->powerups.begin() + i);
							}
						}
					}
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::X))
			{
				Powerup* current = model->player->dropItem(Damage);
				if (current != 0) {

					int inRange = -1;

					float dX, dY, distance;
					for (int i = 0; i < model->car.size(); i++)
					{
						dX = (model->car[i]->position.x - current->position.x);
						dY = (model->car[i]->position.y - current->position.y);

						distance = sqrt((dX*dX) + (dY*dY));

						if (distance < model->car[i]->size.y)
						{
							inRange = i;
						}
					}

					if (inRange > -1)
					{
						model->car[inRange]->damage *= 2;
						for (int i = 0; i < model->powerups.size(); i++) {
							if (&(*current) == &(*(model->powerups[i]))) {
								model->powerups.erase(model->powerups.begin() + i);
							}
						}
					}
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::C))
			{
				Powerup* current = model->player->dropItem(Shield);
				if (current != 0) {
					int inRange = -1;

					float dX, dY, distance;
					for (int i = 0; i < model->car.size(); i++)
					{
						dX = (model->car[i]->position.x - current->position.x);
						dY = (model->car[i]->position.y - current->position.y);

						distance = sqrt((dX*dX) + (dY*dY));

						if (distance < model->car[i]->size.y)
						{
							inRange = i;
						}
					}

					if (inRange > -1)
					{
						model->car[inRange]->shield += 100;
						for (int i = 0; i < model->powerups.size(); i++) {
							if (&(*current) == &(*(model->powerups[i]))) {
								model->powerups.erase(model->powerups.begin() + i);
							}
						}
					}
				}
			}
		}
		//Special checking for NoBrakesCar because it need no ForwardPressed key
		if ((model->car[model->carIndex]->isAcceForward || model->car[model->carIndex]->isAcceBackward) &&
			(model->isCarOverlapped() || model->hitTheWall(model->car[model->carIndex]->sprite)))
		{
			model->car[model->carIndex]->isNoBrakesCarHit = true;
			if (model->car[model->carIndex]->isAcceForward)
				model->car[model->carIndex]->blockDirection = FORWARD;
			else
				model->car[model->carIndex]->blockDirection = REVERSE;
		}
	}
}

bool Controller::isMouseClicked(sf::Event event, sf::RectangleShape button)
{
	if (event.mouseButton.x >= button.getPosition().x && event.mouseButton.x <= (button.getPosition().x + button.getSize().x)
		&& event.mouseButton.y >= button.getPosition().y && event.mouseButton.y <= (button.getPosition().y + button.getSize().y))
		return true;
	return false;
}