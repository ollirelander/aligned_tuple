#include <iostream>
#include <string>

#include <aligned_tuple.hpp>

int main() {
    using namespace at;

    // Construct using `aligned_tuple`
    aligned_tuple<16, int, float> at1(1, 2.2f);

    // Construct using `make_aligned_tuple` with alignment of 8
    auto at2 = make_aligned_tuple<8>(2.2f, 3, std::string("test"));

    // Construct using `make_aligned_tuple` with automatic alignment
    auto at3 = make_aligned_tuple(2.2f, 3, std::string("test"));

    std::cout << "Alignment of at1 -> " << alignof(decltype(at1)) << "\nvalues:\n";
    std::cout << "  1: " << get<0>(at1) << "\n  2: " << get<1>(at1) << std::endl;

    std::cout << "\nAlignment of at2 -> " << alignof(decltype(at2)) << "\nvalues:\n";
    std::cout << "  1: " << get<0>(at2) << "\n  2: " << get<1>(at2) << "\n  3: " << get<2>(at2) << std::endl;

    std::cout << "\nAlignment of at3 -> " << alignof(decltype(at3)) << "\nvalues:\n";
    std::cout << "  1: " << get<0>(at3) << "\n  2: " << get<1>(at3) << "\n  3: " << get<2>(at3) << std::endl;

    return 0;
}
