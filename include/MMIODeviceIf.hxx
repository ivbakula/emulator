#pragma once

#include <cstdint>

namespace ExternalLayer {

class MMIODeviceIf {
 public:
  virtual uint32_t read(uint8_t column, uint32_t row, std::size_t size) = 0;
  virtual void write(uint8_t column, uint32_t row, uint32_t data, std::size_t size) = 0;
};
} // namespace MMIODevice

