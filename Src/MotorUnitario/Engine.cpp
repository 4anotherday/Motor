#include "Engine.h"

#include "MotorUnitario/GameObject.h"
#include <SDL.h>
#include "MotorGrafico/GraphicsEngine.h"
#include "MotorFisico/PhysxEngine.h"
#include "InputManager.h"
#include "MotorAudio/AudioEngine.h"
#include "EngineTime.h"
#include "LuaParser.h"
#include "Logger.h"
#include "ComponentsFactory.h"
#include "Exceptions.h"

#include "Factories.h"

std::unique_ptr<Engine> Engine::instance = nullptr;

Engine::Engine() : _physxEngine(nullptr), _graphicsEngine(nullptr), _audioEngine(nullptr),
_GOs(), _deleteGOs(),
_inputManager(nullptr), _time(nullptr), _luaParser(nullptr),
_run(true), alredyInitialized(false), _changeScene(false), scenesPath(""), _currentScene("")
{
}

void Engine::processEvents()
{
	_inputManager->update();
}

Engine::~Engine()
{
	ComponentsFactory::getInstance()->~ComponentsFactory();
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

void Engine::setViewportColour(float r, float g, float b)
{
	_graphicsEngine->setViewportColour(r, g, b);
}

void Engine::disableShadows()
{
	_graphicsEngine->disableShadows();
}


void Engine::tick()
{
	try {
		processEvents();
		fixedUpdate();
		update();
		lateUpdate();
		_graphicsEngine->render();
		_audioEngine->update();
		_time->update();

		cleanUpGameObjects();
		if (_changeScene)
			changeScene();
	}
	catch (ExcepcionTAD e) {
		Logger::getInstance()->log("Error while executing engine: " + e.msg(), Logger::Level::FATAL);
		shutDown();
		exit(0);
	}
}

bool Engine::init(std::string const& resourcesPath, std::string const& scenesP)
{
	if (alredyInitialized) {
		Logger::getInstance()->log("Engine class is already initialized", Logger::Level::WARN);
		return false;
	}

	scenesPath = scenesP + '/';

	//--------------GraphicsEngine---------------------
	try {
		GraphicsEngine::CreateInstance();
		_graphicsEngine = GraphicsEngine::getInstance();
		_graphicsEngine->setResourcePath(resourcesPath);
		if (!_graphicsEngine->initializeRenderEngine()) {
			Logger::getInstance()->log("Graphics Engine init error", Logger::Level::ERROR);
			throw "Graphics Engine init error";
		}
		Logger::getInstance()->log("Graphics Engine initialized correctly", Logger::Level::INFO);
		//--------------PhysXEngine--------------------
		PhysxEngine::CreateInstance();
		_physxEngine = PhysxEngine::getPxInstance();
		_physxEngine->init();
		Logger::getInstance()->log("Physics Engine initialized correctly", Logger::Level::INFO);
		//---------------AudioEngine--------------------
		AudioEngine::CreateInstance();
		_audioEngine = AudioEngine::getInstance();
		_audioEngine->init();
		Logger::getInstance()->log("Audio Engine initialized correctly", Logger::Level::INFO);
		//-------------InputManager--------------
		_inputManager = InputManager::getInstance();
		Logger::getInstance()->log("Input manager initialized correctly", Logger::Level::INFO);

		_time = EngineTime::getInstance();

		initEngineFactories();

		_luaParser = new LuaParser();

		alredyInitialized = true;
	}
	catch (ExcepcionTAD e) {
		Logger::getInstance()->log("Error inizialise engine: " + e.msg(), Logger::Level::FATAL);
		shutDown();
		exit(0);
	}
	return true;
}

void Engine::run()
{
	while (_run)
	{
		tick();
	}

	shutDown();
}

void Engine::changeScene(const std::string& scene)
{
	_currentScene = scene;
	_changeScene = true;
}

void Engine::stopExecution()
{
	_run = false;
}

void Engine::start()
{
	for (auto& it : _GOs) {
		try {
			it->start();
		}
		catch (...) {
			throw ExcepcionTAD("Error in Start at gameObject " + it->getName());
		}
	}

	_time->startTimeNow();
}

void Engine::fixedUpdate()
{
	int calls = _time->fixedUpdateRequired();

	if (calls == 0) return;
	else if (calls > 2) calls = 2;

	while (calls--) {
		for (auto& it : _GOs) {
			if (it->getEnabled()) {
				try {
					it->fixedUpdate();
				}
				catch (...) {
					throw ExcepcionTAD("Error in FixedUpdate at gameObject " + it->getName());
				}
			}
		}
		_physxEngine->update(_time->fixedDeltaTime() / 1000);
	}


	for (auto& it : _GOs) {
		if (it->getEnabled()) {
			try {
				it->postFixedUpdate();
			}
			catch (...) {
				throw ExcepcionTAD("Error in PostFixedUpdate at gameObject " + it->getName());
			}
		}		
	}

	_time->fixedTimeUpdate();
}

void Engine::update()
{
	for (auto& it : _GOs) {
		if (it->getEnabled()) {
			try {
				it->update();
			}
			catch (...) {
				throw ExcepcionTAD("Error in Update at gameObject " + it->getName());
			}
		}
	}
}

void Engine::lateUpdate()
{
	for (auto& it : _GOs) {
		if (it->getEnabled()) {
			try {
				it->lateUpdate();
			}
			catch (...) {
				throw ExcepcionTAD("Error in LateUpdate at gameObject " + it->getName());
			}
		}
	}
}

void Engine::shutDown()
{
	for (auto go : _GOs) {
		delete go; go = nullptr;
	}

	if (_graphicsEngine != nullptr) {
		_graphicsEngine->shutdown();
	}
	if (_physxEngine != nullptr) {
		delete _physxEngine;
		_physxEngine = nullptr;
	}
	_luaParser->closeLuaVM();
}

void Engine::initEngineFactories()
{
	ComponentsFactory::getInstance()->add("Transform", new TransformFactory());
	ComponentsFactory::getInstance()->add("ImageRenderer", new ImageRenderComponentFactory());
	ComponentsFactory::getInstance()->add("LightComponent", new LightComponentFactory());
	ComponentsFactory::getInstance()->add("RenderObject", new RenderObjectComponentFactory());
	ComponentsFactory::getInstance()->add("Listener", new ListenerComponentFactory());
	ComponentsFactory::getInstance()->add("AudioSource", new AudioSourceComponentFactory());
	ComponentsFactory::getInstance()->add("RigidBody", new RigidBodyComponentFactory());
	ComponentsFactory::getInstance()->add("BoxCollider", new BoxColliderComponentFactory());
	ComponentsFactory::getInstance()->add("SphereCollider", new SphereColliderComponentFactory());
	ComponentsFactory::getInstance()->add("CapsuleCollider", new CapsuleColliderComponentFactory());
	ComponentsFactory::getInstance()->add("Camera", new CameraComponentFactory());
	ComponentsFactory::getInstance()->add("Animator", new AnimatorComponentFactory());
	ComponentsFactory::getInstance()->add("ParticleSystem", new ParticleSystemComponentFactory());
	ComponentsFactory::getInstance()->add("ButtonComponent", new ButtonComponentFactory());
	ComponentsFactory::getInstance()->add("OverlayComponent", new OverlayComponentFactory());
}

void Engine::cleanUpGameObjects()
{
	for (GameObject* go : _deleteGOs) {
		_GOs.remove(go);
		delete go; go = nullptr;
	}
	_deleteGOs.clear();
}

void Engine::changeScene()
{
	_changeScene = false;
	//Remove current scene
	for (auto it = _GOs.begin(); it != _GOs.end();) {
		if (!(*it)->getPersist()) {
			GameObject* go = *it;
			it = _GOs.erase(it);
			delete go;
		}
		else
			++it;
	}
	_graphicsEngine->clearScene();
	//Load new scene
	_luaParser->loadScene(scenesPath + _currentScene);

	start();
}

GameObject* Engine::addGameObject()
{
	_GOs.push_back(new GameObject());
	return _GOs.back();
}

void Engine::remGameObject(GameObject* GO)
{
	_deleteGOs.push_back(GO);
}

void Engine::remGameObjectString(const std::string& GOname)
{
	auto it = _GOs.begin();
	while (it != _GOs.end()) {
		if ((*it)->getName() == GOname) {
			_deleteGOs.push_back(*it);
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
	if (it == _GOs.end()) {
		Logger::getInstance()->log("The game object with the name " + name + " has not been found", Logger::Level::WARN);
		return nullptr;
	}
	return (*it);
}

std::pair<int, int> Engine::getWindowSize()
{
	return _graphicsEngine->getWindowSize();
}

void Engine::setWindowFullScreen()
{
	_graphicsEngine->setFullScreen();
}

void Engine::setShadowColour(float r, float g, float b)
{
	_graphicsEngine->setShadowColour(r, g, b);
}

void Engine::setAmbientLight(float r, float g, float b)
{
	_graphicsEngine->setAmbientLight(r, g, b);
}
