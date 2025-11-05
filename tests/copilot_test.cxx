
//          Copyright David Browne 2025.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

//
// mostly via GitHub Copilot
//

#include <cassert>
#include <cmath>
#include <iostream>
#include <limits>

#include "bam64.hxx"
#include "doctest.h"

using pcs::bam64;

static double wrap_diff(double a, double b, double period) noexcept
{
	// Guard: period must be positive and finite
	if (!(period > 0.0) || !std::isfinite(period)) {
		return std::numeric_limits<double>::quiet_NaN();
	}

	// minimal circular difference in [0, period/2]
	double d = std::fmod(std::fabs(a - b), period);
	if (d < 0.0) d += period;				// defend against any negative fmod result (shouldn't occur with fabs)
	if (d > period * 0.5) d = period - d;	// take the shorter wrap direction
	return d;
}

TEST_SUITE("bam64 - runtime/edge cases")
{
	TEST_CASE("round-trip conversions (degrees / radians / turns / minutes / seconds)")
	{
		const double eps_deg = 1e-12;
		const double eps_rad = 1e-12;
		const double eps_turn = 1e-15;

		SUBCASE("degrees")
		{
			double v = 123.456;
			auto b = pcs::bam64_from_degrees(v);
			double v_back = pcs::to_degrees(b);
			CHECK(wrap_diff(v, v_back, pcs::full_degrees) < eps_deg);
		}

		SUBCASE("radians")
		{
			double v = 1.23456789;
			auto b = pcs::bam64_from_radians(v);
			double v_back = pcs::to_radians(b);
			CHECK(wrap_diff(v, v_back, pcs::two_pi) < eps_rad);
		}

		SUBCASE("turns")
		{
			double v = 0.3141592653589793; // fraction of a turn
			auto b = pcs::bam64_from_turns(v);
			double v_back = pcs::to_fraction(b);
			CHECK(wrap_diff(v, v_back, 1.0) < eps_turn);
		}

		SUBCASE("minutes/seconds")
		{
			double m = 7.5; // minutes (fractional part kept)
			auto b = pcs::bam64_from_minutes(m);
			double m_back = pcs::to_minutes(b);
			CHECK(wrap_diff(m, m_back, 60.0) < 1e-12);

			double s = 12.75;
			auto bs = pcs::bam64_from_seconds(s);
			double s_back = pcs::to_seconds(bs);
			CHECK(wrap_diff(s, s_back, 60.0) < 1e-12);
		}
	}

	TEST_CASE("fraction/complement/opposite/normal semantics")
	{
		auto a = pcs::bam64_from_degrees(30.0);
		double frac = a.fraction();				// in turns
		double comp = a.complement();			// complement in turns
		double opp = a.opposite();				// opposite in turns
		double normal = a.normal();				// normal in turns (range (-0.5, 0.5])

		// fraction in [0,1)
		CHECK(frac >= 0.0);
		CHECK(frac < 1.0);

		// fraction + complement == 1 (mod 1)
		double sum = std::fmod(frac + comp, 1.0);
		if (sum < 0) { sum += 1.0; }
		CHECK(sum < 1e-12);

		// opposite == fraction + 0.5 (mod 1)
		CHECK(std::fabs( std::fmod(frac + 0.5, 1.0) - opp ) < 1e-12);

		// normal should be in (-0.5, 0.5] relative to turns
		CHECK(normal > -0.5 - 1e-15);
		CHECK(normal <=  0.5 + 1e-15);
	}

	TEST_CASE("normal behavior at half boundary")
	{
		auto h = bam64::from_bam_value(pcs::half);
		// Implementation returns fraction() when value == half, so expect +0.5 turns
		CHECK(std::fabs(h.normal() - 0.5) < 1e-15);
	}

	TEST_CASE("large-value wrapping (many whole turns)")
	{
		double small = 0.123456789; // radians < 2*pi
		double big = small + 1e6 * pcs::two_pi; // many whole turns
		auto b_big = pcs::bam64_from_radians(big);
		auto b_small = pcs::bam64_from_radians(small);
		auto diff = b_big - b_small;
		auto check_val = diff.within_tolerance(pcs::bam64_from_turns(1e-10));
		CHECK(check_val);
	}

	TEST_CASE("wrap-around proximity across 0/2^64 boundary")
	{
		// 1 and ULL_MAX should be close when considered circularly with small tolerance
		auto a = bam64::from_bam_value(1ULL);
		auto b = bam64::from_bam_value(std::numeric_limits<unsigned long long>::max());
		// tolerance = 2 units should consider them within distance
		auto tol = bam64::from_bam_value(2ULL);
		CHECK(pcs::within_distance(a, b, tol));
	}

	TEST_CASE("ordering and equality")
	{
		auto x = pcs::bam64_from_degrees(10.0);
		auto y = pcs::bam64_from_degrees(20.0);
		CHECK(x < y);
		CHECK(x == x);
		CHECK_FALSE(x == y);
		CHECK((x <=> y) == std::strong_ordering::less);
	}

	TEST_CASE("alternate 53-bit helpers (to_fraction_alt / to_bam_value_alt)")
	{
		// Choose representative bam values (some small, some large, some mid)
		unsigned long long samples[] = {
			0ULL,
			1ULL,
			0x00000000000007FFULL, // low region, just below epsilon
			0x0000000000000800ULL, // epsilon
			0x0000FFFFFFFFFFFFULL,
			0x7FFFFFFFFFFFFFFFULL,
			std::numeric_limits<unsigned long long>::max()
		};

		for (auto u : samples)
		{
			// alt double captures top 53 bits
			double d = pcs::to_fraction_alt(u);
			unsigned long long u2 = pcs::to_bam_value_alt(d);

			// Upper 53 bits (value >> 11) should match after round-trip
			CHECK((u >> 11) == (u2 >> 11));
		}

		// to_bam_value_alt should normalize fractional input
		double negative = -0.25;
		unsigned long long u_neg = pcs::to_bam_value_alt(negative);
		// negative -0.25 -> fractional 0.75 -> bam > 0
		CHECK(u_neg != 0ULL);
	}

	TEST_CASE("edge - extremes and finiteness")
	{
		// near maximum bam value
		auto near_high = bam64::from_bam_value(std::numeric_limits<unsigned long long>::max() - 1ULL);
		double frac = near_high.fraction();
		double comp = near_high.complement();
		CHECK(std::isfinite(frac));
		CHECK(std::isfinite(comp));

		// ensure fraction is in [0,1] instead of [0,1), because unfortunately values really close to 1 are represented as 1
		CHECK(frac >= 0.0);
		CHECK(frac < 1.0);
	}

	TEST_CASE("binary operators wrap semantics")
	{
		auto h = bam64::from_bam_value(pcs::half);
		auto sum = h + h; // wrap expected
		CHECK(sum.value == 0ULL);

		auto one = bam64::from_bam_value(1ULL);
		auto large = bam64::from_bam_value(std::numeric_limits<unsigned long long>::max());
		auto diff = one - large; // modular subtraction
		// diff should be 2 (1 - ULL_MAX => wraps to 2)
		CHECK(diff.value == 2ULL);
	}
}
