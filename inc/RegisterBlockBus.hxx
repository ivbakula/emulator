#pragma once

#include <map>

#include "RegisterBlockIf.hxx"
#include "WhichEnums.hxx"

// TODO create register blocks via facoty
class RegisterBlockBus {
 public:
  uint32_t read(WhichRegisterBlock which, uint8_t reg);
  void write(WhichRegisterBlock which, uint8_t reg, uint32_t value);

 private:
  std::map<WhichRegisterBlock, RegisterBlockIf*> m_registerBlocks;
};
