#pragma once

#include "PeripherialBus.hxx"
#include <cstdint>

namespace ResourceLayer {
class ResourceBlockIf {
 public:
  virtual uint32_t read(uint32_t index, std::size_t size) = 0;
  virtual void write(uint32_t index, uint32_t value, std::size_t size) = 0;

  static void setExternalBus(ExternalLayer::ExternalBus *externalBus);
  
 protected:
  static ExternalLayer::ExternalBus *m_externalBus;
  // add static member reference to peripherial bus
};
}  // namespace ResourceLayer
