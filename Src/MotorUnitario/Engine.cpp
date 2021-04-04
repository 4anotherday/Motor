#include "Engine.h"
//WIP
#include "MotorGrafico/main.h"
#include "MotorUnitario/GameObject.h"
#include <SDL.h>
#include "MotorGrafico/GraphicsEngine.h"
#include "InputManager.h"

Engine* Engine::instance = nullptr;

Engine::Engine() : _run(true), _graphicsEngine(nullptr), _inputManager(nullptr)
{
}

void Engine::processEvents()
{
	_inputManager->update();
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
	processEvents();
	update();
	//WIP
	fixedUpdate();
	lateUpdate();
	_graphicsEngine->render();
}

void Engine::init()
{
	_inputManager = InputManager::getInstance();
	_graphicsEngine = GraphicsEngine::getInstance();
	_graphicsEngine->initRoot();
	_graphicsEngine->initWindow();
}

void Engine::run()
{
	start();
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
	for (auto& it : _GOs) {
		it->start();
	}
}

void Engine::fixedUpdate()
{
	for (auto& it : _GOs) {
		it->fixedUpdate();
	}
}

void Engine::update()
{
	for (auto& it : _GOs) {
		it->update();
	}
}

void Engine::lateUpdate()
{
	for (auto& it : _GOs) {
		it->lateUpdate();
	}
}

GameObject* Engine::addGameObject()
{
	_GOs.push_back(new GameObject());
	return _GOs.back();
}

void Engine::remGameObject(GameObject* GO)
{
	auto it = _GOs.begin();
	while (it != _GOs.end()) {
		if ((*it) == GO) {
			it = _GOs.erase(it);
			break;
		}
		else
			it++;
	}
}

void Engine::remGameObjectString(std::string const& GOname)
{
	auto it = _GOs.begin();
	while (it != _GOs.end()) {
		if ((*it)->getName() == GOname) {
			delete (*it);
			it = _GOs.erase(it);
			break;
		}
		else
			it++;
	}
}

GameObject* Engine::findGameObject(std::string name)
{
	auto it = _GOs.begin();
	while (it != _GOs.end()) {
		if ((*it)->getName() == name) {
			break;
		}
		else
			it++;
	}
	return (it == _GOs.end()) ? (nullptr) : (*it);
}

void Engine::freeEnginesResources() {
}