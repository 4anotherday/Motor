#include "Engine.h"
//WIP
#include "MotorGrafico/main.h"
#include "MotorUnitario/GameObject.h"
#include <SDL.h>
#include "MotorGrafico/GraphicsEngine.h"
#include "InputManager.h"
#include "MotorAudio/AudioEngine.h"
#include "ComponentsFactory.h"
#include "ComponentFactory.h"
#include "Time.h"
#include "Transform.h"
#include "KeyCodes.h"
#include <iostream>

std::unique_ptr<Engine> Engine::instance = nullptr;

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
	if (instance.get() == nullptr) {
		instance.reset(new Engine());
	}
	return instance.get();
}

void Engine::tick()
{
	processEvents();
	update();
	//WIP
	fixedUpdate();
	lateUpdate();
	_graphicsEngine->render();
	_time->update();
	testing();
}

void Engine::init()
{
	initFactories();
	GameObject* TEST = addGameObject();
	TEST->addComponent(new Transform(TEST));
	TEST->addComponent(new AudioSourceComponent(TEST, "Assets\Audio\ProtoDarkMaze_Menu.mp3"));
	_inputManager = InputManager::getInstance();
	_graphicsEngine = GraphicsEngine::getInstance();
	setResourcesPath("Assets/prueba.cfg");	// TESTING! This line must be called in game init, before the initialization of Engine
	_audioEngine = AudioEngine::getInstance();
	_time = Time::getInstance();
	_graphicsEngine->initRoot();
	_graphicsEngine->initWindow();
	_graphicsEngine->setup();

	_graphicsEngine->loadScene(); //WIP
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

void Engine::setResourcesPath(std::string const& resourcesPath)
{
	_graphicsEngine->setResourcePath(resourcesPath);
}

void Engine::testing()
{
	if (MouseInput::getInstance()->isMouseButtonJustUp(MouseButton::X1)) {
		std::cout << "El boton del raton esta abajo \n";
	}
	if (MouseInput::getInstance()->isMouseButtonJustDown(MouseButton::MIDDLE)) {
		std::cout << "La rueda se ha pulsado \n";
	}
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
	_audioEngine->update();
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

void Engine::initFactories()
{
	ComponentsFactory::add("ImageRenderer", new ImageRenderComponentFactory());
	ComponentsFactory::add("Light", new LightComponentFactory());
	ComponentsFactory::add("RenderObject", new RenderObjectComponentFactory());
	ComponentsFactory::add("Listener", new ListenerComponentFactory());
	ComponentsFactory::add("AudioSource", new AudioSourceComponentFactory());
	ComponentsFactory::add("RigidBody", new RigidBodyComponentFactory());
	ComponentsFactory::add("Collider", new ColliderComponentFactory());
	ComponentsFactory::add("Camera", new CameraComponentFactory());
	ComponentsFactory::add("Animator", new AnimatorComponentFactory());
	ComponentsFactory::add("ParticleSystem", new ParticleSystemComponentFactory());

	// GameObject* go = new GameObject();
	// Component* ir = ComponentsFactory::getComponentByName("ImageRenderer");
	// ir->setGameObject(go);
	// go->addComponent(ir);
	// go->addComponent(ComponentsFactory::getComponentByName("Light"));
	// go->addComponent(ComponentsFactory::getComponentByName("RenderObject"));
	// go->addComponent(ComponentsFactory::getComponentByName("Listener"));
	// go->addComponent(ComponentsFactory::getComponentByName("AudioSource"));
	// go->addComponent(ComponentsFactory::getComponentByName("RigidBody"));
	// go->addComponent(ComponentsFactory::getComponentByName("Collider"));
	// go->addComponent(ComponentsFactory::getComponentByName("Camera"));
	// go->addComponent(ComponentsFactory::getComponentByName("Animator"));
	// go->addComponent(ComponentsFactory::getComponentByName("ParticleSystem"));
}