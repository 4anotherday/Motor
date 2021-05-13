#include "RenderObjectComponent.h"
#include "GameObject.h"
#include "Transform.h"
#include "ComponentIDs.h"
#include "includeLUA.h"
#include "MotorGrafico/RenderObject.h"
#include <algorithm>

RenderObjectComponent::RenderObjectComponent() :Component(ComponentId::RenderObject, nullptr), _renderObject(nullptr),
_transform(nullptr), _meshName("")
{
}

RenderObjectComponent::~RenderObjectComponent()
{
}

void RenderObjectComponent::awake(luabridge::LuaRef& data)
{
	if (LUAFIELDEXIST(MeshName))
		_meshName = GETLUASTRINGFIELD(MeshName);
	else throw "Mesh doesn't exists\n";
	_renderObject = new RenderObject(_meshName, _gameObject->getName());
	_renderObject->init();

	_transform = static_cast<Transform*>(_gameObject->getComponent(ComponentId::Transform));

	//To establish proportions relative to the mesh
	Vector3 size = _renderObject->getMeshSize();
	float _maxSize = std::max({ size.getX(), size.getY(), size.getZ() });
	_transform->setProportions(size / _maxSize);

	if (LUAFIELDEXIST(Material))
		setMaterial(GETLUASTRINGFIELD(Material));
	else throw "Material doesn't exists\n ";

	if (LUAFIELDEXIST(Visible))
		setVisible(GETLUAFIELD(Visible, bool));

	if (LUAFIELDEXIST(Shadows))
		setCastShadows(GETLUAFIELD(Shadows, bool));

	float renderDist = 999;
	if (LUAFIELDEXIST(RenderingDistance))
		setRenderingDistance(GETLUAFIELD(RenderingDistance, float));

	if (LUAFIELDEXIST(RotateAngle) && LUAFIELDEXIST(Rotate))
	{
		float x, y, z;
		x = y = z = 0;
		if (!data["Rotate"]["X"].isNil()) x = data["Rotate"]["X"].cast<float>();
		if (!data["Rotate"]["Y"].isNil()) y = data["Rotate"]["Y"].cast<float>();
		if (!data["Rotate"]["Z"].isNil()) z = data["Rotate"]["Z"].cast<float>();
		rotate(GETLUAFIELD(RotateAngle, float), x, y, z);
	}
}

void RenderObjectComponent::start()
{
	float x = static_cast<float>(_transform->getPosition().getX());
	float y = static_cast<float>(_transform->getPosition().getY());
	float z = static_cast<float>(_transform->getPosition().getZ());
	_renderObject->setPosition(x, y, z);
}

void RenderObjectComponent::update()
{
	float x = static_cast<float>(_transform->getPosition().getX());
	float y = static_cast<float>(_transform->getPosition().getY());
	float z = static_cast<float>(_transform->getPosition().getZ());
	_renderObject->setPosition(x, y, z);

	Vector3 dir = _transform->getRotation();
	Quaternion q = _transform->ToQuaternion(dir.getX(), dir.getY(), dir.getZ());
	_renderObject->setRotation(q.x, q.y, q.z, q.w);


	/*	
		start size: 50  200  50  -> scale 1 1 1 -> end size: 0.25  1  0.25
	*/
	Vector3 size = _transform->getSize();
	_renderObject->setScale(size.getX(), size.getY(), size.getZ());
}

void RenderObjectComponent::setMaterial(std::string const& materialName)
{
	_renderObject->setMaterial(materialName);
}

void RenderObjectComponent::setPosition(float x, float y, float z)
{
	_renderObject->setPosition(x, y, z);
}

void RenderObjectComponent::rotate(float angle, float x, float y, float z)
{
	_renderObject->rotate(angle, x, y, z);
}

void RenderObjectComponent::setScale(float x, float y, float z)
{
	_renderObject->setScale(x, y, z);
}

void RenderObjectComponent::scale(float x, float y, float z)
{
	_renderObject->scale(x, y, z);
}

void RenderObjectComponent::lookAt(float x, float y, float z)
{
	_renderObject->lookAt(x, y, z);
}

void RenderObjectComponent::setVisible(bool visible)
{
	_renderObject->setVisible(visible);
}

void RenderObjectComponent::setCastShadows(bool castShadows)
{
	_renderObject->setCastShadows(castShadows);
}

void RenderObjectComponent::setRenderingDistance(float distance)
{
	_renderObject->setRenderingDistance(distance);
}
void RenderObjectComponent::setAlpha(float alpha)
{
	if (alpha >= 0.0f && alpha <= 1.0f)
		_renderObject->setAlpha(alpha);
	else Logger::getInstance()->log("alpha value must be in range [0,1]", Logger::Level::WARN);
}

void RenderObjectComponent::onEnable()
{
	_renderObject->setVisible(true);
}

void RenderObjectComponent::onDisable()
{
	_renderObject->setVisible(false);
}