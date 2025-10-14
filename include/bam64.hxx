
//          Copyright David Browne 2021-2025.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

// opening include guard
#if !defined(PCS_BAM64_HXX)
#define PCS_BAM64_HXX

namespace pcs
{
	// radian related constants
	inline constexpr static double pi =	3.1415926535897931;
	inline constexpr static double twopi =	6.2831853071795862;
	inline constexpr static double tau =	6.2831853071795862;

	// detail namespace for helper functions
	namespace detail
	{
		// truncate towards zero
		inline constexpr double trunc(double value) noexcept			{ return static_cast<double>(static_cast<long long>(value)); }

		// fractional part of value
		inline constexpr double fmod(double x, double y) noexcept		{ return x / y - trunc(x / y); }

		// absolute value
		inline constexpr double abs(double value) noexcept				{ return (value < 0) ? -value : value; }

	}	// namespace detail

	// convert an angle to a representation that is in the range [0, 2pi)
	// good for wrapping angles that may be large, with many extra turns
	inline constexpr double ang_full(double ang)
	{
		double turns = detail::fmod(detail::abs(ang), pcs::twopi);

		// compensate for negative angle
		if (ang < 0)				{ turns = (1.0 - turns); }

		return pcs::twopi * turns;
	}

	// convert an angle to a normalized representation that is in the range (-pi, pi]
	// good for wrapping angles that may be large, with many extra turns
	inline constexpr double ang_norm(double ang)
	{
		double turns = detail::fmod(detail::abs(ang), pcs::twopi);

		// compensate for negative angle
		if (ang < 0.0)				{ turns = (1.0 - turns); }

		// compensate if in latter half of period
		if (turns > 0.5)			{ turns = (turns - 1.0); }

		return pcs::twopi * turns;
	}


	// convert an angle to a representation that is in the range [0, 2pi)
	// good for wrapping angles that are only a little out of range (angles that might have an extra turn, +/-)
	inline constexpr double full_ang(double ang)
	{
		// adjust from the negative side
		while (ang < 0.0)			{ ang += pcs::twopi; }

		// adjust from the positive side
		while (ang >= pcs::twopi)	{ ang -= pcs::twopi; }

		return ang;
	}

	// convert an angle to a normalized representation that is in the range (-pi, pi)
	// good for wrapping angles that are only a little out of range (angles that might have an extra turn, +/-)
	inline constexpr double norm_ang(double ang)
	{
		// adjust from the negative side
		while (ang < -pcs::pi)		{ ang += pcs::twopi; }

		// adjust from the positive side
		while (ang > pcs::pi)		{ ang -= pcs::twopi; }

		return ang;
	}

	// 64-bit binary angular measurement (bam).
	// a bam has 64 bits of precision, while a double has only 53 bits of precision,
	// which means that multiple adjacent bam values can map to a single double value.
	// this is a position, not a quantity. size comparison makes no sense.
	// distance between values can make sense, but what units? bam is not a quantity.
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

			// constants for converting to/from degrees, radians, turns, time units, etc.
			static constexpr double turn_base =		  1.0;					//   1 turn					-> 1 period
			static constexpr double time_base =		 60.0;					//  60 minutes or seconds	-> 1 hour or 1 minute
			static constexpr double degree_base =	360.0;					// 360 degrees				-> 1 circle
			static constexpr double radian_base =	pcs::twopi;				// 2pi radians				-> 1 circle

			// half period bam value constant
			static constexpr unsigned long long half =	0x8000000000000000;

			// truncate towards zero
			static constexpr double trunc(double value) noexcept		{ return static_cast<double>(static_cast<long long>(value)); }

			// the floating point remainder of division
			static constexpr double fmod(double x, double y) noexcept	{ return x / y - bam64::trunc(x / y); }

			// workhorse function for creating a bam from a fractional part of a full period
			static constexpr bam64 fractional_base(double value, double base) noexcept
			{
				double fraction = bam64::fmod(value, base);
				if (fraction < 0)	{ fraction += 1.0; }	// don't allow negative values if you are casting to an unsigned type
				return bam64{ .value = static_cast<unsigned long long>(fraction * bam64::unit_period_to_bam) };
			}

		public:
			// the bam value
			unsigned long long value;

			// whether you are trying make a bam from a turn, a minute, an hour, a degree, or radian value, all the whole amounts of
			// whichever representation you are using, it will use the fraction of the value for making the bam value.

			static constexpr bam64 from_bam_value(unsigned long long bam_value) noexcept	{ return { .value = bam_value }; }
			static constexpr bam64 from_turns(double turns) noexcept						{ return bam64::fractional_base(turns,		bam64::turn_base); }
			static constexpr bam64 from_time(double time_units) noexcept					{ return bam64::fractional_base(time_units,	bam64::time_base); }
			static constexpr bam64 from_degrees(double degrees) noexcept					{ return bam64::fractional_base(degrees,	bam64::degree_base); }
			static constexpr bam64 from_radians(double radians) noexcept					{ return bam64::fractional_base(radians,	bam64::radian_base); }
			static constexpr bam64 from_base(double value, double base) noexcept			{ if (base == 0.0)	{ return { .value = 0 }; }
																							  return bam64::fractional_base(value, base); }

			// full - period value in range [0, 1) * base
			// comp - complementary period value in range [0, 1) * base
			// norm - normalized period value in range (-0.5, 0.5] * base

			[[nodiscard]] constexpr double turns_full() const noexcept				{ return this->value * bam64::bam_to_unit_period; }
			[[nodiscard]] constexpr double turns_comp() const noexcept				{ return (-(*this)).turns_full(); }
			[[nodiscard]] constexpr double turns_norm() const noexcept				{ return (this->value > bam64::half) ? -this->turns_comp() : this->turns_full(); }

			[[nodiscard]] constexpr double base_full(double base) const noexcept	{ return base * this->turns_full(); }
			[[nodiscard]] constexpr double base_comp(double base) const noexcept	{ return base * this->turns_comp(); }
			[[nodiscard]] constexpr double base_norm(double base) const noexcept	{ return (this->value > bam64::half) ? -this->base_comp(base) : this->base_full(base); }

			[[nodiscard]] constexpr double time_full() const noexcept				{ return this->base_full(bam64::time_base); }
			[[nodiscard]] constexpr double time_comp() const noexcept				{ return this->base_comp(bam64::time_base); }
			[[nodiscard]] constexpr double time_norm() const noexcept				{ return this->base_norm(bam64::time_base); }

			[[nodiscard]] constexpr double degrees_full() const noexcept			{ return this->base_full(bam64::degree_base); }
			[[nodiscard]] constexpr double degrees_comp() const noexcept			{ return this->base_comp(bam64::degree_base); }
			[[nodiscard]] constexpr double degrees_norm() const noexcept			{ return this->base_norm(bam64::degree_base); }

			[[nodiscard]] constexpr double radians_full() const noexcept			{ return this->base_full(bam64::radian_base); }
			[[nodiscard]] constexpr double radians_comp() const noexcept			{ return this->base_comp(bam64::radian_base); }
			[[nodiscard]] constexpr double radians_norm() const noexcept			{ return this->base_norm(bam64::radian_base); }

			// relies on unsigned overflow
			[[nodiscard]] constexpr bam64 operator +(bam64 rhs) const noexcept		{ return { .value = this->value + rhs.value }; }

			// relies on unsigned underflow
			[[nodiscard]] friend constexpr bam64 operator -(bam64 lhs, bam64 rhs) noexcept		{ return { .value = lhs.value - rhs.value }; }

			// unary plus is identity operation
			[[nodiscard]] constexpr bam64 operator +() const noexcept				{ return { .value = this->value }; }

			// two's complement negation
			// for a BAM, negation is its complement
			[[nodiscard]] constexpr bam64 operator -() const noexcept				{ return { .value = ~(this->value) + 1ULL }; }

			// the position half a period away
			[[nodiscard]] constexpr bam64 operator ~() const noexcept				{ return { .value = this->value + bam64::half }; }

			[[nodiscard]] constexpr bam64 operator *(double mult) const noexcept	{ return bam64::from_turns(this->turns_full() * mult); }

			[[nodiscard]] friend constexpr bam64 operator *(double mult, const bam64 &bam) noexcept
			{
				return bam64::from_turns(bam.turns_full() * mult);
			}

			[[nodiscard]] constexpr bam64 operator /(double turns) const noexcept
			{
				if (turns == 0.0)	{ return { .value = 0 }; }
				return bam64::from_turns(this->turns_full() / turns);
			}

			[[nodiscard]] constexpr bam64 operator /(const bam64 &bam) noexcept
			{
				if (bam.value == 0.0)	{ return { .value = 0 }; }
				return bam64::from_turns(this->turns_full() / bam.turns_full());
			}

			[[nodiscard]] constexpr std::strong_ordering operator <=>(const bam64 &other) const noexcept
			{
				return this->value <=> other.value;
			}

			[[nodiscard]] constexpr bool operator ==(const bam64 &other) const noexcept
			{
				return this->value == other.value;
			}

			// is the value within the tolerance range of zero?
			[[nodiscard]] constexpr bool within_tolerance(bam64 tolerance) const noexcept
			{
				bam64 neg_val = -(*this);								// we approach zero from both the low and high sides, so we need the negative value too
				bam64 min_val = ((*this) > neg_val) ? neg_val : *this;	// choose whichever is smaller in magnitude
				return min_val <= tolerance;							// if the smaller magnitude value is within the tolerance, then we are within tolerance
			}

	};	// struct bam64

	// are two bam values within the specified tolerance of each other?
	inline constexpr bool within_distance(bam64 a, bam64 b, bam64 tolerance) noexcept
	{
		bam64 diff = (a - b);
		return diff.within_tolerance(tolerance);
	}

	// "whole" is a whole number of full periods, and "frac" is the fractional part of a full period:
	// 
	// bam64::from_turns  ((whole * 1)	  + frac_turns)			== bam::64::from_turns(frac_turns),		frac_turns		in range [0, 1)
	// bam64::from_time	  ((whole * 60)	  + frac_time_units)	== bam::64::from_time(frac_time_units),	frac_time_units	in range [0, 60)
	// bam64::from_degrees((whole * 360)  + frac_degrees)		== bam::64::from_degrees(frac_degrees),	frac_degrees	in range [0, 360)
	// bam64::from_radians((whole * 2pi)  + frac_radians)		== bam::64::from_radians(frac_radians),	frac_radians	in range [0, 2pi)
	// bam64::from_base	  ((whole * base) + frac_base)			== bam::64::from_base(frac_base, base),	frac_radians	in range [0, base)
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
		hundred_twentieth =			0x0222222222222220,		//    3		degrees
		hundred_eightieth =			0x016c16c16c16c170,		//    2		degrees
		two_hundred_fortieth =		0x0111111111111110,		//    1.5	degrees
		three_hundred_sixtieth =	0x00b60b60b60b60b8,		//    1		degrees

		radian =					0x28be60db93910600,		//   57.295779513082323 degrees of a circle
		degree =					0x00b60b60b60b60b8,		//    1		degrees of a circle
		minute =					0x0444444444444440,		//    6		degrees of an hour
		second =					0x0444444444444440,		//    6		degrees of a minute
		arc_minute =				0x000308b91419ca25,		//   1/60	degrees of a circle
		arc_second =				0x00000cf2049a07a2		//   1/3600	degrees of a circle
	};

}	// namespace pcs

// closing include guard
#endif
