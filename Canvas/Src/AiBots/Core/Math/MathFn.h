#pragma once

#include "Core/Debug/Error.h"

#include <math.h>
#include <sstream>
#include <string>
#include <vector>
#include <limits>

#include <iomanip>

//------------------------------------------------------------------------
//  Math utility functions and constants
//------------------------------------------------------------------------

//a few useful constants
const int MaxInt = (std::numeric_limits<int>::max)();
const double maxDouble = (std::numeric_limits<double>::max)();
const double minDouble = (std::numeric_limits<double>::min)();
const float MaxFloat = (std::numeric_limits<float>::max)();
const float MinFloat = (std::numeric_limits<float>::min)();

const double Pi = 3.14159;
const double TwoPi = Pi * 2;
const double HalfPi = Pi / 2;
const double QuarterPi = Pi / 4;

// returns true if the value is a NaN
template <typename T>
inline bool isNaN(T val)
{
	return val != val;
}

inline double getRadiansFromDegrees(double degs)
{
	return TwoPi * (degs / 360.0);
}

// returns true if the parameter is equal to zero
inline bool IsZero(double val)
{
	return ((-minDouble < val) && (val < minDouble));
}

// returns true is the third parameter is in the range described by the first two
inline bool InRange(double start, double end, double val)
{
	if (start < end)
	{
		if ((val > start) && (val < end)) return true;
		else return false;
	}

	else
	{
		if ((val < start) && (val > end)) return true;
		else return false;
	}
}

template <class T>
T Maximum(const T& v1, const T& v2)
{
	return v1 > v2 ? v1 : v2;
}

inline int getRandomIntInRange(int x, int y)
{
	RIO_ASSERT(y >= x, "<getRandomIntInRange>: y is less than x");
	return rand() % (y - x + 1) + x;
}

// returns a random double between zero and 1
inline double getRandomDoubleNormalized()
{
	return ((rand()) / (RAND_MAX + 1.0));
}

inline double getRandomDoubleInRange(double x, double y)
{
	return x + getRandomDoubleNormalized()*(y - x);
}

inline bool getRandomBool()
{
	bool result = false;
	if (getRandomDoubleNormalized() > 0.5)
	{
		result = true;
	}
	return result;
}

// returns a random double in the range -1 < n < 1
inline double getRandomClamped()
{
	return getRandomDoubleNormalized() - getRandomDoubleNormalized();
}

// returns the maximum of two values
template <class T>
inline T getMaxOf(const T& a, const T& b)
{
	if (a > b) return a; return b;
}

// returns the minimum of two values
template <class T>
inline T getMinOf(const T& a, const T& b)
{
	if (a < b) return a; return b;
}

// clamps the first argument between the second two
template <class T, class U, class V>
inline void clamp(T& arg, const U& minVal, const V& maxVal)
{
	RIO_ASSERT(((double)minVal < (double)maxVal), "<clamp>MaxVal < MinVal!");

	if (arg < (T)minVal)
	{
		arg = (T)minVal;
	}

	if (arg > (T)maxVal)
	{
		arg = (T)maxVal;
	}
}

// rounds a double up or down depending on its value
inline int Rounded(double val)
{
	int integral = (int)val;
	double mantissa = val - integral;

	if (mantissa < 0.5)
	{
		return integral;
	}

	else
	{
		return integral + 1;
	}
}

// compares two real numbers. Returns true if they are equal
inline bool isEqual(float a, float b)
{
	if (fabs(a - b) < 1E-12)
	{
		return true;
	}

	return false;
}

inline bool isEqual(double a, double b)
{
	if (fabs(a - b) < 1E-12)
	{
		return true;
	}

	return false;
}