#include "Game.h"

Game::Game()
{
	this->model = new Model();
	this->view = new View(model);
	this->controller = new Controller(model, view);
}

Game::~Game() {}

void Game::loop()
{
	while (view->window.isOpen())
	{
		controller->inputs();
		model->update();
		view->render();
		//for each in model->updatables.update();
		//for each in view->renderables.render();
	}

}