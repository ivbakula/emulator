#include "PeripherialBus.hxx"
#include <cstdint>
#include "SystemMemory.hxx"

namespace ExternalLayer {
void ExternalBus::write(DeviceEnum which, uint32_t row, uint8_t column, uint32_t data, std::size_t size) {
  if (m_mmioDevices.find(which) != m_mmioDevices.end()) {
    m_mmioDevices[which]->write(row, column, data, size);
  }
}

uint32_t ExternalBus::read(DeviceEnum which, uint32_t row, uint8_t column, std::size_t size) {
  uint32_t retval{0};

  if (m_mmioDevices.find(which) != m_mmioDevices.end()) {
    retval = m_mmioDevices[which]->read(row, column, size);
  }
  return retval;
}

std::map<DeviceEnum, MMIODeviceIf*> ExternalBus::m_mmioDevices {
  {DeviceEnum::DEVICE_SYS_MEMORY, new SystemMemory}
};
} // namespace ExternalLayer
