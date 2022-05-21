#pragma once

#include <map>

#include "ExecutionBlockIf.hxx"

namespace ExecutionLayer {
enum class ExecutionBlocksEnum {
  BLOCK_ARITHMETIC,
  BLOCK_REGOPS,  // operations preformed on internal registers
  BLOCK_CTRL,
  BLOCK_BRANCH,
  BLOCK_MEMORY
};

class ExecutionBlockBus {
 public:
  void executeTypeR(ExecutionBlocksEnum block, uint8_t opcode, uint8_t dstreg, uint8_t op1reg, uint8_t op2reg);
  void executeTypeI(ExecutionBlocksEnum block, uint8_t opcode, uint8_t dstreg, uint8_t op1reg, int16_t imm);

  static void setExecutionBlock(ExecutionBlocksEnum name, ExecutionBlockIf* block);
 private:
  static std::map<ExecutionBlocksEnum, ExecutionBlockIf*> m_executionBlocks;
};
}  // namespace ExecutionLayer
