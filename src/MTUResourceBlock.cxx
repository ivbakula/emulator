#include "MTUResourceBlock.hxx"
#include "PeripherialBus.hxx"

namespace ResourceLayer {
uint32_t MTUResourceBlock::read(uint32_t address, std::size_t size) {
  uint8_t column;
  uint32_t row;
  ExternalLayer::DeviceEnum which = translateAddress(address, column, row);

  return m_externalBus->read(which, column, row, size);
}

void MTUResourceBlock::write(uint32_t address, uint32_t value, std::size_t size) {
  uint8_t column;
  uint32_t row;
  ExternalLayer::DeviceEnum which = translateAddress(address, column, row);

  m_externalBus->write(which, column, row, value, size);
}

ExternalLayer::DeviceEnum MTUResourceBlock::translateAddress(uint32_t address, uint8_t& column, uint32_t& row) {
  ExternalLayer::DeviceEnum retval {};
  constexpr uint32_t MEMORY_ALIGNEMENT{0x4}; // 4-byte alignement
  constexpr uint32_t SYSTEM_MEMORY_SIZE{16000}; // 16K of system memory (RAM)
  constexpr uint32_t SYSTEM_MEMORY_START{0x4};
  constexpr uint32_t SYSTEM_MEMORY_END{SYSTEM_MEMORY_START + SYSTEM_MEMORY_SIZE};
  
  if (address < SYSTEM_MEMORY_END && address >= SYSTEM_MEMORY_START) {
    retval = ExternalLayer::DeviceEnum::DEVICE_SYS_MEMORY;
  }
  // else throw sigbus
  
  column = (address - SYSTEM_MEMORY_START) % 4;
  row = (address - SYSTEM_MEMORY_START) / 4;

  return retval;
}
} // namespace ResourceLayer
