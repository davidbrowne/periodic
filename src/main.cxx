
//          Copyright David Browne 2021-2025.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#include "periodic.hxx"
#include "bam64.hxx"
#include "utility.hxx"
#include <cstdio>

//
//
// This file contains main(), and it is used for both running the unit tests and
// for playing around with some examples and ideas. This file doesn't have anything
// to demonstrate beyond that.
//
//

void new_constants()
{																									//		standard				alternate
	[[maybe_unused]] auto none =					pcs::bam64_from_degrees(  0		);				// 0x0000000000000000	->	0x0000000000000000
	[[maybe_unused]] auto whole =					pcs::bam64_from_degrees(360		);				// 0x0000000000000000	->	0x0000000000000000
	[[maybe_unused]] auto fifteen_sixteenths =		pcs::bam64_from_degrees(337.5	);				// 0xf000000000000000	->	0xf000000000000000
	[[maybe_unused]] auto eleven_twelfths =			pcs::bam64_from_degrees(330		);				// 0xeaaaaaaaaaaaa800	->	0xeaaaaaaaaaaaa800
	[[maybe_unused]] auto seven_eighths =			pcs::bam64_from_degrees(315		);				// 0xe000000000000000	->	0xe000000000000000
	[[maybe_unused]] auto five_sixths =				pcs::bam64_from_degrees(300		);				// 0xd555555555555800	->	0xd555555555555800
	[[maybe_unused]] auto thirteen_sixteenths =		pcs::bam64_from_degrees(292.5	);				// 0xd000000000000000	->	0xd000000000000000
	[[maybe_unused]] auto four_fifths =				pcs::bam64_from_degrees(288		);				// 0xccccccccccccd000	->	0xccccccccccccd000
	[[maybe_unused]] auto three_fourths =			pcs::bam64_from_degrees(270		);				// 0xc000000000000000	->	0xc000000000000000
	[[maybe_unused]] auto eleven_sixteenths =		pcs::bam64_from_degrees(247.5	);				// 0xb000000000000000	->	0xb000000000000000
	[[maybe_unused]] auto two_thirds =				pcs::bam64_from_degrees(240		);				// 0xaaaaaaaaaaaaa800	->	0xaaaaaaaaaaaaa800
	[[maybe_unused]] auto five_eighths =			pcs::bam64_from_degrees(225		);				// 0xa000000000000000	->	0xa000000000000000
	[[maybe_unused]] auto three_fifths =			pcs::bam64_from_degrees(216		);				// 0x9999999999999800	->	0x9999999999999800
	[[maybe_unused]] auto seven_twelfths =			pcs::bam64_from_degrees(210		);				// 0x9555555555555800	->	0x9555555555555800
	[[maybe_unused]] auto nine_sixteenths =			pcs::bam64_from_degrees(202.5	);				// 0x9000000000000000	->	0x9000000000000000
	[[maybe_unused]] auto half =					pcs::bam64_from_degrees(180		);				// 0x8000000000000000	->	0x8000000000000000
	[[maybe_unused]] auto seven_sixteenths =		pcs::bam64_from_degrees(157.5	);				// 0x7000000000000000	->	0x7000000000000000
	[[maybe_unused]] auto five_twelfths =			pcs::bam64_from_degrees(150		);				// 0x6aaaaaaaaaaaac00	->	0x6aaaaaaaaaaaa800	*
	[[maybe_unused]] auto two_fifths =				pcs::bam64_from_degrees(144		);				// 0x6666666666666800	->	0x6666666666666800
	[[maybe_unused]] auto three_eighths =			pcs::bam64_from_degrees(135		);				// 0x6000000000000000	->	0x6000000000000000
	[[maybe_unused]] auto third =					pcs::bam64_from_degrees(120		);				// 0x5555555555555400	->	0x5555555555555000	*
	[[maybe_unused]] auto five_sixteenths =			pcs::bam64_from_degrees(112.5	);				// 0x5000000000000000	->	0x5000000000000000
	[[maybe_unused]] auto fourth =					pcs::bam64_from_degrees( 90		);				// 0x4000000000000000	->	0x4000000000000000
	[[maybe_unused]] auto fifth =					pcs::bam64_from_degrees( 72		);				// 0x3333333333333400	->	0x3333333333333000	*
	[[maybe_unused]] auto three_sixteenths =		pcs::bam64_from_degrees( 67.5	);				// 0x3000000000000000	->	0x3000000000000000
	[[maybe_unused]] auto sixth =					pcs::bam64_from_degrees( 60		);				// 0x2aaaaaaaaaaaaa00	->	0x2aaaaaaaaaaaa800	*
	[[maybe_unused]] auto eighth =					pcs::bam64_from_degrees( 45		);				// 0x2000000000000000	->	0x2000000000000000
	[[maybe_unused]] auto tenth =					pcs::bam64_from_degrees( 36		);				// 0x1999999999999a00	->	0x1999999999999800	*
	[[maybe_unused]] auto twelfth =					pcs::bam64_from_degrees( 30		);				// 0x1555555555555500	->	0x1555555555555000	*
	[[maybe_unused]] auto fifteenth =				pcs::bam64_from_degrees( 24		);				// 0x1111111111111100	->	0x1111111111111000	*
	[[maybe_unused]] auto sixteenth =				pcs::bam64_from_degrees( 22.5	);				// 0x1000000000000000	->	0x1000000000000000
	[[maybe_unused]] auto eighteenth =				pcs::bam64_from_degrees( 20		);				// 0x0e38e38e38e38e00	->	0x0e38e38e38e38800	*
	[[maybe_unused]] auto twentieth =				pcs::bam64_from_degrees( 18		);				// 0x0ccccccccccccd00	->	0x0cccccccccccc800	*
	[[maybe_unused]] auto twenty_fourth =			pcs::bam64_from_degrees( 15		);				// 0x0aaaaaaaaaaaaa80	->	0x0aaaaaaaaaaaa800	*
	[[maybe_unused]] auto thirtieth =				pcs::bam64_from_degrees( 12		);				// 0x0888888888888880	->	0x0888888888888800	*
	[[maybe_unused]] auto thirty_second =			pcs::bam64_from_degrees( 11.25	);				// 0x0800000000000000	->	0x0800000000000000
	[[maybe_unused]] auto thirty_sixth =			pcs::bam64_from_degrees( 10		);				// 0x071c71c71c71c700	->	0x071c71c71c71c000	*
	[[maybe_unused]] auto fourty_fifth =			pcs::bam64_from_degrees(  8		);				// 0x05b05b05b05b05c0	->	0x05b05b05b05b0000	*
	[[maybe_unused]] auto fourty_eighth =			pcs::bam64_from_degrees(  7.5	);				// 0x0555555555555540	->	0x0555555555555000	*
	[[maybe_unused]] auto sixtieth =				pcs::bam64_from_degrees(  6		);				// 0x0444444444444440	->	0x0444444444444000	*
	[[maybe_unused]] auto sixty_fourth =			pcs::bam64_from_degrees(  5.625	);				// 0x0400000000000000	->	0x0400000000000000
	[[maybe_unused]] auto seventy_second =			pcs::bam64_from_degrees(  5		);				// 0x038e38e38e38e380	->	0x038e38e38e38e000	*
	[[maybe_unused]] auto ninetieth =				pcs::bam64_from_degrees(  4		);				// 0x02d82d82d82d82e0	->	0x02d82d82d82d8000	*
	[[maybe_unused]] auto hundredth =				pcs::bam64_from_degrees(  3.6	);				// 0x028f5c28f5c28f60	->	0x028f5c28f5c28800	*
	[[maybe_unused]] auto hundred_twentieth =		pcs::bam64_from_degrees(  3		);				// 0x0222222222222220	->	0x0222222222222000	*
	[[maybe_unused]] auto hundred_eightieth =		pcs::bam64_from_degrees(  2		);				// 0x016c16c16c16c170	->	0x016c16c16c16c000	*
	[[maybe_unused]] auto two_hundred_fortieth =	pcs::bam64_from_degrees(  1.5	);				// 0x0111111111111110	->	0x0111111111111000	*
	[[maybe_unused]] auto three_hundred_sixtieth =	pcs::bam64_from_degrees(  1		);				// 0x00b60b60b60b60b8	->	0x00b60b60b60b6000	*

	[[maybe_unused]] auto radian =					pcs::bam64_from_degrees(180.0/pcs::pi);			// 0x28be60db93910600	->	0x28be60db93910000	*	57.295779513082323	->	57.295779513082294
	[[maybe_unused]] auto degree =					pcs::bam64_from_degrees(1);						// 0x00b60b60b60b60b8	->	0x00b60b60b60b6000	*
	[[maybe_unused]] auto arc_minute =				pcs::bam64_from_degrees(1.0/60.0);				// 0x000308b91419ca25	->	0x000308b91419c800	*
	[[maybe_unused]] auto arc_second =				pcs::bam64_from_degrees(1.0/3600.0);			// 0x00000cf2049a07a2	->	0x00000cf2049a0000	*
	[[maybe_unused]] auto tenth_degree =			pcs::bam64_from_degrees(1.0/10.0);				// 0x00123456789abcdf	->	0x00123456789ab800	*
	[[maybe_unused]] auto hundredth_degree =		pcs::bam64_from_degrees(1.0/100.0);				// 0x0001d208a5a912e3	->	0x0001d208a5a91000	*
	[[maybe_unused]] auto minute =					pcs::bam64_from_degrees(6);						// 0x0444444444444440	->	0x0444444444444000	*
	[[maybe_unused]] auto second =					pcs::bam64_from_degrees(6);						// 0x0444444444444440	->	0x0444444444444000	*

	[[maybe_unused]] auto epsilon =					pcs::bam64::from_bam_value(0x0000000000000800);	// 0x0000000000000800


	// 0xfffffffffffff800
	[[maybe_unused]] auto high_bam = pcs::bam64::from_bam_value(0xfffffffffffff800);
	[[maybe_unused]] auto highest_bam = pcs::bam64::from_bam_value(0xffffffffffffffff);
}


// this function is a place to just test out whatever
static void sandbox_function()
{
	// put fun code here

	[[maybe_unused]] constexpr auto underlying = pcs::to_underlying(pcs::radian);
	[[maybe_unused]] constexpr auto something2 = pcs::to_degrees(pcs::bam64::from_bam_value(pcs::radian));

	constexpr auto input_val = 190;
	constexpr auto output_period = 360.0;
	constexpr auto output_min = -180.0;
	constexpr auto input_period = 360.0;
	constexpr auto input_origin = 45.0;

	[[maybe_unused]] constexpr auto answer = pcs::forward_convert(input_val, input_period, input_origin, output_min, output_period);

	pcs::forward_period_converter from_turns_to_centered_degrees{.output_period = 360.0, .output_min = -180.0};

	[[maybe_unused]] auto d = from_turns_to_centered_degrees(.75);
	[[maybe_unused]] auto rd = from_turns_to_centered_degrees.reverse(.75);

	pcs::reverse_period_converter bearing_degrees_to_math_degrees{.input_period = 360.0, .output_period = 360.0, .input_origin = 90.0};
	[[maybe_unused]] auto q = bearing_degrees_to_math_degrees(180.0);
	[[maybe_unused]] auto rq = bearing_degrees_to_math_degrees.reverse(180.0);

	pcs::reverse_period_converter math_degrees_to_bearing_degrees{.input_period = 360.0, .output_period = 360.0, .input_origin = 90.0};
	[[maybe_unused]] auto s = math_degrees_to_bearing_degrees(135.0);
	[[maybe_unused]] auto rs = math_degrees_to_bearing_degrees.reverse(135.0);

	math_degrees_to_bearing_degrees.output_min = -180.0;
	[[maybe_unused]] auto t = math_degrees_to_bearing_degrees(135.0);
	[[maybe_unused]] auto rt = math_degrees_to_bearing_degrees.reverse(135.0);

	[[maybe_unused]] auto fbam1 = pcs::bam64::from_bam_value(pcs::to_bam_value_alt(pcs::pi));
	[[maybe_unused]] auto fbam2 = pcs::bam64::from_bam_value(pcs::to_bam_value_alt(pcs::pi));

	//	pcs::bam64 start = pcs::bam64::from_bam_value(0x9999999999999800);
	pcs::bam64 start = pcs::bam64::from_bam_value(0);

	pcs::bam64 some_turns{ pcs::fourth };
	[[maybe_unused]] auto complement = ~some_turns;

	[[maybe_unused]] pcs::bam64 default_ctor;
	[[maybe_unused]] auto designated_init = pcs::bam64{ .value = 0x4000000000000000 };
	[[maybe_unused]] auto direct_init = pcs::bam64{0x4000000000000000};
	[[maybe_unused]] auto ninetydegrees = pcs::bam64_from_radians(pcs::half_pi);
	[[maybe_unused]] auto ninetydegrees_mult9 = pcs::bam64_from_radians(pcs::half_pi * 9.0);
	[[maybe_unused]] auto ninetydegrees_mult5 = pcs::bam64_from_radians(pcs::half_pi * 5.0);
	[[maybe_unused]] auto sixtydegrees_mult7 = pcs::bam64_from_radians(pcs::pi / 3.0 * 7.0);
	[[maybe_unused]] auto sixtydegrees_mult7_2 = pcs::bam64_from_degrees(60 * 7.0);
	[[maybe_unused]] auto sixtydegrees_mult5 = pcs::bam64_from_radians(pcs::pi / 3.0 * 5.0);
	[[maybe_unused]] auto thirtydegrees_mult25 = pcs::bam64_from_radians(pcs::pi / 6.0 * 25.0);
	[[maybe_unused]] auto thirtydegrees_mult14 = pcs::bam64_from_radians(pcs::pi / 6.0 * 14.0);
	[[maybe_unused]] auto thirtydegrees_mult13 = pcs::bam64_from_radians(pcs::pi / 6.0 * 13.0);
	[[maybe_unused]] auto thirtydegrees_mult11 = pcs::bam64_from_radians(pcs::pi / 6.0 * 11.0);

	new_constants();
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
