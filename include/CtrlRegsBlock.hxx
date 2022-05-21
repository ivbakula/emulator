#include "ResourceBlockIf.hxx"

namespace ResourceLayer {

enum CtrlRegisterEnum {
  HALT,
  BREAK,
  ERROR,
  ALL
};

class CtrlRegsBlock : public ResourceBlockIf {
 public:
  uint32_t read(uint32_t index, std::size_t size) override;
  void write(uint32_t index, uint32_t value, std::size_t size) override;

 private:
  union {
    uint8_t data;
    struct  {
    uint8_t m_halt : 1;
    uint8_t m_break : 1;
    uint8_t m_error : 1;
    uint8_t m_normal: 1;
    uint8_t not_used : 4;
    } registerFields;
  } m_ctrlRegister;
};
} // namespace ResourceLayer
