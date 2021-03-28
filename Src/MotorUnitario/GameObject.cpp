#include "GameObject.h"
#include "Component.h"
#include "Exceptions.h"

#define _COMPONENT_START_SIZE_ 15
#define _COMPONENT_INCREASE_SIZE_ size_t(5)

GameObject::GameObject() : _children(), _components(_COMPONENT_START_SIZE_, nullptr), _parent(nullptr), _name(), _enable(true), _persist(false)
{
	// TODO: Tranform
	/*Transform* tranform = new Transform();
	tranform->setId(0);
	_components[0] = tranform;	
	_activeComponents.pushback(transform);
	*/
}

void GameObject::start()
{
	for (auto& comp : _activeComponents)
		if(comp.second->getEnabled()) 
			comp.second->start();

	for (GameObject* go : _children)
		if(go->getEnabled()) 
			go->start();
}

void GameObject::update()
{
	for (auto& comp : _activeComponents)
		if (comp.second->getEnabled())
			comp.second->update();

	for (GameObject* go : _children)
		if (go->getEnabled()) 
			go->update();
}

void GameObject::fixedUpdate()
{
	for (auto& comp : _activeComponents)
		if (comp.second->getEnabled())
			comp.second->fixedUpdate();

	for (GameObject* go : _children)
		if (go->getEnabled()) 
			go->fixedUpdate();
}

void GameObject::lateUpdate()
{
	for (auto& comp : _activeComponents)
		if (comp.second->getEnabled())
			comp.second->lateUpdate();

	for (GameObject* go : _children)
		if (go->getEnabled()) 
			go->lateUpdate();
}

void GameObject::addComponent(Component* component)
{
	unsigned int id = component->getId();

	if ((int)id < 0)
		throw InvalidAccessException("Id of component cant be below zero");

	if (_components[id] != nullptr)
		throw ComponentException("Component already exists");

	if (id >= _components.size())
		_components.resize(id + _COMPONENT_INCREASE_SIZE_, nullptr);

	_components[id] = component;

	insertInOrder(id, component);
}

void GameObject::removeComponent(unsigned int componentId)
{
	if (componentId >= _components.size())
		throw ComponentException("Component doesn't exists or it's not in gameObject named \": " + _name + "\"");

	removeFromActiveComponents(componentId);

	delete _components[componentId];
	_components[componentId] = nullptr;
}

void GameObject::addChild(GameObject* gameObject)
{
	gameObject->setParent(this);
	_children.push_back(gameObject);
}

Component* GameObject::getComponent(unsigned int componentId) const
{
	if (componentId >= _components.size())
		return nullptr;

	return _components[componentId];
}

void GameObject::insertInOrder(unsigned int componentId, Component* component)
{
	auto begin = _activeComponents.begin();
	auto end = _activeComponents.end();

	while ((begin != end) && begin->first < componentId) {
		++begin;
	}

	_activeComponents.insert(begin, std::make_pair(componentId, component));
}

void GameObject::removeFromActiveComponents(unsigned int componentId)
{
	auto begin = _activeComponents.begin();
	auto end = _activeComponents.end();

	while ((begin != end)) {
		if (begin->first == componentId) {
			_activeComponents.erase(begin);
			return;
		}
		++begin;
	}
}