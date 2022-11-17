#pragma once

#include <cinttypes>
#include <memory>

namespace crc {

class CodeBase {
  friend class Encoder;

public:
  using SharedConstPtr = std::shared_ptr<const CodeBase>;
  using UniquePtr = std::unique_ptr<CodeBase>;

  virtual UniquePtr clone() const noexcept = 0;

  virtual ~CodeBase() noexcept = default;

private:
  virtual uint64_t updateCrc(uint64_t value, uint8_t c) = 0;

  virtual uint64_t startValue() const noexcept { return 0; }
  virtual uint64_t result(uint64_t value) const noexcept { return value; }
};

}; // namespace crc
