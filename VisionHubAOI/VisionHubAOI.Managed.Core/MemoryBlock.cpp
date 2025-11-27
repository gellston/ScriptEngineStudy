
#include "Core/Collection/MemoryBlock.h"


#pragma region Constructor
VisionHub::V1::MemoryBlock::MemoryBlock(visionhub::v1::memoryBlock& block) {
	*this->memoryBlock = std::make_shared<visionhub::v1::memoryBlock>(block);
}
#pragma endregion


#pragma region Destructor
VisionHub::V1::MemoryBlock::~MemoryBlock() {

	this->Cleanup(false);
}
#pragma endregion

#pragma region Finalizer
VisionHub::V1::MemoryBlock::!MemoryBlock() {
	this->Cleanup(true);
}
#pragma endregion


#pragma region Private Functions
void VisionHub::V1::MemoryBlock::Cleanup(bool finalizing) {
	if (this->disposing == true) return;
	this->disposing = true;


	if (!finalizing) {
		// managed code clean up
	}

	if (this->memoryBlock != nullptr) {
		delete this->memoryBlock;
		this->memoryBlock = nullptr;
	}
}
#pragma endregion

#pragma region Public Functions
std::size_t VisionHub::V1::MemoryBlock::Capacity::get() {
	return this->memoryBlock->get()->capacity;
}

System::IntPtr VisionHub::V1::MemoryBlock::Data::get() {
	return System::IntPtr(this->memoryBlock->get()->data);
}
#pragma endregion


