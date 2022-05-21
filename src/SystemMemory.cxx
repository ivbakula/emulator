#include "SystemMemory.hxx"

namespace ExternalLayer {
uint32_t SystemMemory::read(uint8_t column, uint32_t row, std::size_t size) {
  uint32_t retval {0};
  if (row < 4000) {
    switch (size) {
      case sizeof(uint32_t):
        retval |= (m_blockRam[row][column+3] << 24);
        retval |= (m_blockRam[row][column+2] << 16);
        [[fallthrough]];
      case sizeof(uint16_t):
        retval |= (m_blockRam[row][column+1] << 8);
        [[fallthrough]];
      case sizeof(uint8_t):
        retval |= m_blockRam[row][column];
        break;
      default:
        break;
    }
   } else {
    // raise an exception
  }
  return retval;
}

void SystemMemory::write(uint8_t column, uint32_t row, uint32_t data, std::size_t size) {
  if (row < 4000) {
    switch (size) {
      case sizeof(uint32_t):
        m_blockRam[row][column+3] = data & (0xff << 24);
        m_blockRam[row][column+2] = data & (0xff << 16);
        [[fallthrough]];
      case sizeof(uint16_t):
        m_blockRam[row][column+1] = data & (0xff << 8);
        [[fallthrough]];
      case sizeof(uint8_t):
        m_blockRam[row][column] = data & 0xff;
        break;
      default:
        break;
    }
  }
}
} // namespace ExternalLayer
