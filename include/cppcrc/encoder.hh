#pragma once

/**
 * @file encoder.hh
 * @author kafuu (kafuuneko@gmail.com)
 * @brief Cyclic Redundancy Check based on
 * libcrc(https://github.com/lammertb/libcrc)
 * @version 0.2
 * @date 2021-12-12
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "code_base.hh"
#include <cstdint>
#include <istream>
#include <memory>
#include <string_view>
#include <type_traits>

namespace cppcrc {

class Encoder {

public:
  explicit Encoder(const CodeBase::SharedConstPtr &code) noexcept
      : mCodePrototype(code), mCode(code->clone()), mValue(code->startValue()) {  }

  explicit Encoder(const CodeBase::SharedConstPtr &code, std::istream &input)
      : Encoder(code) {
    this->update(input);
  }

  template <
      class Iterator,
      std::enable_if_t<
          std::is_same_v<std::make_unsigned_t<std::remove_cv_t<
                             std::remove_reference_t<decltype(*(Iterator{}))>>>,
                         uint8_t>,
          int> = 0>
  explicit Encoder(const CodeBase::SharedConstPtr &code, Iterator first,
                   Iterator last)
      : Encoder(code) {
    this->update(first, last);
  }

  explicit Encoder(const CodeBase::SharedConstPtr &code, std::string_view str)
      : Encoder(code) {
    this->update(str);
  }

  void update(uint8_t c) noexcept {
    mValue = mCode->updateCrc(mValue, c);
  }

  void update(std::istream &input) {
    uint8_t c = 0;

    if (!input) {
      return;
    }

    while (input.read(reinterpret_cast<char *>(&c), 1)) {
      this->update(c);
    }
  }

  template <
      class Iterator,
      std::enable_if_t<
          std::is_same_v<std::make_unsigned_t<std::remove_cv_t<
                             std::remove_reference_t<decltype(*(Iterator{}))>>>,
                         uint8_t>,
          int> = 0>
  void update(Iterator first, Iterator last) {
    uint8_t c = 0;
    for (; first != last; ++first) {
      this->update(*first);
    }
  }

  void update(std::string_view str) { this->update(str.cbegin(), str.cend()); }

  void reset() noexcept {
    mCode = mCodePrototype->clone();
    mValue = mCode->startValue();
  }

  uint64_t value() noexcept { return mCode->result(mValue); }

private:
  std::shared_ptr<const CodeBase> mCodePrototype;
  std::unique_ptr<CodeBase> mCode;
  
  uint64_t mValue;
};

} // namespace cppcrc
