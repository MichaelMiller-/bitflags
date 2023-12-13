# bitflags

[![Clang](https://github.com/MichaelMiller-/bitfield/actions/workflows/clang.yml/badge.svg)](https://github.com/MichaelMiller-/bitfield/actions/workflows/clang.yml) [![GCC](https://github.com/MichaelMiller-/bitfield/actions/workflows/gcc.yml/badge.svg)](https://github.com/MichaelMiller-/bitfield/actions/workflows/gcc.yml) [![MSVC](https://github.com/MichaelMiller-/bitfield/actions/workflows/msvc2019.yml/badge.svg)](https://github.com/MichaelMiller-/bitfield/actions/workflows/msvc2019.yml)
Note: currently no released compiler supports reflections

**bitflags** is a small header-only library that allows you to create bit flags from enumerations. In contrast to many other approaches
no magic constants need to be inserted to mark the last element. Also, the values of the enum elements
do not have to be multiples of 2, but can be freely selected and macros are not used as well.

## Requirements
- Compiler that supports [C++ Reflection](https://en.cppreference.com/w/cpp/experimental/reflect)

## Example

Live Example
https://godbolt.org/z/hWxP6bh1Y

```c++
#include <bitflags/bitflags.h>

enum class Flags {
    Flag1,
    Flag2,
    Flag3,
    Flag4,
    Flag5 = 5,
    Flag6 = 20,
};

auto usage(bitflags::bitflags<Flags> flags) {
    if (flags & Flags::Flag1) {
        std::puts("Flag1 is set");
    }
    if (flags & Flags::Flag2) {
        std::puts("Flag2 is set");
    }
    if (flags & Flags::Flag3) {
        std::puts("Flag3 is set");
    }
    if (flags & Flags::Flag4) {
        std::puts("Flag4 is set");
    }
    // ...
}

int main() {
    using bitflags::operator|; // or using namespace bitfield;
    usage(Flags::Flag1 | Flags::Flag2 | Flags::Flag5);
    return 0;
}
```
