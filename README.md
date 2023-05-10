# Aligned Tuple C++14 [![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

This library provides an implementation of a tuple where the elements are aligned to a specified alignment. It can be useful in scenarios where alignment matters, such as with SIMD instructions or when writing low-level code.

## Installation

This is a header-only library, so simply add `aligned_tuple.hpp` to your project's include path.

## Usage

### Constructing

The aligned tuple can be constructed using the `aligned_tuple` class constructor or the `make_aligned_tuple` function. Here are some usage examples:

```c++
#include <iostream>
#include <string>

#include <aligned_tuple.hpp>

int main() {
    using namespace at;

    // Construct using `aligned_tuple` class constructor
    aligned_tuple<16, int, float> at1(1, 2.2f);

    // Construct using `make_aligned_tuple` with alignment of 8
    auto at2 = make_aligned_tuple<8>(2.2f, 3, std::string("test"));

    // Construct using `make_aligned_tuple` with automatic alignment
    auto at3 = make_aligned_tuple(2.2f, 3, std::string("test"));

    return 0;
}
```

### Retrieving elements

You can retrieve elements from an aligned tuple using the `get` function. Here's an example:

```c++
#include <iostream>
#include <string>

#include <aligned_tuple.hpp>

int main() {
    using namespace at;

    // Construct an aligned tuple
    auto at = make_aligned_tuple<16>(1, 2.2f, std::string("test"));

    // Retrieve the first element
    auto first_element = get<0>(at);
    std::cout << "First element: " << first_element << std::endl;

    // Retrieve the second element
    auto second_element = get<1>(at);
    std::cout << "Second element: " << second_element << std::endl;

    // Retrieve the third element
    auto third_element = get<2>(at);
    std::cout << "Third element: " << third_element << std::endl;

    return 0;
}
```
