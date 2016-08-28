#pragma once

#include "Core/Math/MathFn.h"
#include <math.h>
#include <limits>

struct Vector2
{
	double x = 0.0;
	double y = 0.0;

	Vector2()
	{}

	Vector2(double a, double b) 
		: x(a) 
		, y(b)
	{}

	// sets x and y to zero
	void setToZero()
	{
		x = 0.0;
		y = 0.0;
	}

	// returns true if both x and y are zero
	bool isZero() const
	{
		return (x*x + y*y) < minDouble;
	}

	inline double getLength() const;

	// returns the squared length of the 2D vector (thereby avoiding the sqrt)
	inline double getLengthSquared() const;

	inline void normalize();
	static inline Vector2 getNormalized(const Vector2& v);

	static inline double getDistance(const Vector2& v1, const Vector2& v2);
	static inline double getDistanceSquared(const Vector2& v1, const Vector2& v2);

	inline double dot(const Vector2& v2) const;

	// TODO -- revise this rule for OpenGL coordinate system
	// returns positive if v2 is clockwise of this vector,
	// negative if anticlockwise (assuming the Y axis is pointing down, X axis to right like a Window app)
	inline int getSign(const Vector2& v2) const;

	// returns a vector perpendicular to this vector
	inline Vector2 getPerpendicular() const;

	// adjusts x and y so that the length of the vector does not exceed max
	inline void truncate(double max);

	inline double getDistance(const Vector2 &v2) const;

	inline double getDistanceSquared(const Vector2 &v2)const;

	inline void Reflect(const Vector2& norm);

	inline Vector2 getReverse() const;


	//we need some overloaded operators
	const Vector2& operator+=(const Vector2 &rhs)
	{
		x += rhs.x;
		y += rhs.y;

		return *this;
	}

	const Vector2& operator-=(const Vector2 &rhs)
	{
		x -= rhs.x;
		y -= rhs.y;

		return *this;
	}

	const Vector2& operator*=(const double& rhs)
	{
		x *= rhs;
		y *= rhs;

		return *this;
	}

	const Vector2& operator/=(const double& rhs)
	{
		x /= rhs;
		y /= rhs;

		return *this;
	}

	bool operator==(const Vector2& rhs)const
	{
		return (isEqual(x, rhs.x) && isEqual(y, rhs.y));
	}

	bool operator!=(const Vector2& rhs)const
	{
		return (x != rhs.x) || (y != rhs.y);
	}

};

inline Vector2 operator*(const Vector2 &lhs, double rhs);
inline Vector2 operator*(double lhs, const Vector2 &rhs);
inline Vector2 operator-(const Vector2 &lhs, const Vector2 &rhs);
inline Vector2 operator+(const Vector2 &lhs, const Vector2 &rhs);
inline Vector2 operator/(const Vector2 &lhs, double val);

inline double Vector2::getLength()const
{
	return sqrt(x * x + y * y);
}

inline double Vector2::getLengthSquared() const
{
	return (x * x + y * y);
}

inline double Vector2::dot(const Vector2& v2) const
{
	return x*v2.x + y*v2.y;
}

// returns positive if v2 is clockwise of this vector,
// minus if anticlockwise (Y axis pointing down, X axis to right)
enum 
{ 
	clockwise = 1,
	anticlockwise = -1 
};

inline int Vector2::getSign(const Vector2& v2)const
{
	if (y*v2.x > x*v2.y)
	{
		return anticlockwise;
	}
	else
	{
		return clockwise;
	}
}

inline Vector2 Vector2::getPerpendicular() const
{
	return Vector2(-y, x);
}

// calculates the euclidean distance between two vectors
inline double Vector2::getDistance(const Vector2 &v2) const
{
	double ySeparation = v2.y - y;
	double xSeparation = v2.x - x;

	return sqrt(ySeparation*ySeparation + xSeparation*xSeparation);
}

// calculates the euclidean distance squared between two vectors 
inline double Vector2::getDistanceSquared(const Vector2 &v2) const
{
	double ySeparation = v2.y - y;
	double xSeparation = v2.x - x;

	return ySeparation*ySeparation + xSeparation*xSeparation;
}

// truncates a vector so that its length does not exceed max
inline void Vector2::truncate(double max)
{
	if (this->getLength() > max)
	{
		this->normalize();
		*this *= max;
	}
}

// given a normalized vector this method reflects the vector it is operating upon
// (like the path of a ball bouncing off a wall)
inline void Vector2::Reflect(const Vector2& norm)
{
	*this += 2.0 * this->dot(norm) * norm.getReverse();
}

inline Vector2 Vector2::getReverse() const
{
	return Vector2(-this->x, -this->y);
}

inline void Vector2::normalize()
{
	double vector_length = this->getLength();

	if (vector_length > std::numeric_limits<double>::epsilon())
	{
		this->x /= vector_length;
		this->y /= vector_length;
	}
}

// static
inline Vector2 Vector2::getNormalized(const Vector2& v)
{
	Vector2 vec = v;

	double vectorLength = vec.getLength();

	if (vectorLength > std::numeric_limits<double>::epsilon())
	{
		vec.x /= vectorLength;
		vec.y /= vectorLength;
	}

	return vec;
}

// static
inline double Vector2::getDistance(const Vector2& v1, const Vector2& v2)
{
	double ySeparation = v2.y - v1.y;
	double xSeparation = v2.x - v1.x;

	return sqrt(ySeparation*ySeparation + xSeparation*xSeparation);
}

// static
inline double Vector2::getDistanceSquared(const Vector2& v1, const Vector2& v2)
{
	double ySeparation = v2.y - v1.y;
	double xSeparation = v2.x - v1.x;

	return ySeparation*ySeparation + xSeparation*xSeparation;
}

inline double Vec2DLength(const Vector2& v)
{
	return sqrt(v.x*v.x + v.y*v.y);
}

inline double Vec2DLengthSq(const Vector2& v)
{
	return (v.x*v.x + v.y*v.y);
}

inline Vector2 operator*(const Vector2 &lhs, double rhs)
{
	Vector2 result(lhs);
	result *= rhs;
	return result;
}

inline Vector2 operator*(double lhs, const Vector2 &rhs)
{
	Vector2 result(rhs);
	result *= lhs;
	return result;
}

// overload the - operator
inline Vector2 operator-(const Vector2 &lhs, const Vector2 &rhs)
{
	Vector2 result(lhs);
	result.x -= rhs.x;
	result.y -= rhs.y;

	return result;
}

// overload the + operator
inline Vector2 operator+(const Vector2 &lhs, const Vector2 &rhs)
{
	Vector2 result(lhs);
	result.x += rhs.x;
	result.y += rhs.y;

	return result;
}

// overload the / operator
inline Vector2 operator/(const Vector2 &lhs, double val)
{
	Vector2 result(lhs);
	result.x /= val;
	result.y /= val;

	return result;
}

// returns true if the target position is in the field of view of the entity
// positioned at posFirst facing in facingFirst
inline bool isSecondInFieldOfViewOfFirst(Vector2 firstPosition, Vector2 facingFirst, Vector2 posSecond, double fov)
{
	Vector2 toTarget = Vector2::getNormalized(posSecond - firstPosition);
	return facingFirst.dot(toTarget) >= cos(fov / 2.0);
}
