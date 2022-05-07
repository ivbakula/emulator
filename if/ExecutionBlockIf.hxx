#pragma once

#include <cstdint>

class ExecutionBlockIf {
 public:
  virtual ~ExecutionBlockIf() = default;
  virtual bool executeTypeR(uint8_t opcode, uint8_t dstreg, uint8_t op1reg, uint8_t op2reg) = 0;
  virtual bool executeTypeI(uint8_t opcode, uint8_t dstreg, uint8_t op1reg, int32_t imm) = 0;

 protected:
  virtual bool internalExecute(uint8_t opcode, uint8_t dstreg, uint32_t op1, uint32_t imm) = 0;
};
