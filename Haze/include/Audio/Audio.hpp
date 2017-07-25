#ifndef HAZE_AUDIO_HPP
#define HAZE_AUDIO_HPP

#include "fmod.hpp"
#include "Haze.hpp"
#include <iostream>

class Audio
{
	static FMOD::System *system;
	static bool init;
	Audio();
public:
	static void initialize();
	static void terminate();
};

#endif // !HAZE_AUDIO_HPP
