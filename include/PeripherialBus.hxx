#pragma once

#include <cstdint>
#include <map>

#include "MMIODeviceIf.hxx"

namespace ExternalLayer {

enum class DeviceEnum {
  DEVICE_SYS_MEMORY
};

class ExternalBus {
 public:
  virtual void write(DeviceEnum which, uint32_t row, uint8_t column, uint32_t data, std::size_t size);
  virtual uint32_t read(DeviceEnum which, uint32_t row, uint8_t column, std::size_t size);

 private:
  static std::map<DeviceEnum, MMIODeviceIf*> m_mmioDevices;
};
} // namespace ExternalLayer
