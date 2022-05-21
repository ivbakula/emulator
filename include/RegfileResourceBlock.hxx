#include "ResourceBlockIf.hxx"

namespace ResourceLayer {

class RegfileResourceBlock : public ResourceBlockIf {
 public:
  uint32_t read(uint32_t index, std::size_t size) override;
  void write(uint32_t index, uint32_t value, std::size_t size) override;

 private:
  uint32_t m_regfile[32] {0, 0x4};

  union {
    uint8_t data;
    struct {
      uint8_t m_zf : 1;
      uint8_t m_nf : 1;
      uint8_t m_if : 1;
    } flags;
  } m_status;
};

}  // namespace ResourceLayer
