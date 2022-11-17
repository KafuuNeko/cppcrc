#pragma once

#include "code_base.hh"

namespace crc {

class CodeCrc8 : public CodeBase {
public:
  static CodeBase::SharedConstPtr instance();

  virtual CodeBase::UniquePtr clone() const noexcept override {
    return std::make_unique<CodeCrc8>(*this);
  }

private:
  virtual uint64_t updateCrc(uint64_t value, uint8_t c) override;
};

} // namespace crc