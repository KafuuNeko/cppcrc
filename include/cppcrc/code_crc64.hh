#pragma once

#include "code_base.hh"

namespace cppcrc {

class CodeCrc64 : public CodeBase {
public:
  enum class Type { ecma, we };
  
  static CodeBase::SharedConstPtr ecmaInstance();
  static CodeBase::SharedConstPtr weInstance();

  CodeCrc64(Type type) noexcept : mType(type) {}

  virtual CodeBase::UniquePtr clone() const noexcept override {
    return std::make_unique<CodeCrc64>(*this);
  }


private:
  const Type mType;

  virtual uint64_t startValue() const noexcept override;

  virtual uint64_t result(uint64_t value) const noexcept override;

  virtual uint64_t updateCrc(uint64_t value, uint8_t c) override;
};

} // namespace cppcrc