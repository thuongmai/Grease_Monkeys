#include "View.h"

View::View(Model* m)
{
	this->model = m;

	//WINDOW
	window.create(sf::VideoMode(800, 600), "Grease Monkeys");
	window.setFramerateLimit(30);
	stage = new Map("Assets/map_tileset.png", sf::Vector2u(32, 32), model->mapData, model->mapCols, model->mapRows);

	//Set HealthBar
	healthBar.setSize(sf::Vector2f(0, 0));
	healthBar.setPosition(window.getSize().x - 105, 5);
	healthBar.setFillColor(sf::Color::Yellow);

	//Set View
	view.reset(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));
	view.setViewport(sf::FloatRect(0, 0, 1.f, 1.f));

	positionView.x = window.getSize().x / 2;
	positionView.y = window.getSize().y / 2;
	window.setView(view);

	//PLAY BUTTON
	playButton.setSize(sf::Vector2f(300, 100));
	playButton.setPosition(window.getSize().x / 2 - playButton.getSize().x / 2, window.getSize().y / 2);
	playButton.setFillColor(sf::Color::Blue);
	playButton.setOutlineColor(sf::Color::Yellow);

	//QUIT BUTTON
	quitButton.setSize(sf::Vector2f(playButton.getSize().x, playButton.getSize().y));
	quitButton.setPosition(playButton.getPosition().x, playButton.getPosition().y + playButton.getSize().y + 50);
	quitButton.setFillColor(playButton.getFillColor());
	quitButton.setOutlineColor(playButton.getOutlineColor());

	//PAUSE BUTTON
	pauseButton.setSize(sf::Vector2f(50, 50));
	pauseButton.setPosition(5, 5);
	if (!pauseButtonTexture.loadFromFile("Assets/pauseButton.png"))
	{
		std::cout << "Cannot load the pause button";
	}
	pauseButton.setTexture(&pauseButtonTexture);

	//FONT AND TEXT
	if (!font.loadFromFile("Assets/RAVIE.TTF"))
	{
		std::cout << "Cannot load the font";
	}
	playButtonText.setFont(font);
	playButtonText.setString("PLAY");
	playButtonText.setColor(sf::Color::Yellow);
	playButtonText.setCharacterSize(55);
	playButtonText.setPosition((playButton.getPosition().x * 2 + playButton.getSize().x) / 2 - playButton.getSize().x / 3,
		(playButton.getPosition().y * 2 + playButton.getSize().y) / 2 - playButton.getSize().y / 3);

	titleText.setFont(font);
	titleText.setString("GREASE MONKEY");
	titleText.setCharacterSize(60);
	titleText.setColor(sf::Color::Yellow);
	titleText.setPosition(45,
		(playButton.getPosition().y / 2 + playButton.getSize().y) / 2);
	titleText.setScale(1.0f, 1.2f);

	quitButtonText.setFont(font);
	quitButtonText.setString("QUIT");
	quitButtonText.setColor(sf::Color::Yellow);
	quitButtonText.setCharacterSize(55);
	quitButtonText.setPosition((quitButton.getPosition().x * 2 + quitButton.getSize().x) / 2 - quitButton.getSize().x / 3,
		(quitButton.getPosition().y * 2 + quitButton.getSize().y) / 2 - quitButton.getSize().y / 3);

	gameState = PLAY;
}

View::~View() {}

void View::render()
{
	window.clear();


	switch (gameState)
	{
	case START:
		window.setView(window.getDefaultView());
		playButtonText.setString("PLAY");
		playButtonText.setCharacterSize(55);
		window.draw(playButton);
		window.draw(playButtonText);
		window.draw(titleText);
		quitButtonText.setString("EXIT");
		window.draw(quitButton);
		window.draw(quitButtonText);
		break;

	case PLAY:
		window.draw(*stage);
		window.setView(view);
		scrollScreen();
		for (int i = 0; i < model->car.size(); i++) {
			//window.draw(model->car[i]->sprite); // Enable this to see the Hitbox
			window.draw(model->car[i]->image);
		}
		window.draw(model->enemies[0]->image);
		//player currently drawn on top for debug reasons to see where the player is
		window.draw(model->player->image);

		window.draw(model->player->inv->getShape());
		for (int i = 0; i < model->powerups.size(); i++)
		{
			if (model->powerups[i] != 0) {
				window.draw(model->powerups[i]->getShape());
			}
		}

		if (model->player->isInCar) {
			if (model->car[model->carIndex]->shield > 0) {
				healthBar.setFillColor(sf::Color::Blue);
			}
			else {
				healthBar.setFillColor(sf::Color::Yellow);
			}
			healthBar.setSize(sf::Vector2f(model->car[model->carIndex]->health, 5));
		}
		else {
			healthBar.setSize(sf::Vector2f(0, 0));
		}
		window.draw(healthBar);
		window.draw(pauseButton);

		//----- Enable this to see the collision zone (hitbox)
		//window.draw(model->one);
		//window.draw(model->two);

		break;

	case PAUSE:
		window.setView(window.getDefaultView());
		playButtonText.setString("RESUME");
		playButtonText.setCharacterSize(40);
		window.draw(playButton);
		window.draw(playButtonText);
		window.draw(titleText);
		quitButtonText.setString("QUIT");
		window.draw(quitButton);
		window.draw(quitButtonText);
		break;
	case RESUME:
		break;
	case QUIT:
		break;
	case WIN:
		break;
	case LOSE:
		break;
	}
	window.display();
}

void View::scrollScreen()
{

	if (model->player->posX + 10 > window.getSize().x / 2 && model->player->posX < 628)
	{
		positionView.x = model->player->posX + 10;
	}
	else if (model->player->posX >= 628)
	{
		positionView.x = 628;
	}
	else
	{
		positionView.x = window.getSize().x / 2;
	}


	if (model->player->posY + 10 > window.getSize().y / 2 && model->player->posY < 723)
		positionView.y = model->player->posY + 10;
	else if (model->player->posY >= 723)
	{
		positionView.y = 723;
	}
	else
		positionView.y = window.getSize().y / 2;

	view.setCenter(positionView);
}