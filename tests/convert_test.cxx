
//          Copyright David Browne 2021-2025.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#include "periodic.hxx"

//#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

TEST_SUITE("test pcs")
{
	TEST_CASE("forward and reverse")
	{

		constexpr auto output_period = 1.0;						// output period
		constexpr auto output_min = -0.5;						// minimum value of periodic output range
		constexpr auto input_period = 1.0;						// input period
		constexpr auto input_origin = 0.25;						// input origin in output units

		SUBCASE("forward/reverse equality with reverse inputs")
		{
			CHECK_EQ(pcs::forward_convert(1.0, input_period, input_origin, output_min, output_period),
					 pcs::reverse_convert(-1.0, input_period, input_origin, output_min, output_period));
			CHECK_EQ(pcs::forward_convert(0.9, input_period, input_origin, output_min, output_period),
					 pcs::reverse_convert(-0.9, input_period, input_origin, output_min, output_period));
			CHECK_EQ(pcs::forward_convert(0.8, input_period, input_origin, output_min, output_period),
					 pcs::reverse_convert(-0.8, input_period, input_origin, output_min, output_period));
			CHECK_EQ(pcs::forward_convert(0.7, input_period, input_origin, output_min, output_period),
					 pcs::reverse_convert(-0.7, input_period, input_origin, output_min, output_period));
			CHECK_EQ(pcs::forward_convert(0.6, input_period, input_origin, output_min, output_period),
					 pcs::reverse_convert(-0.6, input_period, input_origin, output_min, output_period));
			CHECK_EQ(pcs::forward_convert(0.5, input_period, input_origin, output_min, output_period),
					 pcs::reverse_convert(-0.5, input_period, input_origin, output_min, output_period));
			CHECK_EQ(pcs::forward_convert(0.4, input_period, input_origin, output_min, output_period),
					 pcs::reverse_convert(-0.4, input_period, input_origin, output_min, output_period));
			CHECK_EQ(pcs::forward_convert(0.3, input_period, input_origin, output_min, output_period),
					 pcs::reverse_convert(-0.3, input_period, input_origin, output_min, output_period));
			CHECK_EQ(pcs::forward_convert(0.2, input_period, input_origin, output_min, output_period),
					 pcs::reverse_convert(-0.2, input_period, input_origin, output_min, output_period));
			CHECK_EQ(pcs::forward_convert(0.1, input_period, input_origin, output_min, output_period),
					 pcs::reverse_convert(-0.1, input_period, input_origin, output_min, output_period));
			CHECK_EQ(pcs::forward_convert(0.0, input_period, input_origin, output_min, output_period),
					 pcs::reverse_convert(0.0, input_period, input_origin, output_min, output_period));
			CHECK_EQ(pcs::forward_convert(-0.1, input_period, input_origin, output_min, output_period),
					 pcs::reverse_convert(0.1, input_period, input_origin, output_min, output_period));
			CHECK_EQ(pcs::forward_convert(-0.2, input_period, input_origin, output_min, output_period),
					 pcs::reverse_convert(0.2, input_period, input_origin, output_min, output_period));
			CHECK_EQ(pcs::forward_convert(-0.3, input_period, input_origin, output_min, output_period),
					 pcs::reverse_convert(0.3, input_period, input_origin, output_min, output_period));
			CHECK_EQ(pcs::forward_convert(-0.4, input_period, input_origin, output_min, output_period),
					 pcs::reverse_convert(0.4, input_period, input_origin, output_min, output_period));
			CHECK_EQ(pcs::forward_convert(-0.5, input_period, input_origin, output_min, output_period),
					 pcs::reverse_convert(0.5, input_period, input_origin, output_min, output_period));
			CHECK_EQ(pcs::forward_convert(-0.6, input_period, input_origin, output_min, output_period),
					 pcs::reverse_convert(0.6, input_period, input_origin, output_min, output_period));
			CHECK_EQ(pcs::forward_convert(-0.7, input_period, input_origin, output_min, output_period),
					 pcs::reverse_convert(0.7, input_period, input_origin, output_min, output_period));
			CHECK_EQ(pcs::forward_convert(-0.8, input_period, input_origin, output_min, output_period),
					 pcs::reverse_convert(0.8, input_period, input_origin, output_min, output_period));
			CHECK_EQ(pcs::forward_convert(-0.9, input_period, input_origin, output_min, output_period),
					 pcs::reverse_convert(0.9, input_period, input_origin, output_min, output_period));
			CHECK_EQ(pcs::forward_convert(-1.0, input_period, input_origin, output_min, output_period),
					 pcs::reverse_convert(1.0, input_period, input_origin, output_min, output_period));
		}

	}
}