#include "FSM.hxx"

#include "ExecutionBlockBus.hxx"
#include "ResourceBlockBus.hxx"

namespace ControlLayer {

constexpr uint8_t OFFSET_SCHEME{3};
constexpr uint8_t OFFSET_OPCODE{4};
constexpr uint8_t OFFSET_DSTREG{7};
constexpr uint8_t OFFSET_SRCREG_1{12};
constexpr uint8_t OFFSET_SRCREG_2{16};
constexpr uint8_t OFFSET_IMM_I{16};
constexpr uint8_t OFFSET_IMM_IB{15};

constexpr uint32_t MASK_BLOCK{7};
constexpr uint32_t MASK_SCHEME{1 << OFFSET_SCHEME};
constexpr uint32_t MASK_OPCODE{7 << OFFSET_OPCODE};
constexpr uint32_t MASK_DSTREG{31 << OFFSET_DSTREG};
constexpr uint32_t MASK_SRCREG_1{31 << OFFSET_SRCREG_1};
constexpr uint32_t MASK_SRCREG_2{31 << OFFSET_SRCREG_2};
constexpr uint32_t MASK_IMM_I{unsigned(65535 << OFFSET_IMM_I)};
constexpr uint32_t MASK_IMM_IB{unsigned(131071 << OFFSET_IMM_IB)};

bool StateMachine::executeState(void) {
  bool status{true};
  uint32_t pc = m_resourceBlockBus.read(ResourceLayer::ResourceBlocksEnum::BLOCK_REGFILE, 1);  // read program counter

  uint8_t block{0};
  uint8_t scheme{0};
  uint8_t opcode{0};
  uint8_t dstreg{0};
  uint8_t srcreg1{0};
  uint8_t srcreg2{0};
  uint32_t imm{0};

  switch (m_currentState) {
    case State::STATE_INIT:
      m_nextState = State::STATE_FETCH;
      break;

    case State::STATE_FETCH:
      m_nextState = State::STATE_DECODE;
      m_currentInstruction = m_resourceBlockBus.read(ResourceLayer::ResourceBlocksEnum::BLOCK_MTU, pc);
      break;

    case State::STATE_DECODE:
      block = m_currentInstruction & MASK_BLOCK;
      scheme = (m_currentInstruction & MASK_SCHEME) >> OFFSET_SCHEME;
      opcode = (m_currentInstruction & MASK_OPCODE) >> OFFSET_OPCODE;
      dstreg = (m_currentInstruction & MASK_DSTREG) >> OFFSET_DSTREG;
      srcreg1 = (m_currentInstruction & MASK_SRCREG_1) >> OFFSET_SRCREG_1;

      if (scheme) {
        srcreg2 = (m_currentInstruction & MASK_SRCREG_2) >> OFFSET_SRCREG_2;
      } else {
        imm = (m_currentInstruction & MASK_IMM_I) >> OFFSET_IMM_I;
      }
      m_nextState = State::STATE_EXECUTE;
      break;

    case State::STATE_EXECUTE:
      if (block == 7 && opcode == 7) {
        m_nextState = State::STATE_HALT;
      }
      if (scheme) {  // Type-R coding scheme
        m_executionBlockBus.executeTypeR(static_cast<ExecutionLayer::ExecutionBlocksEnum>(block), opcode, dstreg, srcreg1, srcreg2);
      } else {
        m_executionBlockBus.executeTypeI(static_cast<ExecutionLayer::ExecutionBlocksEnum>(block), opcode, dstreg, srcreg1, imm);
      }
    case State::STATE_HALT:
      m_nextState = State::STATE_HALT;
      [[fallthrough]];
    case State::STATE_ERROR:
      m_nextState = State::STATE_ERROR;
      [[fallthrough]];
    default:
      m_nextState = State::STATE_ERROR;
      status = false;
  }
  m_currentState = m_nextState;
  return status;
}
}  // namespace ControlLayer
