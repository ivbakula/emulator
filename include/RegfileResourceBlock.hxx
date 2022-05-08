#include "ResourceBlockIf.hxx"

namespace ResourceLayer {

class RegfileResourceBlock : public ResourceBlockIf {
 public:
  uint32_t read(uint32_t index) override;
  void write(uint32_t index, uint32_t value) override;

  static bool registeredInFactory;

 private:
  uint32_t m_regfile[32];
};
}  // namespace ResourceLayer
