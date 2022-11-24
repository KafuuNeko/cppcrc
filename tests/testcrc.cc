#include "cppcrc.hh"

#define CATCH_CONFIG_MAIN
#include "catch.hh"

using namespace cppcrc;

TEST_CASE("TEST CRC8", "CRC8('123456789')") {
    Encoder encoder(CodeCrc8::instance());
    encoder.update("123456789");

    REQUIRE(encoder.value() == 162ull);
}

TEST_CASE("TEST CRC16", "CRC16('123456789')") {
    Encoder encoder(CodeCrc16::instance());
    encoder.update("123456789");

    REQUIRE(encoder.value() == 47933ull);
}

TEST_CASE("TEST CRC32", "CRC32('123456789')") {
    Encoder encoder(CodeCrc32::instance());
    encoder.update("123456789");

    REQUIRE(encoder.value() == 3421780262ull);
}

TEST_CASE("TEST CRC64 ECMA", "CRC64_ECMA('123456789')") {
    Encoder encoder(CodeCrc64::ecmaInstance());
    encoder.update("123456789");

    REQUIRE(encoder.value() == 7800480153909949255ull);
}

TEST_CASE("TEST CRC64 WE", "CRC64_WE('123456789')") {
    Encoder encoder(CodeCrc64::weInstance());
    encoder.update("123456789");

    REQUIRE(encoder.value() == 7128171145767219210ull);
}

TEST_CASE("TEST CRCKRMIT", "CRCKRMIT('123456789')") {
    Encoder encoder(CodeCrcKrmit::instance());
    encoder.update("123456789");

    REQUIRE(encoder.value() == 35105);
}

TEST_CASE("TEST CRCSICK", "CRCSICK('123456789')") {
    Encoder encoder(CodeCrcSick::instance());
    encoder.update("123456789");

    REQUIRE(encoder.value() == 22182);
}

TEST_CASE("TEST CRCDNP", "CRCDNP('123456789')") {
    Encoder encoder(CodeCrcDnp::instance());
    encoder.update("123456789");

    REQUIRE(encoder.value() == 33514);
}