#include "crc/code_crc64.hh"

#include <cinttypes>

namespace crc {

static constexpr uint64_t kPoly = 0x42F0E1EBA9EA3693ull;
static constexpr uint64_t kStartECMA = 0x0000000000000000ull;
static constexpr uint64_t kStartWE = 0xFFFFFFFFFFFFFFFFull;

static bool kTableInit = false;
static uint64_t kTable[256];

void initTable() {

  if (kTableInit) {
    return;
  }

  for (uint64_t i = 0; i < 256; i++) {

    uint64_t crc = 0;
    uint64_t c = i << 56;

    for (uint64_t j = 0; j < 8; j++) {

      if ((crc ^ c) & 0x8000000000000000ull) {
        crc = (crc << 1) ^ kPoly;
      } else {
        crc = crc << 1;
      }

      c = c << 1;
    }

    kTable[i] = crc;
  }

  kTableInit = true;
}

CodeBase::const_ptr CodeCrc64::ecmaInstance() {
  static auto ptr = std::make_shared<CodeCrc64>(Type::ecma);
  return ptr;
}

CodeBase::const_ptr CodeCrc64::weInstance() {
  static auto ptr = std::make_shared<CodeCrc64>(Type::we);
  return ptr;
}

uint64_t CodeCrc64::startValue() const noexcept {
  if (mType == Type::ecma) {
    return kStartECMA;
  } else {
    return kStartWE;
  }
}

uint64_t CodeCrc64::result(uint64_t value) const noexcept {
  if (mType == Type::we) {
    return value ^ static_cast<uint64_t>(-1);
  }
  return value;
}

uint64_t CodeCrc64::updateCrc(uint64_t value, uint8_t c, uint8_t pre) const {
  if (!kTableInit) {
    initTable();
  }
  return (value << 8) ^ kTable[((value >> 56) ^ static_cast<uint64_t>(c)) &
                               0x00000000000000FFull];
}

} // namespace crc