#include "ExecutionBlockIf.hxx"

namespace ExecutionLayer {

enum {
  OPCODE_BR,
  OPCODE_BEQ,
  OPCODE_BLT,
  OPCODE_BLE,
  
  OPCODE_BGT,
  OPCODE_BGE,
  OPCODE_CMP,
  OPCODE_IRET
};

class BranchBlock : public ExecutionBlockIf {
 protected:
  void internalExecute(uint8_t opcode, uint8_t dstreg, uint32_t op1, uint32_t op2) override;
};
} // namespace ExecutionLayer
