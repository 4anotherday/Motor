#pragma once
#ifndef COLLIDERCOMPONENT_H
#define COLLIDERCOMPONENT_H

#include "Component.h"

class GameObject;
class Collider;
class BoxCollider;
class SphereCollider;
class CapsuleCollider;
class Vector3;

#define VEC3_TO_TUPLE(vec) std::tuple<float, float, float>(vec.getX(), vec.getY(), vec.getZ())
#define TUPLE_TO_VEC3(tuple) Vector3(std::get<0>(tuple), std::get<1>(tuple), std::get<2>(tuple))

class ColliderComponent : public Component {
public:

	/// <summary>
	/// Callback for gameobject collision
	/// </summary>
	/// <param name="thisGO"></param>
	/// <param name="otherGO"></param>
	static void gameObjectsCollision(GameObject* thisGO, GameObject* otherGO);

	/// <summary>
	/// Callback for trgger collision
	/// </summary>
	/// <param name="thisGO"></param>
	/// <param name="otherGO"></param>
	static void gameObjectTriggered(GameObject* thisGO, GameObject* otherGO);

	/// <summary>
	/// Destructor of the class
	/// </summary>
	~ColliderComponent();

	/// <summary>
	/// Sets the collider for collisions
	/// </summary>
	void setCollider();

	/// <summary>
	/// Sets the collider as a trigger
	/// </summary>
	void setTrigger();

	/// <summary>
	/// Sets the position of the transform to a specified one
	/// </summary>
	void setPosition(Vector3 pos);

	/// <summary>
	/// Sets the rotation of the transform to a specified one
	/// </summary>
	void setRotation(Vector3 rot);

protected:
	/// <summary>
	/// Contructor of the class
	/// </summary>
	/// <param name="id">Component ID</param>
	/// <param name="gameObject">GameObject owner of the component</param>
	ColliderComponent(int id, GameObject* gameObject);

	/// <summary>
	/// Contructor of the class
	/// </summary>
	/// <param name="id">Component ID</param>
	ColliderComponent(int id);

	Collider* _collider;
};

#endif // !COLLIDERCOMPONENT_H
//////////////////////////////////////////////////////

class BoxColliderComponent : public ColliderComponent {
public:

	/// <summary>
	/// Contructor of the class
	/// </summary>
	/// <param name="gameObject">GameObject owner of the component</param>
	BoxColliderComponent(GameObject* gameObject);

	/// <summary>
	/// Contructor of the class
	/// </summary>
	BoxColliderComponent();

	/// <summary>
	/// Destructor of the class
	/// </summary>
	virtual ~BoxColliderComponent();

	/// <summary>
	/// Changes box size
	/// </summary>
	/// <param name="x">New width</param>
	/// <param name="y">New height</param>
	/// <param name="z">New depth</param>
	void setScale(int width, int heigh, int depth);
};

/////////////////////////////////////////////////////////

class SphereColliderComponent : public ColliderComponent {
public:

	/// <summary>
	/// Contructor of the class
	/// </summary>
	/// <param name="gameObject">GameObject owner of the component</param>
	SphereColliderComponent(GameObject* gameObject);

	/// <summary>
	/// Contructor of the class
	/// </summary>
	SphereColliderComponent();

	/// <summary>
	/// Destructor of the class
	/// </summary>
	virtual ~SphereColliderComponent();

	/// <summary>
	/// Changes sphere radius
	/// </summary>
	/// <param name="r">New new radius</param>
	void setScale(int radius);
};

////////////////////////////////////////////////////

class CapsuleColliderComponent : public ColliderComponent {
public:

	/// <summary>
	/// Contructor of the class
	/// </summary>
	/// <param name="gameObject">GameObject owner of the component</param>
	CapsuleColliderComponent(GameObject* gameObject);

	/// <summary>
	/// Contructor of the class
	/// </summary>
	CapsuleColliderComponent();

	/// <summary>
	/// Destructor of the class
	/// </summary>
	virtual ~CapsuleColliderComponent();

	/// <summary>
	/// Changes capsule's dimensions
	/// </summary>
	/// <param name="r">New radius</param>
	/// <param name="l">New length</param>
	void setScale(int radius, int length);
};