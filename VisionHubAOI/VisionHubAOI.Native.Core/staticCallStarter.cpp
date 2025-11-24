#include "core/binding/staticCallStarter.h"




#pragma region Constructor
visionhub::v1::staticCallStarter::staticCallStarter(std::function<void()> caller)  {

	if (caller != nullptr)
		caller();
}
#pragma endregion
