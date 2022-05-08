#pragma once
#include "ResourceBlockBus.hxx"
#include "ExecutionBlockBus.hxx"

namespace ControlLayer {
enum class State {
  STATE_INIT,
  STATE_FETCH,
  STATE_DECODE,
  STATE_EXECUTE,
  STATE_HALT,
  STATE_ERROR
};

class StateMachine {
 public:
  StateMachine() = delete;

  StateMachine(ResourceLayer::ResourceBlockBus& resourceBlockBus,
               ExecutionLayer::ExecutionBlockBus& executionBlockBus)
      : m_resourceBlockBus{resourceBlockBus}, m_executionBlockBus{executionBlockBus} {}

  bool executeState(void);

 private:
  State m_currentState {State::STATE_INIT};
  State m_nextState {State::STATE_HALT};
  uint32_t m_currentInstruction {0x0};

  ResourceLayer::ResourceBlockBus& m_resourceBlockBus;
  ExecutionLayer::ExecutionBlockBus& m_executionBlockBus;
}; 
} // namespace ControlLayer
