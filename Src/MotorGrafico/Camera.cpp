#include "Camera.h"
#include <OgreRenderWindow.h>

Camera::Camera(Ogre::SceneManager* scn, Ogre::RenderWindow* rWin, int cameraNum) :_camera(new Ogre::Camera("camera" + cameraNum, scn)), _renderWindow(rWin), _node(nullptr),
_viewport(nullptr)
{
	//CHANGE: si tenemos algo que gestione la escena llamarlo para que sea hijo de otro nodo
	_camera->setAutoAspectRatio(true);
	_node = scn->getRootSceneNode()->createChildSceneNode(_camera->getName());
	_node->attachObject(_camera);

	_viewport = rWin->addViewport(_camera);
	_viewport->setBackgroundColour(Ogre::ColourValue(0.2, 0.2, 0.2));
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

void Camera::setCamera(Ogre::Camera* cam)
{
	if (cam == nullptr)
		throw "Null camera";
	if (_camera != nullptr)
	{
		delete _camera;
		delete _viewport;
	}
	_camera = cam;
	_viewport = _camera->getViewport();
}

void Camera::setNode(Ogre::SceneNode* node)
{
	if (node == nullptr)
		throw "null node";
	if (_node != nullptr) {
		_node->detachObject(_camera);
	}
	_node = node;
	_node->attachObject(_camera);
}

void Camera::setReenderWindow(Ogre::RenderWindow* renderWin)
{
	//errors check
	if (renderWin == nullptr)
		throw "null renderWin";

	_renderWindow = renderWin;
}
