#ifndef BITFLAGS_H
#define BITFLAGS_H

#include <array>
#include <bitset>
#include <utility>

#if __has_include(<experimental/reflect>)
#include <experimental/reflect>

namespace bitflags {

namespace detail {
template <typename T, auto Index>
  requires std::experimental::reflect::Constant<T>
struct constant_and_index {
  static constexpr auto value =
      std::pair{std::experimental::reflect::get_constant_v<T>, Index};
};
} // namespace detail

template <typename T>
  requires std::is_enum_v<T>
class bitflags {
  using reflection_t = reflexpr(T);
  using enumerators_t =
      std::experimental::reflect::get_enumerators_t<reflection_t>;

  static constexpr auto bits =
      std::experimental::reflect::get_size_v<enumerators_t>;

  static constexpr auto lookup = [] {
    return []<auto... Is>(std::index_sequence<Is...>) {
      return std::array{detail::constant_and_index<
          std::experimental::reflect::get_element_t<Is, enumerators_t>,
          Is>::value...};
    }(std::make_index_sequence<
               std::experimental::reflect::get_size_v<enumerators_t>>{});
  }();

  std::bitset<bits> flags;

public:
  constexpr bitflags() = default;

  constexpr bitflags(T value) {
    const auto it =
        std::find_if(begin(lookup), end(lookup),
                     [value](auto const &elem) { return elem.first == value; });
    flags.set(it->second);
  }

  [[nodiscard]] auto operator==(bitflags const &) const -> bool = default;

  [[nodiscard]] friend constexpr auto operator|(bitflags lhs,
                                                bitflags rhs) noexcept
      -> bitflags {
    auto result{lhs};
    result.flags |= rhs.flags;
    return result;
  }

  [[nodiscard]] constexpr auto operator&(T value) const noexcept -> bool {
    const auto it =
        std::find_if(begin(lookup), end(lookup),
                     [value](auto const &elem) { return elem.first == value; });
    return flags.test(it->second);
  }
};

template <typename T>
  requires std::is_enum_v<T>
[[nodiscard]] constexpr auto operator|(T lhs, T rhs) noexcept -> bitflags<T> {
  return bitflags<T>{lhs} | bitflags<T>{rhs};
}
} // namespace bitflags

#else
#error C++ reflection is not supported
#endif

#endif