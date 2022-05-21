#include <gmock/gmock-spec-builders.h>
#include "ExecutionBlockIf.hxx"
#include "ArithExecBlock.hxx"
#include "MockResourceBlockBus.hxx"
#include "ResourceBlockBus.hxx"

using namespace testing;

class TestArithExecBlock : public Test {
 protected:
  ExecutionLayer::ArithExecBlock m_arithBlock;
  MockResourceBlockBus m_mockResourceBlockBus;

  void SetUp() override {
    ExecutionLayer::ExecutionBlockIf::setResourceBlockBus(&m_mockResourceBlockBus);
  }
  void TearDown() override {
    ExecutionLayer::ExecutionBlockIf::setResourceBlockBus(nullptr);
  }
};

TEST_F(TestArithExecBlock, testArithRScheme) {
  constexpr uint8_t OPCODE {ExecutionLayer::OPCODE_ADD};
  constexpr uint8_t DSTREG {6};
  constexpr uint8_t SRC1REG {7};
  constexpr uint8_t SRC2REG {8};
  constexpr uint8_t PC_INDEX {1};

  constexpr uint32_t SRC1REG_CONTENT {16};
  constexpr uint32_t SRC2REG_CONTENT {24};
  constexpr uint32_t PC_CURRENT {0};

  EXPECT_CALL(m_mockResourceBlockBus, read(ResourceLayer::ResourceBlocksEnum::BLOCK_REGFILE, SRC1REG, sizeof(uint32_t)))
      .WillOnce(Return(SRC1REG_CONTENT));
  EXPECT_CALL(m_mockResourceBlockBus, read(ResourceLayer::ResourceBlocksEnum::BLOCK_REGFILE, SRC2REG, sizeof(uint32_t)))
      .WillOnce(Return(SRC2REG_CONTENT));
  EXPECT_CALL(m_mockResourceBlockBus, write(ResourceLayer::ResourceBlocksEnum::BLOCK_REGFILE, DSTREG,
                                            SRC1REG_CONTENT + SRC2REG_CONTENT, sizeof(uint32_t)));

  // incPc
  EXPECT_CALL(m_mockResourceBlockBus, read(ResourceLayer::ResourceBlocksEnum::BLOCK_REGFILE, PC_INDEX, sizeof(uint32_t))).WillOnce(Return(PC_CURRENT));
  EXPECT_CALL(m_mockResourceBlockBus, write(ResourceLayer::ResourceBlocksEnum::BLOCK_REGFILE, PC_INDEX, PC_CURRENT + 4, sizeof(uint32_t)));

  m_arithBlock.executeTypeR(OPCODE, DSTREG, SRC1REG, SRC2REG);
}
