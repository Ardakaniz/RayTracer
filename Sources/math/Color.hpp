#pragma once

namespace math {
	struct Color {
		float r,g,b;
	};

	constexpr Color BLACK = { 0., 0., 0. };
	constexpr Color WHITE = { 1., 1., 1. };
	constexpr Color RED   = { 1., 0., 0. };
	constexpr Color GREEN = { 0., 1., 0. };
	constexpr Color BLUE  = { 0., 0., 1. };
}