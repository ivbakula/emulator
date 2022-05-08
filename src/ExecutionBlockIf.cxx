#include "ExecutionBlockIf.hxx"
#include "ResourceBlockBus.hxx"

namespace ExecutionLayer {

void ExecutionBlock::executeTypeR(uint8_t opcode, uint8_t dstreg, uint8_t op1reg, uint8_t op2reg) {
  uint32_t op1 = resourceBlockBus->read(ResourceLayer::ResourceBlocksEnum::BLOCK_REGFILE, op1reg);
  uint32_t op2 = resourceBlockBus->read(ResourceLayer::ResourceBlocksEnum::BLOCK_REGFILE, op2reg);

  internalExecute(opcode, dstreg, op1, op2);
}

void ExecutionBlock::setResourceBlockBus(ResourceLayer::ResourceBlockBus *rscBlkBus) {
  resourceBlockBus = rscBlkBus;
}
ResourceLayer::ResourceBlockBus* ExecutionBlock::resourceBlockBus {};

void ExecutionBlock::incPc() {
  uint32_t pc = resourceBlockBus->read(ResourceLayer::ResourceBlocksEnum::BLOCK_REGFILE, 1) + 0x4;
  resourceBlockBus->write(ResourceLayer::ResourceBlocksEnum::BLOCK_REGFILE, 1, pc);
}
} // namespace ExecutionLayer
