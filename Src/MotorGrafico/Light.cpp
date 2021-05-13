#include "Light.h"
#include "GraphicsEngine.h"
#include "Exceptions.h"

#pragma warning(push, 0)
#include "OgreLight.h"
#include "OgreSceneManager.h"
#pragma warning(pop)

#include <string>

unsigned int Light::_lightCount = 0;

Light::Light(const std::string& gameObjectName) : _id(_lightCount++), _light(nullptr)
{
	Ogre::SceneManager* sm = GraphicsEngine::getInstance()->getSceneManager();

	//sceneManager debera ser un SceneManager de Ogre statico por todo el motor grafico

	_light = sm->createLight(gameObjectName + std::string("_lightObject_") + std::to_string(_id));
	_light->setType(Ogre::Light::LightTypes::LT_POINT);


	//Attach the light object to the sceneNode somewhere
	//Re-launch of our own exception instead of Ogre's exception
	try {
		_lightNode = sm->getSceneNode(gameObjectName);
		_lightNode->attachObject(_light);
	}
	catch (...) {
		throw SceneNodeException(gameObjectName + std::string(" node does not exist"));
	}
}

Light::~Light()
{
}

void Light::setLightType(Light::LightType type)
{
	_light->setType((Ogre::Light::LightTypes)type);
}

Light::LightType Light::getLightType()
{
	return (LightType)_light->getType();
}

void Light::setDiffuse(float red, float green, float blue)
{
	_light->setDiffuseColour(red, green, blue);
}

void Light::setDiffuse(const Colour& diffuse)
{
	_light->setDiffuseColour(diffuse.red, diffuse.green, diffuse.blue);
}

const Colour Light::getDiffuse() const
{
	const Ogre::ColourValue& colourOgre = _light->getDiffuseColour();

	return Colour(colourOgre.r, colourOgre.g, colourOgre.b, colourOgre.a);
}

void Light::setSpecular(float red, float green, float blue)
{
	_light->setSpecularColour(red, green, blue);
}

void Light::setSpecular(const Colour& specular)
{
	_light->setSpecularColour(specular.red, specular.green, specular.blue);
}

const Colour Light::getSpecular() const
{
	const Ogre::ColourValue& colourOgre = _light->getSpecularColour();

	return Colour(colourOgre.r, colourOgre.g, colourOgre.b, colourOgre.a);
}

void Light::setAttenuation(float range, float constant, float linear, float quadratic)
{
	_light->setAttenuation(range, constant, linear, quadratic);
}

const float Light::getAttenuationRange() const
{
	return _light->getAttenuationRange();
}

const float Light::getAttenuationConstant() const
{
	return _light->getAttenuationConstant();
}

const float Light::getAttenuationLinear() const
{
	return _light->getAttenuationLinear();
}

const float Light::getAttenuationQuadric() const
{
	return _light->getAttenuationQuadric();
}

void Light::setSpotlightRange(float innerAngle, float outerAngle, float fallof) {
	_light->setSpotlightRange(Ogre::Radian(innerAngle), Ogre::Radian(outerAngle), fallof);
}

const float Light::getSpotlightFallOff() const
{
	return _light->getSpotlightFalloff();
}

const float Light::getSpotlightInnerAngle() const
{
	return _light->getSpotlightInnerAngle().valueRadians();
}

const float Light::getSpotlightOuterAngle() const
{
	return _light->getSpotlightOuterAngle().valueRadians();
}

void Light::setPowerScale(float power)
{
	_light->setPowerScale(power);
}

const float Light::getPowerScale() const
{
	return _light->getPowerScale();
}

void Light::setVisible(bool visible)
{
	_light->setVisible(visible);
}

const bool Light::getVisible() const
{
	return _light->getVisible();
}

void Light::setDirection(float x, float y, float z)
{
	_lightNode->setDirection(Ogre::Vector3(x, y, z));
}

void Light::updatePosition(float x, float y, float z)
{
	_lightNode->setPosition(Ogre::Vector3(x, y, z));
}
