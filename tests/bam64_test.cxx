
//          Copyright David Browne 2025.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#include "bam64.hxx"

//#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

TEST_SUITE("test bam64")
{
	TEST_CASE("builders and constructors")
	{
		SUBCASE("builders")
		{
			// static class method builders
			auto three_quarters = pcs::bam64::from_bam_value(pcs::three_fourths);
			auto from_bam64_base_val = pcs::bam64::from_base(45, pcs::detail::second_base);

			// builders from outside the class
			auto from_turns_val = pcs::bam64_from_turns(0.75);
			auto from_minutes_val = pcs::bam64_from_minutes(45);
			auto from_second_val = pcs::bam64_from_seconds(45);
			auto from_degrees_val = pcs::bam64_from_degrees(270);
			auto from_radians_val = pcs::bam64_from_radians(pcs::pi * 1.5);
			auto from_base_val = pcs::bam64_from_base(270, pcs::detail::degree_base);

			// all these should be equal
			CHECK_EQ(three_quarters.value, 0xC000000000000000);
			CHECK_EQ(pcs::to_fraction(three_quarters), 0.75);

			CHECK_EQ(three_quarters, from_bam64_base_val);
			CHECK_EQ(from_bam64_base_val, from_turns_val);
			CHECK_EQ(from_turns_val, from_minutes_val);
			CHECK_EQ(from_minutes_val, from_second_val);
			CHECK_EQ(from_second_val, from_degrees_val);
			CHECK_EQ(from_degrees_val, from_radians_val);
			CHECK_EQ(from_radians_val, from_base_val);
		}

		SUBCASE("initialization")
		{
			// pcs::bam64 has no defined constructors
			[[maybe_unused]] pcs::bam64 default_ctor;

			// designated initialization
			auto named_value_bam = pcs::bam64{ .value = 0x4000000000000000 };
			CHECK_EQ(pcs::to_radians(named_value_bam), pcs::half_pi);
		}
	}

	TEST_CASE("bam value")
	{
		auto val1 = pcs::bam64::from_bam_value(pcs::fifth);
		auto val2 = pcs::bam64_from_degrees(72.0);
		CHECK_EQ(val1, val2);
	}

	TEST_CASE("conversion")
	{
		auto val1 = pcs::bam64_from_degrees(270.0);
		CHECK_EQ(val1.fraction(), 0.75);
		CHECK_EQ(val1.complement(), 0.25);
		CHECK_EQ(val1.opposite(), 0.25);
		CHECK_EQ(val1.normal(), -0.25);

		CHECK_EQ(pcs::to_fraction(val1), 0.75);
		CHECK_EQ(pcs::to_minutes(val1), 45.0);
		CHECK_EQ(pcs::to_seconds(val1), 45.0);
		CHECK_EQ(pcs::to_degrees(val1), 270.0);
		CHECK_EQ(pcs::to_radians(val1), pcs::pi * 1.5);
		CHECK_EQ(pcs::to_base(val1, 100.0), 75.0);

		CHECK_EQ(pcs::to_fraction_complement(val1), 0.25);
		CHECK_EQ(pcs::to_minutes_complement(val1), 15.0);
		CHECK_EQ(pcs::to_seconds_complement(val1), 15.0);
		CHECK_EQ(pcs::to_degrees_complement(val1), 90.0);
		CHECK_EQ(pcs::to_radians_complement(val1), pcs::pi / 2.0);
		CHECK_EQ(pcs::to_base_complement(val1, 100.0), 25.0);

		CHECK_EQ(pcs::to_fraction_opposite(val1), 0.25);
		CHECK_EQ(pcs::to_minutes_opposite(val1), 15.0);
		CHECK_EQ(pcs::to_seconds_opposite(val1), 15.0);
		CHECK_EQ(pcs::to_degrees_opposite(val1), 90.0);
		CHECK_EQ(pcs::to_radians_opposite(val1), pcs::pi / 2.0);
		CHECK_EQ(pcs::to_base_opposite(val1, 100.0), 25.0);

		CHECK_EQ(pcs::to_fraction_normal(val1), -0.25);
		CHECK_EQ(pcs::to_minutes_normal(val1), -15.0);
		CHECK_EQ(pcs::to_seconds_normal(val1), -15.0);
		CHECK_EQ(pcs::to_degrees_normal(val1), -90.0);
		CHECK_EQ(pcs::to_radians_normal(val1), -pcs::pi / 2.0);
		CHECK_EQ(pcs::to_base_normal(val1, 100.0), -25.0);
	}

	TEST_CASE("operators")
	{
		pcs::bam64 a = pcs::bam64_from_degrees(60.0);
		pcs::bam64 b = pcs::bam64_from_degrees(-45.0);

		// unary

		CHECK_UNARY(+a == a);						// clone
		CHECK_EQ((~b).value, 0x2000000000000000);	// complement
		CHECK_EQ((-b).value, 0x6000000000000000);	// opposite

		// binary

		pcs::bam64 c = a + b;
		CHECK_UNARY(pcs::within_distance(c, pcs::bam64_from_degrees(15.0), pcs::bam64::from_bam_value(pcs::epsilon)));

		pcs::bam64 d = a - b;
		CHECK_UNARY(pcs::within_distance(d, pcs::bam64_from_degrees(105.0), pcs::bam64::from_bam_value(pcs::epsilon)));

		CHECK_EQ(a * 4, 4 * a);
		CHECK_EQ(a * 4, pcs::bam64_from_degrees(240.0));

		CHECK_EQ(a / 4, pcs::bam64_from_degrees(15.0));
	}

	TEST_CASE("comparisons")
	{
		// ordering and equality
		auto a = pcs::bam64_from_degrees(10.0);
		auto b = pcs::bam64_from_degrees(177.0);
		CHECK_UNARY(a < b);
		CHECK_UNARY((a == a) && (a != b));

		CHECK_EQ(pcs::bam64_from_degrees(0.0), pcs::bam64_from_degrees(360.0));

		auto c = pcs::bam64_from_degrees(20.0);
		auto d = pcs::bam64_from_degrees(380.0);
		CHECK_UNARY(c > a);
		CHECK_UNARY(c != d);						// in this case, raw values differ even though they represent the same angle
		CHECK_UNARY(pcs::within_distance(c, d, pcs::bam64::from_bam_value(pcs::epsilon)));
		auto diff = c - d;
		CHECK_UNARY(diff.within_tolerance(pcs::bam64::from_bam_value(pcs::epsilon)));

		auto e = pcs::bam64_from_radians(pcs::pi / 4.0);
		auto f = pcs::bam64_from_degrees(405);
		CHECK_UNARY(e <= f);
		CHECK_UNARY(e >= f);
		CHECK_UNARY(e == f);						// in this case, raw values don't differ while they represent the same angle
		CHECK_UNARY(pcs::within_distance(e, f, pcs::bam64::from_bam_value(pcs::epsilon)));
	}
}
