#include "gmock/gmock.h"
#include "ResourceBlockBus.hxx"

class MockResourceBlockBus : public ResourceLayer::ResourceBlockBus {
 public:
  MOCK_METHOD(void, write, (ResourceLayer::ResourceBlocksEnum which, uint32_t index, uint32_t data, std::size_t size), (override));
  MOCK_METHOD(uint32_t, read, (ResourceLayer::ResourceBlocksEnum which, uint32_t index, std::size_t size), (override));
};
