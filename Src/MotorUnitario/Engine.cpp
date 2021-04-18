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
#include "GamePadCodes.h"
#include "ComponentIDs.h"
#include <iostream>
#include "Component.h"

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
	_audioEngine->update();
	_time->update();
	testing();
}

void Engine::init()
{
	initFactories();

	_inputManager = InputManager::getInstance();
	_graphicsEngine = GraphicsEngine::getInstance();
	_audioEngine = AudioEngine::getInstance();
	setResourcesPath("Assets/prueba.cfg");	// TESTING! This line must be called in game init, before the initialization of Engine
	_time = Time::getInstance();
	//Graphics
	_graphicsEngine->initRoot();
	_graphicsEngine->initWindow();
	_graphicsEngine->setup();
	_graphicsEngine->loadScene(); //WIP

	//Audio
	_audioEngine->init();
	//_audioEngine->set_3DSettings(100, 100, 100);

	//GameObject que va a reproducir el sonido
	//GameObject* TEST = addGameObject();
	//Transform* t = new Transform(TEST);
	//TEST->addComponent(t);
	//AudioSourceComponent* aSource = new AudioSourceComponent(TEST, "Assets/Audio/ProtoDarkMaze_Menu.mp3");
	//aSource->playAudio(0);
	//TEST->addComponent(aSource);
	//_GOs.push_back(TEST);

	////GameObject que supone el listener
	//TEST = addGameObject();
	//t = new Transform(TEST);
	//TEST->addComponent(t);
	//t->setPosition(Vector3(10000, 0, 0));
	//ListenerComponent* listener = new ListenerComponent(TEST);
	//TEST->addComponent(listener);
	//_GOs.push_back(TEST);

	//Test Camara
	//TEST = addGameObject();
	//Transform* t = new Transform(TEST);
	//TEST->addComponent(t);
	//CameraComponent* aSource = new CameraComponent("Assets/Audio/ProtoDarkMaze_Menu.mp3", 2, TEST);
	//aSource->setViewportDimensions(0., 0., 0.5, 0.5);
	//TEST->addComponent(aSource);
	//_GOs.push_back(TEST);

	GameObject* TEST2 = addGameObject();
	Transform* t2 = new Transform(TEST2);
	TEST2->addComponent(t2);
	CameraComponent* aSource2 = new CameraComponent("Assets/Audio/ProtoDarkMaze_Menu.mp3", 1, TEST2);
	aSource2->setViewportDimensions(0.5, 0.5, 0.5, 0.5);
	TEST2->addComponent(aSource2);
	_GOs.push_back(TEST2);
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
	double vel = 5;
	if (KeyBoardInput::getInstance()->isKeyDown(KeyCode::KEYCODE_A)) {
		Transform* t = static_cast<Transform*>(TEST->getComponent(ComponentId::Transform));
		Vector3 pos = t->getPosition();
		pos = (Vector3(pos.getX() - vel, pos.getY(), pos.getZ()));
		t->setPosition(pos);
	}
	if (KeyBoardInput::getInstance()->isKeyDown(KeyCode::KEYCODE_D)) {
		Transform* t = static_cast<Transform*>(TEST->getComponent(ComponentId::Transform));
		Vector3 pos = t->getPosition();
		pos = (Vector3(pos.getX() + vel, pos.getY(), pos.getZ()));
		t->setPosition(pos);
	}

	if (KeyBoardInput::getInstance()->isKeyDown(KeyCode::KEYCODE_W)) {
		Transform* t = static_cast<Transform*>(TEST->getComponent(ComponentId::Transform));
		Vector3 pos = t->getPosition();
		pos = (Vector3(pos.getX(), pos.getY() + vel, pos.getZ()));
		t->setPosition(pos);
	}
	if (KeyBoardInput::getInstance()->isKeyDown(KeyCode::KEYCODE_S)) {
		Transform* t = static_cast<Transform*>(TEST->getComponent(ComponentId::Transform));
		Vector3 pos = t->getPosition();
		pos = (Vector3(pos.getX(), pos.getY() - vel, pos.getZ()));
		t->setPosition(pos);
	}
	if (KeyBoardInput::getInstance()->isKeyDown(KeyCode::KEYCODE_P)) {
		Transform* t = static_cast<Transform*>(TEST->getComponent(ComponentId::Transform));
		CameraComponent* c = static_cast<CameraComponent*>(TEST->getComponent(ComponentId::Camera));
		c->setViewportDimensions(0.1, 0.1, 0.1, 0.1);
	}
	if (KeyBoardInput::getInstance()->isKeyDown(KeyCode::KEYCODE_O)) {
		Transform* t = static_cast<Transform*>(TEST->getComponent(ComponentId::Transform));
		CameraComponent* c = static_cast<CameraComponent*>(TEST->getComponent(ComponentId::Camera));
		c->setViewportDimensions(0., 0., 0.5, 0.5);
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