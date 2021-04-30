#include "OverlayComponent.h"
#include "GameObject.h"
#include "ComponentIDs.h"
#include "MotorGrafico/OverlayElement.h"
#include "includeLUA.h"


OverlayComponent::OverlayComponent() : Component(ComponentId::OverlayComponent),
_overlayElement(nullptr)
{
}

OverlayComponent::~OverlayComponent()
{
	delete _overlayElement;
}

void OverlayComponent::awake(luabridge::LuaRef& data)
{
	if(LUAFIELDEXIST("Name"))_overlayElement = new OverlayElement(data["Name"].cast<std::string>());
	if (data["Hide"].cast<bool>()) _overlayElement->hideOverlay();
	else _overlayElement->showOverlay();
	if (LUAFIELDEXIST("Container"))_overlayElement->setMaterial(data["Container"].cast<std::string>(), data["Material"].cast<std::string>());
}

void OverlayComponent::start()
{
	_overlayElement = new OverlayElement(_overlayName);
}

void OverlayComponent::hideOverlay(bool hide)
{
	hide ? _overlayElement->hideOverlay() : _overlayElement->showOverlay();
}

void OverlayComponent::setMaterial(std::string const& containerName, std::string const& materialName)
{
	_overlayElement->setMaterial(containerName, materialName);
}
