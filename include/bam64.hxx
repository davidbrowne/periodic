
//          Copyright David Browne 2025.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

// opening include guard
#if !defined(PCS_BAM64_HXX)
#define PCS_BAM64_HXX

#include <compare>
#include <numbers>

namespace pcs
{
	//          Copyright David Browne 2025.
	// Distributed under the Boost Software License, Version 1.0.
	//    (See accompanying file LICENSE_1_0.txt or copy at
	//          https://www.boost.org/LICENSE_1_0.txt)

	// version info

	constexpr inline int BAM64_MAJOR_VERSION = 0;
	constexpr inline int BAM64_MINOR_VERSION = 1;
	constexpr inline int BAM64_PATCH_VERSION = 0;

	// radian related constants
	inline static constexpr double two_pi =			2.0 * std::numbers::pi_v<double>;	// 6.283185307179586476925286766559005768
	inline static constexpr double tau =			two_pi;
	inline static constexpr double pi =				std::numbers::pi_v<double>;			// 3.141592653589793238462643383279502884
	inline static constexpr double half_pi =		pi / 2.0;

	// degree related constants
	inline static constexpr double half_degrees =	180.0;
	inline static constexpr double full_degrees =	360.0;

	// detail namespace for helper functions
	namespace detail
	{
		// constants for converting to/from degrees, radians, turns, time units, etc.
		inline static constexpr double turn_base =		1.0;					//   1 turn		-> 1 period
		inline static constexpr double minute_base =	60.0;					//  60 minutes	-> 1 hour
		inline static constexpr double second_base =	60.0;					//  60 seconds	-> 1 minute
		inline static constexpr double degree_base =	pcs::full_degrees;		// 360 degrees	-> 1 circle
		inline static constexpr double radian_base =	pcs::two_pi;			// 2pi radians	-> 1 circle

		// truncate towards zero
		inline constexpr double trunc(double value) noexcept			{ return static_cast<double>(static_cast<long long>(value)); }

		// fractional part of value
		inline constexpr double fmod(double x, double y) noexcept		{ return x / y - trunc(x / y); }

		// absolute value
		inline constexpr double abs(double value) noexcept				{ return (value < 0) ? -value : value; }

	}	// namespace detail

	// convert an angle to a representation that is in the range [0, 2pi)
	// good for wrapping angles that may be large, with many extra turns
	inline constexpr double radians_full(double radians)
	{
		double fraction = detail::fmod(detail::abs(radians), pcs::detail::radian_base);

		// compensate for negative angle
		if (radians < 0)				{ fraction = (1.0 - fraction); }

		return pcs::detail::radian_base * fraction;
	}

	// convert an angle to a normalized representation that is in the range (-pi, pi]
	// good for wrapping angles that may be large, with many extra turns
	inline constexpr double radians_normal(double radians)
	{
		double fraction = detail::fmod(detail::abs(radians), pcs::detail::radian_base);

		// compensate for negative angle
		if (radians < 0.0)				{ fraction = (1.0 - fraction); }

		// compensate if in latter half of period
		if (fraction > 0.5)				{ fraction = (fraction - 1.0); }

		return pcs::detail::radian_base * fraction;
	}


	// convert an angle to a representation that is in the range [0, 2pi)
	// good for wrapping angles that are only a little out of range (angles that might have one extra turn, +/-)
	inline constexpr double full_radians(double radians)
	{
		// adjust from the negative side
		while (radians < 0.0)			{ radians += pcs::two_pi; }

		// adjust from the positive side
		while (radians >= pcs::two_pi)	{ radians -= pcs::two_pi; }

		return radians;
	}

	// convert an angle to a normalized representation that is in the range (-pi, pi)
	// good for wrapping angles that are only a little out of range (angles that might have one extra turn, +/-)
	inline constexpr double normal_radians(double radians)
	{
		// adjust from the negative side
		while (radians < -pcs::pi)		{ radians += pcs::two_pi; }

		// adjust from the positive side
		while (radians > pcs::pi)		{ radians -= pcs::two_pi; }

		return radians;
	}


	// alternate versions of to_fraction and to_bam_value that capture only the top 53 bits of precision from a bam value

	// this version skips over neighboring bam values that map to the same double value
	inline constexpr double to_fraction_alt(unsigned long long bam_value) noexcept
	{
		return static_cast<double>(bam_value >> 11) / static_cast<double>(1ULL << 53);
	}

	// this version skips over neighboring bam values that map to the same double value
	inline constexpr unsigned long long to_bam_value_alt(double d) noexcept
	{
		double fract = detail::fmod(d, 1.0);
		if (fract < 0)	{ fract += 1.0; }
		auto u = static_cast<unsigned long long>(fract * (1ULL << 53));		// capture top 53 bits
		u <<= 11;															// shift to top bits
																			// optionally fill lower 11 bits deterministically or with noise
		return u;
	}


	// 64-bit binary angular measurement (bam).
	// a bam has 64 bits of precision, while a double has only 53 bits of precision,
	// which means that multiple adjacent bam values can map to a single double value.
	// this is a position, not a quantity. size comparison makes no sense.
	// distance between values can make sense, but what units? bam is more of a measure rather than a quantity.
	// but can we use the same representation for a swept angle -- but a periodic swept
	// angle, not linear, i.e., we can't represent any whole number of periods, just a fractional part.
	// a full period puts you back to 0.
	//
	// a bam represents a fractional part of a complete period.
	//   1 turn    is a complete period of a whole
	//  60 seconds is a complete period of a minute
	//  60 minutes is a complete period of an hour
	// 360 degrees is a complete period of a circle
	// 2pi radians is a complete period of a circle
	struct bam64
	{
		private:

			// format converters used for going to or from bam format
			static constexpr double unit_period_to_bam = 0x1p64;			// a multiplier constant to create a bam value from a fractional value in [0.0, 1.0)
			static constexpr double bam_to_unit_period = 0x1p-64;			// a multiplier constant to create a [0.0, 1.0) value from a bam value

			// half period bam value constant
			static constexpr unsigned long long half =		0x8000000000000000;

			// for the alternate version, number of consecutive bam values that map to a single double value, going from 64 bits to 53 bits.
			// this is used to skip over neighboring bam values that map to the same double value.
			// for the non-alternate version, this value is the average spacing between bam values that map to neighboring consecutive double values.
			static constexpr unsigned long long epsilon =	0x0000000000000800;

			// absolute value
			[[nodiscard]] static constexpr double abs(double value) noexcept		{ return (value < 0) ? -value : value; }

			// truncate towards zero
			[[nodiscard]] static constexpr double trunc(double value) noexcept		{ return static_cast<double>(static_cast<long long>(value)); }

			// the floating point remainder of division -- returns a value in range (-1.0, 1.0)
			[[nodiscard]] static constexpr double fmod(double x, double y) noexcept
			{
				double turns = x / y;					// gives value in turns
				if (bam64::abs(turns) > 2.0)
				{
					// this way sems to be more accurate for larger values
					return turns - bam64::trunc(turns);
				}
				else
				{
					// this way seems to be more accurate for smaller values

					// adjust from the negative side
					while (turns <= -1.0)				{ turns += 1.0; }

					// adjust from the positive side
					while (turns >= 1.0)				{ turns -= 1.0; }

					return turns;
				}
			}

			// workhorse function for creating a bam from a fractional part of a full period
			[[nodiscard]] static constexpr bam64 fractional_base(double value, double base) noexcept
			{
				double fraction = bam64::fmod(value, base);
				if (fraction < 0)	{ fraction += 1.0; }	// don't allow negative values if you are casting to an unsigned type
				return bam64{ .value = static_cast<unsigned long long>(fraction * bam64::unit_period_to_bam) };
			}


			// for alternate version, nearby bam values that map to neighboring consecutive double values

			// skip over neighboring bam values that map to the same double value
			[[nodiscard]] constexpr bam64 next_alt() noexcept			{ return { .value = this->value + bam64::epsilon }; }

			// skip over neighboring bam values that map to the same double value
			[[nodiscard]] constexpr bam64 previous_alt() noexcept		{ return { .value = this->value - bam64::epsilon }; }

			// alternate method for creating a bam from a fractional part of a full period - captures only the top 53 bits of precision
			[[nodiscard]] static constexpr bam64 fractional_base_alt(double value, double base) noexcept
			{
				double fraction = bam64::fmod(value, base);
				if (fraction < 0)	{ fraction += 1.0; }							// don't allow negative values if you are casting to an unsigned type
				auto u = static_cast<unsigned long long>(fraction * (1ULL << 53));	// capture top 53 bits
				u <<= 11;															// shift to top bits
				return bam64{ .value = u };
			}

			// alternate version that only captures the top 53 bits of precision
			[[nodiscard]] constexpr double fraction_alt(double base = 1.0) const noexcept	{ return base * ((this->value >> 11) / static_cast<double>(1ULL << 53)); }

	public:

			// the bam value
			unsigned long long value;


			// builders

			// can use one of the enum values defined after the struct definition to create a bam64 from a known constant
			[[nodiscard]] static constexpr bam64 from_bam_value(unsigned long long bam_value) noexcept		{ return { .value = bam_value }; }

			// whether you are trying make a bam from a turn, a minute, an hour, a degree, or radian value, all the whole amounts of
			// whichever representation you are using, it will use the fraction of the value for making the bam value.
			[[nodiscard]] static constexpr bam64 from_base(double value, double base) noexcept
			{
				if (base == 0.0)	{ return { .value = 0 }; }
				return bam64::fractional_base(value, base);
			}


			// periodic properties

			// fraction - period value in range [0, 1) * base
			[[nodiscard]] constexpr double fraction(double base = 1.0) const noexcept
			{ 
				unsigned long long bam_value = this->value;

				// shenanigans to avoid prematurely having an erroneous double value of 1.0 when converting large bam values to double
				if (bam_value > 0xfffffffffffff800)
					bam_value = 0xfffffffffffff800;

				return base * bam_value * bam64::bam_to_unit_period;
			}

			// complement - complementary period value in range [0, 1) * base
			[[nodiscard]] constexpr double complement(double base = 1.0) const noexcept		{ return (~(*this)).fraction(base); }

			// opposite - period value half a period away, in range [0, 1) * base
			[[nodiscard]] constexpr double opposite(double base = 1.0) const noexcept		{ return (-(*this)).fraction(base); }

			// normal - normalized period value in range (-0.5, 0.5] * base
			[[nodiscard]] constexpr double normal(double base = 1.0) const noexcept
			{
				return ((this->value > bam64::half) ? -(this->complement(base)) : this->fraction(base));
			}


			// unary operators

			// unary plus is identity operation
			[[nodiscard]] constexpr bam64 operator +() const noexcept						{ return { .value = this->value }; }

			// two's complement negation
			// for a BAM, negation is its complement
			[[nodiscard]] constexpr bam64 operator ~() const noexcept						{ return { .value = ~(this->value) + 1ULL }; }

			// the position half a period away
			[[nodiscard]] constexpr bam64 operator -() const noexcept						{ return { .value = this->value + bam64::half }; }


			// binary operators

			// relies on unsigned overflow
			[[nodiscard]] constexpr bam64 operator +(bam64 rhs) const noexcept				{ return { .value = this->value + rhs.value }; }

			// relies on unsigned underflow
			[[nodiscard]] constexpr bam64 operator -(bam64 rhs) noexcept					{ return { .value = this->value - rhs.value }; }

			[[nodiscard]] constexpr bam64 operator *(double multiplier) const noexcept		{ return bam64::from_base(this->fraction() * multiplier, 1.0); }

			[[nodiscard]] friend constexpr bam64 operator *(double multiplier, bam64 bam) noexcept			{ return bam * multiplier; }

			[[nodiscard]] constexpr bam64 operator /(double divisor) const noexcept
			{
				if (divisor == 0.0)	{ return { .value = 0 }; }
				return bam64::from_base(this->fraction() / divisor, 1.0);
			}


			// comparison functions

			[[nodiscard]] constexpr std::strong_ordering operator <=>(const bam64 &other) const noexcept	{ return this->value <=> other.value; }

			[[nodiscard]] constexpr bool operator ==(const bam64 &other) const noexcept						{ return this->value == other.value; }

			// is the value within the tolerance range of zero?
			[[nodiscard]] constexpr bool within_tolerance(bam64 tolerance) const noexcept
			{
				bam64 comp_val = ~(*this);									// we approach zero from both the low and high sides, so we need the complement value too
				bam64 min_val = ((*this) > comp_val) ? comp_val : *this;	// choose whichever is smaller in magnitude
				return min_val <= tolerance;								// if the smaller magnitude value is within the tolerance, then we are within tolerance
			}

	};	// struct bam64


	// distance comparison

	// are two bam values within the specified tolerance of each other?
	[[nodiscard]] inline constexpr bool within_distance(bam64 a, bam64 b, bam64 tolerance) noexcept
	{
		bam64 diff = (a - b);
		return diff.within_tolerance(tolerance);
	}


	// make bam64s from various periodic units

	//
	[[nodiscard]] inline constexpr bam64 bam64_from_turns(double turns) noexcept				{ return bam64::from_base(turns,	detail::turn_base); }
	[[nodiscard]] inline constexpr bam64 bam64_from_minutes(double minutes) noexcept			{ return bam64::from_base(minutes,	detail::minute_base); }
	[[nodiscard]] inline constexpr bam64 bam64_from_seconds(double seconds) noexcept			{ return bam64::from_base(seconds,	detail::second_base); }
	[[nodiscard]] inline constexpr bam64 bam64_from_degrees(double degrees) noexcept			{ return bam64::from_base(degrees,	detail::degree_base); }
	[[nodiscard]] inline constexpr bam64 bam64_from_radians(double radians) noexcept			{ return bam64::from_base(radians,	detail::radian_base); }
	[[nodiscard]] inline constexpr bam64 bam64_from_base(double value, double base) noexcept	{ return bam64::from_base(value,	base); }


	// convert bam64 to various periodic units

	// fraction - period value in range [0, 1) * base
	[[nodiscard]] inline constexpr double to_fraction(bam64 bam) noexcept						{ return bam.fraction(detail::turn_base); }
	[[nodiscard]] inline constexpr double to_minutes(bam64 bam) noexcept						{ return bam.fraction(detail::minute_base); }
	[[nodiscard]] inline constexpr double to_seconds(bam64 bam) noexcept						{ return bam.fraction(detail::second_base); }
	[[nodiscard]] inline constexpr double to_degrees(bam64 bam) noexcept						{ return bam.fraction(detail::degree_base); }
	[[nodiscard]] inline constexpr double to_radians(bam64 bam) noexcept						{ return bam.fraction(detail::radian_base); }
	[[nodiscard]] inline constexpr double to_base(bam64 bam, double base) noexcept				{ return bam.fraction(base); }

	// complement - complementary period value in range [0, 1) * base
	[[nodiscard]] inline constexpr double to_fraction_complement(bam64 bam) noexcept			{ return bam.complement(detail::turn_base); }
	[[nodiscard]] inline constexpr double to_minutes_complement(bam64 bam) noexcept				{ return bam.complement(detail::minute_base); }
	[[nodiscard]] inline constexpr double to_seconds_complement(bam64 bam) noexcept				{ return bam.complement(detail::second_base); }
	[[nodiscard]] inline constexpr double to_degrees_complement(bam64 bam) noexcept				{ return bam.complement(detail::degree_base); }
	[[nodiscard]] inline constexpr double to_radians_complement(bam64 bam) noexcept				{ return bam.complement(detail::radian_base); }
	[[nodiscard]] inline constexpr double to_base_complement(bam64 bam, double base) noexcept	{ return bam.complement(base); }

	// opposite - period value half a period away, in range [0, 1) * base
	[[nodiscard]] inline constexpr double to_fraction_opposite(bam64 bam) noexcept				{ return bam.opposite(detail::turn_base); }
	[[nodiscard]] inline constexpr double to_minutes_opposite(bam64 bam) noexcept				{ return bam.opposite(detail::minute_base); }
	[[nodiscard]] inline constexpr double to_seconds_opposite(bam64 bam) noexcept				{ return bam.opposite(detail::second_base); }
	[[nodiscard]] inline constexpr double to_degrees_opposite(bam64 bam) noexcept				{ return bam.opposite(detail::degree_base); }
	[[nodiscard]] inline constexpr double to_radians_opposite(bam64 bam) noexcept				{ return bam.opposite(detail::radian_base); }
	[[nodiscard]] inline constexpr double to_base_opposite(bam64 bam, double base) noexcept		{ return bam.opposite(base); }

	// normal - normalized period value in range (-0.5, 0.5] * base
	[[nodiscard]] inline constexpr double to_fraction_normal(bam64 bam) noexcept				{ return bam.normal(detail::turn_base); }
	[[nodiscard]] inline constexpr double to_minutes_normal(bam64 bam) noexcept					{ return bam.normal(detail::minute_base); }
	[[nodiscard]] inline constexpr double to_seconds_normal(bam64 bam) noexcept					{ return bam.normal(detail::second_base); }
	[[nodiscard]] inline constexpr double to_degrees_normal(bam64 bam) noexcept					{ return bam.normal(detail::degree_base); }
	[[nodiscard]] inline constexpr double to_radians_normal(bam64 bam) noexcept					{ return bam.normal(detail::radian_base); }
	[[nodiscard]] inline constexpr double to_base_normal(bam64 bam, double base) noexcept		{ return bam.normal(base); }


	// predefined bam64 constant values

	// "whole" is a whole number of full periods, and "frac" is the fractional part of a full period:
	// 
	// bam64_from_turns		((whole * 1)	+ frac_turns)		== bam64_from_turns(frac_turns),		frac_turns		in range [0, 1)
	// bam64_from_minutes	((whole * 60)	+ frac_minutes)		== bam64_from_minutes(frac_minutes),	frac_minutes	in range [0, 60)
	// bam64_from_seconds	((whole * 60)	+ frac_seconds)		== bam64_from_seconds(frac_seconds),	frac_seconds	in range [0, 60)
	// bam64_from_degrees	((whole * 360)  + frac_degrees)		== bam64_from_degrees(frac_degrees),	frac_degrees	in range [0, 360)
	// bam64_from_radians	((whole * 2pi)  + frac_radians)		== bam64_from_radians(frac_radians),	frac_radians	in range [0, 2pi)
	// bam64_from_base		((whole * base) + frac_base)		== bam64_from_base(frac_base, base),	frac_radians	in range [0, base)
	//
	// negative values are allowed, and they will wrap around correctly.
	// For example, -90 degrees is the same as +270 degrees, and both will produce the same bam value.from_base(double value, double base)
	// 
	// bam values represent fractional parts of a period,
	// where a period is 1 turn, 360 degrees, 2pi radians, 60 minutes, 60 seconds, etc.
	enum : unsigned long long
	{
		none =						0x0000000000000000,		//	  0		degrees
		whole =						0x0000000000000000,		//	360		degrees
		fifteen_sixteenths =		0xf000000000000000,		//  337.5	degrees
		eleven_twelfths =			0xeaaaaaaaaaaaa800,		//  330		degrees
		seven_eighths =				0xe000000000000000,		//  315		degrees
		five_sixths =				0xd555555555555800,		//  300		degrees
		thirteen_sixteenths =		0xd000000000000000,		//  292.5	degrees
		four_fifths =				0xccccccccccccd000,		//  288		degrees
		three_fourths =				0xc000000000000000,		//  270		degrees
		eleven_sixteenths =			0xb000000000000000,		//  247.5	degrees
		two_thirds =				0xaaaaaaaaaaaaa800,		//  240		degrees
		five_eighths =				0xa000000000000000,		//  225		degrees
		three_fifths =				0x9999999999999800,		//  216		degrees
		seven_twelfths =			0x9555555555555800,		//  210		degrees
		nine_sixteenths =			0x9000000000000000,		//  202.5	degrees
		half =						0x8000000000000000,		//  180		degrees
		seven_sixteenths =			0x7000000000000000,		//  157.5	degrees
		five_twelfths =				0x6aaaaaaaaaaaac00,		//  150		degrees
		two_fifths =				0x6666666666666800,		//  144		degrees
		three_eighths =				0x6000000000000000,		//  135		degrees
		third =						0x5555555555555400,		//  120		degrees
		five_sixteenths =			0x5000000000000000,		//  112.5	degrees
		fourth =					0x4000000000000000,		//   90		degrees
		fifth =						0x3333333333333400,		//   72		degrees
		three_sixteenths =			0x3000000000000000,		//   67.5	degrees
		sixth =						0x2aaaaaaaaaaaaa00,		//   60		degrees
		eighth =					0x2000000000000000,		//   45		degrees
		tenth =						0x1999999999999a00,		//   36		degrees
		twelfth =					0x1555555555555500,		//   30		degrees
		fifteenth =					0x1111111111111100,		//   24		degrees
		sixteenth =					0x1000000000000000,		//   22.5	degrees
		eighteenth =				0x0e38e38e38e38e00,		//   20		degrees
		twentieth =					0x0ccccccccccccd00,		//   18		degrees
		twenty_fourth =				0x0aaaaaaaaaaaaa80,		//   15		degrees
		thirtieth =					0x0888888888888880,		//   12		degrees
		thirty_second =				0x0800000000000000,		//   11.25	degrees
		thirty_sixth =				0x071c71c71c71c700,		//   10		degrees
		fourty_fifth =				0x05b05b05b05b05c0,		//    8		degrees
		fourty_eighth =				0x0555555555555540,		//    7.5	degrees
		sixtieth =					0x0444444444444440,		//    6		degrees
		sixty_fourth =				0x0400000000000000,		//    5.625	degrees
		seventy_second =			0x038e38e38e38e380,		//    5		degrees
		ninetieth =					0x02d82d82d82d82e0,		//    4		degrees
		hundredth =					0x028f5c28f5c28f60,		//    3.6	degrees
		hundred_twentieth =			0x0222222222222220,		//    3		degrees
		hundred_eightieth =			0x016c16c16c16c170,		//    2		degrees
		two_hundred_fortieth =		0x0111111111111110,		//    1.5	degrees
		three_hundred_sixtieth =	0x00b60b60b60b60b8,		//    1		degrees

		radian =					0x28be60db93910600,		//   57.295779513082323 degrees of a circle
		degree =					0x00b60b60b60b60b8,		//    1		degrees of a circle
		arc_minute =				0x000308b91419ca25,		//   1/60	degrees of a circle
		arc_second =				0x00000cf2049a07a2,		//   1/3600	degrees of a circle
		tenth_degree =				0x00123456789abcdf,		//   1/10	degrees of a circle		=	0.0017453292519943296  radians	// fab machining tolerance
		hundredth_degree =			0x0001d208a5a912e3,		//   1/100	degrees of a circle		=	0.00017453292519943291 radians	// rotary machining tolerance
		minute =					0x0444444444444440,		//    6		degrees of an hour
		second =					0x0444444444444440,		//    6		degrees of a minute

		epsilon =					0x0000000000000800		// for alternate method, number of consecutive bam values that map to a single double value, going from 64 bits to 53 bits
	};

}	// namespace pcs

// closing include guard
#endif
