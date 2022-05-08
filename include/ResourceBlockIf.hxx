#pragma once

#include <cstdint>

namespace ResourceLayer {
class ResourceBlockIf {
 public:
  virtual uint32_t read(uint32_t index) = 0;
  virtual void write(uint32_t index, uint32_t value) = 0;
};
}  // namespace ResourceLayer
