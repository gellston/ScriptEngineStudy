#pragma once

#ifndef VISIONHUB_AOI_MANAGED_CORE_MEMORY_BLOCK
#define VISIONHUB_AOI_MANAGED_CORE_MEMORY_BLOCK


#include <core/collection/memoryBlock.h>


namespace VisionHub {
	namespace V1 {
		public ref class MemoryBlock {

#pragma region Private Property
		private:
			visionhub::v1::memoryBlock_ptr* memoryBlock = new visionhub::v1::memoryBlock_ptr();
			bool disposing = false;
#pragma endregion

		public:
#pragma region Constructor
			MemoryBlock(visionhub::v1::memoryBlock& block);
#pragma endregion

#pragma region Destructor
			~MemoryBlock();
#pragma endregion

#pragma region Finalizer
			!MemoryBlock();
#pragma endregion

#pragma region Private Functions
		private:
			void Cleanup(bool finalizing);
#pragma endregion

#pragma region Public Property
		public:
			property std::size_t Capacity {
				std::size_t get();
			}

			property System::IntPtr Data {
				System::IntPtr get();
			}
#pragma endregion




		};
	}

}


#endif