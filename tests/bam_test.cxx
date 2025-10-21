tests/bam64_edge_tests.cxx
#include <cassert>
#include <cmath>
#include <iostream>
#include <limits>

#include "../include/bam64.hxx"

using pcs::bam64;

int main()
{
    // Compile-time checks (constexpr APIs)
    static_assert(pcs::bam64_from_degrees(0.0).value == pcs::none, "0 deg -> none");
    static_assert(pcs::bam64_from_degrees(360.0).value == pcs::none, "360 deg wraps to none");
    static_assert(pcs::bam64_from_degrees(180.0).value == pcs::half, "180 deg -> half period");
    static_assert(pcs::bam64_from_radians(pcs::pi).value == pcs::half, "pi rad -> half period");

    // Edge: base == 0.0 must return bam value 0
    static_assert(pcs::bam64_from_base(1.234, 0.0).value == 0ULL, "base==0 -> zero bam");

    // Edge: negative angles wrap: -90 deg == 270 deg
    static_assert(pcs::bam64_from_degrees(-90.0).value == pcs::bam64_from_degrees(270.0).value,
        "negative angle wraps equivalently");

    // Edge: addition overflow wraps to none (half + half == none)
    static_assert((bam64::from_bam_value(bam64::half) + bam64::from_bam_value(bam64::half)).value == pcs::none,
        "half + half -> wrap to none");

    // Edge: ~0 == 0 due to two's complement wrap in this implementation
    static_assert((~bam64::from_bam_value(0ULL)).value == 0ULL, "complement of 0 == 0");

    // Edge: subtraction wrap-around produces small modular difference
    static_assert(pcs::within_distance(bam64::from_bam_value(1ULL),
        bam64::from_bam_value(std::numeric_limits<unsigned long long>::max()),
        bam64::from_bam_value(2ULL)),
        "1 and ULL_MAX should be within distance 2 (wrap-around)");

    // Edge: multiplication by 0 and division by 0 behaviour (per implementation)
    static_assert((pcs::bam64_from_degrees(45.0) * 0.0).value == 0ULL, "mul by 0 -> zero");
    static_assert((pcs::bam64_from_degrees(45.0) / 0.0).value == 0ULL, "div by 0 -> zero");

    // Runtime checks for floating/precision-related edge cases
    {
        // fraction + complement (mod 1) should be 1 (or 0 due to wrap) within epsilon
        auto a = pcs::bam64_from_degrees(30.0);
        double frac = a.fraction();                   // in turns
        double comp = a.complement();                 // complement in turns
        double sum = std::fmod(frac + comp, 1.0);
        constexpr double eps = 1e-15;
        assert(std::fabs(sum - 1.0) < eps || std::fabs(sum) < eps);

        std::cout << "fraction=" << frac << ", complement=" << comp << ", sum_mod=" << sum << "\n";
    }

    {
        // normal() at half boundary should return +0.5 (implementation uses > half to choose sign, so half is +0.5)
        auto h = bam64::from_bam_value(bam64::half);
        double normal_turns = h.normal(); // in turns
        constexpr double eps = 1e-16;
        assert(std::fabs(normal_turns - 0.5) < eps);
        std::cout << "normal(half) = " << normal_turns << " turns\n";
    }

    {
        // very large radians value (many turns) should reduce to the small fractional part
        double small = 0.123456789; // radians < 2pi
        double big = small + 1e6 * pcs::twopi; // many whole turns added
        auto b = pcs::bam64_from_radians(big);
        auto b_small = pcs::bam64_from_radians(small);
        // should be identical (wrap)
        assert(b.value == b_small.value);
        std::cout << "large radians wrapped -> same bam as small fractional radians\n";
    }

    {
        // Verify complement/opposite semantics at wrap boundary: complement of near-zero high-side value.
        auto near_high = bam64::from_bam_value(std::numeric_limits<unsigned long long>::max() - 1ULL);
        // complement and fraction give values; ensure within expected ranges and not NaN
        double frac = near_high.fraction();
        double comp = near_high.complement();
        (void)frac; (void)comp;
        assert(std::isfinite(frac) && std::isfinite(comp));
        std::cout << "near_high fraction=" << frac << ", complement=" << comp << "\n";
    }

    // Ordering / equality edge checks
    {
        auto a = pcs::bam64_from_degrees(10.0);
        auto b = pcs::bam64_from_degrees(20.0);
        assert(a < b);
        assert((a == a) && !(a == b));
        std::cout << "ordering/equality checks OK\n";
    }

    std::cout << "All additional bam64 edge-case tests passed.\n";
    return 0;
}