#include "cppcrc/code_crckrmit.hh"

#include <cinttypes>

#ifdef CPPCRC_THREADSAFE
#include <mutex>
#endif

namespace cppcrc {

constexpr uint16_t kPoly = 0x8408;

#ifdef CPPCRC_THREADSAFE
static std::mutex kLock;
#endif

static bool kInitTable = false;
static uint16_t kTable[256];

static void initTable() {

#ifdef CPPCRC_THREADSAFE
  std::lock_guard<std::mutex> lockGuard(kLock);
#endif

  if (kInitTable) {
    return;
  }

  for (uint16_t i = 0; i < 256; i++) {

    uint16_t crc = 0;
    uint16_t c = i;

    for (uint16_t j = 0; j < 8; j++) {
      crc = ((crc ^ c) & 0x0001) ? ((crc >> 1) ^ kPoly) : (crc >> 1);
      c = c >> 1;
    }

    kTable[i] = crc;
  }

  kInitTable = true;
}

CodeBase::SharedConstPtr CodeCrcKrmit::instance() {
  static auto uniqueInstance = std::make_shared<CodeCrcKrmit>();
  return uniqueInstance;
}

uint64_t CodeCrcKrmit::updateCrc(uint64_t value, uint8_t c) {
  auto crcValue = static_cast<uint16_t>(value);

  if (!kInitTable) {
    initTable();
  }

  return (crcValue >> 8) ^
         kTable[(crcValue ^ static_cast<uint16_t>(c)) & 0x00FF];
}
} // namespace cppcrc