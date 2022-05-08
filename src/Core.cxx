#include "Core.hxx"
#include ""
#include <memory>

Core::Core()
{
  ExecutionLayer::ExecutionBlock::setResourceBlockBus(&m_resourceBlockBus);
  m_stateMachine = std::make_unique<ControlLayer::StateMachine>(m_resourceBlockBus, m_execBlockBus); 
}

void Core::run() {
  while(m_stateMachine->executeState());
}
