#include "ExecutionBlock.hxx"
#include <cstdint>
#include "WhichEnums.hxx"

bool ExecutionBlock::executeTypeR(uint8_t opcode, uint8_t dstreg, uint8_t op1reg, uint8_t op2reg) {
  uint32_t op1 = m_registerBlockBus.read(WhichRegisterBlock::REG_BLOCK_REGFILE, op1reg);
  uint32_t op2 = m_registerBlockBus.read(WhichRegisterBlock::REG_BLOCK_REGFILE, op2reg);

  return internalExecute(opcode, dstreg, op1, op2);
}

bool ExecutionBlock::executeTypeI(uint8_t opcode, uint8_t dstreg, uint8_t op1reg, int32_t imm) {
  uint32_t op1 = m_registerBlockBus.read(WhichRegisterBlock::REG_BLOCK_REGFILE, op1reg);

  return internalExecute(opcode, dstreg, op1, imm);
}

void ExecutionBlock::updatePc() {
  uint32_t currentPc = m_registerBlockBus.read(WhichRegisterBlock::REG_BLOCK_REGFILE, 1);
  m_registerBlockBus.write(WhichRegisterBlock::REG_BLOCK_REGFILE, 1, currentPc + 4);
}

bool ArithmeticBlock::internalExecute(uint8_t opcode, uint8_t dstreg, uint32_t op1, uint32_t op2) {
  switch(opcode) {
    case ArithmeticOpcode::INSTRUCTION_ADD:
      m_registerBlockBus.write(WhichRegisterBlock::REG_BLOCK_REGFILE, dstreg, op1 + op2);
      break;

    case ArithmeticOpcode::INSTRUCTION_SUB:
      m_registerBlockBus.write(WhichRegisterBlock::REG_BLOCK_REGFILE, dstreg, op1 - op2);
      break;

    case ArithmeticOpcode::INSTRUCTION_SHL:
      m_registerBlockBus.write(WhichRegisterBlock::REG_BLOCK_REGFILE, dstreg, op1 << op2);
      break;

    case ArithmeticOpcode::INSTRUCTION_SHR:
      m_registerBlockBus.write(WhichRegisterBlock::REG_BLOCK_REGFILE, dstreg, op1 >> op2);
      break;

    case ArithmeticOpcode::INSTRUCTION_AND:
      m_registerBlockBus.write(WhichRegisterBlock::REG_BLOCK_REGFILE, dstreg, op1 & op2);
      break;

    case ArithmeticOpcode::INSTRUCTION_OR:
      m_registerBlockBus.write(WhichRegisterBlock::REG_BLOCK_REGFILE, dstreg, op1 | op2);
      break;

    case ArithmeticOpcode::INSTRUCTION_NOT:
      m_registerBlockBus.write(WhichRegisterBlock::REG_BLOCK_REGFILE, dstreg, ~op2);
      break;

    case ArithmeticOpcode::INSTRUCTION_XOR:
      m_registerBlockBus.write(WhichRegisterBlock::REG_BLOCK_REGFILE, dstreg, op1 ^ op2);
      break;
  }

  updatePc();

  return true;
}


void BranchBlock::takeBranch(uint8_t pcIndex, uint32_t pc, int32_t offset) {
  m_registerBlockBus.write(WhichRegisterBlock::REG_BLOCK_REGFILE, pcIndex, pc + (offset * 4));
}

bool BranchBlock::internalExecute(uint8_t opcode, uint8_t dstreg, uint32_t op1, uint32_t op2) {
  bool zeroFlag = m_registerBlockBus.read(WhichRegisterBlock::REG_BLOCK_SPECREG, SpecRegs::ZF) ? true : false;
  bool negativeFlag = m_registerBlockBus.read(WhichRegisterBlock::REG_BLOCK_SPECREG, SpecRegs::NF) ? true : false;
  bool branchTaken {false};

  int32_t diff {0};
  uint32_t internalLinkRegister {0};

  // branching is preformed like this: pc = pc + offset
  switch(opcode) {
    case BranchOpcode::INSTRUCTION_BR:
      takeBranch(dstreg, op1, op2);
      branchTaken = true;
      break;

    case BranchOpcode::INSTRUCTION_BEQ:
      if (zeroFlag && !negativeFlag) {
        takeBranch(dstreg, op1, op2);
        branchTaken = true;
      }
      break;

    case BranchOpcode::INSTRUCTION_BLT:
      if (!zeroFlag && negativeFlag) {
        takeBranch(dstreg, op1, op2);
        branchTaken = true;
      }
      break;

    case BranchOpcode::INSTRUCTION_BLE:
      if (zeroFlag || negativeFlag) {
        takeBranch(dstreg, op1, op2);
        branchTaken = true;
      }
      break;

    case BranchOpcode::INSTRUCTION_BGT:
      if (!zeroFlag && !negativeFlag) {
        takeBranch(dstreg, op1, op2);
        branchTaken = true;
      }
      break;

    case BranchOpcode::INSTRUCTION_BGE:
      if (zeroFlag || !negativeFlag) {
        takeBranch(dstreg, op1, op2);
        branchTaken = true;
      }
      break;

    case BranchOpcode::INSTRUCTION_CMP:
      m_registerBlockBus.write(WhichRegisterBlock::REG_BLOCK_SPECREG, SpecRegs::ZF, 0);
      m_registerBlockBus.write(WhichRegisterBlock::REG_BLOCK_SPECREG, SpecRegs::NF, 0);

      diff = op1 - op2;
      if (diff < 0) {
        m_registerBlockBus.write(WhichRegisterBlock::REG_BLOCK_SPECREG, SpecRegs::NF, 1);
      } else if (diff == 0) {
        m_registerBlockBus.write(WhichRegisterBlock::REG_BLOCK_SPECREG, SpecRegs::ZF, 1);
      }
      break;

    case BranchOpcode::INSTRUCTION_IRET:
      internalLinkRegister = m_registerBlockBus.read(WhichRegisterBlock::REG_BLOCK_SPECREG, SpecRegs::ILR);
      break;
  }

  if (!branchTaken) {
    updatePc();
  }
  return true;
}

bool MemoryBlock::internalExecute(uint8_t opcode, uint8_t dstreg, uint32_t op1, uint32_t imm) {
  switch (opcode) {
    case MemoryOpcode::INSTRUCTION_LB:
    case MemoryOpcode::INSTRUCTION_LW:
    case MemoryOpcode::INSTRUCTION_SB:
    case MemoryOpcode::INSTRUCTION_SW:
      break;
  }

  updatePc();
  return true;
}

bool RegisterOperationBlock::internalExecute(uint8_t opcode, uint8_t dstreg, uint32_t op1, uint32_t op2) {
  uint32_t reg {0}; 
  switch (opcode) {
    case RegisterOperationOpcode::INSTRUCTION_LUI:
      reg = m_registerBlockBus.read(WhichRegisterBlock::REG_BLOCK_REGFILE, dstreg);
      m_registerBlockBus.write(WhichRegisterBlock::REG_BLOCK_REGFILE, dstreg, reg | (op2 << 16));
      break;

    case RegisterOperationOpcode::INSTRUCTION_CIF:
      m_registerBlockBus.write(WhichRegisterBlock::REG_BLOCK_SPECREG, SpecRegs::IF, 0);
      break;

    case RegisterOperationOpcode::INSTRUCTION_SIF:
      m_registerBlockBus.write(WhichRegisterBlock::REG_BLOCK_SPECREG, SpecRegs::IF, 1);
      break;

    case RegisterOperationOpcode::INSTRUCTION_SETI:
      m_registerBlockBus.write(WhichRegisterBlock::REG_BLOCK_ISR_VECTOR, dstreg, op1 + op2);
      break;

    case RegisterOperationOpcode::INSTRUCTION_GETI:
      break;

    case RegisterOperationOpcode::INSTRUCTION_CSF: 
      break;
  }

  updatePc();
  return true;
}
