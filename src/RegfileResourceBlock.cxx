#include "RegfileResourceBlock.hxx"

#include "ResourceBlockBus.hxx"

namespace ResourceLayer {
void RegfileResourceBlock::write(uint32_t index, uint32_t value) {
  if (index < 32) {
    m_regfile[index] = value;
  }
  // else throw an exception (not yet implemented)
}

uint32_t RegfileResourceBlock::read(uint32_t index) {
  uint32_t retval{0};
  if (index < 32) {
    retval = m_regfile[index];
  }
  // else throw an exception (not yet implemented)
  return retval;
}
}  // namespace ResourceLayer
