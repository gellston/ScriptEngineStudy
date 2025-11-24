

#include "core/object.h"
#include "core/rect.h"

#include "core/snapShot/snapValue.h"
#include "core/reflection/typeRegistry.h"


#pragma region Static Constructor
STATIC_CTR_DEFINE(visionhub::v1::rect) {

	REFLECTION_BEGIN(rect)
		REFLECTION_PROP(rect, x)
		REFLECTION_PROP(rect, y)
		REFLECTION_PROP(rect, width)
		REFLECTION_PROP(rect, height)
		REFLECTION_PROP(rect, objType)
	REFLECTION_END()

}
#pragma endregion


#pragma region Constructor 

visionhub::v1::rect::rect(double x, double y, double width, double height):visionhub::v1::object(visionhub::v1::coreTypes::rect){

	this->_x = x;
	this->_y = y;
	this->_width = width;
	this->_height = height;
}

#pragma endregion


#pragma region Static Functions
visionhub::v1::rect_ptr visionhub::v1::rect::make_rect(double x, double y, double width, double height) {
	return std::make_shared<visionhub::v1::rect>(x, y, width, height);
}
#pragma endregion



#pragma region Public Functions
visionhub::v1::snapValue_ptr visionhub::v1::rect::snap() {
	auto snapValue = std::make_shared<visionhub::v1::snapValue>();
	snapValueAtt::setKind(snapValue, visionhub::v1::snapKind::_native_);
	snapValueAtt::addField(snapValue, "x", this->_x);
	snapValueAtt::addField(snapValue, "y", this->_y);
	snapValueAtt::addField(snapValue, "width", this->_width);
	snapValueAtt::addField(snapValue, "height", this->_height);

	return snapValue;
}

double visionhub::v1::rect::x() {
	return this->_x;
}

double visionhub::v1::rect::y() {
	return this->_x;
}

double visionhub::v1::rect::width() {
	return this->_x;
}

double visionhub::v1::rect::height() {
	return this->_x;
}

void visionhub::v1::rect::x(double value) {
	this->_x = value;
}

void visionhub::v1::rect::y(double value) {
	this->_y = value;
}

void visionhub::v1::rect::width(double value) {
	this->_width = value;
}

void visionhub::v1::rect::height(double value) {
	this->_height = value;
}
#pragma endregion


