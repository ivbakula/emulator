#pragma once
#include <memory>
#include "PeripherialBus.hxx"
#include "FSM.hxx"

class Core {
 public:
  Core() = delete;
  explicit Core(ExternalLayer::ExternalBus* externalBus); // create buses and fsm
  void run();

 private:
  std::unique_ptr<ControlLayer::StateMachine> m_stateMachine;
  ResourceLayer::ResourceBlockBus m_resourceBlockBus;
  ExecutionLayer::ExecutionBlockBus m_execBlockBus;
};
