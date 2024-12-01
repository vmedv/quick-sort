#pragma once
#include <concepts>
#include <random>
#include <vector>

namespace qs_util {

static std::random_device rd;

template <typename T>
  requires std::integral<T>
std::vector<T> gen_vec(std::size_t size) {
  std::vector<T> v(size);
  std::mt19937 rng(rd());
  std::uniform_int_distribution<T> uni(std::numeric_limits<T>::min(), std::numeric_limits<T>::max());
  for (auto& x : v) {
    x = uni(rng);
  }
  return v;
}

} // namespace qs_util
