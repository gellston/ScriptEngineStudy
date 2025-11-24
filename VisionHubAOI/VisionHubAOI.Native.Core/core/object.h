#pragma once


#ifndef VISIONHUB_AOI_NATIVE_CORE_OBJECT
#define VISIONHUB_AOI_NATIVE_CORE_OBJECT



#include "coreMacro/api.h"
#include "types/coreTypes.h"

#include "binding/helper.h"
#include "binding/staticCallStarter.h"




#include <memory>

namespace visionhub {
	namespace v1 {
		struct snapValue;
		using snapValue_ptr = std::shared_ptr<snapValue>;
		struct object {

		private:
			visionhub::v1::coreTypes type = visionhub::v1::coreTypes::none;

		public:

			//REFERENCE_COUNTER()

#pragma region Static Constructor
			STATIC_CTR_DECLARE()
#pragma endregion

#pragma region Public Constructor
			VISIONHUB_AOI_NATIVE_CORE_API object(visionhub::v1::coreTypes type);
#pragma endregion

#pragma region Public Destructor
			VISIONHUB_AOI_NATIVE_CORE_API virtual ~object() = default;
#pragma endregion

#pragma region Public Functions
			VISIONHUB_AOI_NATIVE_CORE_API visionhub::v1::coreTypes objType();
#pragma endregion

#pragma region Virtual Functions
			VISIONHUB_AOI_NATIVE_CORE_API virtual snapValue_ptr snap() = 0;
#pragma endregion



		};

		using object_ptr = sp<object>;

	}
}

#endif