#include "ExecutionBlockIf.hxx"

namespace ExecutionLayer {

enum {
  OPCODE_BRK,
  OPCODE_HALT = 7
};

class CtrlBlock : public ExecutionBlockIf {
 protected:
  virtual void internalExecute(uint8_t opcode, uint8_t dstreg, uint32_t op1, uint32_t op2) override;
};
} // namespace ExecutionLayer
