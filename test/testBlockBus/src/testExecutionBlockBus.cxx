#include "MockExecBlock.hxx"
#include "gtest/gtest.h"
#include "ExecutionBlockBus.hxx"
#include "ExecutionBlockIf.hxx"

using namespace testing;

class TestBlockBus : public Test {
 protected:
  ExecutionLayer::ExecutionBlockBus m_executionBlockBus;
  MockExecBlock m_mockExecBlock;

  void SetUp() override {
    ExecutionLayer::ExecutionBlockBus::setExecutionBlock(ExecutionLayer::ExecutionBlocksEnum::BLOCK_ARITHMETIC,
                                                         &m_mockExecBlock);
  }

  void TearDown() override {
  }
};

TEST_F(TestBlockBus, testExecutionBlockBus) {
  constexpr uint8_t OPCODE {0};
  constexpr uint8_t DSTREG {6};
  constexpr uint8_t SRC1REG {7};
  constexpr uint8_t SRC2REG {8};

  EXPECT_CALL(m_mockExecBlock, executeTypeR(OPCODE, DSTREG, SRC1REG, SRC2REG)).Times(1);
  m_executionBlockBus.executeTypeR(ExecutionLayer::ExecutionBlocksEnum::BLOCK_ARITHMETIC,
                                   OPCODE, DSTREG, SRC1REG, SRC2REG);
}
