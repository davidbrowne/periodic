#include "periodic.hxx"

//#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

TEST_SUITE("test phi")
{
	TEST_CASE("forward and reverse")
	{
		SUBCASE("basic phi equality")
		{
			CHECK_EQ(period::basic_phi(1.0, -0.5), period::basic_reverse_phi(-1.0, -0.5));
			CHECK_EQ(period::basic_phi(0.9, -0.5), period::basic_reverse_phi(-0.9, -0.5));
			CHECK_EQ(period::basic_phi(0.8, -0.5), period::basic_reverse_phi(-0.8, -0.5));
			CHECK_EQ(period::basic_phi(0.7, -0.5), period::basic_reverse_phi(-0.7, -0.5));
			CHECK_EQ(period::basic_phi(0.6, -0.5), period::basic_reverse_phi(-0.6, -0.5));
			CHECK_EQ(period::basic_phi(0.5, -0.5), period::basic_reverse_phi(-0.5, -0.5));
			CHECK_EQ(period::basic_phi(0.4, -0.5), period::basic_reverse_phi(-0.4, -0.5));
			CHECK_EQ(period::basic_phi(0.3, -0.5), period::basic_reverse_phi(-0.3, -0.5));
			CHECK_EQ(period::basic_phi(0.2, -0.5), period::basic_reverse_phi(-0.2, -0.5));
			CHECK_EQ(period::basic_phi(0.1, -0.5), period::basic_reverse_phi(-0.1, -0.5));
			CHECK_EQ(period::basic_phi( 0.0, -0.5), period::basic_reverse_phi(0.0, -0.5));
			CHECK_EQ(period::basic_phi(-0.1, -0.5), period::basic_reverse_phi(0.1, -0.5));
			CHECK_EQ(period::basic_phi(-0.2, -0.5), period::basic_reverse_phi(0.2, -0.5));
			CHECK_EQ(period::basic_phi(-0.3, -0.5), period::basic_reverse_phi(0.3, -0.5));
			CHECK_EQ(period::basic_phi(-0.4, -0.5), period::basic_reverse_phi(0.4, -0.5));
			CHECK_EQ(period::basic_phi(-0.5, -0.5), period::basic_reverse_phi(0.5, -0.5));
			CHECK_EQ(period::basic_phi(-0.6, -0.5), period::basic_reverse_phi(0.6, -0.5));
			CHECK_EQ(period::basic_phi(-0.7, -0.5), period::basic_reverse_phi(0.7, -0.5));
			CHECK_EQ(period::basic_phi(-0.8, -0.5), period::basic_reverse_phi(0.8, -0.5));
			CHECK_EQ(period::basic_phi(-0.9, -0.5), period::basic_reverse_phi(0.9, -0.5));
			CHECK_EQ(period::basic_phi(-1.0, -0.5), period::basic_reverse_phi(1.0, -0.5));
		}

		constexpr auto output_period = 1.0;						// output period - amplitude scale
		constexpr auto output_value_shift = 0.0;				// linear shift on output
		constexpr auto output_time_shift = -0.5;				// minimum value of periodic output range
		constexpr auto input_period = 1.0;						// input period
		constexpr auto input_time_scale = 1.0;					// 0 < abs(x) < 1.0 is time expansion, abs(x) > 1.0 is time compression, x < 0 is time reversal
		constexpr auto reverse_input_time_scale = -input_time_scale;			// example of time reversal 
		constexpr auto period_offset = 0.0;						// output period amount to periodic offset
		constexpr auto input_value_shift = 0.0;					// linear shift on input

		SUBCASE("total phi equality")
		{
			CHECK_EQ(period::total_phi(1.0, input_time_scale, input_period, input_value_shift, output_period, output_time_shift, output_value_shift, period_offset),
					 period::total_reverse_phi(-1.0, input_time_scale, input_period, input_value_shift, output_period, output_time_shift, output_value_shift, period_offset));
			CHECK_EQ(period::total_phi(0.9, input_time_scale, input_period, input_value_shift, output_period, output_time_shift, output_value_shift, period_offset),
					 period::total_reverse_phi(-0.9, input_time_scale, input_period, input_value_shift, output_period, output_time_shift, output_value_shift, period_offset));
			CHECK_EQ(period::total_phi(0.8, input_time_scale, input_period, input_value_shift, output_period, output_time_shift, output_value_shift, period_offset),
					 period::total_reverse_phi(-0.8, input_time_scale, input_period, input_value_shift, output_period, output_time_shift, output_value_shift, period_offset));
			CHECK_EQ(period::total_phi(0.7, input_time_scale, input_period, input_value_shift, output_period, output_time_shift, output_value_shift, period_offset),
					 period::total_reverse_phi(-0.7, input_time_scale, input_period, input_value_shift, output_period, output_time_shift, output_value_shift, period_offset));
			CHECK_EQ(period::total_phi(0.6, input_time_scale, input_period, input_value_shift, output_period, output_time_shift, output_value_shift, period_offset),
					 period::total_reverse_phi(-0.6, input_time_scale, input_period, input_value_shift, output_period, output_time_shift, output_value_shift, period_offset));
			CHECK_EQ(period::total_phi(0.5, input_time_scale, input_period, input_value_shift, output_period, output_time_shift, output_value_shift, period_offset),
					 period::total_reverse_phi(-0.5, input_time_scale, input_period, input_value_shift, output_period, output_time_shift, output_value_shift, period_offset));
			CHECK_EQ(period::total_phi(0.4, input_time_scale, input_period, input_value_shift, output_period, output_time_shift, output_value_shift, period_offset),
					 period::total_reverse_phi(-0.4, input_time_scale, input_period, input_value_shift, output_period, output_time_shift, output_value_shift, period_offset));
			CHECK_EQ(period::total_phi(0.3, input_time_scale, input_period, input_value_shift, output_period, output_time_shift, output_value_shift, period_offset),
					 period::total_reverse_phi(-0.3, input_time_scale, input_period, input_value_shift, output_period, output_time_shift, output_value_shift, period_offset));
			CHECK_EQ(period::total_phi(0.2, input_time_scale, input_period, input_value_shift, output_period, output_time_shift, output_value_shift, period_offset),
					 period::total_reverse_phi(-0.2, input_time_scale, input_period, input_value_shift, output_period, output_time_shift, output_value_shift, period_offset));
			CHECK_EQ(period::total_phi(0.1, input_time_scale, input_period, input_value_shift, output_period, output_time_shift, output_value_shift, period_offset),
					 period::total_reverse_phi(-0.1, input_time_scale, input_period, input_value_shift, output_period, output_time_shift, output_value_shift, period_offset));
			CHECK_EQ(period::total_phi(0.0, input_time_scale, input_period, input_value_shift, output_period, output_time_shift, output_value_shift, period_offset),
					 period::total_reverse_phi(0.0, input_time_scale, input_period, input_value_shift, output_period, output_time_shift, output_value_shift, period_offset));
			CHECK_EQ(period::total_phi(-0.1, input_time_scale, input_period, input_value_shift, output_period, output_time_shift, output_value_shift, period_offset),
					 period::total_reverse_phi(0.1, input_time_scale, input_period, input_value_shift, output_period, output_time_shift, output_value_shift, period_offset));
			CHECK_EQ(period::total_phi(-0.2, input_time_scale, input_period, input_value_shift, output_period, output_time_shift, output_value_shift, period_offset),
					 period::total_reverse_phi(0.2, input_time_scale, input_period, input_value_shift, output_period, output_time_shift, output_value_shift, period_offset));
			CHECK_EQ(period::total_phi(-0.3, input_time_scale, input_period, input_value_shift, output_period, output_time_shift, output_value_shift, period_offset),
					 period::total_reverse_phi(0.3, input_time_scale, input_period, input_value_shift, output_period, output_time_shift, output_value_shift, period_offset));
			CHECK_EQ(period::total_phi(-0.4, input_time_scale, input_period, input_value_shift, output_period, output_time_shift, output_value_shift, period_offset),
					 period::total_reverse_phi(0.4, input_time_scale, input_period, input_value_shift, output_period, output_time_shift, output_value_shift, period_offset));
			CHECK_EQ(period::total_phi(-0.5, input_time_scale, input_period, input_value_shift, output_period, output_time_shift, output_value_shift, period_offset),
					 period::total_reverse_phi(0.5, input_time_scale, input_period, input_value_shift, output_period, output_time_shift, output_value_shift, period_offset));
			CHECK_EQ(period::total_phi(-0.6, input_time_scale, input_period, input_value_shift, output_period, output_time_shift, output_value_shift, period_offset),
					 period::total_reverse_phi(0.6, input_time_scale, input_period, input_value_shift, output_period, output_time_shift, output_value_shift, period_offset));
			CHECK_EQ(period::total_phi(-0.7, input_time_scale, input_period, input_value_shift, output_period, output_time_shift, output_value_shift, period_offset),
					 period::total_reverse_phi(0.7, input_time_scale, input_period, input_value_shift, output_period, output_time_shift, output_value_shift, period_offset));
			CHECK_EQ(period::total_phi(-0.8, input_time_scale, input_period, input_value_shift, output_period, output_time_shift, output_value_shift, period_offset),
					 period::total_reverse_phi(0.8, input_time_scale, input_period, input_value_shift, output_period, output_time_shift, output_value_shift, period_offset));
			CHECK_EQ(period::total_phi(-0.9, input_time_scale, input_period, input_value_shift, output_period, output_time_shift, output_value_shift, period_offset),
					 period::total_reverse_phi(0.9, input_time_scale, input_period, input_value_shift, output_period, output_time_shift, output_value_shift, period_offset));
			CHECK_EQ(period::total_phi(-1.0, input_time_scale, input_period, input_value_shift, output_period, output_time_shift, output_value_shift, period_offset),
					 period::total_reverse_phi(1.0, input_time_scale, input_period, input_value_shift, output_period, output_time_shift, output_value_shift, period_offset));
		}

		SUBCASE("reverse_input_time_scale")
		{
			CHECK_EQ(period::total_phi(1.0, input_time_scale, input_period, input_value_shift, output_period, output_time_shift, output_value_shift, period_offset),
					 period::total_reverse_phi(1.0, reverse_input_time_scale, input_period, input_value_shift, output_period, output_time_shift, output_value_shift, period_offset));
			CHECK_EQ(period::total_phi(0.9, input_time_scale, input_period, input_value_shift, output_period, output_time_shift, output_value_shift, period_offset),
					 period::total_reverse_phi(0.9, reverse_input_time_scale, input_period, input_value_shift, output_period, output_time_shift, output_value_shift, period_offset));
			CHECK_EQ(period::total_phi(0.8, input_time_scale, input_period, input_value_shift, output_period, output_time_shift, output_value_shift, period_offset),
					 period::total_reverse_phi(0.8, reverse_input_time_scale, input_period, input_value_shift, output_period, output_time_shift, output_value_shift, period_offset));
			CHECK_EQ(period::total_phi(0.7, input_time_scale, input_period, input_value_shift, output_period, output_time_shift, output_value_shift, period_offset),
					 period::total_reverse_phi(0.7, reverse_input_time_scale, input_period, input_value_shift, output_period, output_time_shift, output_value_shift, period_offset));
			CHECK_EQ(period::total_phi(0.6, input_time_scale, input_period, input_value_shift, output_period, output_time_shift, output_value_shift, period_offset),
					 period::total_reverse_phi(0.6, reverse_input_time_scale, input_period, input_value_shift, output_period, output_time_shift, output_value_shift, period_offset));
			CHECK_EQ(period::total_phi(0.5, input_time_scale, input_period, input_value_shift, output_period, output_time_shift, output_value_shift, period_offset),
					 period::total_reverse_phi(0.5, reverse_input_time_scale, input_period, input_value_shift, output_period, output_time_shift, output_value_shift, period_offset));
			CHECK_EQ(period::total_phi(0.4, input_time_scale, input_period, input_value_shift, output_period, output_time_shift, output_value_shift, period_offset),
					 period::total_reverse_phi(0.4, reverse_input_time_scale, input_period, input_value_shift, output_period, output_time_shift, output_value_shift, period_offset));
			CHECK_EQ(period::total_phi(0.3, input_time_scale, input_period, input_value_shift, output_period, output_time_shift, output_value_shift, period_offset),
					 period::total_reverse_phi(0.3, reverse_input_time_scale, input_period, input_value_shift, output_period, output_time_shift, output_value_shift, period_offset));
			CHECK_EQ(period::total_phi(0.2, input_time_scale, input_period, input_value_shift, output_period, output_time_shift, output_value_shift, period_offset),
					 period::total_reverse_phi(0.2, reverse_input_time_scale, input_period, input_value_shift, output_period, output_time_shift, output_value_shift, period_offset));
			CHECK_EQ(period::total_phi(0.1, input_time_scale, input_period, input_value_shift, output_period, output_time_shift, output_value_shift, period_offset),
					 period::total_reverse_phi(0.1, reverse_input_time_scale, input_period, input_value_shift, output_period, output_time_shift, output_value_shift, period_offset));
			CHECK_EQ(period::total_phi(0.0, input_time_scale, input_period, input_value_shift, output_period, output_time_shift, output_value_shift, period_offset),
					 period::total_reverse_phi(0.0, reverse_input_time_scale, input_period, input_value_shift, output_period, output_time_shift, output_value_shift, period_offset));
			CHECK_EQ(period::total_phi(0.1, reverse_input_time_scale, input_period, input_value_shift, output_period, output_time_shift, output_value_shift, period_offset),
					 period::total_reverse_phi(0.1, input_time_scale, input_period, input_value_shift, output_period, output_time_shift, output_value_shift, period_offset));
			CHECK_EQ(period::total_phi(0.2, reverse_input_time_scale, input_period, input_value_shift, output_period, output_time_shift, output_value_shift, period_offset),
					 period::total_reverse_phi(0.2, input_time_scale, input_period, input_value_shift, output_period, output_time_shift, output_value_shift, period_offset));
			CHECK_EQ(period::total_phi(0.3, reverse_input_time_scale, input_period, input_value_shift, output_period, output_time_shift, output_value_shift, period_offset),
					 period::total_reverse_phi(0.3, input_time_scale, input_period, input_value_shift, output_period, output_time_shift, output_value_shift, period_offset));
			CHECK_EQ(period::total_phi(0.4, reverse_input_time_scale, input_period, input_value_shift, output_period, output_time_shift, output_value_shift, period_offset),
					 period::total_reverse_phi(0.4, input_time_scale, input_period, input_value_shift, output_period, output_time_shift, output_value_shift, period_offset));
			CHECK_EQ(period::total_phi(0.5, reverse_input_time_scale, input_period, input_value_shift, output_period, output_time_shift, output_value_shift, period_offset),
					 period::total_reverse_phi(0.5, input_time_scale, input_period, input_value_shift, output_period, output_time_shift, output_value_shift, period_offset));
			CHECK_EQ(period::total_phi(0.6, reverse_input_time_scale, input_period, input_value_shift, output_period, output_time_shift, output_value_shift, period_offset),
					 period::total_reverse_phi(0.6, input_time_scale, input_period, input_value_shift, output_period, output_time_shift, output_value_shift, period_offset));
			CHECK_EQ(period::total_phi(0.7, reverse_input_time_scale, input_period, input_value_shift, output_period, output_time_shift, output_value_shift, period_offset),
					 period::total_reverse_phi(0.7, input_time_scale, input_period, input_value_shift, output_period, output_time_shift, output_value_shift, period_offset));
			CHECK_EQ(period::total_phi(0.8, reverse_input_time_scale, input_period, input_value_shift, output_period, output_time_shift, output_value_shift, period_offset),
					 period::total_reverse_phi(0.8, input_time_scale, input_period, input_value_shift, output_period, output_time_shift, output_value_shift, period_offset));
			CHECK_EQ(period::total_phi(0.9, reverse_input_time_scale, input_period, input_value_shift, output_period, output_time_shift, output_value_shift, period_offset),
					 period::total_reverse_phi(0.9, input_time_scale, input_period, input_value_shift, output_period, output_time_shift, output_value_shift, period_offset));
			CHECK_EQ(period::total_phi(1.0, reverse_input_time_scale, input_period, input_value_shift, output_period, output_time_shift, output_value_shift, period_offset),
					 period::total_reverse_phi(1.0, input_time_scale, input_period, input_value_shift, output_period, output_time_shift, output_value_shift, period_offset));
		}

	}
}