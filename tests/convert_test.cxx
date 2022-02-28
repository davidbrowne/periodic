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
		constexpr auto output_origin = 0.0;						// output origin in input units

		SUBCASE("forward/reverse equality with reverse inputs")
		{
			CHECK_EQ(pcs::forward_convert(1.0, output_origin, input_period, output_min, output_period),
					 pcs::reverse_convert(-1.0, output_origin, input_period, output_min, output_period));
			CHECK_EQ(pcs::forward_convert(0.9, output_origin, input_period, output_min, output_period),
					 pcs::reverse_convert(-0.9, output_origin, input_period, output_min, output_period));
			CHECK_EQ(pcs::forward_convert(0.8, output_origin, input_period, output_min, output_period),
					 pcs::reverse_convert(-0.8, output_origin, input_period, output_min, output_period));
			CHECK_EQ(pcs::forward_convert(0.7, output_origin, input_period, output_min, output_period),
					 pcs::reverse_convert(-0.7, output_origin, input_period, output_min, output_period));
			CHECK_EQ(pcs::forward_convert(0.6, output_origin, input_period, output_min, output_period),
					 pcs::reverse_convert(-0.6, output_origin, input_period, output_min, output_period));
			CHECK_EQ(pcs::forward_convert(0.5, output_origin, input_period, output_min, output_period),
					 pcs::reverse_convert(-0.5, output_origin, input_period, output_min, output_period));
			CHECK_EQ(pcs::forward_convert(0.4, output_origin, input_period, output_min, output_period),
					 pcs::reverse_convert(-0.4, output_origin, input_period, output_min, output_period));
			CHECK_EQ(pcs::forward_convert(0.3, output_origin, input_period, output_min, output_period),
					 pcs::reverse_convert(-0.3, output_origin, input_period, output_min, output_period));
			CHECK_EQ(pcs::forward_convert(0.2, output_origin, input_period, output_min, output_period),
					 pcs::reverse_convert(-0.2, output_origin, input_period, output_min, output_period));
			CHECK_EQ(pcs::forward_convert(0.1, output_origin, input_period, output_min, output_period),
					 pcs::reverse_convert(-0.1, output_origin, input_period, output_min, output_period));
			CHECK_EQ(pcs::forward_convert(0.0, output_origin, input_period, output_min, output_period),
					 pcs::reverse_convert(0.0, output_origin, input_period, output_min, output_period));
			CHECK_EQ(pcs::forward_convert(-0.1, output_origin, input_period, output_min, output_period),
					 pcs::reverse_convert(0.1, output_origin, input_period, output_min, output_period));
			CHECK_EQ(pcs::forward_convert(-0.2, output_origin, input_period, output_min, output_period),
					 pcs::reverse_convert(0.2, output_origin, input_period, output_min, output_period));
			CHECK_EQ(pcs::forward_convert(-0.3, output_origin, input_period, output_min, output_period),
					 pcs::reverse_convert(0.3, output_origin, input_period, output_min, output_period));
			CHECK_EQ(pcs::forward_convert(-0.4, output_origin, input_period, output_min, output_period),
					 pcs::reverse_convert(0.4, output_origin, input_period, output_min, output_period));
			CHECK_EQ(pcs::forward_convert(-0.5, output_origin, input_period, output_min, output_period),
					 pcs::reverse_convert(0.5, output_origin, input_period, output_min, output_period));
			CHECK_EQ(pcs::forward_convert(-0.6, output_origin, input_period, output_min, output_period),
					 pcs::reverse_convert(0.6, output_origin, input_period, output_min, output_period));
			CHECK_EQ(pcs::forward_convert(-0.7, output_origin, input_period, output_min, output_period),
					 pcs::reverse_convert(0.7, output_origin, input_period, output_min, output_period));
			CHECK_EQ(pcs::forward_convert(-0.8, output_origin, input_period, output_min, output_period),
					 pcs::reverse_convert(0.8, output_origin, input_period, output_min, output_period));
			CHECK_EQ(pcs::forward_convert(-0.9, output_origin, input_period, output_min, output_period),
					 pcs::reverse_convert(0.9, output_origin, input_period, output_min, output_period));
			CHECK_EQ(pcs::forward_convert(-1.0, output_origin, input_period, output_min, output_period),
					 pcs::reverse_convert(1.0, output_origin, input_period, output_min, output_period));
		}

	}
}