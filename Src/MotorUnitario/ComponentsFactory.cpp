#include "ComponentsFactory.h"
#include "ComponentFactory.h"

std::map<std::string, ComponentFactory*>_componentTranslator = std::map<std::string, ComponentFactory*>();

void ComponentsFactory::add(std::string name, ComponentFactory* factory)
{
	_componentTranslator.insert(std::make_pair(name, factory));
}

ComponentFactory* ComponentsFactory::getComponentByName(std::string name)
{
	auto it = _componentTranslator.find(name);
	if (it == _componentTranslator.end())
		throw "This component doesn't exist";
	return (*it).second->create();
}
