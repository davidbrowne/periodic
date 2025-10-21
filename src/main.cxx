
//          Copyright David Browne 2021-2022.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

//#include "dev_3rd/nanobench.h"
#include "periodic.hxx"
#include "bam64.hxx"
#include "utility.hxx"
#include <cmath>
#include <iostream>
#include <iomanip>

//
//
// This file contains main(), and it is used for both running the unit tests and
// for playing around with some examples and ideas. This file doesn't have anything
// to demonstrate beyond that.
//
//

void get_epsilon_for_double(pcs::bam64 bam)
{
	double frac = bam.fraction();

	int up_count = 0;
	while (pcs::bam64::from_bam_value(bam.value + up_count + 1).fraction() == frac)
	{
		++up_count;
	}

	int down_count = 0;
	while (pcs::bam64::from_bam_value(bam.value - down_count - 1).fraction() == frac)
	{
		++down_count;
	}

	std::cout << "bam: " << std::showbase << std::nouppercase << std::hex << bam.value << std::dec
		<< std::setprecision(17) << " fract: " << frac << " up_count: " << up_count << ", down_count : " << down_count << "\n";
}


// this function is a place to just test out whatever
static void sandbox_function()
{
	// put fun code here

	pcs::bam64 some_turns{ pcs::fourth };
	[[maybe_unused]] auto complement = ~some_turns;

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

	[[maybe_unused]] auto deg0 =	pcs::bam64_from_degrees(0);				// 0x0000000000000000		none
	[[maybe_unused]] auto deg1 =	pcs::bam64_from_degrees(1);				// 0x00b60b60b60b60b8		threehundredsixtieth
	[[maybe_unused]] auto deg1_5 =	pcs::bam64_from_degrees(1.5);			// 0x0111111111111110		twohundredfortieth
	[[maybe_unused]] auto deg2 =	pcs::bam64_from_degrees(2);				// 0x016c16c16c16c170		hundredeightieth
	[[maybe_unused]] auto deg3 =	pcs::bam64_from_degrees(3);				// 0x0222222222222220		hundredtwentieth
	[[maybe_unused]] auto deg4 =	pcs::bam64_from_degrees(4);				// 0x02d82d82d82d82e0		ninetieth
	[[maybe_unused]] auto deg5 =	pcs::bam64_from_degrees(5);				// 0x038e38e38e38e380		seventysecond
	[[maybe_unused]] auto deg_64 =	pcs::bam64_from_degrees(5.625);			// 0x0400000000000000		sixtyfourth
	[[maybe_unused]] auto deg6 =	pcs::bam64_from_degrees(6);				// 0x0444444444444440		sixtieth
	[[maybe_unused]] auto deg7_5 =	pcs::bam64_from_degrees(7.5);			// 0x0555555555555540		fourtyeighth
	[[maybe_unused]] auto deg8 =	pcs::bam64_from_degrees(8);				// 0x05b05b05b05b05c0		fourtyfifth
	[[maybe_unused]] auto deg10 =	pcs::bam64_from_degrees(10);			// 0x071c71c71c71c700		thirtysixth
	[[maybe_unused]] auto deg_32 =	pcs::bam64_from_degrees(11.25);			// 0x0800000000000000		thirtysecond
	[[maybe_unused]] auto deg12 =	pcs::bam64_from_degrees(12);			// 0x0888888888888880		thirtieth
	[[maybe_unused]] auto deg15 =	pcs::bam64_from_degrees(15);			// 0x0aaaaaaaaaaaaa80		twentyfourth
	[[maybe_unused]] auto deg18 =	pcs::bam64_from_degrees(18);			// 0x0ccccccccccccd00		twentieth
	[[maybe_unused]] auto deg20 =	pcs::bam64_from_degrees(20);			// 0x0e38e38e38e38e00		eighteenth
	[[maybe_unused]] auto deg_16 =	pcs::bam64_from_degrees(22.5);			// 0x1000000000000000		sixteenth
	[[maybe_unused]] auto deg24 =	pcs::bam64_from_degrees(24);			// 0x1111111111111100		fifteenth
	[[maybe_unused]] auto deg30 =	pcs::bam64_from_degrees(30);			// 0x1555555555555500		twelfth
	[[maybe_unused]] auto deg36 =	pcs::bam64_from_degrees(36);			// 0x1999999999999a00		tenth
	[[maybe_unused]] auto deg45 =	pcs::bam64_from_degrees(45);			// 0x2000000000000000		eighth
	[[maybe_unused]] auto deg60 =	pcs::bam64_from_degrees(60);			// 0x2aaaaaaaaaaaaa00		sixth
	[[maybe_unused]] auto deg_67_5 =pcs::bam64_from_degrees(67.5);			// 0x3000000000000000		threesixteenths
	[[maybe_unused]] auto deg72 =	pcs::bam64_from_degrees(72);			// 0x3333333333333400		fifth
	[[maybe_unused]] auto deg90 =	pcs::bam64_from_degrees(90);			// 0x4000000000000000		fourth
	[[maybe_unused]] auto deg_112_5=pcs::bam64_from_degrees(112.5);			// 0x5000000000000000		fivesixteenths
	[[maybe_unused]] auto deg120 =	pcs::bam64_from_degrees(120);			// 0x5555555555555400		third
	[[maybe_unused]] auto deg135 =	pcs::bam64_from_degrees(135);			// 0x6000000000000000		threeeighths
	[[maybe_unused]] auto deg150 =	pcs::bam64_from_degrees(150);			// 0x6aaaaaaaaaaaac00		fivetwelfths
	[[maybe_unused]] auto deg_157_5=pcs::bam64_from_degrees(157.5);			// 0x7000000000000000		sevensixteenths
	[[maybe_unused]] auto deg180 =	pcs::bam64_from_degrees(180);			// 0x8000000000000000		half
	[[maybe_unused]] auto deg_202_5=pcs::bam64_from_degrees(202.5);			// 0x9000000000000000		ninesixteenths
	[[maybe_unused]] auto deg210 =	pcs::bam64_from_degrees(210);			// 0x9555555555555800		seventwelfths
	[[maybe_unused]] auto deg225 =	pcs::bam64_from_degrees(225);			// 0xa000000000000000		fiveeighths
	[[maybe_unused]] auto deg240 =	pcs::bam64_from_degrees(240);			// 0xaaaaaaaaaaaaa800		twothirds
	[[maybe_unused]] auto deg_247_5=pcs::bam64_from_degrees(247.5);			// 0xb000000000000000		elevensixteenths
	[[maybe_unused]] auto deg270 =	pcs::bam64_from_degrees(270);			// 0xc000000000000000		threefourths
	[[maybe_unused]] auto deg292_5 =pcs::bam64_from_degrees(292.5);			// 0xd000000000000000		thirteensixteenths
	[[maybe_unused]] auto deg300 =	pcs::bam64_from_degrees(300);			// 0xd555555555555800		fivesixths
	[[maybe_unused]] auto deg315 =	pcs::bam64_from_degrees(315);			// 0xe000000000000000		seveneighths
	[[maybe_unused]] auto deg330 =	pcs::bam64_from_degrees(330);			// 0xeaaaaaaaaaaaa800		eleventwelfths
	[[maybe_unused]] auto deg337_5 =pcs::bam64_from_degrees(337.5);			// 0xf000000000000000		fifteensixteenths

	[[maybe_unused]] auto rad =		pcs::bam64_from_radians(1);				// 0x28be60db93910600		radian
	[[maybe_unused]] auto deg =		pcs::bam64_from_degrees(1);				// 0x00b60b60b60b60b8		degree

	[[maybe_unused]] auto dd1 = pcs::bam64_from_degrees(180.0 / pcs::pi);	// 0x28be60db93910600		radian
	[[maybe_unused]] auto dd2 = pcs::bam64_from_radians(pcs::pi / 180.0);	// 0x00b60b60b60b60b8		degree

	[[maybe_unused]] auto test_zero = pcs::bam64::from_bam_value(pcs::none);
	[[maybe_unused]] auto test_half = pcs::bam64::from_bam_value(pcs::half);

	[[maybe_unused]] auto comp_zero = test_zero.complement();
	[[maybe_unused]] auto comp_half = test_half.complement();
	[[maybe_unused]] auto comp_half2 = test_half.complement(pcs::full_degrees);

	[[maybe_unused]] constexpr auto norm_neg_twelfth = pcs::radians_normal(-pcs::pi/12);
	[[maybe_unused]] constexpr auto neg_twelfth = pcs::bam64_from_radians(norm_neg_twelfth);
	[[maybe_unused]] constexpr auto hundredth_of_turn = pcs::bam64_from_turns(0.01);
	[[maybe_unused]] constexpr auto tenth_of_a_degree = pcs::bam64_from_turns(1.0 / 3600.0);

	get_epsilon_for_double(deg0);		// bam: 0x0000000000000000 up_count:    0, down_count :    0
	get_epsilon_for_double(deg60);		// bam: 0x2aaaaaaaaaaaaa00 up_count:  255, down_count :  255
	get_epsilon_for_double(deg90);		// bam: 0x4000000000000000 up_count:  512, down_count :  256
	get_epsilon_for_double(deg180);		// bam: 0x8000000000000000 up_count: 1024, down_count :  512
	get_epsilon_for_double(deg240);		// bam: 0xaaaaaaaaaaaaa800 up_count: 1023, down_count : 1023
	get_epsilon_for_double(deg330);		// 
	get_epsilon_for_double(pcs::bam64::from_bam_value(1));		// 
	get_epsilon_for_double(pcs::bam64::from_bam_value(2));		// 
	get_epsilon_for_double(pcs::bam64::from_bam_value(3));		// 
	get_epsilon_for_double(pcs::bam64::from_bam_value(0xFFFFFFFFFFFFFFFF));		// 



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
