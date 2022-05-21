#include "ResourceBlockIf.hxx"

namespace ResourceLayer {

void ResourceBlockIf::setExternalBus(ExternalLayer::ExternalBus *externalBus) {
  m_externalBus = externalBus;
}

ExternalLayer::ExternalBus *ResourceBlockIf::m_externalBus{};
}
