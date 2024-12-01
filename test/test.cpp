#include "quicksort.h"
#include "util.h"

#include <cassert>
#include <iostream>
#include <string>

#define TEST_REP 10

template <typename F>
void abstract_test(std::string test_name, std::size_t size, F& sort_func) {
	auto test_data = qs_util::gen_vec<int>(size);
	auto test_data_actual = test_data;
	auto test_data_expected = test_data;

	std::sort(test_data_expected.begin(), test_data_expected.end());
	sort_func(test_data_actual);

	bool res = true;
	for (std::size_t i = 0; i < size; ++i) res &= test_data_actual[i] == test_data_expected[i];

	if (res) {
		std::cout << "Test: " << test_name << "\nSUCCESS\n\n";
	} else {
		std::cout << "Test: " << test_name << "\nFAIL\n\n";
	}
}
static void seq_test(std::string name, std::size_t size) {
	abstract_test(name, size, qs::seq_quick_sort<int>);
}

static void par_test(std::string name, std::size_t size) {
	abstract_test(name, size, qs::par_quick_sort<int>);
}

int main() {
	seq_test("[seq] one sized array", 1);
	seq_test("[seq] small array", 10);
	seq_test("[seq] big array", 10000000);

	par_test("[par] one sized array", 1);
	par_test("[par] small array", 10);
	par_test("[par] big array", 10000000);
}
