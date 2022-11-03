#include <iostream>

#include "crc/code_crc32.hh"
//#include "crc/code_crc8.hh"
#include "crc/encoder.hh"

int main() {
  auto crc = crc::Encoder{crc::CodeCrc32::instance()};
  crc.update("Hello World");
  std::cout << "crc(\"Hello World\") is " << crc.value() << std::endl;
  return 0;
}