#include "ExecutionBlockBus.hxx"

#include "ArithExecBlock.hxx"
#include "ExecutionBlockIf.hxx"

namespace ExecutionLayer {

void ExecutionBlockBus::executeTypeR(ExecutionBlocksEnum block, uint8_t opcode, uint8_t dstreg, uint8_t op1reg, uint8_t op2reg) {
  if (m_executionBlocks.find(block) != m_executionBlocks.end()) {
    m_executionBlocks[block]->executeTypeR(opcode, dstreg, op1reg, op2reg);
  }
}

void ExecutionBlockBus::executeTypeI(ExecutionBlocksEnum block, uint8_t opcode, uint8_t dstreg, uint8_t op1reg, int16_t imm) {
  if (m_executionBlocks.find(block) != m_executionBlocks.end()) {
    m_executionBlocks[block]->executeTypeI(opcode, dstreg, op1reg, imm);
  }
}

std::map<ExecutionBlocksEnum, ExecutionBlockIf *> ExecutionBlockBus::m_executionBlocks{
    {ExecutionBlocksEnum::BLOCK_ARITHMETIC, new ArithExecBlock}};
}  // namespace ExecutionLayer
