#pragma once

#include "MMIODeviceIf.hxx"

namespace ExternalLayer {

class SystemMemory : public MMIODeviceIf {
 public:
  uint32_t read(uint8_t column, uint32_t row, std::size_t size) override;
  void write(uint8_t column, uint32_t row, uint32_t data, std::size_t size) override;
  
 private:
  // add r0, r1, 10 -> 0x00 0a 02 08
  // hlt -> 0x00000077
  uint8_t m_blockRam[4000][4] {
    {0x00, 0x0a, 0x02, 0x08},
    {0x77, 0x00, 0x00, 0x00},
    {}
  }; // 16K of ram
};
} // namespace ExternalLayer
