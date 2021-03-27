#include "Camera.h"
Camera::Camera(Ogre::SceneManager* scn, int cameraNum) :_camera(new Ogre::Camera("camera" + cameraNum, scn)),_node(nullptr),
	_viewport(nullptr)
{
	//CHANGE: si tenemos algo que gestione la escena llamarlo para que sea hijo de otro nodo
	_node = scn->createSceneNode();
	_node->attachObject(_camera);
	_camera->setAutoAspectRatio(true);
	_viewport = _camera->getViewport();
	_viewport->setOverlaysEnabled(true);
}

Camera::~Camera()
{
	delete _camera;
	delete _node;
}

void Camera::setPlanes(float near, float far)
{
	_camera->setNearClipDistance(near);
	_camera->setFarClipDistance(far);
}

void Camera::setProjection(bool ortho)
{
	if (ortho)
		_camera->setProjectionType(Ogre::PT_ORTHOGRAPHIC);
	else _camera->setProjectionType(Ogre::PT_PERSPECTIVE);

}
void Camera::setFovY(float fovy)
{
	Ogre::Radian fovyInRadians(Ogre::Math::DegreesToRadians(fovy));
	_camera->setFOVy(fovyInRadians);
}
void Camera::setFrustrumDimensions(float left, float right, float top, float bot)
{
	_camera->setFrustumExtents(left, right, top, bot);
}

void Camera::setOrthoWindowDimensions(float w, float h)
{
	if (_camera->getProjectionType() == Ogre::PT_ORTHOGRAPHIC)
		_camera->setOrthoWindow(w, h);
	
}

void Camera::setViewportDimensions(float left, float top, float w, float h)
{
	_viewport->setDimensions(left, top, w, h);

}
