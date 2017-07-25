#include "Audio.hpp"


bool Audio::init = false;

FMOD::System* Audio::system = NULL;

void Audio::initialize()
{
	if (init)
		return;
	FMOD_RESULT result;
	result = FMOD::System_Create(&system);
	if(result)
		err((int)result, "FMOD system creation error");

	result = system->init(100, FMOD_INIT_NORMAL, NULL);
	if (result)
		err((int)result, "FMOD system init error");

	unsigned int version;

	result = system->getVersion(&version);
	if (result)
		err((int)result, "FMOD system version error");
	
	std::cout << "FMOD version: " << version << std::endl;

	init = true;
}

void Audio::terminate()
{
	if (!init)
		return;

	FMOD_RESULT result;
	result = system->close();
	if (result)
		err(result, "FMOD system close error");
	result = system->release();
	if (result)
		err(result, "FMOD system release error");

	init = false;
}
