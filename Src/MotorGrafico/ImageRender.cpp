#include "ImageRender.h"
#include <OgreSceneNode.h>
#include <OgreBillboardSet.h>
#include <OgreSceneManager.h>
#include "GraphicsEngine.h"

ImageRender::ImageRender(const std::string& name) :_billboardSet(nullptr), _billboardSetNode(nullptr)
{
	Ogre::SceneManager* sM = GraphicsEngine::getInstance()->getSceneManager();
	_billboardSetNode = sM->getSceneNode(name);
	_billboardSet = sM->createBillboardSet(1);
	_billboardSet->createBillboard(_billboardSetNode->getPosition());
	_billboardSetNode->attachObject(_billboardSet);
}

ImageRender::~ImageRender()
{
	if (_billboardSet != nullptr) GraphicsEngine::getInstance()->getSceneManager()->destroyBillboardSet(_billboardSet);
}

void ImageRender::setDefaultDimensions(float width, float height)
{
	_billboardSet->setDefaultDimensions(width, height);
}

void ImageRender::setMaterialName(const std::string& name)
{
	_billboardSet->setMaterialName(name);
}

void ImageRender::setVisible(bool visible)
{
	_billboardSet->setVisible(visible);
}

void ImageRender::setBillboardOrigin(BillboardOrigin type)
{
	_billboardSet->setBillboardOrigin((Ogre::BillboardOrigin)type);
}

void ImageRender::setBillboardType(BillboardType type)
{
	_billboardSet->setBillboardType((Ogre::BillboardType)type);
}

void ImageRender::setBillboardRotationType(BillboardRotationType type)
{
	_billboardSet->setBillboardRotationType((Ogre::BillboardRotationType)type);
}

void ImageRender::setPosition(float x, float y, float z)
{
	_billboardSetNode->setPosition((Ogre::Real)x, (Ogre::Real)y, (Ogre::Real)z);
}

void ImageRender::setScale(float x, float y, float z)
{
	_billboardSetNode->scale((Ogre::Real)x, (Ogre::Real)y, (Ogre::Real)z);
}

void ImageRender::setRotation(float x, float y, float z, float angle)
{
	_billboardSetNode->rotate(Ogre::Vector3((Ogre::Real)x, (Ogre::Real)y, (Ogre::Real)z), Ogre::Radian((Ogre::Real)angle));
}