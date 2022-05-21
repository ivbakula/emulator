#pragma once

#include "ResourceBlockIf.hxx"

namespace ResourceLayer {

class MTUResourceBlock : public ResourceBlockIf {
 public:
  uint32_t read(uint32_t address, std::size_t size) override;
  void write(uint32_t address, uint32_t value, std::size_t size) override;

 private:
  ExternalLayer::DeviceEnum translateAddress(uint32_t address, uint8_t& column, uint32_t& row);
};
}
