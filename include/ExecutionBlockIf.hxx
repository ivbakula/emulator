#pragma once

#include <cstdint>
#include "ResourceBlockBus.hxx"

namespace ExecutionLayer {
class ExecutionBlockIf {
 public:
  /*!
   * Execute instruction coded in scheme Type-R (reg-reg-reg)
   */
  virtual void executeTypeR(uint8_t opcode, uint8_t dstreg, uint8_t op1reg, uint8_t op2reg);

  /*!
   * Exectue instruction coded in scheme Type-I and preform sign extension (reg-reg-imm)
   */
  virtual void executeTypeI(uint8_t opcode, uint8_t dstreg, uint8_t op1reg, uint32_t imm);

  /*!
   * Execute instruction coded in scheme Type-IB (reg-imm)
   */
  virtual void executeTypeIB(uint8_t opcode, uint8_t dstreg, uint32_t imm);

  /*!
   * Set pointer to resource block bus. This function is called during core initialization
   */
  static void setResourceBlockBus(ResourceLayer::ResourceBlockBus* rscBlkBus);

 protected:
  virtual void internalExecute(uint8_t opcode, uint8_t dstreg, uint32_t op1, uint32_t op2) = 0;

  /*!
   * Increment program counter
   */
  static void incPc();
  static ResourceLayer::ResourceBlockBus* resourceBlockBus;
};
}  // namespace ExecutionLayer
