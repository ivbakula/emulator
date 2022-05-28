#include <gmock/gmock-spec-builders.h>
#include <cstdint>
#include "ExecutionBlockIf.hxx"
#include "ArithExecBlock.hxx"
#include "MemoryExeBlock.hxx"
#include "MockResourceBlockBus.hxx"
#include "ResourceBlockBus.hxx"
#include "BranchBlock.hxx"

using namespace testing;

class TestExeBlock : public Test {
 protected:
  ExecutionLayer::ArithExecBlock m_arithBlock;
  ExecutionLayer::MemoryExeBlock m_memoryBlock;
  ExecutionLayer::BranchBlock m_branchBlock;
  
  StrictMock<MockResourceBlockBus> m_mockResourceBlockBus;

  void SetUp() override {
    ExecutionLayer::ExecutionBlockIf::setResourceBlockBus(&m_mockResourceBlockBus);
  }
  void TearDown() override {
    ExecutionLayer::ExecutionBlockIf::setResourceBlockBus(nullptr);
  }
};

TEST_F(TestExeBlock, testArithRScheme) {
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

TEST_F(TestExeBlock, testMemoryExeBlockLoadByte) {
  constexpr uint8_t OPCODE {ExecutionLayer::OPCODE_LB};
  constexpr uint8_t DSTREG {6};
  constexpr uint8_t SRCREG {7};
  constexpr uint8_t OFFSET {0x4};

  constexpr uint32_t SRCREG_CONTENT {0xc0ffe};
  constexpr uint32_t MEMORY_CONTENT {0xde};

  // read srcreg in executeTypeI function
  EXPECT_CALL(m_mockResourceBlockBus, read(ResourceLayer::ResourceBlocksEnum::BLOCK_REGFILE, SRCREG, sizeof(uint32_t))).WillOnce(Return(SRCREG_CONTENT));

  // read dstreg in internalExecute
  EXPECT_CALL(m_mockResourceBlockBus, read(ResourceLayer::ResourceBlocksEnum::BLOCK_REGFILE, DSTREG, sizeof(uint32_t)));

  // read memory content at address SRCREG_CONTENT + OFFSET
  EXPECT_CALL(m_mockResourceBlockBus, read(ResourceLayer::ResourceBlocksEnum::BLOCK_MTU, SRCREG_CONTENT + OFFSET, sizeof(uint8_t))).WillOnce(Return(MEMORY_CONTENT));

  // write memory value to register
  EXPECT_CALL(m_mockResourceBlockBus, write(ResourceLayer::ResourceBlocksEnum::BLOCK_REGFILE, DSTREG, MEMORY_CONTENT, sizeof(uint32_t)));

  // increment pc
  EXPECT_CALL(m_mockResourceBlockBus, read(ResourceLayer::ResourceBlocksEnum::BLOCK_REGFILE, 1, sizeof(uint32_t))).WillOnce(Return(4));
  EXPECT_CALL(m_mockResourceBlockBus, write(ResourceLayer::ResourceBlocksEnum::BLOCK_REGFILE, 1, 4 + 4, sizeof(uint32_t)));

  m_memoryBlock.executeTypeI(OPCODE, DSTREG, SRCREG, OFFSET);
}

TEST_F(TestExeBlock, testMemoryExeBlockStoreByte) {
  constexpr uint8_t OPCODE {ExecutionLayer::OPCODE_SB};
  constexpr uint8_t DSTREG {6};
  constexpr uint8_t SRCREG {7};
  constexpr uint8_t OFFSET {0x4};

  constexpr uint32_t DSTREG_CONTENT {0xc0ffe};
  constexpr uint32_t SRCREG_CONTENT {0xbe};

  EXPECT_CALL(m_mockResourceBlockBus, read(ResourceLayer::ResourceBlocksEnum::BLOCK_REGFILE, SRCREG, sizeof(uint32_t))).WillOnce(Return(SRCREG_CONTENT));

  EXPECT_CALL(m_mockResourceBlockBus, read(ResourceLayer::ResourceBlocksEnum::BLOCK_REGFILE, DSTREG, sizeof(uint32_t))).WillOnce(Return(DSTREG_CONTENT));

  EXPECT_CALL(m_mockResourceBlockBus, write(ResourceLayer::ResourceBlocksEnum::BLOCK_MTU, DSTREG_CONTENT + OFFSET, SRCREG_CONTENT, sizeof(uint8_t)));

  // increment pc
  EXPECT_CALL(m_mockResourceBlockBus, read(ResourceLayer::ResourceBlocksEnum::BLOCK_REGFILE, 1, sizeof(uint32_t))).WillOnce(Return(4));
  EXPECT_CALL(m_mockResourceBlockBus, write(ResourceLayer::ResourceBlocksEnum::BLOCK_REGFILE, 1, 4 + 4, sizeof(uint32_t)));

  m_memoryBlock.executeTypeI(OPCODE, DSTREG, SRCREG, OFFSET);
}

TEST_F(TestExeBlock, testBranchBlockCmpLessThen) {
  constexpr uint8_t OPCODE {ExecutionLayer::OPCODE_CMP};
  constexpr uint8_t DSTREG {0};
  constexpr uint8_t SRCREG1 {5};
  constexpr uint8_t SRCREG2 {6};

  constexpr uint8_t ZF_REG {32};
  constexpr uint8_t NF_REG {33};

  // Read operands from the regfile
  EXPECT_CALL(m_mockResourceBlockBus, read(ResourceLayer::ResourceBlocksEnum::BLOCK_REGFILE, SRCREG1, sizeof(uint32_t))).WillOnce(Return(1));

  EXPECT_CALL(m_mockResourceBlockBus, read(ResourceLayer::ResourceBlocksEnum::BLOCK_REGFILE, SRCREG2, sizeof(uint32_t))).WillOnce(Return(2));

  // Read flags from the regfile
  EXPECT_CALL(m_mockResourceBlockBus, read(ResourceLayer::ResourceBlocksEnum::BLOCK_REGFILE, ZF_REG, sizeof(uint32_t)));
  EXPECT_CALL(m_mockResourceBlockBus, read(ResourceLayer::ResourceBlocksEnum::BLOCK_REGFILE, NF_REG, sizeof(uint32_t)));

  // Compare and set appropriate flags
  EXPECT_CALL(m_mockResourceBlockBus, write(ResourceLayer::ResourceBlocksEnum::BLOCK_REGFILE, ZF_REG, 0, sizeof(uint32_t)));
  EXPECT_CALL(m_mockResourceBlockBus, write(ResourceLayer::ResourceBlocksEnum::BLOCK_REGFILE, NF_REG, 1, sizeof(uint32_t)));

  // increment pc
  EXPECT_CALL(m_mockResourceBlockBus, read(ResourceLayer::ResourceBlocksEnum::BLOCK_REGFILE, 1, sizeof(uint32_t))).WillOnce(Return(4));
  EXPECT_CALL(m_mockResourceBlockBus, write(ResourceLayer::ResourceBlocksEnum::BLOCK_REGFILE, 1, 4 + 4, sizeof(uint32_t)));
  
  m_branchBlock.executeTypeR(OPCODE, DSTREG, SRCREG1, SRCREG2);
}

TEST_F(TestExeBlock, testBranchBlockBranchGt) {
  constexpr uint8_t OPCODE {ExecutionLayer::OPCODE_BGT};
  constexpr uint8_t DSTREG {1};
  constexpr uint8_t SRC1REG {1};
  constexpr uint8_t SRC2REG {2};

  constexpr uint8_t ZF_REG {32};
  constexpr uint8_t NF_REG {33};

  constexpr uint32_t CURRENT_PC {0xdead};
  constexpr uint32_t OFFSET {0xbeef};

  // Read operands from the regfile
  EXPECT_CALL(m_mockResourceBlockBus, read(ResourceLayer::ResourceBlocksEnum::BLOCK_REGFILE, SRC1REG, sizeof(uint32_t))).WillOnce(Return(CURRENT_PC));
  EXPECT_CALL(m_mockResourceBlockBus, read(ResourceLayer::ResourceBlocksEnum::BLOCK_REGFILE, SRC2REG, sizeof(uint32_t))).WillOnce(Return(OFFSET));

  // Read flags from the regfile
  EXPECT_CALL(m_mockResourceBlockBus, read(ResourceLayer::ResourceBlocksEnum::BLOCK_REGFILE, ZF_REG, sizeof(uint32_t))).WillOnce(Return(0));
  EXPECT_CALL(m_mockResourceBlockBus, read(ResourceLayer::ResourceBlocksEnum::BLOCK_REGFILE, NF_REG, sizeof(uint32_t))).WillOnce(Return(0));

  // Preform jump
  EXPECT_CALL(m_mockResourceBlockBus, write(ResourceLayer::ResourceBlocksEnum::BLOCK_REGFILE, DSTREG, CURRENT_PC + OFFSET, sizeof(uint32_t)));

  m_branchBlock.executeTypeR(OPCODE, DSTREG, SRC1REG, SRC2REG);
}

TEST_F(TestExeBlock, testBranchBlockDontBranchGt) {
  constexpr uint8_t OPCODE {ExecutionLayer::OPCODE_BGT};
  constexpr uint8_t PC {1};
  constexpr uint8_t SRC2REG {2};

  constexpr uint8_t ZF_REG {32};
  constexpr uint8_t NF_REG {33};

  constexpr uint32_t CURRENT_PC {0xdead};
  constexpr uint32_t OFFSET {0xbeef};

  // Read operands from the regfile
  EXPECT_CALL(m_mockResourceBlockBus, read(ResourceLayer::ResourceBlocksEnum::BLOCK_REGFILE, PC, sizeof(uint32_t))).WillRepeatedly(Return(CURRENT_PC));
  EXPECT_CALL(m_mockResourceBlockBus, read(ResourceLayer::ResourceBlocksEnum::BLOCK_REGFILE, SRC2REG, sizeof(uint32_t))).WillOnce(Return(OFFSET));

  // Read flags from the regfile
  EXPECT_CALL(m_mockResourceBlockBus, read(ResourceLayer::ResourceBlocksEnum::BLOCK_REGFILE, ZF_REG, sizeof(uint32_t))).WillOnce(Return(1));
  EXPECT_CALL(m_mockResourceBlockBus, read(ResourceLayer::ResourceBlocksEnum::BLOCK_REGFILE, NF_REG, sizeof(uint32_t))).WillOnce(Return(0));

  // increment pc
  //  EXPECT_CALL(m_mockResourceBlockBus, read(ResourceLayer::ResourceBlocksEnum::BLOCK_REGFILE, PC, sizeof(uint32_t))).WillOnce(Return(4));
  EXPECT_CALL(m_mockResourceBlockBus, write(ResourceLayer::ResourceBlocksEnum::BLOCK_REGFILE, 1, CURRENT_PC + 4, sizeof(uint32_t)));

  m_branchBlock.executeTypeR(OPCODE, PC, PC, SRC2REG);
}
