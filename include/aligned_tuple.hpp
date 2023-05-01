// Licensed under the MIT License <http://opensource.org/licenses/MIT>.
// SPDX-License-Identifier: MIT
// Copyright (c) 2019 - 2023 Olli Relander
//
// Permission is hereby  granted, free of charge, to any  person obtaining a copy
// of this software and associated  documentation files (the "Software"), to deal
// in the Software  without restriction, including without  limitation the rights
// to  use, copy,  modify, merge,  publish, distribute,  sublicense, and/or  sell
// copies  of  the Software,  and  to  permit persons  to  whom  the Software  is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE  IS PROVIDED "AS  IS", WITHOUT WARRANTY  OF ANY KIND,  EXPRESS OR
// IMPLIED,  INCLUDING BUT  NOT  LIMITED TO  THE  WARRANTIES OF  MERCHANTABILITY,
// FITNESS FOR  A PARTICULAR PURPOSE AND  NONINFRINGEMENT. IN NO EVENT  SHALL THE
// AUTHORS  OR COPYRIGHT  HOLDERS  BE  LIABLE FOR  ANY  CLAIM,  DAMAGES OR  OTHER
// LIABILITY, WHETHER IN AN ACTION OF  CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE  OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef ALIGNED_TUPLE_HPP
#define ALIGNED_TUPLE_HPP

#include <cstddef>

namespace at {
	namespace get_impl {
		template<std::size_t N> struct getter;
	}

	template<std::size_t Align, typename T, typename... Ts>
	class aligned_tuple {
	public:
		static_assert(Align >= alignof(T), "Alignment must be greater than default alignment!");
		static_assert((Align & (Align - 1)) == 0, "Alignment must be power of two!");

		template<std::size_t N> friend struct get_impl::getter;

		constexpr aligned_tuple(const T& first, const Ts&... rest)
			: current_value(first), rest(rest...) {}

		constexpr std::size_t size() const noexcept {
			return rest.size() + 1;
		}

		static constexpr std::size_t alignment = Align;
	private:
		alignas(Align) T current_value;
		aligned_tuple<Align, Ts...> rest;
	};

	template<std::size_t Align, typename T>
	class aligned_tuple<Align, T> {
	public:
		static_assert(Align >= alignof(T), "Alignment must be greater than default alignment!");
		static_assert((Align & (Align - 1)) == 0, "Alignment must be power of two!");

		template<std::size_t N> friend struct get_impl::getter;

		constexpr aligned_tuple(const T& first)
			: current_value(first) {}

		constexpr std::size_t size() const noexcept {
			return 1;
		}

		static constexpr std::size_t alignment = Align;
	private:
		alignas(Align) T current_value;
	};

	template<std::size_t Align, typename... Ts>
	constexpr aligned_tuple<Align, Ts...> make_aligned_tuple(const Ts&... values) noexcept {
		return aligned_tuple<Align, Ts...>(values...);
	}

	namespace get_impl {
		template <std::size_t N, typename... Ts>
		struct nth_type;

		template <typename T, typename... Ts>
		struct nth_type<0, T, Ts...> {
			typedef T type;
		};

		template <std::size_t N, typename T, typename... Ts>
		struct nth_type<N, T, Ts...> {
			typedef typename nth_type<N - 1, Ts...>::type type;
		};

		template<std::size_t N, typename... Ts>
		using nth_type_t = typename nth_type<N, Ts...>::type;

		template <std::size_t I>
		struct getter {
			template <std::size_t Align, typename... Ts>
			static constexpr nth_type_t<I, Ts...>& get(aligned_tuple<Align, Ts...>& tuple) noexcept {
				return getter<I - 1>::get(tuple.rest);
			}
		};

		template <>
		struct getter<0> {
			template <std::size_t Align, typename T, typename... Ts>
			static constexpr T& get(aligned_tuple<Align, T, Ts...>& tuple) noexcept {
				return tuple.current_value;
			}
		};
	}

	template<std::size_t I, std::size_t Align, typename... Ts>
	constexpr get_impl::nth_type_t<I, Ts...>& get(aligned_tuple<Align, Ts...>& tuple) noexcept {
		return get_impl::getter<I>::get(tuple);
	}
}

#endif
