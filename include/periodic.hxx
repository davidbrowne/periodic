//          Copyright David Browne 2021-2022.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

// opening include guard
#if !defined(PER_PERIODIC_HXX)
#define PER_PERIODIC_HXX

#include <type_traits>				// requirements
#include <concepts>					// requirements
#include <array>					// underlying storage
#include <tuple>					// tuple interface for structured bindings, matrix variadic constructor
#include <algorithm>				// min()
#include <numbers>					// pi_v<>, inv_pi_v<>
#include <version>					// feature test macros
#include <limits>					// for cxcm
#include <cmath>					// for cxcm

//
// periodic coordinate system
//

// version info

constexpr inline int PERIODIC_MAJOR_VERSION = 0;
constexpr inline int PERIODIC_MINOR_VERSION = 1;
constexpr inline int PERIODIC_PATCH_VERSION = 0;

namespace pcs
{
	namespace cxcm
	{
		// copyright for cxcm
		
		//          Copyright David Browne 2020-2022.
		// Distributed under the Boost Software License, Version 1.0.
		//    (See accompanying file LICENSE_1_0.txt or copy at
		//          https://www.boost.org/LICENSE_1_0.txt)

		constexpr inline int CXCM_MAJOR_VERSION = 0;
		constexpr inline int CXCM_MINOR_VERSION = 1;
		constexpr inline int CXCM_PATCH_VERSION = 7;

		namespace limits
		{
			namespace detail
			{
				// long doubles vary between compilers and platforms. Windows MSVC and clang on Windows both use
				// the same representation as double. For gcc and linux, etc., it is often represented by an extended
				// precision data structure with 80 bits (64 bits of significand). sizeof(long double) on gcc on Windows
				// (at least MSYS2) is 16, implying it is 128 bits, but std::numeric_limits<long double> returns values
				// consistent with an 80 bit representation.
				constexpr long double get_largest_fractional_long_double() noexcept
				{
					if constexpr (std::numeric_limits<long double>::digits == 64)
					{
						// if digits is 64, then long double is using extended precision, and we can
						// just barely get away with casting to a long long to remove the fractional
						// part and keep the rest of the bits, without overflow.
						return 0x1.fffffffffffffffep+62L;
					}
					else
					{
						// assuming that long double does the same thing as double (which is true for
						// MSVC and clang on windows).
						return 0x1.fffffffffffffp+51L;
					}
				}
			}

			//
			// largest_fractional_value
			//

			// the largest floating point value that has a fractional representation

			template <std::floating_point T>
			constexpr inline T largest_fractional_value = T();

			template <>
			constexpr inline long double largest_fractional_value<long double> = detail::get_largest_fractional_long_double();

			template <>
			constexpr inline double largest_fractional_value<double> = 0x1.fffffffffffffp+51;

			template <>
			constexpr inline float largest_fractional_value<float> = 0x1.fffffep+22f;
		}

		// don't worry about esoteric input.
		// much faster than strict or standard when non constant evaluated,
		// though standard library is a little better in debugger.
		namespace relaxed
		{

			//
			// abs(), fabs()
			//

			// absolute value

			template <std::floating_point T>
			constexpr T abs(T value) noexcept
			{
				return (value < T(0)) ? -value : value;
			}

			template <std::signed_integral T>
			constexpr T abs(T value) noexcept
			{
				return (value < T(0)) ? -value : value;
			}

			template <std::unsigned_integral T>
			constexpr T abs(T value) noexcept
			{
				return value;
			}

			template <std::floating_point T>
			constexpr T fabs(T value) noexcept
			{
				return abs(value);
			}

			//
			// trunc()
			//

			// this is the workhorse function for floor(), ceil(), and round().

			// rounds towards zero

			template <std::floating_point T>
			constexpr T trunc(T value) noexcept
			{
				return static_cast<T>(static_cast<long long>(value));
			}

			// float specialization
			template <>
			constexpr float trunc(float value) noexcept
			{
				return static_cast<float>(static_cast<int>(value));
			}

			//
			// floor()
			//

			// rounds towards negative infinity

			template <std::floating_point T>
			constexpr T floor(T value) noexcept
			{
				const T truncated_value = trunc(value);

				// truncation rounds to zero which is right direction for positive values,
				// but we need to go the other way for negative values.

				// negative non-integral value
				if (truncated_value > value)
					return (truncated_value - T(1.0f));

				// positive or integral value
				return truncated_value;
			}

			//
			// ceil()
			//

			// rounds towards positive infinity

			template <std::floating_point T>
			constexpr T ceil(T value) noexcept
			{
				const T truncated_value = trunc(value);

				// truncation rounds to zero which is right direction for negative values,
				// but we need to go the other way for positive values.

				// positive non-integral value
				if (truncated_value < value)
					return (truncated_value + T(1.0f));

				// negative or integral value
				return truncated_value;
			}

			//
			// round()
			//

			// rounds to nearest integral position, halfway cases away from zero

			template <std::floating_point T>
			constexpr T round(T value) noexcept
			{
				// zero could be handled either place, but here it is with the negative values.

				// positive value, taking care of halfway case.
				if (value > T(0))
					return trunc(value + T(0.5f));

				// negative or zero value, taking care of halfway case.
				return trunc(value - T(0.5f));
			}

			//
			// fract() - not in standard library
			//

			// the fractional part of a floating point number - always non-negative.

			template <std::floating_point T>
			constexpr T fract(T value) noexcept
			{
				return value - floor(value);
			}

			//
			// fmod()
			//

			// the floating point remainder of division

			template <std::floating_point T>
			constexpr T fmod(T x, T y) noexcept
			{
				return x - trunc(x / y) * y;
			}

			//
			// round_even() - not in standard library
			//

			// rounds to nearest integral position, halfway cases towards even

			template <std::floating_point T>
			constexpr T round_even(T value) noexcept
			{
				T trunc_value = trunc(value);
				bool is_even = (fmod(trunc_value, T(2)) == T(0));
				bool is_halfway = (fract(value) == T(0.5));

				// the special case
				if (is_halfway)
					if (is_even)
						return trunc_value;

				// zero could be handled either place, but here it is with the negative values.

				// positive value, taking care of halfway case.
				if (value > T(0))
					return trunc(value + T(0.5f));

				// negative or zero value, taking care of halfway case.
				return trunc(value - T(0.5f));
			}

			//
			// sqrt()
			//

			namespace detail
			{
				//	By itself, converging_sqrt() over all the 32-bit floats gives:
				//		75% of the time gives same answer as std::sqrt()
				//		25% of the time gives answer within 1 ulp of std::sqrt()
				template <std::floating_point T>
				constexpr T converging_sqrt(T arg) noexcept
				{
					T current_value = arg;
					T previous_value = T(0);

					while (current_value != previous_value)
					{
						previous_value = current_value;
						current_value = (T(0.5) * current_value) + (T(0.5) * (arg / current_value));
					}

					return current_value;
				}

				// 2 refinements:
				// all floats: 71.05% same as reciprocal of std::sqrt(), 28.95% apparently within 1 ulp.
				// a double sample of (2^52, 2^52 + 2^31-1] 62.01% exact match, 37.99% apparently within 1 ulp
				// best for implementing rsqrt()
				//
				// 3 refinements:
				// all floats: 62.65% same as reciprocal of std::sqrt(), 37.35% apparently within 1 ulp.
				// a double sample of (2^52, 2^52 + 2^31-1] 50% exact match, 50% apparently within 1 ulp
				// best for implementing sqrt()
				template <std::floating_point T>
				constexpr T inverse_sqrt(T arg) noexcept
				{
					T current_value = T(1.0) / converging_sqrt(arg);

					current_value += T(0.5) * current_value * (T(1.0) - arg * current_value * current_value);					// first refinement
					current_value += T(0.5) * current_value * (T(1.0) - arg * current_value * current_value);					// second refinement

					current_value += T(0.5) * current_value * (T(1.0) - arg * current_value * current_value);					// third refinement
					return current_value;
				}
			}

			// square root
			//	This version with inverse_sqrt(), when used over all the 32-bit floats gives:
			//
			//	with 3 refinements:
			//		all floats: 76.5% same result as std::sqrt, 23.5% apparently within 1 ulp
			//		a double sample of (2^52, 2^52 + 2^31-1] 99.99923% exact match, 0.0007717% apparently within 1 ulp
			//
			template <std::floating_point T>
			constexpr T sqrt(T arg) noexcept
			{
				return arg * detail::inverse_sqrt(arg);
			}

			// float specialization - uses double internally - relied upon by rsqrt<T>() when [T = float]
			//		100% match with std::sqrt
			template <>
			constexpr float sqrt(float value) noexcept
			{
				return static_cast<float>(sqrt(static_cast<double>(value)));
			}

			// reciprocal of square root
			//	all floats (no specializations): 84.75% same result as reciprocal of std::sqrt(), 15.25% apparently within 1 ulp
			//	all floats (sqrt() specialization): 100% same result as reciprocal of std::sqrt()
			//	a double sample starting after 2^52 for INT_MAX next values: 99.99923% exact match, 0.0007717% apparently within 1 ulp
			//	a double sample starting after 1.25 for INT_MAX next values: 90.34% exact match, 9.66% apparently within 1 ulp
			//	a double sample starting after 123456.789 for INT_MAX next values: 86.84% exact match, 13.16% apparently within 1 ulp
			//	a double sample starting after 0.0 for INT_MAX next values: 86.17% exact match, 13.83% apparently within 1 ulp (11.5 hrs to calc this)
			//	a double sample starting before std::numeric_limits<double>::max() for INT_MAX prev values: 84.81% exact match, 15.19% apparently within 1 ulp (1.5 hrs to calc this)
			template <std::floating_point T>
			constexpr T rsqrt(T arg) noexcept
			{
				return T(1.0) / sqrt(arg);
			}

			// this specialization is not necessary given sqrt() float specialization and our simple generic rsqrt()
			//
			//// float specialization - uses double internally
			////		100% match with (1.0f / std::sqrt) when using sqrt() float specialization
			////		all floats (no specializations): 74.01% match with (1.0f / std::sqrt), 25.99% apparently within 1 ulp
			//template <>
			//constexpr float rsqrt(float value) noexcept
			//{
			//	return static_cast<float>(rsqrt(static_cast<double>(value)));
			//}

		} // namespace relaxed

		//
		// isnan()
		//

		// I've seen comments on the Microsoft/STL Github Issue that tracks where they are implementing
		// std::isnan for c++20, and said that on some compilers with various compiler switches, what
		// we are using here, (x != x) or !(x == x), can be optimized away, so this is not a good practice. So
		// microsoft is in the process of making this stuff constexpr, and they need to have a compiler
		// intrinsic to do it. https://github.com/microsoft/STL/issues/65#issuecomment-563886838

	#if defined(_MSC_VER)
	#pragma float_control(precise, on, push)
	#endif

		template <std::floating_point T>
		constexpr bool isnan(T value) noexcept
		{
			return (value != value);
		}

	#if defined(_MSC_VER)
	#pragma float_control(pop)
	#endif

		//
		// isinf()
		//

		template <std::floating_point T>
		constexpr bool isinf(T value) noexcept
		{
			return (value == -std::numeric_limits<T>::infinity()) || (value == std::numeric_limits<T>::infinity());
		}

		//
		// fpclassify()
		//

		template <std::floating_point T>
		constexpr int fpclassify(T value) noexcept
		{
			if (isnan(value))
				return FP_NAN;
			else if (isinf(value))
				return FP_INFINITE;
			else if (value == 0)				// intentional use of the implicit cast of 0 to T.
				return FP_ZERO;
			else if (relaxed::abs(value) < std::numeric_limits<T>::min())
				return FP_SUBNORMAL;

			return FP_NORMAL;
		}

		//
		// isnormal()
		//

		template <std::floating_point T>
		constexpr bool isnormal(T value) noexcept
		{
			return (fpclassify(value) == FP_NORMAL);
		}

		//
		// isfinite()
		//

		template <std::floating_point T>
		constexpr bool isfinite(T value) noexcept
		{
			return !isnan(value) && !isinf(value);
		}

		// try and match standard library requirements.
		// this namespace is pulled into parent namespace via inline.
		inline namespace strict
		{

			namespace detail
			{

				//
				// isnormal_or_subnormal()
				//

				// standard library screening requirement for these functions

				template <std::floating_point T>
				constexpr bool isnormal_or_subnormal(T value) noexcept
				{
					// intentional use of the implicit cast of 0 to T.
					return isfinite(value) && (value != 0);
				}

				//
				// fails_fractional_input_constraints()
				//

				// the fractional functions,e.g., trunc(), floor(), ceil(), round(), need the input to satisfy
				// certain constraints before it further processes the input. if this function returns true,
				// the constraints weren't met, and the fractional functions will do no further work and return
				// the value as is.

				template <std::floating_point T>
				constexpr bool fails_fractional_input_constraints(T value) noexcept
				{
					// if any of the following constraints are not met, return true:
					// no NaNs
					// no +/- infinity
					// no +/- 0
					// no value that can't even have a fractional part
					return !isnormal_or_subnormal(value) || (relaxed::abs(value) > limits::largest_fractional_value<T>);
				}

				//
				// constexpr_trunc()
				//

				// rounds towards zero

				template <std::floating_point T>
				constexpr T constexpr_trunc(T value) noexcept
				{
					// screen out unnecessary input
					if (fails_fractional_input_constraints(value))
						return value;

					return relaxed::trunc(value);
				}

				//
				// constexpr_floor()
				//

				// rounds towards negative infinity

				template <std::floating_point T>
				constexpr T constexpr_floor(T value) noexcept
				{
					// screen out unnecessary input
					if (fails_fractional_input_constraints(value))
						return value;

					return relaxed::floor(value);
				}

				//
				// constexpr_ceil()
				//

				// rounds towards positive infinity

				template <std::floating_point T>
				constexpr T constexpr_ceil(T value) noexcept
				{
					// screen out unnecessary input
					if (fails_fractional_input_constraints(value))
						return value;

					return relaxed::ceil(value);
				}

				//
				// constexpr_round()
				//

				// rounds to nearest integral position, halfway cases away from zero

				template <std::floating_point T>
				constexpr T constexpr_round(T value) noexcept
				{
					// screen out unnecessary input
					if (fails_fractional_input_constraints(value))
						return value;

					// halfway rounding can bump into max long long value for truncation
					// (for extended precision), so be more gentle at the end points.
					// this works because the largest_fractional_value remainder is T(0.5f).
					if (value == limits::largest_fractional_value<T>)
						return value + T(0.5f);
					else if (value == -limits::largest_fractional_value<T>)			// we technically don't have to do this for negative case (one more number in negative range)
						return value - T(0.5f);

					return relaxed::round(value);
				}

				//
				// constexpr_fract()
				//

				template <std::floating_point T>
				constexpr T constexpr_fract(T value) noexcept
				{
					// screen out unnecessary input
					if (fails_fractional_input_constraints(value))
						return value;

					return relaxed::fract(value);
				}

				//
				// constexpr_fmod()
				//

				template <std::floating_point T>
				constexpr T constexpr_fmod(T x, T y) noexcept
				{
					// screen out unnecessary input

					if (isnan(x) || isnan(y) || !isfinite(x))
						return std::numeric_limits<T>::quiet_NaN();

					if (isinf(y))
						return x;

					if (x == T(0) && y != T(0))
						return 0;

					if (y == 0)
						return std::numeric_limits<T>::quiet_NaN();

					return relaxed::fmod(x, y);
				}

				//
				// constexpr_round_even()
				//

				// rounds to nearest integral position, halfway cases away from zero

				template <std::floating_point T>
				constexpr T constexpr_round_even(T value) noexcept
				{
					// screen out unnecessary input
					if (fails_fractional_input_constraints(value))
						return value;

					// halfway rounding can bump into max long long value for truncation
					// (for extended precision), so be more gentle at the end points.
					// this works because the largest_fractional_value remainder is T(0.5f).
					if (value == limits::largest_fractional_value<T>)
						return value + T(0.5f);
					else if (value == -limits::largest_fractional_value<T>)			// we technically don't have to do this for negative case (one more number in negative range)
						return value - T(0.5f);

					return relaxed::round_even(value);
				}

				//
				// constexpr_sqrt()
				//

				template <std::floating_point T>
				constexpr T constexpr_sqrt(T value) noexcept
				{
					// screen out unnecessary input

					// arg == +infinity or +/-0, return val unmodified
					// arg == NaN, return Nan
					if (!isnormal_or_subnormal(value))
						return value;

					// arg < 0, return NaN
					if (value < T(0.0))
						return std::numeric_limits<T>::quiet_NaN();

					return relaxed::sqrt(value);
				}

				//
				// constexpr_inverse_sqrt()
				//

				template <std::floating_point T>
				constexpr T constexpr_rsqrt(T value) noexcept
				{
					// screen out unnecessary input

					// arg == NaN, return Nan
					if (isnan(value))
						return value;

					// arg == +infinity , return 0
					if (value == std::numeric_limits<T>::infinity())
						return T(0.0);

					// arg == -infinity or +/-0, return Nan
					if (!isnormal_or_subnormal(value))
						return std::numeric_limits<T>::quiet_NaN();

					// arg <= 0, return NaN
					if (value <= T(0.0))
						return std::numeric_limits<T>::quiet_NaN();

					return relaxed::rsqrt(value);
				}

			} // namespace detail

			//
			// abs(), fabs()
			//


			// absolute value

			template <std::floating_point T>
			constexpr T abs(T value) noexcept
			{
				if (!detail::isnormal_or_subnormal(value))
					return value;

				return relaxed::abs(value);
			}

			// don't know what to do if someone tries to negate the most negative number.
			// standard says behavior is undefined if you can't represent the result by return type.
			template <std::integral T>
			constexpr T abs(T value) noexcept
			{
				return relaxed::abs(value);
			}

			template <std::floating_point T>
			constexpr T fabs(T value) noexcept
			{
				return abs(value);
			}


			//
			// trunc()
			//

	#if !defined(PERIODIC_CXCM_DISABLE_RUNTIME_OPTIMIZATIONS) && (defined(_DEBUG) || defined(_M_IX86))

			// rounds towards zero

			template <std::floating_point T>
			constexpr T trunc(T value) noexcept
			{
				if (std::is_constant_evaluated())
				{
					return detail::constexpr_trunc(value);
				}
				else
				{
					return std::trunc(value);
				}
			}

	#else

			// rounds towards zero

			template <std::floating_point T>
			constexpr T trunc(T value) noexcept
			{
				return detail::constexpr_trunc(value);
			}

	#endif

			//
			// floor()
			//

	#if !defined(PERIODIC_CXCM_DISABLE_RUNTIME_OPTIMIZATIONS) && (defined(_DEBUG) || defined(_M_IX86))

			// rounds towards negative infinity

			template <std::floating_point T>
			constexpr T floor(T value) noexcept
			{
				if (std::is_constant_evaluated())
				{
					return detail::constexpr_floor(value);
				}
				else
				{
					return std::floor(value);
				}
			}

	#else

			// rounds towards negative infinity

			template <std::floating_point T>
			constexpr T floor(T value) noexcept
			{
				return detail::constexpr_floor(value);
			}

	#endif

			//
			// ceil()
			//

	#if !defined(PERIODIC_CXCM_DISABLE_RUNTIME_OPTIMIZATIONS) && (defined(_DEBUG) || defined(_M_IX86))

			// rounds towards positive infinity

			template <std::floating_point T>
			constexpr T ceil(T value) noexcept
			{
				if (std::is_constant_evaluated())
				{
					return detail::constexpr_ceil(value);
				}
				else
				{
					return std::ceil(value);
				}
			}

	#else

			// rounds towards positive infinity

			template <std::floating_point T>
			constexpr T ceil(T value) noexcept
			{
				return detail::constexpr_ceil(value);
			}

	#endif

			//
			// round()
			//

	#if !defined(PERIODIC_CXCM_DISABLE_RUNTIME_OPTIMIZATIONS) && (defined(_DEBUG) || defined(_M_IX86))

			// rounds to nearest integral position, halfway cases away from zero

			template <std::floating_point T>
			constexpr T round(T value) noexcept
			{
				if (std::is_constant_evaluated())
				{
					return detail::constexpr_round(value);
				}
				else
				{
					return std::round(value);
				}
			}

	#else

			// rounds to nearest integral position, halfway cases away from zero

			template <std::floating_point T>
			constexpr T round(T value) noexcept
			{
				return detail::constexpr_round(value);
			}

	#endif

			//
			// fract()
			//

			// there is no standard c++ version of this, so always call constexpr version

			// the fractional part of a floating point number - always non-negative.

			template <std::floating_point T>
			constexpr T fract(T value) noexcept
			{
				return detail::constexpr_fract(value);
			}

			//
			// fmod()
			//

	#if !defined(PERIODIC_CXCM_DISABLE_RUNTIME_OPTIMIZATIONS) && (defined(_DEBUG) || defined(_M_IX86))

			// the floating point remainder of division

			template <std::floating_point T>
			constexpr T fmod(T x, T y) noexcept
			{
				if (std::is_constant_evaluated())
				{
					return detail::constexpr_fmod(x, y);
				}
				else
				{
					return std::fmod(x, y);
				}
			}

	#else

			// the floating point remainder of division

			template <std::floating_point T>
			constexpr T fmod(T x, T y) noexcept
			{
				return detail::constexpr_fmod(x, y);
			}

	#endif

			//
			// round_even()
			//

			// there is no standard c++ version of this, so always call constexpr version

			// rounds to nearest integral position, halfway cases towards even

			template <std::floating_point T>
			constexpr T round_even(T value) noexcept
			{
				return detail::constexpr_round_even(value);
			}

			//
			// sqrt()
			//

	#if PERIODIC_CXCM_APPROXIMATIONS_ALLOWED

		#if !defined(PERIODIC_CXCM_DISABLE_RUNTIME_OPTIMIZATIONS) && (defined(_DEBUG) || defined(_M_IX86))

			template <std::floating_point T>
			constexpr T sqrt(T value) noexcept
			{
				if (std::is_constant_evaluated())
				{
					return detail::constexpr_sqrt(value);
				}
				else
				{
					return std::sqrt(value);
				}
			}

		#else

			template <std::floating_point T>
			constexpr T sqrt(T value) noexcept
			{
				return detail::constexpr_sqrt(value);
			}

		#endif

	#else

		template <std::floating_point T>
		T sqrt(T value) noexcept
		{
			return std::sqrt(value);
		}

	#endif

			//
			// rsqrt() - inverse square root
			//

	#if PERIODIC_CXCM_APPROXIMATIONS_ALLOWED

		#if !defined(PERIODIC_CXCM_DISABLE_RUNTIME_OPTIMIZATIONS) && (defined(_DEBUG) || defined(_M_IX86))

			template <std::floating_point T>
			constexpr T rsqrt(T value) noexcept
			{
				if (std::is_constant_evaluated())
				{
					return detail::constexpr_rsqrt(value);
				}
				else
				{
					return T(1.0) / std::sqrt(value);
				}
			}

		#else

			template <std::floating_point T>
			constexpr T rsqrt(T value) noexcept
			{
				return detail::constexpr_rsqrt(value);
			}

		#endif

	#else

		template <std::floating_point T>
		T rsqrt(T value) noexcept
		{
			return T(1.0) / std::sqrt(value);
		}

	#endif

		} // namespace strict

	} // namespace cxcm


	// 2 * pi = tau
	// https://tauday.com/tau-manifesto
	template <std::floating_point T>
	constexpr inline T tau = T(2 * std::numbers::pi_v<T>);

	// input_value is value to convert
	// input period is period of input-related values
	// input_origin is the origin of the input pcs in output pcs coords, so therefore in output_period
	// output_min is the min value of output range, where range => [output_min, output_min + output_period)
	// output_period is the period of output-related values, and is a scale factor on the output
	constexpr double forward_convert(double input_value, double input_period, double input_origin, double output_min, double output_period) noexcept
	{
		// normalize parameters to period == 1
		const double norm_input = (input_value / input_period) + (input_origin / output_period);
		const double norm_minimum_output = output_min / output_period;

		// scale output by output_period
		return output_period * (norm_input - cxcm::floor(norm_input - norm_minimum_output));
	}

	// input_value is value to convert
	// input period is period of input-related values
	// input_origin is the origin of the input pcs in output pcs coords, so therefore in output_period
	// output_min is the min value of output range, where range => [output_min, output_min + output_period)
	// output_period is the period of output-related values, and is a scale factor on the output
	constexpr double reverse_convert(double input_value, double input_period, double input_origin, double output_min, double output_period) noexcept
	{
		// normalize parameters to period == 1
		const double norm_input = (input_value / input_period) - (input_origin / output_period);
		const double norm_minimum_output = output_min / output_period;

		// scale output by output_period
		return output_period * (cxcm::ceil(norm_input + norm_minimum_output) - norm_input);
	}

	// there are so many parameters depending on the input and output situations.
	// we default all the parameters to a simple turn-based system, and we use
	// designated initializers to change these parameters as needed. we then apply
	// the forward or reverse period conversion on the input value.

	// normal forward conversion
	struct forward_period_converter
	{
		double input_period = 1.0;	// the period of the input values
		double output_period = 1.0;	// the period of the output values
		double input_origin = 0.0;	// the input origin in output_period units (i.e., in output pcs coords)
		double output_min = 0.0;	// the minimum of the output range, in output_period units

		// 
		constexpr double operator()(double input_value) const noexcept
		{
			return forward(input_value);
		}

		// 
		[[nodiscard]] constexpr double forward(double input_value) const noexcept
		{
			return forward_convert(input_value, input_period, input_origin, output_min, output_period);
		}

		// 
		[[nodiscard]] constexpr double reverse(double input_value) const noexcept
		{
			return reverse_convert(input_value, input_period, input_origin, output_min, output_period);
		}
	};

	// normal reverse conversion
	struct reverse_period_converter
	{
		double input_period = 1.0;	// the period of the input values
		double output_period = 1.0;	// the period of the output values
		double input_origin = 0.0;	// the input origin in output_period units (i.e., in output pcs coords)
		double output_min = 0.0;	// the minimum of the output range, in output_period units

		// 
		constexpr double operator()(double input_value) const noexcept
		{
			return forward(input_value);
		}

		// 
		[[nodiscard]] constexpr double forward(double input_value) const noexcept
		{
			return reverse_convert(input_value, input_period, input_origin, output_min, output_period);
		}

		// 
		[[nodiscard]] constexpr double reverse(double input_value) const noexcept
		{
			return forward_convert(input_value, input_period, input_origin, output_min, output_period);
		}
	};


	// 64-bit binary angular measurement.
	// this is a position, not a quantity.
	// size comparison makes no sense.
	// distance between values can make sense, but what units? bam is not a quantity.
	// but can we use the same representation for a swept angle -- but a periodic swept
	// angle, not linear, i.e., we couldn't represent more than one swept turn
	struct bam64
	{
		unsigned long long value;

		static constexpr double unit_period_to_bam = 0x1p64;
		static constexpr double bam_to_unit_period = 0x1p-64;

		static constexpr unsigned long long zero_turn			{ 0x0000000000000000 };
		static constexpr unsigned long long quarter_turn		{ 0x4000000000000000 };
		static constexpr unsigned long long half_turn			{ 0x8000000000000000 };
		static constexpr unsigned long long three_quarter_turn	{ 0xC000000000000000 };
		static constexpr unsigned long long eighth_turn			{ 0x2000000000000000 };
		static constexpr unsigned long long sixteenth_turn		{ 0x1000000000000000 };
		static constexpr unsigned long long thirty_second_turn	{ 0x0800000000000000 };
		static constexpr unsigned long long sixty_fourth_turn	{ 0x0400000000000000 };

		static constexpr unsigned long long radian_turn			{ 0x28be60db93910600 };
		static constexpr unsigned long long degree_turn			{ 0x00b60b60b60b60b8 };

		static constexpr bam64 from_turns(double turns) noexcept
		{
			return bam64{ .value = static_cast<unsigned long long>(cxcm::fract(turns) * unit_period_to_bam) };
		}

		static constexpr bam64 from_degrees(double degrees) noexcept
		{
			return from_turns(degrees / 360.0);
		}

		static constexpr bam64 from_radians(double radians) noexcept
		{
			return from_turns(radians / tau<double>);
		}

		[[nodiscard]] constexpr double to_turns() const noexcept
		{
			return this->value * bam_to_unit_period;
		}

		[[nodiscard]] constexpr double to_degrees() const noexcept
		{
			return 360.0 * to_turns();
		}

		[[nodiscard]] constexpr double to_radians() const noexcept
		{
			return tau<double> * to_turns();
		}

		// relies on unsigned overflow
		constexpr bam64 operator +(bam64 rhs) const noexcept
		{
			return { this->value + rhs.value };
		}

		// relies on unsigned underflow
		constexpr bam64 operator -(bam64 rhs) const noexcept
		{
			return { this->value - rhs.value };
		}

		// unary plus is identity operation
		constexpr bam64 operator +() const noexcept
		{
			return { this->value };
		}

		// two's complement negation
		// for a BAM, negation is its complement -> (1 - bam)
		constexpr bam64 operator -() const noexcept
		{
			return { ~(this->value) + 1ULL };
		}

		// two's complement - same as negation
		// for a BAM, negation is its complement -> (1 - normalized_periodic_value)
		constexpr bam64 operator ~() const noexcept
		{
			return { ~(this->value) + 1ULL };
		}

	};

}	// namespace pcs


// closing include guard
#endif
