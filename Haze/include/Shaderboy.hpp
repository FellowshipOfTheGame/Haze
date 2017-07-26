#ifndef SHADERBOY
#define SHADERBOY

#include "Game.hpp"

class Shaderboy : public Game
{
public:
	Shaderboy(int width, int height);
	~Shaderboy();
	void update(InputState* state, float delta) override;
	void draw(float interpolation) override;
};

#endif // !SHADERBOY
