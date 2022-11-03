#include "crc/code_crc32.hh"

#include <cinttypes>

namespace crc {

constexpr uint32_t kPoly = 0xEDB88320ul;

static bool kTableInit = false;
static uint32_t kTable[256];

void initTable() {

  if (kTableInit) {
    return;
  }

  for (uint32_t i = 0; i < 256; i++) {

    uint32_t crc = i;

    for (uint32_t j = 0; j < 8; j++) {
      if (crc & 0x00000001L) {
        crc = (crc >> 1) ^ kPoly;
      } else {
        crc = crc >> 1;
      }
    }

    kTable[i] = crc;
  }

  kTableInit = true;
}

CodeBase::const_ptr CodeCrc32::instance() {
  static auto ptr = std::make_shared<CodeCrc32>();
  return ptr;
}

uint64_t CodeCrc32::updateCrc(uint64_t value, uint8_t c, uint8_t pre) const {
  if (!kTableInit) {
    initTable();
  }
  uint32_t crc32Value = static_cast<uint32_t>(value);
  return (crc32Value >> 8) ^
         kTable[(crc32Value ^ static_cast<uint32_t>(c)) & 0x000000FFul];
}

} // namespace crc