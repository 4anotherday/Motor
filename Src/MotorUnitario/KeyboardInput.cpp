#include "KeyBoardInput.h"
#include "SDL_events.h"

std::unique_ptr<KeyBoardInput> KeyBoardInput::instance = nullptr;

KeyBoardInput::KeyBoardInput() : _keyJustDown(), _keyJustUp(), _keyboardState(SDL_GetKeyboardState(NULL))
{
}

KeyBoardInput::~KeyBoardInput()
{
}

KeyBoardInput* KeyBoardInput::getInstance()
{
	if (instance.get() == nullptr) {
		instance.reset(new KeyBoardInput());
	}
	return instance.get();
}

void KeyBoardInput::reset()
{
	_keyJustDown.reset();
	_keyJustUp.reset();
}

void KeyBoardInput::receiveEvent(SDL_Event* event)
{
	switch (event->type) {
	case SDL_KEYDOWN:
		//Checks if repeat is true, which means this is not the first time this 
		//Event has been processed. Which means this key has/has not just been pressed
		if (event->key.repeat==0) 
			_keyJustDown[event->key.keysym.scancode] = 1;
		break;
	case SDL_KEYUP:
		_keyJustUp[event->key.keysym.scancode] = 1;
		break;
	}
}