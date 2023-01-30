#include "math/Color.hpp"
#include <algorithm>

namespace math {
	Color Color::clipped() const {
		return Color{
			.r = std::min(1.f, std::max(0.f, r)),
			.g = std::min(1.f, std::max(0.f, g)),
			.b = std::min(1.f, std::max(0.f, b)),
		};
	}

	Color operator+(const Color& lhs, const Color& rhs) {
		return Color{
			.r = lhs.r + rhs.r,
			.g = lhs.g + rhs.g,
			.b = lhs.b + rhs.b
		};
	}

	Color operator-(const Color& lhs, const Color& rhs) {
		return Color{
			.r = lhs.r - rhs.r,
			.g = lhs.g - rhs.g,
			.b = lhs.b - rhs.b
		};
	}

	Color operator*(const Color& lhs, float scalar) {
		return Color{
			.r = lhs.r * scalar,
			.g = lhs.g * scalar,
			.b = lhs.b * scalar
		};
	}

	Color operator/(const Color& lhs, float scalar) {
		return Color{
			.r = lhs.r / scalar,
			.g = lhs.g / scalar,
			.b = lhs.b / scalar
		};
	}

	Color& operator+=(Color& lhs, const Color& rhs) {
		lhs = lhs + rhs;
		return lhs;
	}

	Color& operator-=(Color& lhs, const Color& rhs) {
		lhs = lhs - rhs;
		return lhs;
	}

	Color& operator*=(Color& lhs, float scalar) {
		lhs = lhs * scalar;
		return lhs;
	}

	Color& operator/=(Color& lhs, float scalar)  {
		lhs = lhs / scalar;
		return lhs;
	}
}