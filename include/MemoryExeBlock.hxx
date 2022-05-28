#pragma once
#include "ExecutionBlockIf.hxx"

namespace ExecutionLayer {

enum {
  OPCODE_LB,
  OPCODE_LHW,
  OPCODE_LW,  
  OPCODE_SB,
  OPCODE_SHW,
  OPCODE_SW
};

class MemoryExeBlock : public ExecutionBlockIf {
 protected:
  virtual void internalExecute(uint8_t opcode, uint8_t dstreg, uint32_t op1, uint32_t op2) override;
};
} // namespace ExecutionLayer
