#include <iostream>
#include <string_view>
#include <vector>

#include "cppcrc.hh"

int main() {
  std::vector<std::pair<const char *, cppcrc::CodeBase::SharedConstPtr>> codes = {
      {"crc8", cppcrc::CodeCrc8::instance()},
      {"crc16", cppcrc::CodeCrc16::instance()},
      {"crc32", cppcrc::CodeCrc32::instance()},
      {"crc64_ecma", cppcrc::CodeCrc64::ecmaInstance()},
      {"crc64_we", cppcrc::CodeCrc64::weInstance()},
      {"crckrmit", cppcrc::CodeCrcKrmit::instance()},
      {"crcsick", cppcrc::CodeCrcSick::instance()},
      {"crcdnp", cppcrc::CodeCrcDnp::instance()}};

  auto str = "123456789";
  for (auto &element : codes) {

    printf("%s('%s') = %llu\n", element.first, str,
           cppcrc::Encoder{element.second, str}.value());
  }

  return 0;
}