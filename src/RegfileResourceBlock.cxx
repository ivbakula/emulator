#include "RegfileResourceBlock.hxx"

#include "ResourceBlockBus.hxx"

#define ZERO_FLAG 32
#define NEGATIVE_FLAG 33
#define INTERRUPT_FLAG 34
#define ALL_FLAGS 35

namespace ResourceLayer {
void RegfileResourceBlock::write(uint32_t index, uint32_t value, std::size_t size) {
  if (index < 32 && index != 0) {
    m_regfile[index] = value;
  } else {
    switch (index) {
      case ZERO_FLAG:
        m_status.flags.m_zf = value;
        break;

      case NEGATIVE_FLAG:
        m_status.flags.m_nf = value;
        break;

      case INTERRUPT_FLAG:
        m_status.flags.m_if = value;
        break;

      case ALL_FLAGS:
        m_status.data = value;
        break;

      default:
        break;
    }
  }
  // else throw an exception (not yet implemented)
}

uint32_t RegfileResourceBlock::read(uint32_t index, std::size_t size) {
  uint32_t retval{0};
  if (index < 32 && index != 0) {
    retval = m_regfile[index];
  } else {
    switch (index) {
      case ZERO_FLAG:
        retval = m_status.flags.m_zf;
        break;

      case NEGATIVE_FLAG:
        retval = m_status.flags.m_nf;
        break;

      case INTERRUPT_FLAG:
        retval = m_status.flags.m_if;
        break;

      case ALL_FLAGS:
        retval = m_status.data;

      default:
        break;
    }
  }
  // else throw an exception (not yet implemented)
  return retval;
}
}  // namespace ResourceLayer
