#pragma once

#include "ExecutionBlockIf.hxx"
#include "RegisterBlockBus.hxx"

class ExecutionBlock : public ExecutionBlockIf {
 public:
  ExecutionBlock() = delete;
  explicit ExecutionBlock(RegisterBlockBus& registerBlockBus) : m_registerBlockBus{registerBlockBus} {}
  virtual ~ExecutionBlock() = default;

  bool executeTypeR(uint8_t opcode, uint8_t dstreg, uint8_t op1reg, uint8_t op2reg) override;
  bool executeTypeI(uint8_t opcode, uint8_t dstreg, uint8_t op1reg, int32_t imm) override;

 protected:
  void updatePc(void);
  RegisterBlockBus& m_registerBlockBus;
};

class ArithmeticBlock : ExecutionBlock {
 public:
  ArithmeticBlock() = delete;
  explicit ArithmeticBlock(RegisterBlockBus& registerBlockBus) : ExecutionBlock(registerBlockBus) {}
  virtual ~ArithmeticBlock() = default;

 protected:
  bool internalExecute(uint8_t opcode, uint8_t dstreg, uint32_t op1, uint32_t imm) override;
};

class BranchBlock : public ExecutionBlock {
 public:
  BranchBlock() = delete;
  explicit BranchBlock(RegisterBlockBus& registerBlockBus) : ExecutionBlock(registerBlockBus) {}
  virtual ~BranchBlock() = default;

 protected:
  bool internalExecute(uint8_t opcode, uint8_t dstreg, uint32_t op1, uint32_t imm) override;

 private:
  void takeBranch(uint8_t pcPtr, uint32_t pc, int32_t offset);
};

class MemoryBlock : public ExecutionBlock {
 public:
  MemoryBlock() = delete;
  explicit MemoryBlock(RegisterBlockBus registerBlockBus) : ExecutionBlock(registerBlockBus) {}
  virtual ~MemoryBlock() = default;

 protected:
  bool internalExecute(uint8_t opcode, uint8_t dstreg, uint32_t op1, uint32_t imm) override;
};

class RegisterOperationBlock : public ExecutionBlock {
 public:
  RegisterOperationBlock() = delete;
  explicit RegisterOperationBlock(RegisterBlockBus registerBlockBus) : ExecutionBlock(registerBlockBus) {}
  virtual ~RegisterOperationBlock() = default;

 protected:
  bool internalExecute(uint8_t opcode, uint8_t dstreg, uint32_t op1, uint32_t imm) override;
};

enum ArithmeticOpcode {
  INSTRUCTION_ADD,
  INSTRUCTION_SUB,
  INSTRUCTION_SHL,
  INSTRUCTION_SHR,
  INSTRUCTION_AND,
  INSTRUCTION_OR,
  INSTRUCTION_NOT,
  INSTRUCTION_XOR
};

enum BranchOpcode {
  INSTRUCTION_BR,
  INSTRUCTION_BEQ,
  INSTRUCTION_BLT,
  INSTRUCTION_BLE,
  INSTRUCTION_BGT,
  INSTRUCTION_BGE,
  INSTRUCTION_CMP,
  INSTRUCTION_IRET
};

enum MemoryOpcode { INSTRUCTION_LB, INSTRUCTION_LW, INSTRUCTION_SB, INSTRUCTION_SW };

enum RegisterOperationOpcode {
  INSTRUCTION_LUI = 1,
  INSTRUCTION_CIF,
  INSTRUCTION_SIF,
  INSTRUCTION_SETI,
  INSTRUCTION_GETI,
  INSTRUCTION_CSF
};
