#include "crc/code_crckrmit.hh"

namespace crc {

constexpr uint16_t kPoly = 0x8408;

static bool kInitTable = false;
static uint16_t kTable[256];

void initTable(void) {
  if (kInitTable) {
    return;
  }

  for (uint16_t i = 0; i < 256; i++) {

    uint16_t crc = 0;
    uint16_t c = i;

    for (uint16_t j = 0; j < 8; j++) {

      if ((crc ^ c) & 0x0001)
        crc = (crc >> 1) ^ kPoly;
      else
        crc = crc >> 1;

      c = c >> 1;
    }

    kTable[i] = crc;
  }

  kInitTable = true;
}

CodeBase::const_ptr CodeCrcKrmit::instance() {
  static auto ptr = std::make_shared<CodeCrcKrmit>();
  return ptr;
}

uint64_t CodeCrcKrmit::updateCrc(uint64_t value, uint8_t c, uint8_t pre) const {
  uint16_t crcValue = static_cast<uint16_t>(value);

  if (!kInitTable) {
    initTable();
  }

  return (crcValue >> 8) ^
         kTable[(crcValue ^ static_cast<uint16_t>(c)) & 0x00FF];
}
} // namespace crc