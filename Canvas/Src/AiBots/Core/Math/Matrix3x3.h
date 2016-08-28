#pragma once

// 2D Matrix class 
#include <math.h>
#include <vector>

#include "Core/Math/MathFn.h"
#include "Core/Math/Vector2.h"

class Matrix3x3
{
public:
	Matrix3x3()
	{
		// initialize the matrix to an identity matrix
		setToIdentityMatrix();
	}

	// create an identity matrix
	inline void setToIdentityMatrix();

	// create a transformation matrix
	inline void translate(double x, double y);

	// create a scale matrix
	inline void scaleMatrix(double xScale, double yScale);

	// create a rotation matrix
	inline void rotate(double rotation);

	// create a rotation matrix from a fwd and side 2D vector
	inline void  rotate(const Vector2 &fwd, const Vector2 &side);

	// applies a transformation matrix to a std::vector of points
	inline void applyTransformationMatrix(std::vector<Vector2>& vPoints);

	// applies a transformation matrix to a point
	inline void applyTransformationMatrix(Vector2& vPoint);

	//accessors to the matrix elements
	void _11(double val){ matrixInner._11 = val; }
	void _12(double val){ matrixInner._12 = val; }
	void _13(double val){ matrixInner._13 = val; }

	void _21(double val){ matrixInner._21 = val; }
	void _22(double val){ matrixInner._22 = val; }
	void _23(double val){ matrixInner._23 = val; }

	void _31(double val){ matrixInner._31 = val; }
	void _32(double val){ matrixInner._32 = val; }
	void _33(double val){ matrixInner._33 = val; }

private:
	struct Matrix
	{
		double _11, _12, _13;
		double _21, _22, _23;
		double _31, _32, _33;

		Matrix()
		{
			_11 = 0.0; _12 = 0.0; _13 = 0.0;
			_21 = 0.0; _22 = 0.0; _23 = 0.0;
			_31 = 0.0; _32 = 0.0; _33 = 0.0;
		}
	};

	Matrix matrixInner;

	// multiplies matrixInner with mIn
	inline void MatrixMultiply(Matrix& mIn);
};

// multiply two matrices together
inline void Matrix3x3::MatrixMultiply(Matrix &mIn)
{
	Matrix3x3::Matrix mat_temp;

	// first row
	mat_temp._11 = (matrixInner._11*mIn._11) + (matrixInner._12*mIn._21) + (matrixInner._13*mIn._31);
	mat_temp._12 = (matrixInner._11*mIn._12) + (matrixInner._12*mIn._22) + (matrixInner._13*mIn._32);
	mat_temp._13 = (matrixInner._11*mIn._13) + (matrixInner._12*mIn._23) + (matrixInner._13*mIn._33);

	// second
	mat_temp._21 = (matrixInner._21*mIn._11) + (matrixInner._22*mIn._21) + (matrixInner._23*mIn._31);
	mat_temp._22 = (matrixInner._21*mIn._12) + (matrixInner._22*mIn._22) + (matrixInner._23*mIn._32);
	mat_temp._23 = (matrixInner._21*mIn._13) + (matrixInner._22*mIn._23) + (matrixInner._23*mIn._33);

	// third
	mat_temp._31 = (matrixInner._31*mIn._11) + (matrixInner._32*mIn._21) + (matrixInner._33*mIn._31);
	mat_temp._32 = (matrixInner._31*mIn._12) + (matrixInner._32*mIn._22) + (matrixInner._33*mIn._32);
	mat_temp._33 = (matrixInner._31*mIn._13) + (matrixInner._32*mIn._23) + (matrixInner._33*mIn._33);

	matrixInner = mat_temp;
}

inline void Matrix3x3::applyTransformationMatrix(std::vector<Vector2>& vPoint)
{
	for (unsigned int i = 0; i < vPoint.size(); ++i)
	{
		double tempX = (matrixInner._11*vPoint[i].x) + (matrixInner._21*vPoint[i].y) + (matrixInner._31);
		double tempY = (matrixInner._12*vPoint[i].x) + (matrixInner._22*vPoint[i].y) + (matrixInner._32);
		vPoint[i].x = tempX;
		vPoint[i].y = tempY;
	}
}

inline void Matrix3x3::applyTransformationMatrix(Vector2& vPoint)
{
	double tempX = (matrixInner._11*vPoint.x) + (matrixInner._21*vPoint.y) + (matrixInner._31);
	double tempY = (matrixInner._12*vPoint.x) + (matrixInner._22*vPoint.y) + (matrixInner._32);
	vPoint.x = tempX;
	vPoint.y = tempY;
}

// create an identity matrix
inline void Matrix3x3::setToIdentityMatrix()
{
	matrixInner._11 = 1;
	matrixInner._12 = 0;
	matrixInner._13 = 0;

	matrixInner._21 = 0;
	matrixInner._22 = 1;
	matrixInner._23 = 0;

	matrixInner._31 = 0;
	matrixInner._32 = 0;
	matrixInner._33 = 1;
}

// create a transformation matrix
inline void Matrix3x3::translate(double x, double y)
{
	Matrix mat;
	mat._11 = 1;
	mat._12 = 0;
	mat._13 = 0;
	mat._21 = 0;
	mat._22 = 1;
	mat._23 = 0;
	mat._31 = x;
	mat._32 = y;
	mat._33 = 1;

	// and multiply
	MatrixMultiply(mat);
}

// create a scale matrix
inline void Matrix3x3::scaleMatrix(double xScale, double yScale)
{
	Matrix3x3::Matrix mat;

	mat._11 = xScale; mat._12 = 0; mat._13 = 0;

	mat._21 = 0; mat._22 = yScale; mat._23 = 0;

	mat._31 = 0; mat._32 = 0; mat._33 = 1;

	// and multiply
	MatrixMultiply(mat);
}

inline void Matrix3x3::rotate(double rot)
{
	Matrix3x3::Matrix mat;

	double Sin = sin(rot);
	double Cos = cos(rot);

	mat._11 = Cos;  mat._12 = Sin; mat._13 = 0;

	mat._21 = -Sin; mat._22 = Cos; mat._23 = 0;

	mat._31 = 0; mat._32 = 0; mat._33 = 1;

	MatrixMultiply(mat);
}

inline void Matrix3x3::rotate(const Vector2& fwd, const Vector2& side)
{
	Matrix3x3::Matrix mat;

	mat._11 = fwd.x;  mat._12 = fwd.y; mat._13 = 0;

	mat._21 = side.x; mat._22 = side.y; mat._23 = 0;

	mat._31 = 0; mat._32 = 0; mat._33 = 1;

	// and multiply
	MatrixMultiply(mat);
}
