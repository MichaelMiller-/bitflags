#include <catch.hpp>

#include <bitflags/bitflags.h>

enum class Flags {
  Flag1,
  Flag2,
  Flag3,
  Flag4,
  Flag5 = 5,
  Flag6 = 20,
};

TEST_CASE("Simple example", "[bitflags]") {
  using bitflags::operator|;
  auto flags = Flags::Flag1 | Flags::Flag2 | Flags::Flag5;

  REQUIRE(flags & Flags::Flag1);
  REQUIRE(flags & Flags::Flag2);
  REQUIRE(not flags & Flags::Flag3);
  REQUIRE(not flags & Flags::Flag4);
  REQUIRE(flags & Flags::Flag5);
  REQUIRE(not flags & Flags::Flag6);
}
