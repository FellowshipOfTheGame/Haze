#ifndef HAZE_GAME_HPP
#define HAZE_GAME_HPP

#include "Audio.hpp"
#include "Physics.hpp"
#include "Graphics.hpp"

#include "Window.hpp"

#include "Input.hpp"
#include "EntitySystem.hpp"

class Game
{
	Audio* audio;
	Physics* physics;
	Graphics* graphics;

	Window* window;

	EntitySystem* system;
	Game();
public:
	Game(const char* name, int width, int height);
	~Game();

	virtual void initialize() final;
	virtual void terminate() final;

	virtual void start() final;

	virtual void update(InputState* input, float delta) = 0;
	virtual void draw(float interpolation) = 0;
};


#endif //HAZE_GAME_HPP
