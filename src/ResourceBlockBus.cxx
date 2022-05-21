#include "ResourceBlockBus.hxx"

#include "MTUResourceBlock.hxx"
#include "RegfileResourceBlock.hxx"

namespace ResourceLayer {

void ResourceBlockBus::write(ResourceBlocksEnum which, uint32_t index, uint32_t data, std::size_t size) {
  if (m_resourceBlocks.find(which) != m_resourceBlocks.end()) {
    m_resourceBlocks[which]->write(index, data, size);
  }
  // else throw an exception (not yet implemented)
}

uint32_t ResourceBlockBus::read(ResourceBlocksEnum which, uint32_t index, std::size_t size) {
  uint32_t retval{};
  if (m_resourceBlocks.find(which) != m_resourceBlocks.end()) {
    retval = m_resourceBlocks[which]->read(index, size);
  }
  // you should throw an exception here, but exceptions and interrupts are not yet implemented
  return retval;
}

std::map<ResourceBlocksEnum, ResourceBlockIf *> ResourceBlockBus::m_resourceBlocks{
    {ResourceBlocksEnum::BLOCK_REGFILE, new RegfileResourceBlock},
    {ResourceBlocksEnum::BLOCK_MTU, new MTUResourceBlock}};
}  // namespace ResourceLayer
