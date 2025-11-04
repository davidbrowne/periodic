
//          Copyright David Browne 2025.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

// opening include guard
#if !defined(PCS_UTILITY_HXX)
#define PCS_UTILITY_HXX

#include <type_traits>				// std::is_enum_v, std::underlying_type_t

namespace pcs
{

	// c++20 doesn't have std::to_underlying(), but c++23 does, so we provide our own.
	template <typename E>
	requires std::is_enum_v<E>
	[[nodiscard]] constexpr std::underlying_type_t<E> to_underlying(E e) noexcept
	{
		return static_cast<std::underlying_type_t<E>>(e);
	}

}	// namespace pcs

// closing include guard
#endif
