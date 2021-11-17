#pragma once

namespace glds
{
	const float Pi = 3.14159265359f;
	const float TwoPi = 6.28318530718f;
	const float HalfPi = 1.57079632679f;
	const float QuarterPi = 0.78539816339f;

	inline float RadToDeg(float radians)
	{
		return radians * 180 / Pi;
	}
	
	inline float DegToRad(float degrees)
	{
		return degrees * Pi / 180;
	}

	template<typename T>
	T Clamp(T val, T min, T max)
	{
		if (val < min) return min;
		if (val > max) return max;

		return val;
	}

	template<typename T>
	T Wrap(T val, T min, T max)
	{
		if (val < min) return max;
		if (val > max) return min;

		return val;
	}

	template<typename T>
	T Lerp(T a, T b, float t)
	{
		t = Clamp(t, 0.0f, 1.0f);

		return a + ((b - a) * t);
	}
}