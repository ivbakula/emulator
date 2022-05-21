#include "MTUResourceBlock.hxx"
#include "PeripherialBus.hxx"
#include "ResourceBlockIf.hxx"
#include "gtest/gtest.h"

using namespace testing;

class TestMtuBlock : public Test {
 protected:
  ResourceLayer::MTUResourceBlock m_mtu;
  ExternalLayer::ExternalBus m_externalBus;

  void SetUp() override {
    ResourceLayer::ResourceBlockIf::setExternalBus(&m_externalBus);
  }

  void TearDown() override {}
};

TEST_F(TestMtuBlock, testMtuBlock) {
  constexpr uint32_t EXPECTED_DATA {0x08020a00};
  constexpr uint32_t ADDRESS {0x00000004};

  uint32_t data = m_mtu.read(ADDRESS, sizeof(uint32_t));
  EXPECT_TRUE(data == EXPECTED_DATA);
}

TEST_F(TestMtuBlock, testMtuBlock2) {
  constexpr uint32_t EXPECTED_DATA {0x00000077};
  constexpr uint32_t ADDRESS {0x00000008};

  uint32_t data = m_mtu.read(ADDRESS, sizeof(uint32_t));
  EXPECT_EQ(data, EXPECTED_DATA);
}
