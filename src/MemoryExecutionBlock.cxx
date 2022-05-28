#include "MemoryExeBlock.hxx"
#include "ResourceBlockBus.hxx"

namespace ExecutionLayer {

void MemoryExeBlock::internalExecute(uint8_t opcode, uint8_t dstreg, uint32_t op1, uint32_t op2) {
  uint32_t ptr = resourceBlockBus->read(ResourceLayer::ResourceBlocksEnum::BLOCK_REGFILE, dstreg, sizeof(uint32_t));
  uint32_t data {};
  switch(opcode) {
    case OPCODE_LB:
      data = resourceBlockBus->read(ResourceLayer::ResourceBlocksEnum::BLOCK_MTU, op1 + op2, sizeof(uint8_t));
      resourceBlockBus->write(ResourceLayer::ResourceBlocksEnum::BLOCK_REGFILE, dstreg, data, sizeof(uint32_t));
      break;
      
    case OPCODE_LHW:
      data = resourceBlockBus->read(ResourceLayer::ResourceBlocksEnum::BLOCK_MTU, op1 + op2, sizeof(uint16_t));
      resourceBlockBus->write(ResourceLayer::ResourceBlocksEnum::BLOCK_REGFILE, dstreg, data, sizeof(uint32_t));
      break;
      
    case OPCODE_LW:
      data = resourceBlockBus->read(ResourceLayer::ResourceBlocksEnum::BLOCK_MTU, op1 + op2, sizeof(uint32_t));
      resourceBlockBus->write(ResourceLayer::ResourceBlocksEnum::BLOCK_REGFILE, dstreg, data, sizeof(uint32_t));
      break;
      
    case OPCODE_SB:
      resourceBlockBus->write(ResourceLayer::ResourceBlocksEnum::BLOCK_MTU, ptr + op2, op1, sizeof(uint8_t));
      break;
      
    case OPCODE_SHW:
      resourceBlockBus->write(ResourceLayer::ResourceBlocksEnum::BLOCK_MTU, ptr + op2, op1, sizeof(uint16_t));
      break;
      
    case OPCODE_SW:
      resourceBlockBus->write(ResourceLayer::ResourceBlocksEnum::BLOCK_MTU, ptr + op2, op1, sizeof(uint32_t));
      break;
      
    default:
      break;
  }

  incPc();
}
} // namespace ExecutionLayer
