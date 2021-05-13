#include "LightComponent.h"
#include "ComponentIDs.h"
#include "GameObject.h"
#include "includeLUA.h"
#include "Transform.h"

LightComponent::LightComponent() :Component(ComponentId::LightComponent), _tr(nullptr), _light(nullptr)
{
}

LightComponent::~LightComponent()
{
	delete _light; _light = nullptr;
}

void LightComponent::awake(luabridge::LuaRef& data)
{
	_light = new Light(_gameObject->getName());

	if (LUAFIELDEXIST(LightType))
		_light->setLightType(convertLightType(data["LightType"]));

	if (LUAFIELDEXIST(Visible))
		_light->setVisible(GETLUAFIELD(Visible, bool));

	if (LUAFIELDEXIST(Diffuse))
		_light->setDiffuse(data["Diffuse"]["Red"].cast<float>(), data["Diffuse"]["Green"].cast<float>(), data["Diffuse"]["Blue"].cast<float>());

	if (LUAFIELDEXIST(Specular))
		_light->setSpecular(data["Specular"]["Red"].cast<float>(), data["Specular"]["Green"].cast<float>(), data["Specular"]["Blue"].cast<float>());

	if (_light->getLightType() != Light::LightType::DIRECTIONAL && LUAFIELDEXIST(Attenuation))
		_light->setAttenuation(data["Attenuation"]["Range"].cast<float>(), data["Attenuation"]["Constant"].cast<float>(),
			data["Attenuation"]["Linear"].cast<float>(), data["Attenuation"]["Quadratic"].cast<float>());

	if (_light->getLightType() == Light::LightType::SPOTLIGHT && LUAFIELDEXIST(SpotLightRange))
		_light->setSpotlightRange(data["SpotLightRange"]["InnerAngle"].cast<float>(), data["SpotLightRange"]["OuterAngle"].cast<float>(),
			data["SpotLightRange"]["FallOf"].cast<float>());

	if (_light->getLightType() != Light::LightType::POINT && LUAFIELDEXIST(LightDirection))
		_light->setDirection(data["LightDirection"]["X"].cast<float>(), data["LightDirection"]["Y"].cast<float>(), data["LightDirection"]["Z"].cast<float>());

	if (LUAFIELDEXIST(Intensity))	
		_light->setPowerScale(data["Intensity"].cast<float>());
	
}

void LightComponent::start()
{
	_tr = GETCOMPONENT(Transform, ComponentId::Transform);
}

void LightComponent::update()
{
	const Vector3& pos = _tr->getPosition();
	_light->updatePosition(pos.getX(), pos.getY(), pos.getZ());
}

const Light::LightType LightComponent::convertLightType(std::string type)
{
	if (type == "POINT") return Light::LightType::POINT;
	else if (type == "DIRECTIONAL") return Light::LightType::DIRECTIONAL;
	else if (type == "SPOTLIGHT") return Light::LightType::SPOTLIGHT;
	//else throw UknownLightTypeException
}

void LightComponent::onEnable()
{
	_light->setVisible(true);
}

void LightComponent::onDisable()
{
	_light->setVisible(false);
}