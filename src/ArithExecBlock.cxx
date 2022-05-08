#include "ArithExecBlock.hxx"
#include "ExecutionBlockIf.hxx"
#include "ResourceBlockBus.hxx"

namespace ExecutionLayer {

void ArithExecBlock::executeTypeI(uint8_t opcode, uint8_t dstreg, uint8_t op1reg, uint32_t imm) {
  //sign extend imm value
  int16_t tmp = imm;
  int32_t cast = tmp;

  uint32_t op1 = resourceBlockBus->read(ResourceLayer::ResourceBlocksEnum::BLOCK_REGFILE, op1reg);
  internalExecute(opcode, dstreg, op1, cast);
}

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

  resourceBlockBus->write(ResourceLayer::ResourceBlocksEnum::BLOCK_REGFILE, dstreg, result);
  ExecutionBlock::incPc();
}
} // namespace ExecutionLayer
