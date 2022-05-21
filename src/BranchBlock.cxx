#include "BranchBlock.hxx"
#include "ResourceBlockBus.hxx"

namespace ExecutionLayer {

void BranchBlock::internalExecute(uint8_t opcode, uint8_t dstreg, uint32_t op1, uint32_t op2) {
  bool isZero = (resourceBlockBus->read(ResourceLayer::ResourceBlocksEnum::BLOCK_REGFILE, 32, sizeof(uint32_t)) == 1);
  bool isNegative = (resourceBlockBus->read(ResourceLayer::ResourceBlocksEnum::BLOCK_REGFILE, 33, sizeof(uint32_t)) == 1);

  uint32_t result {op1 + op2};
  bool doJump {false};
  
  switch (opcode) {
    case OPCODE_BR:
      doJump = true;
      break;
      
    case OPCODE_BEQ:
      doJump = isZero;
      break;
      
    case OPCODE_BLT:
      doJump = isNegative;
      break;
    case OPCODE_BLE:
      doJump = isNegative || isZero;
      break;

    case OPCODE_BGT:
      doJump = (!isNegative) && (!isZero);
      break;
      
    case OPCODE_BGE:
      doJump = !isNegative;
      break;
      
    case OPCODE_CMP:
      result = op1 - op2;
      if (result < 0) {
        resourceBlockBus->write(ResourceLayer::ResourceBlocksEnum::BLOCK_REGFILE, 32, 1, sizeof(uint32_t));
        resourceBlockBus->write(ResourceLayer::ResourceBlocksEnum::BLOCK_REGFILE, 33, 0, sizeof(uint32_t));
      } else if (result == 0) {
        resourceBlockBus->write(ResourceLayer::ResourceBlocksEnum::BLOCK_REGFILE, 32, 0, sizeof(uint32_t));
        resourceBlockBus->write(ResourceLayer::ResourceBlocksEnum::BLOCK_REGFILE, 33, 1, sizeof(uint32_t));
      } else {
        resourceBlockBus->write(ResourceLayer::ResourceBlocksEnum::BLOCK_REGFILE, 32, 0, sizeof(uint32_t));
        resourceBlockBus->write(ResourceLayer::ResourceBlocksEnum::BLOCK_REGFILE, 33, 0, sizeof(uint32_t));               
      }
      break;
      
    case OPCODE_IRET:
      // return from interrupt routine
      break;
      
    default:
      break;
  }

  if (doJump) {
    resourceBlockBus->write(ResourceLayer::ResourceBlocksEnum::BLOCK_REGFILE, 1, result, sizeof(uint32_t));
  } else {
    incPc();
  }
}
} // namespace ExecutionLayer
