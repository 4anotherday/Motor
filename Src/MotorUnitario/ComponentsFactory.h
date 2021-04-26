#pragma once
#ifndef COMPONENTSFACTORY_H
#define COMPONENTSFACTORY_H
#include <string>
#include <map>
#include <memory>

class ComponentFactory;
class Component;

class ComponentsFactory
{
public:

	/// <summary>
	/// Returns the instance of Engine, or nullptr if it doesnt exist yet
	/// </summary>
	static ComponentsFactory* getInstance();

	~ComponentsFactory();
	ComponentsFactory& operator=(const ComponentsFactory&) = delete;
	ComponentsFactory(ComponentsFactory& other) = delete;

	/// <summary>
	/// Adds a new factory with a name to the map
	/// </summary>
	/// <param name="name">The name component</param>
	/// <param name="factory">The equivalent factory</param>
	void add(const std::string& name, ComponentFactory* factory);
	
	/// <summary>
	/// Gets a component based in the name received
	/// </summary>
	/// <param name="name">The name of the desired component</param>
	/// <returns>The desired component</returns>
	Component* getComponentByName(const std::string& name);

private:

	ComponentsFactory() : _componentTranslator() {

	}

	std::map<std::string, ComponentFactory*> _componentTranslator;

	static std::unique_ptr<ComponentsFactory> instance;
};
#endif // !COMPONENTSFACTORY_H


