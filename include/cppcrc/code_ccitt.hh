#pragma once
#include "code_base.hh"
#include <memory>

namespace crc {

// https://srecord.sourceforge.net/crc16-ccitt.html
class CodeCrcCcitt : public CodeBase {
  friend class CodeCrcCcittFactor;
public:

  virtual CodeBase::UniquePtr clone() const noexcept override {
    return std::make_unique<CodeCrcCcitt>(*this);
  }

private:
  virtual uint64_t updateCrc(uint64_t value, uint8_t c) override;
};

} // namespace crc