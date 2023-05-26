#pragma once

#include "feasy.hpp"
#include <cmath>

namespace feasy
{
	namespace math
	{
		inline i32 nextPowerOf2(i32 number)
		{
			// TODO: Assert number >= 0

			if (number == 0)
				return 1;

			else if ((number & (number - 1)) == 0)
				return number;

			i32 power = static_cast<i32>(std::log2(number)) + 1;
			return static_cast<i32>(std::pow(2, power));
		}

		inline i32 max(i32 a, i32 b)
		{
			return a > b ? a : b;
		}

		inline i32 min(i32 a, i32 b)
		{
			return a < b ? a : b;
		}
	}
}