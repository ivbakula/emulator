#include "ArithExecBlock.hxx"
#include <cstdint>
#include "ExecutionBlockIf.hxx"
#include "ResourceBlockBus.hxx"

namespace ExecutionLayer {

void ArithExecBlock::internalExecute(uint8_t opcode, uint8_t dstreg, uint32_t op1, uint32_t op2) {
  uint32_t result {0};
  switch(opcode) {
    case OPCODE_ADD:
      result = op1 + op2;
      break;

    case OPCODE_SUB:
      result = op1 - op2;
      break;

    case OPCODE_SHL:
      result = op1 << op2;
      break;

    case OPCODE_SHR:
      result = op1 >> op2;
      break;

    case OPCODE_AND:
      result = op1 & op2;
      break;

    case OPCODE_OR:
      result = op1 | op2;
      break;

    case OPCODE_NOT:
      result = ~op2;
      break;

    case OPCODE_XOR:
      result = op1 ^ op2;
      break;

    default:
      return;
  };

  resourceBlockBus->write(ResourceLayer::ResourceBlocksEnum::BLOCK_REGFILE, dstreg, result, sizeof(uint32_t));
  ExecutionBlockIf::incPc();
}
} // namespace ExecutionLayer
