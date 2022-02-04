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

		constexpr auto output_period = 360.0;
		constexpr auto output_value_shift = 0.0;
		constexpr auto output_time_shift = -180;
		constexpr auto input_period = 360.0;

		SUBCASE("total phi equality")
		{
			CHECK_EQ(period::total_phi(1.0, input_period, output_period, output_time_shift, output_value_shift),
					 period::total_reverse_phi(-1.0, input_period, output_period, output_time_shift, output_value_shift));
			CHECK_EQ(period::total_phi(0.9, input_period, output_period, output_time_shift, output_value_shift),
					 period::total_reverse_phi(-0.9, input_period, output_period, output_time_shift, output_value_shift));
			CHECK_EQ(period::total_phi(0.8, input_period, output_period, output_time_shift, output_value_shift),
					 period::total_reverse_phi(-0.8, input_period, output_period, output_time_shift, output_value_shift));
			CHECK_EQ(period::total_phi(0.7, input_period, output_period, output_time_shift, output_value_shift),
					 period::total_reverse_phi(-0.7, input_period, output_period, output_time_shift, output_value_shift));
			CHECK_EQ(period::total_phi(0.6, input_period, output_period, output_time_shift, output_value_shift),
					 period::total_reverse_phi(-0.6, input_period, output_period, output_time_shift, output_value_shift));
			CHECK_EQ(period::total_phi(0.5, input_period, output_period, output_time_shift, output_value_shift),
					 period::total_reverse_phi(-0.5, input_period, output_period, output_time_shift, output_value_shift));
			CHECK_EQ(period::total_phi(0.4, input_period, output_period, output_time_shift, output_value_shift),
					 period::total_reverse_phi(-0.4, input_period, output_period, output_time_shift, output_value_shift));
			CHECK_EQ(period::total_phi(0.3, input_period, output_period, output_time_shift, output_value_shift),
					 period::total_reverse_phi(-0.3, input_period, output_period, output_time_shift, output_value_shift));
			CHECK_EQ(period::total_phi(0.2, input_period, output_period, output_time_shift, output_value_shift),
					 period::total_reverse_phi(-0.2, input_period, output_period, output_time_shift, output_value_shift));
			CHECK_EQ(period::total_phi(0.1, input_period, output_period, output_time_shift, output_value_shift),
					 period::total_reverse_phi(-0.1, input_period, output_period, output_time_shift, output_value_shift));
			CHECK_EQ(period::total_phi(0.0, input_period, output_period, output_time_shift, output_value_shift),
					 period::total_reverse_phi(0.0, input_period, output_period, output_time_shift, output_value_shift));
			CHECK_EQ(period::total_phi(-0.1, input_period, output_period, output_time_shift, output_value_shift),
					 period::total_reverse_phi(0.1, input_period, output_period, output_time_shift, output_value_shift));
			CHECK_EQ(period::total_phi(-0.2, input_period, output_period, output_time_shift, output_value_shift),
					 period::total_reverse_phi(0.2, input_period, output_period, output_time_shift, output_value_shift));
			CHECK_EQ(period::total_phi(-0.3, input_period, output_period, output_time_shift, output_value_shift),
					 period::total_reverse_phi(0.3, input_period, output_period, output_time_shift, output_value_shift));
			CHECK_EQ(period::total_phi(-0.4, input_period, output_period, output_time_shift, output_value_shift),
					 period::total_reverse_phi(0.4, input_period, output_period, output_time_shift, output_value_shift));
			CHECK_EQ(period::total_phi(-0.5, input_period, output_period, output_time_shift, output_value_shift),
					 period::total_reverse_phi(0.5, input_period, output_period, output_time_shift, output_value_shift));
			CHECK_EQ(period::total_phi(-0.6, input_period, output_period, output_time_shift, output_value_shift),
					 period::total_reverse_phi(0.6, input_period, output_period, output_time_shift, output_value_shift));
			CHECK_EQ(period::total_phi(-0.7, input_period, output_period, output_time_shift, output_value_shift),
					 period::total_reverse_phi(0.7, input_period, output_period, output_time_shift, output_value_shift));
			CHECK_EQ(period::total_phi(-0.8, input_period, output_period, output_time_shift, output_value_shift),
					 period::total_reverse_phi(0.8, input_period, output_period, output_time_shift, output_value_shift));
			CHECK_EQ(period::total_phi(-0.9, input_period, output_period, output_time_shift, output_value_shift),
					 period::total_reverse_phi(0.9, input_period, output_period, output_time_shift, output_value_shift));
			CHECK_EQ(period::total_phi(-1.0, input_period, output_period, output_time_shift, output_value_shift),
					 period::total_reverse_phi(1.0, input_period, output_period, output_time_shift, output_value_shift));
		}
	}
}