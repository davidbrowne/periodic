
//          Copyright David Browne 2021-2022.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

//#include "dev_3rd/nanobench.h"
#include "periodic.hxx"


//
//
// This file contains main(), and it is used for both running the unit tests and
// for playing around with some example and ideas. This file doesn't have anything
// to demonstrate beyond that.
//
//


// this function is a place to just test out whatever
void sandbox_function()
{
	// put fun code here
	period::bam64 some_turns{ period::bam64::quarter_turn };
	[[maybe_unused]] auto complement = ~some_turns;

	[[maybe_unused]] constexpr auto foo = period::bam64::from_radians(period::tau<double> * period::bam64::radian_turn);
	[[maybe_unused]] constexpr auto bar = period::bam64::from_degrees(360.0 * period::bam64::degree_turn);


	constexpr auto input_val = 190;
	constexpr auto output_period = 360.0;
	constexpr auto output_value_shift = 0.0;
	constexpr auto output_time_shift = -180.0;
	constexpr auto input_period = 360.0;
	constexpr auto input_time_scale = 1.0;
	constexpr auto period_offset = 45.0;
	constexpr auto input_value_shift = 0.0;

	[[maybe_unused]] constexpr auto answer = period::total_phi(input_val, input_time_scale, input_period, input_value_shift, output_period, output_time_shift, output_value_shift, period_offset);

#if 0
	double time_offset = -0.5;
	//double time_offset = 0.0;
	std::printf("period::basic_phi( 1.0, %g) = %g\n", time_offset, period::basic_reverse_phi(-1.0, time_offset));
	std::printf("period::basic_phi( 0.9, %g) = %g\n", time_offset, period::basic_reverse_phi(-0.9, time_offset));
	std::printf("period::basic_phi( 0.8, %g) = %g\n", time_offset, period::basic_reverse_phi(-0.8, time_offset));
	std::printf("period::basic_phi( 0.7, %g) = %g\n", time_offset, period::basic_reverse_phi(-0.7, time_offset));
	std::printf("period::basic_phi( 0.6, %g) = %g\n", time_offset, period::basic_reverse_phi(-0.6, time_offset));
	std::printf("period::basic_phi( 0.5, %g) = %g\n", time_offset, period::basic_reverse_phi(-0.5, time_offset));
	std::printf("period::basic_phi( 0.4, %g) = %g\n", time_offset, period::basic_reverse_phi(-0.4, time_offset));
	std::printf("period::basic_phi( 0.3, %g) = %g\n", time_offset, period::basic_reverse_phi(-0.3, time_offset));
	std::printf("period::basic_phi( 0.2, %g) = %g\n", time_offset, period::basic_reverse_phi(-0.2, time_offset));
	std::printf("period::basic_phi( 0.1, %g) = %g\n", time_offset, period::basic_reverse_phi(-0.1, time_offset));
	std::printf("period::basic_phi( 0.0, %g) = %g\n", time_offset, period::basic_reverse_phi( 0.0, time_offset));
	std::printf("period::basic_phi(-0.1, %g) = %g\n", time_offset, period::basic_reverse_phi( 0.1, time_offset));
	std::printf("period::basic_phi(-0.2, %g) = %g\n", time_offset, period::basic_reverse_phi( 0.2, time_offset));
	std::printf("period::basic_phi(-0.3, %g) = %g\n", time_offset, period::basic_reverse_phi( 0.3, time_offset));
	std::printf("period::basic_phi(-0.4, %g) = %g\n", time_offset, period::basic_reverse_phi( 0.4, time_offset));
	std::printf("period::basic_phi(-0.5, %g) = %g\n", time_offset, period::basic_reverse_phi( 0.5, time_offset));
	std::printf("period::basic_phi(-0.6, %g) = %g\n", time_offset, period::basic_reverse_phi( 0.6, time_offset));
	std::printf("period::basic_phi(-0.7, %g) = %g\n", time_offset, period::basic_reverse_phi( 0.7, time_offset));
	std::printf("period::basic_phi(-0.8, %g) = %g\n", time_offset, period::basic_reverse_phi( 0.8, time_offset));
	std::printf("period::basic_phi(-0.9, %g) = %g\n", time_offset, period::basic_reverse_phi( 0.9, time_offset));
	std::printf("period::basic_phi(-1.0, %g) = %g\n", time_offset, period::basic_reverse_phi( 1.0, time_offset));

#endif

	for (int i = 360; i >= -360; i -= 30)
		std::printf("period::total_phi(%d, %g, %g, %g, %g, %g, %g, %g) = %g\n",
					i, input_time_scale, input_period, input_value_shift, output_period, output_time_shift, output_value_shift, period_offset,
					period::total_reverse_phi(-i, input_time_scale, input_period, input_value_shift, output_period, output_time_shift, output_value_shift, period_offset));


	period::period_convert from_turns_to_centered_degrees{.output_period = 360.0, .output_min = -180.0};

	auto d = from_turns_to_centered_degrees(.75);
	auto rd = from_turns_to_centered_degrees.reverse(.75);

	period::reverse_period_convert bearing_degrees_to_math_degrees{.input_period = 360.0, .output_period = 360.0, .period_offset = 90.0};
	auto q = bearing_degrees_to_math_degrees(180.0);
	auto rq = bearing_degrees_to_math_degrees.reverse(180.0);

	period::reverse_period_convert math_degrees_to_bearing_degrees{.input_period = 360.0, .output_period = 360.0, .period_offset = 90.0};
	auto s = math_degrees_to_bearing_degrees(135.0);
	auto rs = math_degrees_to_bearing_degrees.reverse(135.0);


	// periodic or repeating periods
	// non-periodic or non-repeating periods or discontinuous?

	// inverses of the above

	// periodic coordinate systems
	// inverses of periodic coordinate systems

	// BAMs
	// BAM tolerance w.r.t. double

	// turns

	// angle position vs angle displacement (or swept angle)

	// conversions between turns/radians/degrees/etc

	// unsigned period (e.g., angles from [0, 360) degrees)
	// signed period (e.g., angles from [-180, 180) degrees)

	// phase shift/amplitude shift/amplitude scaling/period scaling
}


// reversing parameter pack stuff


// https://twitter.com/the_whole_daisy/status/1379580525078147072
// https://godbolt.org/z/h5P1Mxsrz
// TLDR -- operator precedence ('=' is right to left, ',' is left to right) matters with binary fold expressions.
//
//#include <iostream>
//
//template <class... Ts>
//void print_args_backwards(Ts... ts)
//{
//	auto print_one = [](auto t)
//	{
//		std::cout << t << std::endl;
//
//		// Anything with a reasonable assignment operator will work here
//		return std::type_identity<void>{};
//	};
//
//	// Backwards:
//	(print_one(ts) = ...);
//
//	// Forwards:
//	(print_one(ts), ...);
//}
//
//int main()
//{
//	print_args_backwards(1, 2, "hello", 3, 4, "world");
//}


// https://stackoverflow.com/questions/51408771/c-reversed-integer-sequence-implementation
//
//#include <utility>
//#include <type_traits>
//
//template <std::size_t ... Is>
//constexpr auto indexSequenceReverse (std::index_sequence<Is...> const &)
//-> decltype( std::index_sequence<sizeof...(Is)-1U-Is...>{} );
//
//template <std::size_t N>
//using makeIndexSequenceReverse = decltype(indexSequenceReverse(std::make_index_sequence<N>{}));
//
//int main()
//{
//	static_assert( std::is_same<std::index_sequence<4U, 3U, 2U, 1U, 0U>,
//				   makeIndexSequenceReverse<5U>>::value, "!" );
//}


// https://stackoverflow.com/questions/47303466/compile-time-reversal-of-parameter-pack-expansion
//
//template<typename T>
//struct Test
//{
//	template <std::size_t...Is, typename... B>
//	Test(std::index_sequence<Is...>, B&&... vv) :
//		b{std::get<sizeof...(Is) - 1 - Is>(std::tie(vv...))...}
//	{}
//
//	public:
//		template<typename... B>
//		explicit Test(B... vv) : Test(std::index_sequence_for<B...>{}, vv...) {}
//	private:
//		std::byte b[sizeof(T)];
//};


#if defined(__clang__) && (__clang_major__ < 13)
// clang 10.0 does not like colors on windows (link problems with isatty and fileno)
#define DOCTEST_CONFIG_COLORS_NONE
#endif

#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"

int main(int argc, char *argv[])
{
	sandbox_function();


	//
	// doctest
	//

	int doctest_result = 0;

// comment out if we define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN somewhere to get the main() from doctest
#define DONT_USE_DOCTEST_MAIN

#if defined(DONT_USE_DOCTEST_MAIN)

	doctest::Context context;
	context.applyCommandLine(argc, argv);

	doctest_result = context.run();				// run

	if (context.shouldExit())					// important - query flags (and --exit) rely on the user doing this
		return doctest_result;					// propagate the result of the tests

#endif



	return EXIT_SUCCESS + doctest_result;
}
