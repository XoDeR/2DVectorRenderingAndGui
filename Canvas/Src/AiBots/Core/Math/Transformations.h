#pragma once

#include <vector>

#include "Vector2.h"
#include "Core/Math/Matrix3x3.h"
#include "Transformations.h"

// TODO remake to TransformSystem

//------------------------------------------------------------------------
//  Functions for converting 2D vectors between World and Local space.
//------------------------------------------------------------------------

// given a std::vector of 2D vectors, a position, orientation and scale,
// this function transforms the 2D vectors into the object's world space
inline std::vector<Vector2> getWorldTransform(std::vector<Vector2>& points, const Vector2& pos, const Vector2& forward, const Vector2& side, const Vector2& scale)
{
	// copy the original vertices into the buffer about to be transformed
	std::vector<Vector2> TranVector2Ds = points;

	// create a transformation matrix
	Matrix3x3 matTransform;

	// scale
	if ((scale.x != 1.0) || (scale.y != 1.0))
	{
		matTransform.scaleMatrix(scale.x, scale.y);
	}

	// rotate
	matTransform.rotate(forward, side);
	// and translate
	matTransform.translate(pos.x, pos.y);
	// now transform the object's vertices
	matTransform.applyTransformationMatrix(TranVector2Ds);

	return TranVector2Ds;
}

// given a std::vector of 2D vectors, a position and  orientation
// this function transforms the 2D vectors into the object's world space
inline std::vector<Vector2> getWorldTransform(std::vector<Vector2>& points, const Vector2& pos, const Vector2& forward, const Vector2& side)
{
	// copy the original vertices into the buffer about to be transformed
	std::vector<Vector2> TranVector2Ds = points;

	// create a transformation matrix
	Matrix3x3 matTransform;

	// rotate
	matTransform.rotate(forward, side);
	// and translate
	matTransform.translate(pos.x, pos.y);
	// now transform the object's vertices
	matTransform.applyTransformationMatrix(TranVector2Ds);

	return TranVector2Ds;
}

// Transforms a point from the agent's local space into world space
inline Vector2 getTransformedFromLocalSpaceToWorldSpace(const Vector2& point, const Vector2& AgentHeading, const Vector2& AgentSide, const Vector2& AgentPosition)
{
	// make a copy of the point
	Vector2 TransPoint = point;

	// create a transformation matrix
	Matrix3x3 matTransform;

	// rotate
	matTransform.rotate(AgentHeading, AgentSide);
	// and translate
	matTransform.translate(AgentPosition.x, AgentPosition.y);
	// now transform the vertices
	matTransform.applyTransformationMatrix(TransPoint);

	return TransPoint;
}

// Transforms a vector from the agent's local space into world space
inline Vector2 VectorToWorldSpace(const Vector2& vec, const Vector2& AgentHeading, const Vector2& AgentSide)
{
	// make a copy of the point
	Vector2 TransVec = vec;

	// create a transformation matrix
	Matrix3x3 matTransform;

	// rotate
	matTransform.rotate(AgentHeading, AgentSide);

	// now transform the vertices
	matTransform.applyTransformationMatrix(TransVec);

	return TransVec;
}

inline Vector2 getTransformedPointToLocalSpace(const Vector2& point, Vector2& AgentHeading, Vector2& AgentSide, Vector2& AgentPosition)
{
	// make a copy of the point
	Vector2 TransPoint = point;

	// create a transformation matrix
	Matrix3x3 matTransform;

	double Tx = -AgentPosition.dot(AgentHeading);
	double Ty = -AgentPosition.dot(AgentSide);

	// create the transformation matrix
	matTransform._11(AgentHeading.x);
	matTransform._12(AgentSide.x);
	matTransform._21(AgentHeading.y);
	matTransform._22(AgentSide.y);
	matTransform._31(Tx); 
	matTransform._32(Ty);

	// now transform the vertices
	matTransform.applyTransformationMatrix(TransPoint);

	return TransPoint;
}

inline Vector2 VectorToLocalSpace(const Vector2 &vec, const Vector2& AgentHeading, const Vector2& AgentSide)
{
	// make a copy of the point
	Vector2 TransPoint = vec;

	// create a transformation matrix
	Matrix3x3 matTransform;

	// create the transformation matrix
	matTransform._11(AgentHeading.x); matTransform._12(AgentSide.x);
	matTransform._21(AgentHeading.y); matTransform._22(AgentSide.y);

	// now transform the vertices
	matTransform.applyTransformationMatrix(TransPoint);

	return TransPoint;
}

// rotates 2D vector angle rads around the origin
inline void rotateVector2DAroundOrigin(Vector2& v, double angle)
{
	// create a transformation matrix
	Matrix3x3 mat;

	// rotate
	mat.rotate(angle);

	// now transform the object's vertices
	mat.applyTransformationMatrix(v);
}

// given an origin, a facing direction, a 'field of view' describing the 
// limit of the outer whiskers, a whisker length and the number of whiskers
// this method returns a vector containing the end positions of a series
// of whiskers radiating away from the origin and with equal distance between
// them. (like the spokes of a wheel clipped to a specific segment size)
inline std::vector<Vector2> createWhiskers(unsigned int NumWhiskers, double WhiskerLength, double fov, Vector2 facing, Vector2 origin)
{
	//this is the magnitude of the angle separating each whisker
	double SectorSize = fov / (double)(NumWhiskers - 1);

	std::vector<Vector2> whiskers;
	Vector2 temp;
	double angle = -fov*0.5;

	for (unsigned int w = 0; w < NumWhiskers; ++w)
	{
		// create the whisker extending outwards at this angle
		temp = facing;
		rotateVector2DAroundOrigin(temp, angle);
		whiskers.push_back(origin + WhiskerLength * temp);

		angle += SectorSize;
	}

	return whiskers;
}
