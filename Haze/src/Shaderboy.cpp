#include "Shaderboy.hpp"

Shaderboy::Shaderboy(int width, int height) : Game("Shaderboy", width, height)
{
}

Shaderboy::~Shaderboy()
{
}

void Shaderboy::update(InputState* state, float delta)
{
	std::cout << "Update";
}

void Shaderboy::draw(float interpolation)
{
	std::cout << "Draw";
}
