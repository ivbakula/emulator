#pragma once

#include "RegisterBlockIf.hxx"

class Regfile : public RegisterBlockIf {
 public:
  virtual ~Regfile() = default;

  uint32_t read(uint8_t reg) override;
  void write(uint8_t reg, uint32_t value) override;

 private:
  uint32_t m_regfile[32];
};

class IsrVector : public RegisterBlockIf {
 public: 
  virtual ~IsrVector() = default;

  uint32_t read(uint8_t reg) override;
  void write(uint8_t reg, uint32_t value) override;
 private:
  uint32_t m_isrVector[32];
};

class SpecialRegs : public RegisterBlockIf {
 public:
  virtual ~SpecialRegs() = default;

  uint32_t read(uint8_t reg) override;
  void write(uint8_t reg, uint32_t value) override;

 private:
  struct StatusRegisters {
    uint32_t m_zf : 1;
    uint32_t m_nf : 1;
    uint32_t m_if : 1;
  };
  uint32_t m_savePc;
};
