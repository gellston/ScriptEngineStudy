#pragma once

#ifndef VISIONHUB_AOI_MANAGED_CORE_BLOB
#define VISIONHUB_AOI_MANAGED_CORE_BLOB


//C++
#include <core/collection/blob.h>

//C++/CLI

//C#

namespace VisionHub {
	namespace V1 {
		public ref class Blob {
		private:
#pragma region Private Property
			visionhub::v1::blob_ptr* blob = new visionhub::v1::blob_ptr();
			bool disposing = false;
#pragma endregion

		public:
#pragma region Constructor
			Blob(visionhub::v1::blob_ptr _blob);
#pragma endregion

#pragma region Destructor
			~Blob();
#pragma endregion

#pragma region Finalizer
			!Blob();
#pragma endregion

#pragma region Private Functions
		private:
			void Cleanup(bool finalizing);
#pragma endregion

#pragma region Public Property
		public:
			property std::size_t Size {
				std::size_t get();
			}

			property System::IntPtr Data {
				System::IntPtr get();
			}

			property System::IntPtr Handle {
				System::IntPtr get();
			}
#pragma endregion


		};
	}
}


#endif
