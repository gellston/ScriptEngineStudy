
#include "core/reflection/typeRegistry.h"

#include <unordered_map>


#pragma region Impl
namespace visionhub {
	namespace v1 {
		class impl_typeRegistry {
		public:
			std::unordered_map<visionhub::v1::coreTypes, typeInfo> tables;
		};
	}
}
#pragma endregion



#pragma region Constructor
visionhub::v1::typeRegistry::typeRegistry() : impl(new impl_typeRegistry()) {

}

#pragma endregion




#pragma region Public Functions
visionhub::v1::typeRegistry& visionhub::v1::typeRegistry::get() {

	static visionhub::v1::typeRegistry _instance;

	return _instance;
}

void visionhub::v1::typeRegistry::add(visionhub::v1::typeInfo ti) {
	this->impl->tables[ti.coreType] = std::move(ti);
}

visionhub::v1::typeInfo* visionhub::v1::typeRegistry::find(visionhub::v1::coreTypes type) {
	if (this->impl->tables.find(type) == this->impl->tables.end()) return nullptr;
	return &this->impl->tables[type];
}

std::vector<visionhub::v1::typeInfo> visionhub::v1::typeRegistry::typeInfo() {
	std::vector<visionhub::v1::typeInfo> result;
	for (auto keypair : this->impl->tables) {
		result.push_back(keypair.second);
	}
	return result;
}
#pragma endregion
