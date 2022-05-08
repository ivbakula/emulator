#pragma once

#include <cstdint>
#include "ResourceBlockBus.hxx"

namespace ExecutionLayer {
class ExecutionBlockIf {
 public:
  virtual void executeTypeR(uint8_t opcode, uint8_t dstreg, uint8_t op1reg, uint8_t op2reg) = 0;
  virtual void executeTypeI(uint8_t opcode, uint8_t dstreg, uint8_t op1reg, uint32_t imm) = 0;

 protected:
  virtual void internalExecute(uint8_t opcode, uint8_t dstreg, uint32_t op1, uint32_t op2) = 0;
};

class ExecutionBlock : public ExecutionBlockIf {
 public:
  virtual void executeTypeR(uint8_t opcode, uint8_t dstreg, uint8_t op1reg, uint8_t op2reg) override;

  static void setResourceBlockBus(ResourceLayer::ResourceBlockBus* rscBlkBus);
 protected:
  static void incPc();
  static ResourceLayer::ResourceBlockBus* resourceBlockBus;
};
} // namespace ExecutionLayer
