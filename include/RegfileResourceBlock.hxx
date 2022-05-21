#include "ResourceBlockIf.hxx"

namespace ResourceLayer {

class RegfileResourceBlock : public ResourceBlockIf {
 public:
  uint32_t read(uint32_t index, std::size_t size) override;
  void write(uint32_t index, uint32_t value, std::size_t size) override;

 private:
  uint32_t m_regfile[32] {0, 0x4};
};
}  // namespace ResourceLayer
