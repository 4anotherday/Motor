#pragma once
#ifndef LIGHT_COMPONENT_H
#define LIGHT_COMPONENT_H

#include "Component.h"
#include "MotorGrafico/Light.h"

class Transform;
class GameObject;

class LightComponent : public Component
{
public:

	LightComponent();

	~LightComponent();

	/// <summary>
	/// Method to initialize required attributes for the component
	/// </summary>
	virtual void awake(luabridge::LuaRef& data) override;

	void start() override;

	void update() override;

	/// <summary>
	/// Changes light type to given type
	/// </summary>
	/// <param name="type">: light's type</param>
	inline void setType(Light::LightType type) { _light->setLightType(type); }

	/// <summary>
	/// Return light's type
	/// </summary>
	/// <returns>Light's type</returns>
	inline Light::LightType getLightType() { return _light->getLightType(); }

	/// <summary>
	/// Sets light's diffuse to given color
	/// </summary>
	/// <param name="red">: R parameter of the color</param>
	/// <param name="green">: G parameter of the color</param>
	/// <param name="blue">: B parameter of the color</param>
	inline void setDiffuse(float red, float green, float blue) { _light->setDiffuse(red, green, blue); }

	/// <summary>
	/// Sets light's diffuse to given color
	/// </summary>
	/// <param name="diffuse">: Colour structure</param>
	inline void setDiffuse(const Colour& diffuse) { _light->setDiffuse(diffuse.red, diffuse.green, diffuse.blue); }

	/// <summary>
	/// Returns light's diffuse color
	/// </summary>
	/// <returns>diffuse colour</returns>
	inline const Colour& getDiffuse() const { _light->getDiffuse(); }

	/// <summary>
	/// Sets light's specular to given color
	/// </summary>
	/// <param name="red">: R parameter of the color</param>
	/// <param name="green">: G parameter of the color</param>
	/// <param name="blue">: B parameter of the color</param>
	inline void setSpecular(float red, float green, float blue) { _light->setSpecular(red, green, blue); }

	/// <summary>
	/// Sets light's diffuse to given color
	/// </summary>
	/// <param name="specular">: Colour structure</param>
	inline void setSpecular(const Colour& specular) { _light->setSpecular(specular.red, specular.green, specular.blue); }

	/// <summary>
	/// Returns light's specular color
	/// </summary>
	/// <returns>specular colour</returns>
	inline const Colour& getSpecular() const { _light->getSpecular(); }

	/// <summary>
	/// Sets attenuation for the light
	/// </summary>
	/// <param name="range">: The absolute upper range of the light in world units.</param>
	/// <param name="constant">: The constant factor in the attenuation formula: 1.0 means never attenuate, 0.0 is complete attenuation.</param>
	/// <param name="linear">: The linear factor in the attenuation formula: 1 means attenuate evenly over the distance.</param>
	/// <param name="quadratic">: The quadratic factor in the attenuation formula: adds a curvature to the attenuation formula.</param>
	inline void setAttenuation(float range, float constant, float linear, float quadratic) { _light->setAttenuation(range, constant, linear, quadratic); }

	/// <summary>
	/// Returns light's attenuation range
	/// </summary>
	/// <returns>The absolute upper range of the light in world units</returns>
	inline const float getAttenuationRange() const { return _light->getAttenuationRange(); }

	/// <summary>
	/// Returns the constant factor in the attenuation formula
	/// </summary>
	/// <returns>Constant factor of light's attenuation</returns>
	inline const float getAttenuationConstant() const { return _light->getAttenuationConstant(); }

	/// <summary>
	/// Returns the linear factor in the attenuation formula
	/// </summary>
	/// <returns>Linear factor of light's attenuation</returns>
	inline const float getAttenuationLinear() const { return _light->getAttenuationLinear(); }

	/// <summary>
	/// Returns the quadric factor in the attenuation formula
	/// </summary>
	/// <returns>quadric factor of light's attenuation</returns>
	inline const float getAttenuationQuadric() const { return _light->getAttenuationQuadric(); }

	/// <summary>
	/// Only usefull if the type of this light is set to SpotLight
	/// </summary>
	/// <param name="innerAngle">: Angle covered by the bright inner cone.</param>
	/// <param name="outerAngle">: Angle covered by the outer cone.</param>
	/// <param name="fallof">:  The rate of falloff between the inner and outer cones. 1.0 means a linear falloff,
	///							less means slower falloff, higher means faster falloff.</param>
	inline void setSpotlightRange(float innerAngle, float outerAngle, float falloff) { _light->setSpotlightRange(innerAngle, outerAngle, falloff); }

	/// <summary>
	/// Only usefull if light's type is set to spotLight
	/// </summary>
	/// <returns>splotlight fallOf</returns>
	inline const float getSpotlightFallOff() const { return _light->getSpotlightFallOff(); }

	/// <summary>
	/// Only usefull if light's type is set to spotLight
	/// </summary>
	/// <returns>splotlight inner angle</returns>
	inline const float getSpotlightInnerAngle() const { return _light->getSpotlightInnerAngle(); }

	/// <summary>
	/// Only usefull if light's type is set to spotLight
	/// </summary>
	/// <returns>splotlight outter angle</returns>
	inline const float getSpotlightOuterAngle() const { return _light->getSpotlightOuterAngle(); }

	/// <summary>
	/// Sets the intensity of this light
	/// </summary>
	/// <param name="power">: Default value is already set at 1</param>
	inline void setPowerScale(float power) { _light->setPowerScale(power); }

	/// <summary>
	/// Return the intensity of this light
	/// </summary>
	/// <returns>intensity of this light</returns>
	inline const float getPowerScale() const { _light->getPowerScale(); }

	/// <summary>
	/// Changes light visibility
	/// </summary>
	/// <param name="visible">true means visible</param>
	inline void setVisible(bool visible) { _light->setVisible(visible); }

	/// <summary>
	/// Returns the value set by MovableObject::setVisible only.
	/// </summary>
	/// <returns>if it's visible or not</returns>
	inline const bool getVisible() const { return _light->getVisible(); }

	/// <summary>
	///	String to light type converter required for lua.
	/// </summary>
	/// <returns>if it's visible or not</returns>
	const Light::LightType convertLightType(std::string type);


private:

	/// <summary>
	/// Redefined by child classes called when component is enabled
	/// </summary>
	void onEnable() override;

	/// <summary>
	/// Redefined by child classes called when component is disabled
	/// </summary>
	void onDisable() override;

	Transform* _tr;
	Light* _light;
};

#endif LIGHT_COMPONENT_H
