#include "FSM.hxx"

#include <cstdint>
#include <iostream>

#include "ExecutionBlockBus.hxx"
#include "ResourceBlockBus.hxx"

namespace ControlLayer {

union DecoderMux {
  uint32_t data;
  struct {
    uint32_t block : 3;
    uint32_t scheme : 2;
    uint32_t opcode : 3;
    uint32_t dstreg : 5;
    uint32_t srcreg : 5;
    uint32_t not_used : 14;
  } common_bits;

  struct {
    uint32_t common : 18;
    uint32_t src2reg : 5;
    uint32_t not_used : 9;
  } type_r;

  struct {
    uint32_t common : 18;
    uint32_t imm : 14;
  } type_i;

  struct {
    uint32_t common : 13;  // don't use srcreg.
    uint32_t imm : 18;
  } type_ib;
};

constexpr uint32_t CODING_SCHEME_TYPE_R{0x0};
constexpr uint32_t CODING_SCHEME_TYPE_I{0x1};
constexpr uint32_t CODING_SCHEME_TYPE_IB{0x2};

bool StateMachine::executeState(void) {
  bool status{true};
  uint32_t pc = m_resourceBlockBus.read(ResourceLayer::ResourceBlocksEnum::BLOCK_REGFILE, 1, sizeof(uint32_t));  // read program counter

  uint8_t block{0};
  uint8_t scheme{0};
  uint8_t opcode{0};
  uint8_t dstreg{0};
  uint8_t srcreg1{0};
  uint8_t srcreg2{0};
  uint32_t imm{0};

  DecoderMux decoderMux;
  switch (m_currentState) {
    case State::STATE_INIT:
      m_nextState = State::STATE_FETCH;
      break;

    case State::STATE_FETCH:
      m_nextState = State::STATE_DECODE;
      m_currentInstruction = m_resourceBlockBus.read(ResourceLayer::ResourceBlocksEnum::BLOCK_MTU, pc, sizeof(uint32_t));
      break;

    case State::STATE_DECODE:
      decoderMux.data = m_currentInstruction;

      block = decoderMux.common_bits.block;
      scheme = decoderMux.common_bits.scheme;
      opcode = decoderMux.common_bits.opcode;
      dstreg = decoderMux.common_bits.dstreg;
      srcreg1 = (scheme != CODING_SCHEME_TYPE_IB) ? decoderMux.common_bits.srcreg : 0;
      srcreg2 = (scheme == CODING_SCHEME_TYPE_R) ? decoderMux.type_r.src2reg : 0;
      imm = (scheme == CODING_SCHEME_TYPE_I) ? decoderMux.type_i.imm : ((scheme == CODING_SCHEME_TYPE_IB) ? decoderMux.type_ib.imm : 0);

      m_nextState = State::STATE_EXECUTE;
      break;

    case State::STATE_EXECUTE:
      switch (scheme) {
        case CODING_SCHEME_TYPE_R:
          m_executionBlockBus.executeTypeR(static_cast<ExecutionLayer::ExecutionBlocksEnum>(block), opcode, dstreg, srcreg1, srcreg2);
          break;
          
        case CODING_SCHEME_TYPE_I:
          m_executionBlockBus.executeTypeI(static_cast<ExecutionLayer::ExecutionBlocksEnum>(block), opcode, dstreg, srcreg1, imm);
          break;
          
        case CODING_SCHEME_TYPE_IB:
          m_executionBlockBus.executeTypeIB(static_cast<ExecutionLayer::ExecutionBlocksEnum>(block), opcode, dstreg, imm);
          break;
          
        default:
          break;
      }
      m_nextState = State::STATE_CHECK;
      break;

    case State::STATE_CHECK:
      // go to halt state for now if ctrl register is != 0
      if(m_resourceBlockBus.read(ResourceLayer::ResourceBlocksEnum::BLOCK_CTRL_REGS, 3, sizeof(uint32_t))) {
        m_nextState = State::STATE_HALT;
      } else {
        m_nextState = State::STATE_FETCH;
      }
      break;
            
    case State::STATE_HALT:
      m_nextState = State::STATE_HALT;
      status = false;
      break;
      
    case State::STATE_ERROR:
      m_nextState = State::STATE_ERROR;
      break;
      
    default:
      m_nextState = State::STATE_ERROR;
  }
  m_currentState = m_nextState;
  return status;
}
}  // namespace ControlLayer
