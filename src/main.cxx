
//          Copyright David Browne 2021-2022.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

//#include "dev_3rd/nanobench.h"
#include "periodic.hxx"


//
//
// This file contains main(), and it is used for both running the unit tests and
// for playing around with some examples and ideas. This file doesn't have anything
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

	for (int i = 360; i >= -360; i -= 30)
		std::printf("period::total_phi(%d, %g, %g, %g, %g, %g, %g, %g) = %g\n",
					i, input_time_scale, input_period, input_value_shift, output_period, output_time_shift, output_value_shift, period_offset,
					period::total_reverse_phi(-i, input_time_scale, input_period, input_value_shift, output_period, output_time_shift, output_value_shift, period_offset));

#endif


	period::period_converter from_turns_to_centered_degrees{.output_period = 360.0, .output_min = -180.0};

	[[maybe_unused]] auto d = from_turns_to_centered_degrees(.75);
	[[maybe_unused]] auto rd = from_turns_to_centered_degrees.reverse(.75);

	period::reverse_period_converter bearing_degrees_to_math_degrees{.input_period = 360.0, .output_period = 360.0, .period_offset = 90.0};
	[[maybe_unused]] auto q = bearing_degrees_to_math_degrees(180.0);
	[[maybe_unused]] auto rq = bearing_degrees_to_math_degrees.reverse(180.0);

	period::reverse_period_converter math_degrees_to_bearing_degrees{.input_period = 360.0, .output_period = 360.0, .period_offset = 90.0};
	[[maybe_unused]] auto s = math_degrees_to_bearing_degrees(135.0);
	[[maybe_unused]] auto rs = math_degrees_to_bearing_degrees.reverse(135.0);


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
