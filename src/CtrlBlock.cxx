#include "CtrlBlock.hxx"
#include "ResourceBlockBus.hxx"

namespace ExecutionLayer {

constexpr uint32_t CTRL_REGISTER_BREAK{1};
constexpr uint32_t CTRL_REGISTER_HALT {0};
void CtrlBlock::internalExecute(uint8_t opcode, uint8_t dstreg, uint32_t op1, uint32_t op2) {
  switch (opcode) {
    case OPCODE_BRK:
      resourceBlockBus->write(ResourceLayer::ResourceBlocksEnum::BLOCK_CTRL_REGS, CTRL_REGISTER_BREAK, 1, sizeof(uint32_t));    // write to break regsiter
      break;
      
    case OPCODE_HALT:
      resourceBlockBus->write(ResourceLayer::ResourceBlocksEnum::BLOCK_CTRL_REGS, CTRL_REGISTER_HALT, 1, sizeof(uint32_t)); // 0 - halt register
    default:
      break;
  }
  incPc();
};
} // namespace ExecutionLayer
