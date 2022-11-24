#include "cppcrc/code_crcsick.hh"
#include <cstdint>

namespace cppcrc {
constexpr uint16_t kPoly = 0x8005;

const CodeBase& CodeCrcSick::instance() {
  static const CodeCrcSick uniqueInstance;
  return uniqueInstance;
}

uint64_t CodeCrcSick::updateCrc(uint64_t value, uint8_t c) {
  auto crcValue = static_cast<uint16_t>(value);

  uint16_t high = 0x00FF & static_cast<uint16_t>(c);
  uint16_t low = (0x00FF & static_cast<uint16_t>(mPre)) << 8;

  crcValue = (crcValue & 0x8000) ? ((crcValue << 1) ^ kPoly) : (crcValue << 1);
  crcValue ^= (high | low);

  mPre = c;

  return crcValue;
}

} // namespace cppcrc
