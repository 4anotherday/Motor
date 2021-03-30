#include "Engine.h"
//WIP
#include "MotorGrafico/main.h"
#include "MotorUnitario/GameObject.h"
#include <SDL.h>
#include "MotorGrafico/GraphicsEngine.h"

Engine* Engine::instance = nullptr;

Engine::Engine() : _run(true)
{
}

Engine::~Engine()
{
}

Engine* Engine::getInstance()
{
	if (instance == nullptr) {
		instance = new Engine();
	}
	return instance;
}

void Engine::tick()
{
	update();
	//WIP
	fixedUpdate();
	lateUpdate();
}

void Engine::init()
{
	SDL_Init(SDL_INIT_EVERYTHING);

	Uint32 flags = SDL_WINDOW_ALLOW_HIGHDPI; //SDL_WINDOW_RESIZABLE
	std::string nombre = "Prueba";
	sdlWindow = SDL_CreateWindow(nombre.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, flags);

	graphicsEngine = GraphicsEngine::getInstance();
	graphicsEngine->initRoot();
	graphicsEngine->initWindow();
}

void Engine::run()
{
	while (_run)
	{
		tick();
	}
}

void Engine::changeScene(std::string scene)
{
}

void Engine::stopExecution()
{
	_run = false;
}

void Engine::start()
{
	for (auto& it : GOs) {
		it->start();
	}
}

void Engine::fixedUpdate()
{
	for (auto& it : GOs) {
		it->fixedUpdate();
	}
}

void Engine::update()
{
	for (auto& it : GOs) {
		it->update();
	}
}

void Engine::lateUpdate()
{
	for (auto& it : GOs) {
		it->lateUpdate();
	}
}

GameObject* Engine::addGameObject()
{
	GOs.push_back(new GameObject());
	return GOs.back();
}

void Engine::remGameObject(GameObject* GO)
{
	auto it = GOs.begin();
	while (it != GOs.end()) {
		if ((*it) == GO) {
			it = GOs.erase(it);
			break;
		}
		else
			it++;
	}
}

void Engine::remGameObjectString(std::string const& GOname)
{
	auto it = GOs.begin();
	while (it != GOs.end()) {
		if ((*it)->getName() == GOname) {
			delete (*it);
			it = GOs.erase(it);
			break;
		}
		else
			it++;
	}
}

GameObject* Engine::findGameObject(std::string name)
{
	auto it = GOs.begin();
	while (it != GOs.end()) {
		if ((*it)->getName() == name) {
			break;
		}
		else
			it++;
	}
	return (it == GOs.end()) ? (nullptr) : (*it);
}

void Engine::freeEnginesResources() {
}