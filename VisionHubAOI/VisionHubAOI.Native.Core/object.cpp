

#include "core/object.h"
#include "core/reflection/typeRegistry.h"

#include <iostream>


#pragma region Static Constructor

STATIC_CTR_DEFINE(visionhub::v1::object) {
	REFLECTION_BEGIN(object)
		REFLECTION_PROP(object, objType)
	REFLECTION_END()
}

#pragma endregion

#pragma region Constructor

visionhub::v1::object::object(visionhub::v1::coreTypes type) {
	this->type = type;
}
#pragma endregion





#pragma region Public Functions
visionhub::v1::coreTypes visionhub::v1::object::objType() {
	return this->type;
}
#pragma endregion
