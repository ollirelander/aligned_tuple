#include <iostream>
#include <string>

#include <aligned_tuple.hpp>


int main() {
	using namespace at;

	//construct using constructor
	auto at1 = aligned_tuple<8, int, float>(1, 2.2f);

	//construct using make_aligned_tuple with alignment of 16
	auto at2 = make_aligned_tuple<16>(2.2f, 3, std::string("test"));

	//construct using make_aligned_tuple with automatic alignment
	auto at3 = make_aligned_tuple(2.2f, 3, std::string("test"));

	std::cout
		<< "Alignment of at1 -> " << alignof(decltype(at1))
		<< "\nvalues:\n  1: " << get<0>(at1)
		<< "\n  2: " << get<1>(at1);

	std::cout
		<< "\n\nAlignment of at2 -> " << alignof(decltype(at2))
		<< "\nvalues:\n  1: " << get<0>(at2)
		<< "\n  2: " << get<1>(at2)
		<< "\n  3: " << get<2>(at2);

	std::cout
		<< "\n\nAlignment of at3 -> " << alignof(decltype(at3))
		<< "\nvalues:\n  1: " << get<0>(at3)
		<< "\n  2: " << get<1>(at3)
		<< "\n  3: " << get<2>(at3);

	return 0;
}
