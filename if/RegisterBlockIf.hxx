#pragma once

#include <cstdint>

class RegisterBlockIf {
 public:
  virtual ~RegisterBlockIf() = default;

  virtual uint32_t read(uint8_t reg) = 0;
  virtual void write(uint8_t reg, uint32_t value) = 0;
};
