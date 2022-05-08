#include "ExecutionBlockIf.hxx"

namespace ExecutionLayer {
enum {
  OPCODE_ADD = 0,
  OPCODE_SUB,
  OPCODE_SHL,
  OPCODE_SHR,
  OPCODE_AND,
  OPCODE_OR,
  OPCODE_NOT,
  OPCODE_XOR
};

class ArithExecBlock : public ExecutionBlock {
 public:
  void executeTypeI(uint8_t opcode, uint8_t dstreg, uint8_t op1reg, uint32_t imm) override;

 protected:
  virtual void internalExecute(uint8_t opcode, uint8_t dstreg, uint32_t op1, uint32_t op2)  override;
};
} // namespace ExecutionLayer
