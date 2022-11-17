#pragma once

#include "code_base.hh"

namespace cppcrc {

class CodeCrc32 : public CodeBase {
public:
  static CodeBase::SharedConstPtr instance();

  virtual CodeBase::UniquePtr clone() const noexcept override {
    return std::make_unique<CodeCrc32>(*this);
  }

private:
  virtual uint64_t startValue() const noexcept override { return 0xFFFFFFFFul; }

  virtual uint64_t updateCrc(uint64_t value, uint8_t c) override;

  virtual uint64_t result(uint64_t value) const noexcept override {
    return value ^ static_cast<uint32_t>(-1);
  }
};

} // namespace cppcrc