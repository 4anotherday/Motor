#include "ImageRenderComponent.h"
#include "ComponentIDs.h"
#include "Transform.h"
#include "GameObject.h"
#include "includeLUA.h"

ImageRender::BillboardOrigin getBillboardOrigin(std::string cmp);
ImageRender::BillboardType getBillboardType(std::string cmp);
ImageRender::BillboardRotationType getBillboardRotationType(std::string cmp);

ImageRenderComponent::ImageRenderComponent() : Component(ComponentId::ImageRender), _imageRender(nullptr), _tr(nullptr)
{
}

ImageRenderComponent::~ImageRenderComponent()
{
	delete _imageRender; _imageRender == nullptr;
}
void ImageRenderComponent::awake(luabridge::LuaRef& data)
{
	_imageRender = new ImageRender(_gameObject->getName());
	if (LUAFIELDEXIST("DefaultDimension"))
	{
		int w = data["DefaultDimension"]["W"].cast<float>();
		int h = data["DefaultDimension"]["H"].cast<float>();

		_imageRender->setDefaultDimensions(w, h);
	}

	if (LUAFIELDEXIST("MaterialName"))_imageRender->setMaterialName(GETLUASTRINGFIELD(MaterialName));

	if (LUAFIELDEXIST("Visible"))
		_imageRender->setVisible(GETLUAFIELD(Visible, bool));

	if (LUAFIELDEXIST("BillboardOrigin"))
		_imageRender->setBillboardOrigin(getBillboardOrigin(GETLUASTRINGFIELD(BillboardOrigin)));
	if (LUAFIELDEXIST("BillboardType"))
		_imageRender->setBillboardType(getBillboardType(GETLUASTRINGFIELD(BillboardType)));
	if (LUAFIELDEXIST("BillboardRotationType"))
		_imageRender->setBillboardRotationType(getBillboardRotationType(GETLUASTRINGFIELD(BillboardRotationType)));

	if (LUAFIELDEXIST("Scale"))_imageRender->setScale(data["Scale"]["X"].cast<float>(), data["Scale"]["Y"].cast<float>(), data["Scale"]["Z"].cast<float>());

	if (LUAFIELDEXIST("Rotation"))_imageRender->setRotation(data["Rotation"]["X"].cast<float>(), data["Rotation"]["Y"].cast<float>(),
		data["Rotation"]["Z"].cast<float>(), data["Rotation"]["Angle"].cast<float>());
}

void ImageRenderComponent::start()
{
	_tr = static_cast<Transform*>(_gameObject->getComponent(ComponentId::Transform));

	float x, y, z;
	if (_tr != nullptr) {
		x = static_cast<float>(_tr->getPosition().getX());
		y = static_cast<float>(_tr->getPosition().getY());
		z = static_cast<float>(_tr->getPosition().getZ());		
	}
	else {
		//Default positions
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}
	
	_imageRender->setPosition(x, y, z);
}

void ImageRenderComponent::update()
{
	float x = static_cast<float>(_tr->getPosition().getX());
	float y = static_cast<float>(_tr->getPosition().getY());
	float z = static_cast<float>(_tr->getPosition().getZ());

	_imageRender->setPosition(x, y, z);
}

void ImageRenderComponent::onEnable()
{
	_imageRender->setVisible(true);
}

void ImageRenderComponent::onDisable()
{
	_imageRender->setVisible(false);
}

ImageRender::BillboardOrigin getBillboardOrigin(std::string cmp) {
	if (cmp == "BBO_TOP_LEFT")
		return ImageRender::BillboardOrigin::BBO_TOP_LEFT;
	else if (cmp == "BBO_TOP_CENTER")
		return ImageRender::BillboardOrigin::BBO_TOP_CENTER;
	else if (cmp == "BBO_TOP_RIGHT")
		return ImageRender::BillboardOrigin::BBO_TOP_RIGHT;
	else if (cmp == "BBO_CENTER_LEFT")
		return ImageRender::BillboardOrigin::BBO_CENTER_LEFT;
	else if (cmp == "BBO_CENTER")
		return ImageRender::BillboardOrigin::BBO_CENTER;
	else if (cmp == "BBO_CENTER_RIGHT")
		return ImageRender::BillboardOrigin::BBO_CENTER_RIGHT;
	else if (cmp == "BBO_BOTTOM_LEFT")
		return ImageRender::BillboardOrigin::BBO_BOTTOM_LEFT;
	else if (cmp == "BBO_BOTTOM_CENTER")
		return ImageRender::BillboardOrigin::BBO_BOTTOM_CENTER;
	else if (cmp == "BBO_BOTTOM_RIGHT")
		return ImageRender::BillboardOrigin::BBO_BOTTOM_RIGHT;
}

ImageRender::BillboardType getBillboardType(std::string cmp)
{
	if (cmp == "BBT_POINT")
		return ImageRender::BillboardType::BBT_POINT;
	else if (cmp == "BBT_ORIENTED_COMMON")
		return ImageRender::BillboardType::BBT_ORIENTED_COMMON;
	else if (cmp == "BBT_ORIENTED_SELF")
		return ImageRender::BillboardType::BBT_ORIENTED_SELF;
	else if (cmp == "BBT_PERPENDICULAR_COMMON")
		return ImageRender::BillboardType::BBT_PERPENDICULAR_COMMON;
	else if (cmp == "BBT_PERPENDICULAR_SELF")
		return ImageRender::BillboardType::BBT_PERPENDICULAR_SELF;
}

ImageRender::BillboardRotationType getBillboardRotationType(std::string cmp)
{
	if (cmp == "BBR_VERTEX")
		return ImageRender::BillboardRotationType::BBR_VERTEX;
	else if (cmp == "BBR_TEXCOORD")
		return ImageRender::BillboardRotationType::BBR_TEXCOORD;
}