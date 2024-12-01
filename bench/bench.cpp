#include "quicksort.h"
#include <algorithm>
#include <chrono>
#include <cstddef>
#include <numeric>
#include <ranges>
#include <vector>
#include <iostream>
#include "util.h"

using namespace std::chrono_literals;

#define BREPS 5

static constexpr std::size_t B_ARRAY_SIZE = 100000000;

template <typename T, typename F>
auto abstract_bench(std::vector<T> v, F& sort_func) -> decltype(auto) {
	auto start = std::chrono::system_clock::now();
	sort_func(v);
	auto end = std::chrono::system_clock::now();
	return end - start;
}

void bench(std::size_t arr_size) {
	std::chrono::milliseconds seq_acc = 0ms, par_acc = 0ms;
	for(auto&& i : std::ranges::views::iota(1, BREPS + 1)) {
		auto v = qs_util::gen_vec<int>(arr_size);
		auto seq_m = duration_cast<std::chrono::milliseconds>(abstract_bench(v, qs::seq_quick_sort<int>));
		seq_acc += seq_m;
		auto par_m = duration_cast<std::chrono::milliseconds>(abstract_bench(v, qs::par_quick_sort<int>));
		par_acc += par_m;

		std::cout << std::format("Run #{}\n\tsequental: {}\n\tparallel: {}\n\tacceleration: {}\n\n",
			   i, seq_m, par_m, static_cast<double>(seq_m.count()) / par_m.count());
	}
	std::cout << std::format("sequental avg time: {}\nparallel avg time: {}\nparallel {} times faster than sequental", 
	     seq_acc / BREPS, par_acc / BREPS, static_cast<double>(seq_acc.count()) / par_acc.count());
}

int main() {
	bench(B_ARRAY_SIZE);
}
