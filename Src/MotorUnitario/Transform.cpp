#include "Transform.h"
#include "GameObject.h"
#include "ComponentIDs.h"
#include "RigidBodyComponent.h"
#include "ColliderComponent.h"
#include "MotorGrafico/GraphicsEngine.h"
#include "includeLUA.h"

#include <math.h>
#define PI 3.14159265


Transform::Transform(): Component(ComponentId::Transform), _position(0, 0, 0), _rotation(0, 0, 0), _scale(1, 1, 1)
{

}

void Transform::setPosition(const Vector3& position)
{
	_position = position;
	RigidBodyComponent* rb = dynamic_cast<RigidBodyComponent*>(_gameObject->getComponent(ComponentId::Rigidbody));
	if (rb != nullptr) {
		rb->setPosition(_position);
	}

	ColliderComponent* boxColl = dynamic_cast<BoxColliderComponent*>(_gameObject->getComponent(ComponentId::BoxCollider));
	ColliderComponent* sphColl = dynamic_cast<SphereColliderComponent*>(_gameObject->getComponent(ComponentId::SphereCollider));
	ColliderComponent* capsColl = dynamic_cast<CapsuleColliderComponent*>(_gameObject->getComponent(ComponentId::CapsuleCollider));
	if (boxColl != nullptr) {
		boxColl->setPosition(_position);
	}
	else if (sphColl != nullptr) {
		sphColl->setPosition(_position);
	}
	else if (capsColl != nullptr) {
		capsColl->setPosition(_position);
	}
}

void Transform::awake(luabridge::LuaRef& data)
{
	const std::string& parentName = _gameObject->getParent() != nullptr ? _gameObject->getParent()->getName() : "";
	GraphicsEngine::getInstance()->addNode(_gameObject->getName(), parentName);

	luabridge::LuaRef lua_coord = data["Coord"];
	_position = { lua_coord["X"].cast<double>(),lua_coord["Y"].cast<double>(), lua_coord["Z"].cast<double>() };
	std::cout << "Tr: X=" << _position.getX() << ", Y=" << _position.getY() << ", Z=" << _position.getZ() << std::endl;
}

void Transform::updateFromPhysics(const Vector3& position, const Vector3& rotation)
{
	_position = position;
	_rotation = rotation;
}

void Transform::setRotation(const Vector3& rotation)
{
	_rotation = rotation;

	RigidBodyComponent* rb = dynamic_cast<RigidBodyComponent*>(_gameObject->getComponent(ComponentId::Rigidbody));
	if (rb != nullptr) {
		rb->setRotation(_rotation);
	}

	ColliderComponent* boxColl = dynamic_cast<BoxColliderComponent*>(_gameObject->getComponent(ComponentId::BoxCollider));
	ColliderComponent* sphColl = dynamic_cast<SphereColliderComponent*>(_gameObject->getComponent(ComponentId::SphereCollider));
	ColliderComponent* capsColl = dynamic_cast<CapsuleColliderComponent*>(_gameObject->getComponent(ComponentId::CapsuleCollider));
	if (boxColl != nullptr) {
		boxColl->setPosition(_position);
	}
	else if (sphColl != nullptr) {
		sphColl->setPosition(_position);
	}
	else if (capsColl != nullptr) {
		capsColl->setPosition(_position);
	}
}

Transform::~Transform()
{
}

Vector3 Transform::getForward() const
{
	double X = sin(_rotation.getY() * PI / 180.0) * cos(_rotation.getX() * PI / 180.0);
	double Y = sin(-_rotation.getX() * PI / 180.0);
	double Z = cos(_rotation.getX() * PI / 180.0) * cos(_rotation.getY() * PI / 180.0);

	return Vector3(X, Y, -Z);
}
