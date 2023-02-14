#pragma once

namespace math {
	struct Color {
		float r,g,b;

		// Returns the color with its values clamped between 0.0 and 1.0
		Color clamped() const;
		
		inline Color& clamp()
		{ *this = clamped(); return *this; }
	};
	
	Color operator+(const Color& lhs, const Color& rhs);
	Color operator-(const Color& lhs, const Color& rhs);
	Color operator*(const Color& lhs, float scalar);
	Color operator/(const Color& lhs, float scalar);

	Color& operator+=(Color& lhs, const Color& rhs);
	Color& operator-=(Color& lhs, const Color& rhs);
	Color& operator*=(Color& lhs, float scalar);
	Color& operator/=(Color& lhs, float scalar);

	constexpr Color BLACK = { 0., 0., 0. };
	constexpr Color WHITE = { 1., 1., 1. };
	constexpr Color RED   = { 1., 0., 0. };
	constexpr Color GREEN = { 0., 1., 0. };
	constexpr Color BLUE  = { 0., 0., 1. };
}