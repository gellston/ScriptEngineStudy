
#include "core/image.h"


#include "core/collection/memoryBlock.h"
#include "core/collection/memoryPool.h"

#include "core/reflection/typeRegistry.h"

#include "core/snapShot/snapValue.h"



#pragma region Static Constructor
STATIC_CTR_DEFINE(visionhub::v1::image) {

	REFLECTION_BEGIN(image)
		REFLECTION_PROP(image, objType)
		REFLECTION_PROP(image, width)
		REFLECTION_PROP(image, height)
		REFLECTION_PROP(image, channel)
		REFLECTION_PROP(image, stride)
		REFLECTION_PROP(image, size)
		REFLECTION_PROP(image, depth)
		REFLECTION_PROP(image, data)
	REFLECTION_END()

}
#pragma endregion




#pragma region IMPL
namespace visionhub {
	namespace v1 {
		struct impl_image {
		public:

			unsigned int width = 0;
			unsigned int height = 0;
			unsigned int channel = 0;
			std::size_t stride = 0;

			std::size_t size = 0;
			depthType depth = depthType::bit8;
			

			memoryBlock block;

		};
	}
}
#pragma endregion


#pragma region Public Constructor
visionhub::v1::image::image(unsigned int width, unsigned int height, unsigned int channel, depthType depth) 
	: object(visionhub::v1::coreTypes::image), impl(new impl_image()) {

	this->impl->width = width;
	this->impl->height = height;
	this->impl->channel = channel;
	this->impl->depth = depth;
	this->impl->stride = static_cast<int>(depthType::bit8) * width;

	this->impl->size = this->impl->width * this->impl->height * this->impl->channel * static_cast<int>(depthType::bit8);

	if (this->impl->size <= 0) {
		throw std::exception("Invalid image size");
	}


	try {
		memoryBlock block;
		block.capacity = this->impl->size;
		block.data = (uint8_t*)std::malloc(block.capacity);
		std::memset(block.data, 0, block.capacity);
		block.holder = std::shared_ptr<void>(block.data, [this](void* raw) {
			if (!raw) return;
			std::free(raw);
		});


		this->impl->block = block;
	}
	catch (...) {
		throw;
	}




}


visionhub::v1::image::image(unsigned int width, unsigned int height, unsigned int channel, depthType depth, std::shared_ptr<memoryPool> pool)
	: object(visionhub::v1::coreTypes::image), impl(new impl_image()) {

	this->impl->width = width;
	this->impl->height = height;
	this->impl->channel = channel;
	this->impl->depth = depth;
	this->impl->stride = static_cast<int>(depthType::bit8) * width;

	this->impl->size = this->impl->width * this->impl->height * this->impl->channel * static_cast<int>(depthType::bit8);

	if (this->impl->size <= 0) {
		throw std::exception("Invalid image size");
	}


	try {
		auto block = pool->acquire(this->impl->size);
		this->impl->block = block;
	}
	catch (...) {
		throw;
	}

}


visionhub::v1::image_ptr visionhub::v1::image::make_image(unsigned int width, unsigned int height, unsigned int channel, visionhub::v1::depthType depth) {
	return std::make_shared<image>(width, height, channel, depth);
}
#pragma endregion


#pragma region Public Destructor
visionhub::v1::image::~image() {
	
}
#pragma endregion


#pragma region Public Functions
visionhub::v1::snapValue_ptr visionhub::v1::image::snap() {

	try {

		auto snapValue = std::make_shared<visionhub::v1::snapValue>();

		visionhub::v1::snapValueAtt::setKind(snapValue, visionhub::v1::snapKind::_native_);
		visionhub::v1::snapValueAtt::addField(snapValue, "width", this->impl->width);
		visionhub::v1::snapValueAtt::addField(snapValue, "height", this->impl->height);
		visionhub::v1::snapValueAtt::addField(snapValue, "channel", this->impl->channel);
		visionhub::v1::snapValueAtt::addField(snapValue, "depth", (unsigned int)this->impl->depth);
		visionhub::v1::snapValueAtt::addField(snapValue, "data", this->impl->block);


		return snapValue;
	}
	catch (...) {
		throw;
	}

}

unsigned int visionhub::v1::image::width() {
	return this->impl->width;
}

unsigned int visionhub::v1::image::height() {
	return this->impl->height;
}

unsigned int visionhub::v1::image::channel() {
	return this->impl->channel;
}

visionhub::v1::depthType visionhub::v1::image::depth() {
	return this->impl->depth;
}

std::size_t visionhub::v1::image::stride() {
	return this->impl->stride;
}

std::size_t visionhub::v1::image::size() {
	return this->impl->size;
}

visionhub::v1::memoryBlock visionhub::v1::image::data() {
	return this->impl->block;
}
#pragma endregion


