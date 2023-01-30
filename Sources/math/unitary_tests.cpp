#include "math/Vec.hpp"

#include <cassert>
#include <iostream>
#include <iomanip>
#include <cmath>

namespace test {
	bool almost_eq(float a, float b) {
		return std::fabs(a - b) < 1e-5;
	}

	void run_vec() {
		using namespace math;

		Vec v1{ 1., 2., 3. };
		Vec v2{ 0., -1., 214.4535 };

		const Vec sum = v1 + v2;
		assert(almost_eq(sum.x, 1.) && almost_eq(sum.y, 1.) && almost_eq(sum.z, 217.4535));

		const Vec factor_sum = v1 + 10.;
		assert(almost_eq(factor_sum.x, 11.) && almost_eq(factor_sum.y, 12.) && almost_eq(factor_sum.z, 13.));

		const Vec diff = v1 - v2;
		assert(almost_eq(diff.x, 1.) && almost_eq(diff.y, 3.) && almost_eq(diff.z, -211.4535));

		const Vec factor_diff = v1 - 10.;
		assert(almost_eq(factor_diff.x, -9.) && almost_eq(factor_diff.y, -8.) && almost_eq(factor_diff.z, -7.));

		const Vec mul = v1 * 2.;
		assert(almost_eq(mul.x, 2.) && almost_eq(mul.y, 4.) && almost_eq(mul.z, 6.));
	}
}