

#include "core/object.h"
#include "core/test.h"

#include "core/snapShot/snapValue.h"
#include "core/reflection/typeRegistry.h"


#pragma region Static Constructor
STATIC_CTR_DEFINE(visionhub::v1::test) {

	REFLECTION_BEGIN(test)
		REFLECTION_PROP(test, x)
		REFLECTION_PROP(test, y)
		REFLECTION_PROP(test, width)
		REFLECTION_PROP(test, height)
		REFLECTION_PROP(test, objType)
		REFLECTION_PROP(test, get)
		REFLECTION_PROP(test, get2)
	REFLECTION_END()

}
#pragma endregion


#pragma region Constructor 

visionhub::v1::test::test(double x, double y, double width, double height) :visionhub::v1::object(visionhub::v1::coreTypes::test) {

	this->_x = x;
	this->_y = y;
	this->_width = width;
	this->_height = height;
}

visionhub::v1::test_ptr visionhub::v1::test::make_test(double x, double y, double width, double height) {
	return std::make_shared<test>(x, y, width, height);
}



#pragma endregion


#pragma region Public Functions
std::shared_ptr<visionhub::v1::snapValue> visionhub::v1::test::snap() {
	auto snapValue = std::make_shared<visionhub::v1::snapValue>();
	snapValueAtt::setKind(snapValue, visionhub::v1::snapKind::_native_);
	snapValueAtt::addField(snapValue, "x", this->_x);
	snapValueAtt::addField(snapValue, "y", this->_y);
	snapValueAtt::addField(snapValue, "width", this->_width);
	snapValueAtt::addField(snapValue, "height", this->_height);
	snapValueAtt::addField(snapValue, "height", this->_height);
	return snapValue;
}

double visionhub::v1::test::x() {
	return this->_x;
}

double visionhub::v1::test::y() {
	return this->_x;
}

double visionhub::v1::test::width() {
	return this->_x;
}

double visionhub::v1::test::height() {
	return this->_x;
}

void visionhub::v1::test::x(double value) {
	this->_x = value;
}

void visionhub::v1::test::y(double value) {
	this->_y = value;
}

void visionhub::v1::test::width(double value) {
	this->_width = value;
}

void visionhub::v1::test::height(double value) {
	this->_height = value;
}

std::vector<visionhub::v1::test_ptr> visionhub::v1::test::get() {
	std::vector<visionhub::v1::test_ptr> temp;

	for (int index = 0; index < 2; index++)
		temp.push_back(std::make_shared<visionhub::v1::test>(100, 100, 100, 100));

	return temp;
}

std::unordered_map<std::string, visionhub::v1::test_ptr> visionhub::v1::test::get2() {
	std::unordered_map<std::string, visionhub::v1::test_ptr> temp;
	for (int index = 0; index < 2; index++)
		temp.insert({ "test", std::make_shared<visionhub::v1::test>(100, 100, 100, 100) });
	return temp;
}

std::unordered_map<std::string, int> visionhub::v1::test::get3() {
	std::unordered_map<std::string, int> temp;
	for (int index = 0; index < 2; index++)
		temp.insert({ "test", 1});
	return temp;
}
#pragma endregion


