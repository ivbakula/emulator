#include "gmock/gmock.h"
#include "ExecutionBlockIf.hxx"


class MockExecBlock : public ExecutionLayer::ExecutionBlockIf {
 public:
  MOCK_METHOD(void, executeTypeR, (uint8_t opcode, uint8_t dstreg, uint8_t op1reg, uint8_t op2reg), (override));
  MOCK_METHOD(void, executeTypeI, (uint8_t opcode, uint8_t dstreg, uint8_t op1reg, uint32_t imm), (override));

 protected:
  MOCK_METHOD(void, internalExecute, (uint8_t opcode, uint8_t dstreg, uint32_t op1, uint32_t op2), (override));
};
