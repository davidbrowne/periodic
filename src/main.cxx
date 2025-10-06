
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
	pcs::bam64 some_turns{ pcs::bam64::turn::fourth };
	[[maybe_unused]] auto complement = ~some_turns;

	[[maybe_unused]] auto underlying = pcs::to_underlying(pcs::bam64::turn::radian);
	[[maybe_unused]] auto something = 360.0 * pcs::to_underlying(pcs::bam64::turn::radian) * pcs::bam64::bam_to_unit_period;

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

	[[maybe_unused]] auto degzero = pcs::bam64(pcs::bam64::turn::full).degrees_full();
	[[maybe_unused]] auto degsixtyfourth = pcs::bam64(pcs::bam64::sixty_fourth).degrees_full();
	[[maybe_unused]] auto deg32nd = pcs::bam64(pcs::bam64::turn::thirty_second).degrees_full();
	[[maybe_unused]] auto deg16th = pcs::bam64(pcs::bam64::turn::sixteenth).degrees_full();
	[[maybe_unused]] auto deg8th = pcs::bam64(pcs::bam64::turn::eighth).degrees_full();
	[[maybe_unused]] auto deg4th = pcs::bam64(pcs::bam64::turn::fourth).degrees_full();
	[[maybe_unused]] auto deghalf = pcs::bam64(pcs::bam64::turn::half);
	[[maybe_unused]] auto deghalf1 = deghalf.degrees_full();
	[[maybe_unused]] auto deghalf2 = deghalf.degrees_norm();
	[[maybe_unused]] auto deg3quarters = pcs::bam64(pcs::bam64::turn::three_quarter).degrees_full();
	[[maybe_unused]] auto deg12th = pcs::bam64(pcs::bam64::turn::twelfth).degrees_full();
	[[maybe_unused]] auto deg6th = pcs::bam64(pcs::bam64::turn::sixth).degrees_full();
	[[maybe_unused]] auto degthird = pcs::bam64(pcs::bam64::turn::third).degrees_full();
	[[maybe_unused]] auto deg5th = pcs::bam64(pcs::bam64::turn::fifth).degrees_full();

	auto deg3quarters_bam = pcs::bam64::from_degrees(270.0);
	[[maybe_unused]] auto bamtest = (~deg3quarters_bam).degrees_full();
	auto degquarter = pcs::bam64::from_degrees(90.0);
	[[maybe_unused]] auto bamtest1 = (~degquarter).degrees_full();
	auto degnegquarter = pcs::bam64::from_degrees(-90.0);
	[[maybe_unused]] auto bamtest2 = degnegquarter.degrees_full();

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

	[[maybe_unused]] auto oneradian = pcs::bam64{pcs::bam64::turn::radian};
	[[maybe_unused]] auto fifthturn = pcs::bam64{pcs::bam64::turn::fifth};
	[[maybe_unused]] auto fifteenthturn = pcs::bam64{pcs::bam64::turn::fifteenth};
	[[maybe_unused]] auto thirdturn = pcs::bam64{pcs::bam64::turn::third};
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
