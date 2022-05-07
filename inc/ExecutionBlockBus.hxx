#pragma once

#include <map>

#include "ExecutionBlockIf.hxx"
#include "WhichEnums.hxx"

// TODO create ExecutionBlocks via factory

class ExecutionBlockBus {
 public:
  ExecutionBlockBus();
  void executeTypeR(WhichExecBlock which, uint8_t opcode, uint8_t dstreg, uint8_t op1reg, uint8_t op2reg);
  void executeTypeI(WhichExecBlock which, uint8_t opcode, uint8_t dstreg, uint32_t op1, uint32_t op2);

 private:
  std::map<WhichExecBlock, ExecutionBlockIf*> m_execBlocks;
};
