#include "Engine.h"

#include "MotorUnitario/GameObject.h"
#include <SDL.h>
#include "MotorGrafico/GraphicsEngine.h"
#include "MotorFisico/PhysxEngine.h"
#include "InputManager.h"
#include "MotorAudio/AudioEngine.h"
#include "EngineTime.h"
#include "Logger.h"

std::unique_ptr<Engine> Engine::instance = nullptr;

Engine::Engine() : _run(true), _graphicsEngine(nullptr), _inputManager(nullptr), alredyInitialized(false)
{
}

void Engine::processEvents()
{
	_inputManager->update();
}

Engine::~Engine()
{
	for (auto go : _GOs) {
		delete go; go = nullptr;
	}
	delete _physxEngine; _physxEngine = nullptr;
}

Engine* Engine::getInstance()
{
	return instance.get();
}

void Engine::CreateInstance()
{
	if (instance.get() == nullptr) {
		instance.reset(new Engine());
	}
	else {
		Logger::getInstance()->log("Trying to create Engine instance and it already exist", Logger::Level::WARN);
	}
}

void Engine::tick()
{
	processEvents();
	fixedUpdate();
	update();
	lateUpdate();
	_graphicsEngine->render();
	_audioEngine->update();
	_physxEngine->update(_time->deltaTime());
	_time->update();
}

bool Engine::init(std::string const& resourcesPath)
{
	if (alredyInitialized) {
		Logger::getInstance()->log("Engine class is already initialized", Logger::Level::WARN);
		return false;
	}

	_inputManager = InputManager::getInstance();
	GraphicsEngine::CreateInstance();
	_graphicsEngine = GraphicsEngine::getInstance();
	_graphicsEngine->setResourcePath(resourcesPath);
	if (!_graphicsEngine->initializeRenderEngine()) {
		Logger::getInstance()->log("Graphics Engine init error", Logger::Level::ERROR);
		throw "Graphics Engine init error";
	}
	PhysxEngine::CreateInstance();
	_physxEngine = PhysxEngine::getPxInstance();
	_physxEngine->init();
	AudioEngine::CreateInstance();
	_audioEngine = AudioEngine::getInstance();
	_time = EngineTime::getInstance();

	alredyInitialized = true;
	return true;
}

void Engine::run()
{
	start();

	while (_run)
	{
		tick();
	}

	shutDown();
}

void Engine::changeScene(const std::string& scene)
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
	int calls = _time->fixedUpdateRequired();

	if (calls == 0) return;

	for (calls; calls > 0; --calls) {
		for (auto& it : _GOs) {
			it->fixedUpdate();
		}
	}
	_time->fixedTimeUpdate();
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

void Engine::shutDown()
{
	if (_graphicsEngine != nullptr) {
		_graphicsEngine->shutdown();
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

void Engine::remGameObjectString(const std::string& GOname)
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

GameObject* Engine::findGameObject(const std::string& name)
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