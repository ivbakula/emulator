#include "ExecutionBlockIf.hxx"
#include <cstdint>
#include <limits>
#include "ResourceBlockBus.hxx"

namespace ExecutionLayer {

void ExecutionBlockIf::executeTypeR(uint8_t opcode, uint8_t dstreg, uint8_t op1reg, uint8_t op2reg) {
  uint32_t op1 = resourceBlockBus->read(ResourceLayer::ResourceBlocksEnum::BLOCK_REGFILE, op1reg, sizeof(uint32_t));
  uint32_t op2 = resourceBlockBus->read(ResourceLayer::ResourceBlocksEnum::BLOCK_REGFILE, op2reg, sizeof(uint32_t));

  internalExecute(opcode, dstreg, op1, op2);
}

void ExecutionBlockIf::executeTypeI(uint8_t opcode, uint8_t dstreg, uint8_t op1reg, uint32_t imm) {
  uint32_t op1 = resourceBlockBus->read(ResourceLayer::ResourceBlocksEnum::BLOCK_REGFILE, op1reg, sizeof(uint32_t));
  constexpr uint32_t IMM_MAX{(1<<14)-1};
  constexpr uint32_t WORD_MAX{std::numeric_limits<uint32_t>::max()};
  constexpr uint32_t SIGN_EXTEND_MASK {WORD_MAX & (~IMM_MAX)};
  constexpr uint32_t SIGN_BIT {1 << 13};

  // sign-extend
  if (imm & SIGN_BIT) {
    imm |= SIGN_EXTEND_MASK;
  }

  internalExecute(opcode, dstreg, op1, imm);
}

void ExecutionBlockIf::executeTypeIB(uint8_t opcode, uint8_t dstreg, uint32_t imm) {
  imm = imm << 13;
  uint32_t op1 {0};
  internalExecute(opcode, dstreg, op1, imm);
}

void ExecutionBlockIf::setResourceBlockBus(ResourceLayer::ResourceBlockBus *rscBlkBus) {
  resourceBlockBus = rscBlkBus;
}

ResourceLayer::ResourceBlockBus* ExecutionBlockIf::resourceBlockBus {};

void ExecutionBlockIf::incPc() {
  uint32_t pc = resourceBlockBus->read(ResourceLayer::ResourceBlocksEnum::BLOCK_REGFILE, 1, sizeof(uint32_t)) + 0x4;
  resourceBlockBus->write(ResourceLayer::ResourceBlocksEnum::BLOCK_REGFILE, 1, pc, sizeof(uint32_t));
}
} // namespace ExecutionLayer
