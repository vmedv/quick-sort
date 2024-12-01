#pragma once
#include <algorithm>
#include <vector>

#include "cilk/cilk.h"

namespace qs {

static constexpr auto SIMPLE_SORT_THRESHOLD = 0.00001;

template <typename T>
void heap_sort(std::vector<T>& arr, std::size_t l, std::size_t r) {
  std::make_heap(arr.begin() + l, arr.begin() + r + 1);
  std::sort_heap(arr.begin() + l, arr.begin() + r + 1);
}

template <typename T>
std::size_t part(std::vector<T>& arr, std::size_t l, std::size_t r) {
  auto v = arr[(l + r) / 2];
  std::size_t i = l;
  std::size_t j = r;
  while (i <= j) {
 while (arr[i] < v) {
      i++;
    }
    while (arr[j] > v) {
      j--;
    }
    if (i >= j) {
      break;
    }
    std::swap(arr[i++], arr[j--]);
  }
  return j;
}

template <typename T>
void seq_quick_sort_impl(std::vector<T>& arr, std::size_t l, std::size_t r, std::size_t size) {
  if (l >= r) {
    return;
  }
  /*if (r - l < size * SIMPLE_SORT_THRESHOLD) {*/
  if (r - l < 3000) {
    heap_sort(arr, l, r);
    return;
  }
  auto q = part(arr, l, r);
  seq_quick_sort_impl(arr, l, q, size);
  seq_quick_sort_impl(arr, q + 1, r, size);
}

template <typename T>
void seq_quick_sort(std::vector<T>& arr) {
  seq_quick_sort_impl(arr, 0, arr.size() - 1, arr.size());
}

template <typename T>
void par_quick_sort_impl(std::vector<T>& arr, std::size_t l, std::size_t r, std::size_t size) {
  if (l >= r) {
    return;
  }
  if (r - l < 3000) {
    heap_sort(arr, l, r);
    return;
  }
  auto q = part(arr, l, r);
  cilk_spawn 
  par_quick_sort_impl(arr, l, q, size);
  par_quick_sort_impl(arr, q + 1, r, size);
  cilk_sync;
}

template <typename T>
void par_quick_sort(std::vector<T>& arr) {
  par_quick_sort_impl(arr, 0, arr.size() - 1, arr.size());
}

} // namespace qs
