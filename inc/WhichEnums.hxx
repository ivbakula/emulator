#pragma once

enum class WhichRegisterBlock {
  REG_BLOCK_REGFILE,
  REG_BLOCK_ISR_VECTOR,
  REG_BLOCK_SPECREG
};

enum class WhichExecBlock {
  EXEC_BLOCK_ARITHMETIC,
  EXEC_BLOCK_MEMORY,
  EXEC_BLOCK_BRANCH,
  EXEC_BLOCK_SPECREG_OPS,
  EXEC_BLOCK_CONTROL
};

enum SpecRegs {
  ZF, NF, IF, // status registers
  ILR // internal link register
};
