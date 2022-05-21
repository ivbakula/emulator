#include "CtrlRegsBlock.hxx"

namespace ResourceLayer {

uint32_t CtrlRegsBlock::read(uint32_t index, std::size_t size) {
  switch (index) {
    case CtrlRegisterEnum::HALT: return m_ctrlRegister.registerFields.m_halt;
    case CtrlRegisterEnum::BREAK: return m_ctrlRegister.registerFields.m_break;
    case CtrlRegisterEnum::ERROR: return m_ctrlRegister.registerFields.m_error;
    case CtrlRegisterEnum::ALL: return m_ctrlRegister.data;
    default:
      break;
  }
  return -1;
}

void CtrlRegsBlock::write(uint32_t index, uint32_t value, std::size_t size) {
  switch(static_cast<CtrlRegisterEnum>(index)) {
    case CtrlRegisterEnum::ERROR:
      m_ctrlRegister.registerFields.m_error = value;
      break;

    case CtrlRegisterEnum::BREAK:
      m_ctrlRegister.registerFields.m_break = value;
      break;

    case CtrlRegisterEnum::HALT:
      m_ctrlRegister.registerFields.m_halt = value;
      break;

    case CtrlRegisterEnum::ALL:
      m_ctrlRegister.data = value;
      break;

    default:
      break;
  }
}
} // namespace ResourceLayer
