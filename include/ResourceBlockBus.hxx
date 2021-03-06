#pragma once

#include <cstdint>
#include <map>

#include "ResourceBlockIf.hxx"

namespace ResourceLayer {
enum class ResourceBlocksEnum {
  BLOCK_REGFILE,
  BLOCK_ISRVECTOR,
  BLOCK_CTRL_REGS,
  BLOCK_MTU,
}; 

// TODO add enum for register names
class ResourceBlockBus {
 public: 
  virtual void write(ResourceBlocksEnum which, uint32_t index, uint32_t data, std::size_t size);
  virtual uint32_t read(ResourceBlocksEnum which, uint32_t index, std::size_t size);

 private:
  static std::map<ResourceBlocksEnum, ResourceBlockIf*> m_resourceBlocks;
};
} // namespace ResourceLayer
