#pragma once

#include "code_base.hh"

namespace cppcrc {

class CodeCrc8 : public CodeBase {
public:
  static const CodeBase &instance();

  virtual CodeBase::UniquePtr clone() const noexcept override {
    return std::make_unique<CodeCrc8>(*this);
  }

private:
  virtual uint64_t updateCrc(uint64_t value, uint8_t c) override;
};

} // namespace cppcrc