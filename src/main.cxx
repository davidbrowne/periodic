
//          Copyright David Browne 2021-2022.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

//#include "dev_3rd/nanobench.h"
#include "periodic.hxx"
#include <cmath>


//
//
// This file contains main(), and it is used for both running the unit tests and
// for playing around with some examples and ideas. This file doesn't have anything
// to demonstrate beyond that.
//
//


template <std::floating_point T>
constexpr inline T PI = std::numbers::pi_v<T>;

template <std::floating_point T>
constexpr inline T tau = T(T(2) * PI<T>);

template <std::floating_point T>
constexpr inline T TWOPI = tau<T>;

// seems to be worse than full_ang()
static double ang_full(double ang)
{
	static double i{};
	double turns = std::modf(std::abs(ang) / tau<double>, &i);

	if (ang < 0)
	{
		turns = (1.0 - turns);
	}

	return tau<double> *turns;
}

// seems to be worse than ang_in_minuspi_pluspi()
static double ang_norm(double ang)
{
	static double i{};
	double turns = std::modf(std::abs(ang) / tau<double>, &i);

	if (ang < 0.0)
	{
		turns = (1.0 - turns);
	}

	if (turns > 0.5)
	{
		turns = (turns - 1.0);
	}

	return tau<double> *turns;
}


// Convert an angle in any system to the system [0, TWOPI).
// Convert an angle to a value in the range (0 <= value < TWOPI).
static double full_ang(double angle)
{
	while (angle < 0.0)
		angle += TWOPI<double>;

	while (angle >= TWOPI<double>)
		angle -= TWOPI<double>;

	return angle;
}

// Convert an angle in any system to the system (-PI, PI).
// RETURNS: a double value in the range (-PI <= return value <= PI).
// NOTE:	very similar to full_ang()
static double ang_in_minuspi_pluspi(double ang)							// ang is any real number radian value
{
	while (ang < -PI<double>)
		ang += TWOPI<double>;

	while (ang > PI<double>)
		ang -= TWOPI<double>;

	return ang;
}

// this function is a place to just test out whatever
static void sandbox_function()
{









	// put fun code here
	pcs::bam64 some_turns{ pcs::bam64::fourth };
	[[maybe_unused]] auto complement = ~some_turns;

	[[maybe_unused]] constexpr auto underlying = pcs::to_underlying(pcs::bam64::radian);
//	[[maybe_unused]] constexpr auto something1 = 360.0 * pcs::to_underlying(pcs::bam64::radian) * pcs::bam64::bam_to_unit_period;
	[[maybe_unused]] constexpr auto something2 = pcs::bam64::from_bam_value(pcs::bam64::radian).degrees_full();

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

	[[maybe_unused]] auto degzero = pcs::bam64(pcs::bam64::none).degrees_full();
	[[maybe_unused]] auto degsixtyfourth = pcs::bam64(pcs::bam64::sixty_fourth).degrees_full();
	[[maybe_unused]] auto deg32nd = pcs::bam64(pcs::bam64::thirty_second).degrees_full();
	[[maybe_unused]] auto deg16th = pcs::bam64(pcs::bam64::sixteenth).degrees_full();
	[[maybe_unused]] auto deg8th = pcs::bam64(pcs::bam64::eighth).degrees_full();
	[[maybe_unused]] auto deg4th = pcs::bam64(pcs::bam64::fourth).degrees_full();
	[[maybe_unused]] auto deghalf = pcs::bam64(pcs::bam64::half);
	[[maybe_unused]] auto deghalf1 = deghalf.degrees_full();
	[[maybe_unused]] auto deghalf2 = deghalf.degrees_norm();
	[[maybe_unused]] auto deg3quarters = pcs::bam64(pcs::bam64::three_fourths).degrees_full();
	[[maybe_unused]] auto deg12th = pcs::bam64(pcs::bam64::twelfth).degrees_full();
	[[maybe_unused]] auto deg6th = pcs::bam64(pcs::bam64::sixth).degrees_full();
	[[maybe_unused]] auto degthird = pcs::bam64(pcs::bam64::third).degrees_full();
	[[maybe_unused]] auto deg5th = pcs::bam64(pcs::bam64::fifth).degrees_full();

	auto deg3quarters_bam = pcs::bam64::from_degrees(270.0);
	[[maybe_unused]] auto bamtest = (~deg3quarters_bam).degrees_full();
	auto degquarter = pcs::bam64::from_degrees(90.0);
	[[maybe_unused]] auto bamtest1 = (~degquarter).degrees_full();
	auto degnegquarter = pcs::bam64::from_degrees(-90.0);
	[[maybe_unused]] auto bamtest2 = degnegquarter.degrees_full();
	auto degbigneg = pcs::bam64::from_degrees(-700.0);

	[[maybe_unused]] auto bamtest3 = degnegquarter.degrees_comp();
	[[maybe_unused]] auto bamtest4 = degnegquarter.radians_comp();
	[[maybe_unused]] auto bamtest5 = degquarter.degrees_comp();
	[[maybe_unused]] auto bamtest6 = degquarter.radians_comp();

	[[maybe_unused]] auto bamtest7 = degnegquarter.degrees_full();
	[[maybe_unused]] auto bamtest8 = degnegquarter.degrees_norm();
	[[maybe_unused]] auto bamtest9 = degnegquarter.radians_full();
	[[maybe_unused]] auto bamtest0 = degnegquarter.radians_norm();

	[[maybe_unused]] auto bamtest11 = degquarter.degrees_full();
	[[maybe_unused]] auto bamtest12 = degquarter.degrees_norm();
	[[maybe_unused]] auto bamtest13 = degquarter.radians_full();
	[[maybe_unused]] auto bamtest14 = degquarter.radians_norm();

	[[maybe_unused]] auto factor1 = 360.0 * 0x1p-64;
	[[maybe_unused]] auto factor2 = 6.2831853071795862 * 0x1p-64;

	[[maybe_unused]] auto oneradian = pcs::bam64{pcs::bam64::radian};
	[[maybe_unused]] auto fifthturn = pcs::bam64{pcs::bam64::fifth};
	[[maybe_unused]] auto fifteenthturn = pcs::bam64{pcs::bam64::fifteenth};
	[[maybe_unused]] auto thirdturn = pcs::bam64{pcs::bam64::third};
	[[maybe_unused]] auto thirtydegrees = pcs::bam64::from_degrees(30);
	[[maybe_unused]] auto sixtydegrees = pcs::bam64::from_degrees(60);
	[[maybe_unused]] auto thirdturndeg = pcs::bam64::from_degrees(120);
	[[maybe_unused]] auto fifthturndeg = pcs::bam64::from_degrees(72);
	[[maybe_unused]] auto fifteenturndeg = pcs::bam64::from_degrees(24);
	[[maybe_unused]] auto tenthturndeg = pcs::bam64::from_degrees(36);
	[[maybe_unused]] auto eighteenthturndeg = pcs::bam64::from_degrees(20);
	[[maybe_unused]] auto twentythturndeg = pcs::bam64::from_degrees(18);
	[[maybe_unused]] auto twentyfourthturndeg = pcs::bam64::from_degrees(15);
	[[maybe_unused]] auto thirtiethturndeg = pcs::bam64::from_degrees(12);
	[[maybe_unused]] auto thirtysixthturndeg = pcs::bam64::from_degrees(10);
	[[maybe_unused]] auto fourtyfifthturndeg = pcs::bam64::from_degrees(8);
	[[maybe_unused]] auto sixtiethturndeg = pcs::bam64::from_degrees(6);
	[[maybe_unused]] auto seventysecondturndeg = pcs::bam64::from_degrees(5);
	[[maybe_unused]] auto radian_again = pcs::bam64::from_degrees(57.295779513082321);
	[[maybe_unused]] auto radian_again1 = pcs::bam64::from_radians(1.0);
	[[maybe_unused]] auto radian_again2 = pcs::bam64::from_degrees(180.0 / PI<double>);
	[[maybe_unused]] auto radian_again3 = pcs::bam64{static_cast<unsigned long long>(0x1p63 / PI<double>)};
	[[maybe_unused]] auto radian_again4 = pcs::bam64{0x28B0000000000009};
	[[maybe_unused]] auto radian_again5 = pcs::bam64{0x0477d1a894a74e40};

	[[maybe_unused]] auto deg1 =	pcs::bam64::from_degrees(1);		// 0x00b60b60b60b60b8		threehundredsixtieth
	[[maybe_unused]] auto deg1_5 =	pcs::bam64::from_degrees(1.5);		// 0x0111111111111110		twohundredfortieth
	[[maybe_unused]] auto deg2 =	pcs::bam64::from_degrees(2);		// 0x016c16c16c16c170		hundredeightieth
	[[maybe_unused]] auto deg3 =	pcs::bam64::from_degrees(3);		// 0x0222222222222220		hundredtwentieth
	[[maybe_unused]] auto deg4 =	pcs::bam64::from_degrees(4);		// 0x02d82d82d82d82e0		ninetieth
	[[maybe_unused]] auto deg5 =	pcs::bam64::from_degrees(5);		// 0x038e38e38e38e380		seventysecond
	[[maybe_unused]] auto deg_64 =	pcs::bam64::from_degrees(5.625);	// 0x0400000000000000		sixtyfourth
	[[maybe_unused]] auto deg6 =	pcs::bam64::from_degrees(6);		// 0x0444444444444440		sixtieth
	[[maybe_unused]] auto deg7_5 =	pcs::bam64::from_degrees(7.5);		// 0x0555555555555540		fourtyeighth
	[[maybe_unused]] auto deg8 =	pcs::bam64::from_degrees(8);		// 0x05b05b05b05b05c0		fourtyfifth
	[[maybe_unused]] auto deg10 =	pcs::bam64::from_degrees(10);		// 0x071c71c71c71c700		thirtysixth
	[[maybe_unused]] auto deg_32 =	pcs::bam64::from_degrees(11.25);	// 0x0800000000000000		thirtysecond
	[[maybe_unused]] auto deg12 =	pcs::bam64::from_degrees(12);		// 0x0888888888888880		thirtieth
	[[maybe_unused]] auto deg15 =	pcs::bam64::from_degrees(15);		// 0x0aaaaaaaaaaaaa80		twentyfourth
	[[maybe_unused]] auto deg18 =	pcs::bam64::from_degrees(18);		// 0x0ccccccccccccd00		twentieth
	[[maybe_unused]] auto deg20 =	pcs::bam64::from_degrees(20);		// 0x0e38e38e38e38e00		eighteenth
	[[maybe_unused]] auto deg_16 =	pcs::bam64::from_degrees(22.5);		// 0x1000000000000000		sixteenth
	[[maybe_unused]] auto deg24 =	pcs::bam64::from_degrees(24);		// 0x1111111111111100		fifteenth
	[[maybe_unused]] auto deg30 =	pcs::bam64::from_degrees(30);		// 0x1555555555555500		twelfth
	[[maybe_unused]] auto deg36 =	pcs::bam64::from_degrees(36);		// 0x1999999999999a00		tenth
	[[maybe_unused]] auto deg45 =	pcs::bam64::from_degrees(45);		// 0x2000000000000000		eighth
	[[maybe_unused]] auto deg60 =	pcs::bam64::from_degrees(60);		// 0x2aaaaaaaaaaaaa00		sixth
	[[maybe_unused]] auto deg_67_5 =pcs::bam64::from_degrees(67.5);		// 0x3000000000000000		threesixteenths
	[[maybe_unused]] auto deg72 =	pcs::bam64::from_degrees(72);		// 0x3333333333333400		fifth
	[[maybe_unused]] auto deg90 =	pcs::bam64::from_degrees(90);		// 0x4000000000000000		fourth
	[[maybe_unused]] auto deg_112_5=pcs::bam64::from_degrees(112.5);	// 0x5000000000000000		fivesixteenths
	[[maybe_unused]] auto deg120 =	pcs::bam64::from_degrees(120);		// 0x5555555555555400		third
	[[maybe_unused]] auto deg135 =	pcs::bam64::from_degrees(135);		// 0x6000000000000000		threeeighths
	[[maybe_unused]] auto deg150 =	pcs::bam64::from_degrees(150);		// 0x6aaaaaaaaaaaac00		fivetwelfths
	[[maybe_unused]] auto deg_157_5=pcs::bam64::from_degrees(157.5);	// 0x7000000000000000		sevensixteenths
	[[maybe_unused]] auto deg180 =	pcs::bam64::from_degrees(180);		// 0x8000000000000000		half
	[[maybe_unused]] auto deg_202_5=pcs::bam64::from_degrees(202.5);	// 0x9000000000000000		ninesixteenths
	[[maybe_unused]] auto deg210 =	pcs::bam64::from_degrees(210);		// 0x9555555555555800		seventwelfths
	[[maybe_unused]] auto deg225 =	pcs::bam64::from_degrees(225);		// 0xa000000000000000		fiveeighths
	[[maybe_unused]] auto deg240 =	pcs::bam64::from_degrees(240);		// 0xaaaaaaaaaaaaa800		twothirds
	[[maybe_unused]] auto deg_247_5=pcs::bam64::from_degrees(247.5);	// 0xb000000000000000		elevensixteenths
	[[maybe_unused]] auto deg270 =	pcs::bam64::from_degrees(270);		// 0xc000000000000000		threefourths
	[[maybe_unused]] auto deg292_5 =pcs::bam64::from_degrees(292.5);	// 0xd000000000000000		thirteensixteenths
	[[maybe_unused]] auto deg300 =	pcs::bam64::from_degrees(300);		// 0xd555555555555800		fivesixths
	[[maybe_unused]] auto deg315 =	pcs::bam64::from_degrees(315);		// 0xe000000000000000		seveneighths
	[[maybe_unused]] auto deg330 =	pcs::bam64::from_degrees(330);		// 0xeaaaaaaaaaaaa800		eleventwelfths
	[[maybe_unused]] auto deg337_5 =pcs::bam64::from_degrees(337.5);	// 0xf000000000000000		fifteensixteenths

	[[maybe_unused]] auto rad =		pcs::bam64::from_radians(1);		// 0x28be60db93910600		radian
	[[maybe_unused]] auto deg =		pcs::bam64::from_degrees(1);		// 0x00b60b60b60b60b8		degree

	[[maybe_unused]] auto dd = pcs::bam64::from_radians(PI<double> / 180.0);		// 0x28be60db93910600		radian


	[[maybe_unused]] constexpr auto comp0 = (pcs::bam64::from_degrees(315) + pcs::bam64::from_degrees(22.5));
	[[maybe_unused]] auto comp1 = pcs::bam64::from_degrees(225);
	[[maybe_unused]] auto res1 = comp1.degrees_comp();
	[[maybe_unused]] auto res2 = (~comp1).degrees_full();
	[[maybe_unused]] auto res3 = comp1.degrees_norm();

	constexpr double seconds_per_hour = 3600.0;
	[[maybe_unused]] auto b1 = pcs::bam64::from_base(2400.0, seconds_per_hour);
	[[maybe_unused]] auto b2 = b1.base_full(1);
	[[maybe_unused]] auto b3 = b1.base_norm(300);
	[[maybe_unused]] auto b4 = b1.base_comp(seconds_per_hour);

	[[maybe_unused]] auto p1 = pcs::bam64::from_base(1200.0, seconds_per_hour);
	[[maybe_unused]] auto p2 = p1.base_full(1);
	[[maybe_unused]] auto p3 = p1.base_norm(300);
	[[maybe_unused]] auto p4 = p1.base_comp(seconds_per_hour);

	[[maybe_unused]] double foobar = 0x1p-64;
	[[maybe_unused]] auto foobar1 = pcs::bam64::from_degrees(-90);
	[[maybe_unused]] auto foobar2 = pcs::bam64::from_degrees(90);

	constexpr int ninety_factor = 17;
	auto ninetydegrees = pcs::tau<double> / 4.0;
	auto mult_ninety = ninetydegrees + ninety_factor * pcs::tau<double>;
	auto add_ninety = ninetydegrees;
	for (int i = 0; i < ninety_factor; ++i)
	{
		add_ninety += pcs::tau<double>;
	}
	[[maybe_unused]] auto test_ninety1 = (mult_ninety == add_ninety);

	[[maybe_unused]] auto fang1 = full_ang(mult_ninety);
	[[maybe_unused]] auto fang2 = full_ang(add_ninety);
	[[maybe_unused]] auto fang3 = ang_full(mult_ninety);
	[[maybe_unused]] auto fang4 = ang_full(add_ninety);


	[[maybe_unused]] auto threequarters = pcs::bam64(pcs::bam64::three_fourths).radians_full();

	[[maybe_unused]] auto mang1 = ang_in_minuspi_pluspi(mult_ninety);
	[[maybe_unused]] auto mang2 = ang_in_minuspi_pluspi(add_ninety);
	[[maybe_unused]] auto mang3 = ang_norm(mult_ninety);
	[[maybe_unused]] auto mang4 = ang_norm(add_ninety);

	[[maybe_unused]] auto sfang1 = full_ang(pcs::tau<double> + pcs::tau<double> - ninetydegrees);
	[[maybe_unused]] auto sfang2 = full_ang(ninetydegrees - pcs::tau<double> - pcs::tau<double>);
	[[maybe_unused]] auto sfang3 = ang_full(pcs::tau<double> + pcs::tau<double> - ninetydegrees);
	[[maybe_unused]] auto sfang4 = ang_full(ninetydegrees - pcs::tau<double> - pcs::tau<double>);

	[[maybe_unused]] auto smang1 = ang_in_minuspi_pluspi(pcs::tau<double> + pcs::tau<double> - ninetydegrees);
	[[maybe_unused]] auto smang2 = ang_in_minuspi_pluspi(ninetydegrees - pcs::tau<double> - pcs::tau<double>);
	[[maybe_unused]] auto smang3 = ang_norm(pcs::tau<double> + pcs::tau<double> - ninetydegrees);
	[[maybe_unused]] auto smang4 = ang_norm(ninetydegrees - pcs::tau<double> - pcs::tau<double>);



	auto ninetytest1 = pcs::bam64::from_radians(mult_ninety).radians_full();
	auto ninetytest2 = pcs::bam64::from_radians(mult_ninety).radians_norm();
	auto ninetytest3 = pcs::bam64::from_radians(add_ninety).radians_full();
	auto ninetytest4 = pcs::bam64::from_radians(add_ninety).radians_norm();
	[[maybe_unused]] auto test_ninety2 = (ninetytest1 == ninetytest3);
	[[maybe_unused]] auto test_ninety3 = (ninetytest2 == ninetytest4);

	// more BAMs
	// BAM tolerance w.r.t. double

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
