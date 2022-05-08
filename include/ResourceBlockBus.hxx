#pragma once

#include <cstdint>
#include <map>

#include "ResourceBlockIf.hxx"

namespace ResourceLayer {
enum class ResourceBlocksEnum {
  BLOCK_REGFILE,
  BLOCK_ISRVECTOR,
  BLOCK_SPECREGS,
  BLOCK_MTU,
}; 

// TODO add enum for register names

class ResourceBlockBus {
 public: 
  void write(ResourceBlocksEnum which, uint32_t index, uint32_t data);
  uint32_t read(ResourceBlocksEnum which, uint32_t index);

 private:
  static std::map<ResourceBlocksEnum, ResourceBlockIf*> m_resourceBlocks;
};
} // namespace ResourceLayer