#include "CameraComponent.h"
#include "MotorGrafico/Camera.h"
#include "ComponentIDs.h"
#include "Transform.h"
#include "GameObject.h"
#include "KeyboardInput.h"
#include "includeLUA.h"

void CameraComponent::awake(luabridge::LuaRef& data)
{
	/*
	setProjection(data["Projection"].cast<bool>());
	setFovY(data["Fovy"].cast<float>());
	setFrustrumDimensions(data["Frustrum"]["Left"].cast<float>(), data["Frustrum"]["Right"].cast<float>(),
		data["Frustrum"]["Top"].cast<float>(), data["Frustrum"]["Bot"].cast<float>());
	setOrthoWindowDimensions(data["OrthoWindow"]["W"].cast<float>(), data["OrthoWindow"]["H"].cast<float>());
*/

	//It is necesary to create the camera in this method and not in the constructor because each camera
	//Has its own viewport and it is necesary to specify its zOrder when creating a new one
	// (Viewports zOrders can not be modified)

	int zOrder = 1;
	if (LUAFIELDEXIST(zOrder))
		zOrder = GETLUAFIELD(zOrder, int);

	if(LUAFIELDEXIST(SlaveRotation))
		_slaveRotation = GETLUAFIELD(SlaveRotation, bool);

	float l, t, w, h;
	l = t = 0, w = h = 1;
	if (LUAFIELDEXIST(Viewport))
	{
		if (!data["Viewport"]["Left"].isNil())
			l = data["Viewport"]["Left"].cast<float>();
		if (!data["Viewport"]["Top"].isNil())
			t = data["Viewport"]["Top"].cast<float>();
		if (!data["Viewport"]["H"].isNil())
			h = data["Viewport"]["H"].cast<float>();
		if (!data["Viewport"]["W"].isNil())
			w = data["Viewport"]["W"].cast<float>();
	}

	_camera = new Camera(_gameObject->getName(), zOrder, l, t, w, h);

	if (LUAFIELDEXIST(DisplayOverlays))
		_camera->renderOverlays(GETLUAFIELD(DisplayOverlays, bool));

	if (LUAFIELDEXIST(Plane)) {
		float near, far;
		near = far = 0;
		if (!data["Plane"]["Near"].isNil())
			near = data["Plane"]["Near"].cast<float>();
		if (!data["Plane"]["Far"].isNil())
			far = data["Plane"]["Far"].cast<float>();
		setPlanes(near, far);
	}

	if (LUAFIELDEXIST(Compositors)) {
		for (int i = 1; i <= data["Compositors"].length(); i += 2) {
			_camera->addCompositor(data["Compositors"][i].tostring().c_str());
			setCompositor(data["Compositors"][i].tostring().c_str(), data["Compositors"][i + 1].cast<bool>());
		}
	}
}

CameraComponent::CameraComponent() : Component(ComponentId::Camera), _camera(nullptr), _tr(nullptr), _slaveRotation(false)
{
}

CameraComponent::~CameraComponent()
{
	delete _camera; _camera == nullptr;
}

void CameraComponent::start()
{
	_tr = static_cast<Transform*>(_gameObject->getComponent(ComponentId::Transform));

	Vector3 rot = _tr->getRotation();
	_camera->setOrientation(rot.getX(), rot.getY(), rot.getZ());
}

void CameraComponent::update()
{
	if (KeyBoardInput::getInstance()->isKeyDown(KeyCode::KEYCODE_S)) {
		_camera->pitchDegrees(-1, true);
	}
	else if (KeyBoardInput::getInstance()->isKeyDown(KeyCode::KEYCODE_W)) {
		_camera->pitchDegrees(1, true);
	}
	if (KeyBoardInput::getInstance()->isKeyDown(KeyCode::KEYCODE_A)) {
		_camera->yawDegrees(-1, true);
	}
	else if (KeyBoardInput::getInstance()->isKeyDown(KeyCode::KEYCODE_D)) {
		_camera->yawDegrees(1, true);
	}

	Vector3 pos = _tr->getPosition();

	if (KeyBoardInput::getInstance()->isKeyDown(KeyCode::KEYCODE_LEFT)) {
		pos.setX(pos.getX() - 0.05);
	}
	else if (KeyBoardInput::getInstance()->isKeyDown(KeyCode::KEYCODE_RIGHT)) {
		pos.setX(pos.getX() + 0.05);
	}
	if (KeyBoardInput::getInstance()->isKeyDown(KeyCode::KEYCODE_UP)) {
		pos.setY(pos.getY() + 0.05);
	}
	else if (KeyBoardInput::getInstance()->isKeyDown(KeyCode::KEYCODE_DOWN)) {
		pos.setY(pos.getY() - 0.05);
	}
	if (KeyBoardInput::getInstance()->isKeyDown(KeyCode::KEYCODE_E)) {
		pos.setZ(pos.getZ() + 0.05);
	}
	else if (KeyBoardInput::getInstance()->isKeyDown(KeyCode::KEYCODE_Q)) {
		pos.setZ(pos.getZ() - 0.05);
	}
	_tr->setPosition(pos);
	_camera->setPosition(static_cast<float>(pos.getX()), static_cast<float>(pos.getY()), static_cast<float>(pos.getZ()));

	if (_slaveRotation) {
		Vector3 rot = _tr->getRotation();
		_camera->setOrientation(rot.getX(), rot.getY(), rot.getZ());
	}
}

void CameraComponent::rotate(float angle, int xAxis, int yAxis, int zAxis)
{
	if(!_slaveRotation)
		_camera->rotate(angle, xAxis, yAxis, zAxis);
}

void CameraComponent::lookAt(float x, float y, float z)
{
	if (!_slaveRotation)
		_camera->lookAt(x, y, z);
}

void CameraComponent::pitchDegrees(float degrees, bool world)
{
	if (!_slaveRotation)
		_camera->pitchDegrees(degrees, world);	
}

void CameraComponent::pitchRadians(float radians, bool world)
{
	if (!_slaveRotation)
		_camera->pitchRadians(radians, world);
}

void CameraComponent::yawDegrees(float degrees, bool world)
{
	_camera->yawDegrees(degrees, world);
}

void CameraComponent::yawRadians(float radians, bool world)
{
	if (!_slaveRotation)
		_camera->yawRadians(radians, world);
}

void CameraComponent::rollDegrees(float degrees, bool world)
{
	if (!_slaveRotation)
		_camera->rollDegrees(degrees, world);
}

void CameraComponent::rollRadians(float radians, bool world)
{
	if (!_slaveRotation)
		_camera->rollRadians(radians, world);
}

void CameraComponent::setOrientation(float x, float y, float z)
{
	if (!_slaveRotation)
		_camera->setOrientation(x, y, z);
}

void CameraComponent::setPlanes(float near, float far)
{
	_camera->setPlanes(near, far);
}

void CameraComponent::setProjection(bool ortho)
{
	_camera->setProjection(ortho);
}

void CameraComponent::setFovY(float fovy)
{
	_camera->setFovY(fovy);
}

void CameraComponent::setFrustrumDimensions(float left, float right, float top, float bot)
{
	_camera->setFrustrumDimensions(left, right, top, bot);
}

void CameraComponent::setOrthoWindowDimensions(float w, float h)
{
	_camera->setOrthoWindowDimensions(w, h);
}

void CameraComponent::setViewportVisibility(bool visible, float x, float y, float w, float h)
{
	_camera->setViewportVisibility(visible, x, y, w, h);
}

void CameraComponent::setViewportDimensions(float left, float top, float w, float h)
{
	_camera->setViewportDimensions(left, top, w, h);
}

const Vector3& CameraComponent::getOrientation()
{
	std::tuple<float, float, float> rot = _camera->getOrientation();
	return Vector3(std::get<0>(rot), std::get<1>(rot), std::get<2>(rot));
}

void CameraComponent::setCompositor(const char* compositor, bool enable)
{
	_camera->setCompositor(compositor, enable);
}

void CameraComponent::onEnable()
{
	_camera->setViewportVisibility(true);
}

void CameraComponent::onDisable()
{
	_camera->setViewportVisibility(false);
}
