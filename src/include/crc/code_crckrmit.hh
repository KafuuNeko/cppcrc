#pragma once
#include "code_base.hh"

namespace crc {

class CodeCrcKrmit : public CodeBase {
public:
  static CodeBase::const_ptr instance();

private:
  virtual uint64_t updateCrc(uint64_t value, uint8_t c,
                             uint8_t pre) const override;

  virtual uint64_t result(uint64_t value) const noexcept override {
    uint16_t lowByte = (value & 0xFF00) >> 8;
    uint16_t highByte = (value & 0x00FF) << 8;
    return lowByte | highByte;
  }
};

} // namespace crc
