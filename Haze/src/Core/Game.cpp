#include "Game.hpp"

Game::Game(const char* name, int width, int height) : window(new Window(width, height, nullptr)) { }

Game::~Game()
{
	delete window;
	terminate();
}

void Game::start()
{
	while (window->running())
	{
		float dt;
		window->update();
		update(window->getInput(), dt);
		draw(dt);
	}
}


void Game::initialize()
{
	Audio::initialize();
	Physics::initialize();
	Graphics::initialize(window);
}

void Game::terminate()
{
	Audio::terminate();
	Physics::terminate();
	Graphics::terminate();
}
