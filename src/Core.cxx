#include "Core.hxx"

#include <memory>

Core::Core(ExternalLayer::ExternalBus* externalBus) {
  ResourceLayer::ResourceBlockIf::setExternalBus(externalBus);
  ExecutionLayer::ExecutionBlockIf::setResourceBlockBus(&m_resourceBlockBus);
  m_stateMachine = std::make_unique<ControlLayer::StateMachine>(m_resourceBlockBus, m_execBlockBus);
}

void Core::run() {
  m_stateMachine->executeState();

  for (int i = 0; i < 6; i++) {
    m_stateMachine->executeState();
  }
}
