#pragma once

#ifndef VISIONHUB_AOI_MANAGED_CORE_VALUE
#define VISIONHUB_AOI_MANAGED_CORE_VALUE


//C++
#include <core/collection/value.h>

//C++/CLI
#include "ValueKind.h"
#include "Blob.h"

//C#

namespace VisionHub {
	namespace V1 {
		ref class Value;
		using Map = System::Collections::Generic::Dictionary<System::String^, Value^>;
		using Array = System::Collections::Generic::List<Value^>;
		public ref class Value {

		private:
#pragma region Private Property
			visionhub::v1::value_ptr * value = new visionhub::v1::value_ptr();
			bool disposing = false;
#pragma endregion

#pragma region Constructor
		public:
			Value(visionhub::v1::value_ptr _value);
			Value(visionhub::v1::value& _value);
			Value(System::IntPtr handle);
			Value(const bool&);
			Value(const int8_t&);
			Value(const int16_t&);
			Value(const int32_t&);
			Value(const int64_t&);
			Value(const uint8_t&);
			Value(const uint16_t&);
			Value(const uint32_t&);
			Value(const uint64_t&);
			Value(const float&);
			Value(const double&);
			Value(System::String^ s);
			Value(Map^);
			Value(Array^);
			Value(Blob^);



#pragma endregion

#pragma region Destructor
			~Value();
#pragma endregion

#pragma region Finalizer
			!Value();
#pragma endregion


#pragma region Private Functions
		private:
			void Cleanup(bool finalizing);
#pragma endregion


#pragma region Public Property
		public:
			property VisionHub::V1::ValueKind Kind {
				VisionHub::V1::ValueKind get();
			}

			property std::size_t Size {
				std::size_t get();
			}

			property std::size_t Count {
				std::size_t get();
			}

			property System::Collections::Generic::List<System::String^>^ Keys {
				System::Collections::Generic::List<System::String^>^ get();
			}

			property Value^ default[System::String^] {
				Value^ get(System::String^);
			}

			property Value^ default[int] {
				Value^ get(int);
			}

			property System::IntPtr Handle {
				System::IntPtr get();
			}
#pragma endregion


#pragma region Public Functions

			array<uint8_t>^ Serialize();
			static VisionHub::V1::Value^ Deserialize(array<uint8_t>^ data);


			bool Get(bool% value);
			bool Get(int8_t% value);
			bool Get(int16_t% value);
			bool Get(int32_t% value);
			bool Get(int64_t% value);
			bool Get(uint8_t% value);
			bool Get(uint16_t% value);
			bool Get(uint32_t% value);
			bool Get(uint64_t% value);
			bool Get(float% value);
			bool Get(double% value);
			bool Get(System::String^% value);
			bool Get(Map^% value);
			bool Get(Array^% value);
			bool Get(Blob^% value);
			

			void Set(const bool& value);
			void Set(const int8_t& value);
			void Set(const int16_t& value);
			void Set(const int32_t& value);
			void Set(const int64_t& value);
			void Set(const uint8_t& value);
			void Set(const uint16_t& value);
			void Set(const uint32_t& value);
			void Set(const uint64_t& value);

			void Set(const float& value);
			void Set(const double& value);
			void Set(System::String^ value);
			void Set(Map^ value);
			void Set(Array^ value);
			void Set(Blob^ value);
#pragma endregion





		};
		
	}
}


#endif
