#pragma once
//------------------------------------------------------------------------
//  Math2D
//------------------------------------------------------------------------
#include "Core/Math/MathFn.h"
#include "Core/Math/Vector2.h"
#include "Core/Math/Matrix3x3.h"
#include "Core/Math/Transformations.h"

#include <math.h>
#include <vector>

// given a plane and a ray this function determines how far along the ray 
// an intersection occurs. Returns negative if the ray is parallel
inline double DistanceToRayPlaneIntersection(Vector2 RayOrigin, Vector2 RayHeading, Vector2 PlanePoint, /*any point on the plane*/ Vector2 PlaneNormal)
{

	double d = -PlaneNormal.dot(PlanePoint);
	double numer = PlaneNormal.dot(RayOrigin) + d;
	double denom = PlaneNormal.dot(RayHeading);

	// normal is parallel to vector
	if ((denom < 0.000001) && (denom > -0.000001))
	{
		return (-1.0);
	}

	return -(numer / denom);
}

enum span_type{ plane_backside, plane_front, on_plane };

// PointOnPlane -- any point on the plane
inline span_type WhereIsPoint(Vector2 point, Vector2 PointOnPlane, Vector2 PlaneNormal)
{
	Vector2 dir = PointOnPlane - point;

	double d = dir.dot(PlaneNormal);

	if (d < -0.000001)
	{
		return plane_front;
	}

	else if (d > 0.000001)
	{
		return plane_backside;
	}

	return on_plane;
}

const double pi = 3.14159;

inline double GetRayCircleIntersect(Vector2 RayOrigin, Vector2 RayHeading, Vector2 CircleOrigin, double radius)
{

	Vector2 ToCircle = CircleOrigin - RayOrigin;
	double length = ToCircle.getLength();
	double v = ToCircle.dot(RayHeading);
	double d = radius*radius - (length*length - v*v);

	// If there was no intersection, return -1
	if (d < 0.0) return (-1.0);

	// Return the distance to the [first] intersecting point
	return (v - sqrt(d));
}

inline bool DoRayCircleIntersect(Vector2 RayOrigin, Vector2 RayHeading, Vector2 CircleOrigin, double radius)
{

	Vector2 ToCircle = CircleOrigin - RayOrigin;
	double length = ToCircle.getLength();
	double v = ToCircle.dot(RayHeading);
	double d = radius*radius - (length*length - v*v);

	// If there was no intersection, return -1
	return (d < 0.0);
}

// Given a point P and a circle of radius R centered at C this function
// determines the two points on the circle that intersect with the 
// tangents from P to the circle. Returns false if P is within the circle.
inline bool GetTangentPoints(Vector2 C, double R, Vector2 P, Vector2& T1, Vector2& T2)
{
	Vector2 PmC = P - C;
	double SqrLen = PmC.getLengthSquared();
	double RSqr = R*R;
	if (SqrLen <= RSqr)
	{
		// P is inside or on the circle
		return false;
	}

	double InvSqrLen = 1 / SqrLen;
	double Root = sqrt(fabs(SqrLen - RSqr));

	T1.x = C.x + R*(R*PmC.x - PmC.y*Root)*InvSqrLen;
	T1.y = C.y + R*(R*PmC.y + PmC.x*Root)*InvSqrLen;
	T2.x = C.x + R*(R*PmC.x + PmC.y*Root)*InvSqrLen;
	T2.y = C.y + R*(R*PmC.y - PmC.x*Root)*InvSqrLen;

	return true;
}

// given a line segment AB and a point P, this function calculates the perpendicular distance between them
inline double getDistanceToLineSegment(Vector2 A, Vector2 B, Vector2 P)
{
	//if the angle is obtuse between PA and AB is obtuse then the closest
	//vertex must be A
	double dotA = (P.x - A.x)*(B.x - A.x) + (P.y - A.y)*(B.y - A.y);

	if (dotA <= 0) return Vector2::getDistance(A, P);

	// if the angle is obtuse between PB and AB is obtuse then the closest vertex must be B
	double dotB = (P.x - B.x)*(A.x - B.x) + (P.y - B.y)*(A.y - B.y);

	if (dotB <= 0) return Vector2::getDistance(B, P);

	// calculate the point along AB that is the closest to P
	Vector2 Point = A + ((B - A) * dotA) / (dotA + dotB);

	// calculate the distance P-Point
	return Vector2::getDistance(P, Point);
}

// as above, but avoiding sqrt
inline double DistToLineSegmentSq(Vector2 A, Vector2 B, Vector2 P)
{
	// if the angle is obtuse between PA and AB is obtuse then the closest vertex must be A
	double dotA = (P.x - A.x)*(B.x - A.x) + (P.y - A.y)*(B.y - A.y);

	if (dotA <= 0) return Vector2::getDistanceSquared(A, P);

	// if the angle is obtuse between PB and AB is obtuse then the closest vertex must be B
	double dotB = (P.x - B.x)*(A.x - B.x) + (P.y - B.y)*(A.y - B.y);

	if (dotB <= 0) return Vector2::getDistanceSquared(B, P);

	// calculate the point along AB that is the closest to P
	Vector2 Point = A + ((B - A) * dotA) / (dotA + dotB);

	//calculate the distance P-Point
	return Vector2::getDistanceSquared(P, Point);
}


// Given 2 lines in 2D space AB, CD this returns true if an intersection occurs.
inline bool doLinesIntersect2D(Vector2 A, Vector2 B, Vector2 C, Vector2 D)
{
	double rTop = (A.y - C.y)*(D.x - C.x) - (A.x - C.x)*(D.y - C.y);
	double sTop = (A.y - C.y)*(B.x - A.x) - (A.x - C.x)*(B.y - A.y);

	double Bot = (B.x - A.x)*(D.y - C.y) - (B.y - A.y)*(D.x - C.x);

	if (Bot == 0)//parallel
	{
		return false;
	}

	double invBot = 1.0 / Bot;
	double r = rTop * invBot;
	double s = sTop * invBot;

	if ((r > 0) && (r < 1) && (s > 0) && (s < 1))
	{
		//lines intersect
		return true;
	}

	//lines do not intersect
	return false;
}

//	Given 2 lines in 2D space AB, CD this returns true if an 
//	intersection occurs and sets dist to the distance the intersection occurs along AB
inline bool doLinesIntersect2D(Vector2 A, Vector2 B, Vector2 C, Vector2 D, double& dist)
{
	double rTop = (A.y - C.y)*(D.x - C.x) - (A.x - C.x)*(D.y - C.y);
	double sTop = (A.y - C.y)*(B.x - A.x) - (A.x - C.x)*(B.y - A.y);

	double Bot = (B.x - A.x)*(D.y - C.y) - (B.y - A.y)*(D.x - C.x);


	if (Bot == 0)//parallel
	{
		if (isEqual(rTop, 0) && isEqual(sTop, 0))
		{
			return true;
		}
		return false;
	}

	double r = rTop / Bot;
	double s = sTop / Bot;

	if ((r > 0) && (r < 1) && (s > 0) && (s < 1))
	{
		dist = Vector2::getDistance(A, B) * r;

		return true;
	}

	else
	{
		dist = 0;

		return false;
	}
}

//	Given 2 lines in 2D space AB, CD this returns true if an 
//	intersection occurs and sets dist to the distance the intersection
//  occurs along AB. Also sets the 2d vector point to the point of intersection
inline bool doLinesIntersect2D(Vector2 A, Vector2 B, Vector2 C, Vector2 D, double& dist, Vector2& point)
{
	double rTop = (A.y - C.y)*(D.x - C.x) - (A.x - C.x)*(D.y - C.y);
	double rBot = (B.x - A.x)*(D.y - C.y) - (B.y - A.y)*(D.x - C.x);

	double sTop = (A.y - C.y)*(B.x - A.x) - (A.x - C.x)*(B.y - A.y);
	double sBot = (B.x - A.x)*(D.y - C.y) - (B.y - A.y)*(D.x - C.x);

	if ((rBot == 0) || (sBot == 0))
	{
		//lines are parallel
		return false;
	}

	double r = rTop / rBot;
	double s = sTop / sBot;

	if ((r > 0) && (r < 1) && (s > 0) && (s < 1))
	{
		dist = Vector2::getDistance(A, B) * r;

		point = A + r * (B - A);

		return true;
	}

	else
	{
		dist = 0;

		return false;
	}
}

//----------------------- ObjectIntersection2D ---------------------------
//
//  tests two polygons for intersection. *Does not check for enclosure*
//------------------------------------------------------------------------
inline bool ObjectIntersection2D(const std::vector<Vector2>& object1,
	const std::vector<Vector2>& object2)
{
	//test each line segment of object1 against each segment of object2
	for (unsigned int r = 0; r < object1.size() - 1; ++r)
	{
		for (unsigned int t = 0; t < object2.size() - 1; ++t)
		{
			if (doLinesIntersect2D(object2[t], object2[t + 1], object1[r], object1[r + 1]))
			{
				return true;
			}
		}
	}

	return false;
}

//  tests a line segment against a polygon for intersection
//  Does not check for enclosure
inline bool SegmentObjectIntersection2D(const Vector2& A, const Vector2& B, const std::vector<Vector2>& object)
{
	//test AB against each segment of object
	for (unsigned int r = 0; r < object.size() - 1; ++r)
	{
		if (doLinesIntersect2D(A, B, object[r], object[r + 1]))
		{
			return true;
		}
	}

	return false;
}

// Returns true if the two circles overlap
inline bool areCirclesOverlapped(double x1, double y1, double r1, double x2, double y2, double r2)
{
	double DistBetweenCenters = sqrt((x1 - x2) * (x1 - x2) +
		(y1 - y2) * (y1 - y2));

	if ((DistBetweenCenters < (r1 + r2)) || (DistBetweenCenters < fabs(r1 - r2)))
	{
		return true;
	}

	return false;
}

// Returns true if the two circles overlap
inline bool areCirclesOverlapped(Vector2 c1, double r1, Vector2 c2, double r2)
{
	double DistBetweenCenters = sqrt((c1.x - c2.x) * (c1.x - c2.x) +
		(c1.y - c2.y) * (c1.y - c2.y));

	if ((DistBetweenCenters < (r1 + r2)) || (DistBetweenCenters < fabs(r1 - r2)))
	{
		return true;
	}

	return false;
}

//--------------------------- TwoCirclesEnclosed ---------------------------
//
//  returns true if one circle encloses the other
//-------------------------------------------------------------------------
inline bool TwoCirclesEnclosed(double x1, double y1, double r1,
	double x2, double y2, double r2)
{
	double DistBetweenCenters = sqrt((x1 - x2) * (x1 - x2) +
		(y1 - y2) * (y1 - y2));

	if (DistBetweenCenters < fabs(r1 - r2))
	{
		return true;
	}

	return false;
}

// Given two circles this function calculates the intersection points of any overlap.
inline bool TwoCirclesIntersectionPoints(double x1, double y1, double r1,
	double x2, double y2, double r2,
	double &p3X, double &p3Y,
	double &p4X, double &p4Y)
{
	// first check to see if they overlap
	if (!areCirclesOverlapped(x1, y1, r1, x2, y2, r2))
	{
		return false;
	}

	//calculate the distance between the circle centers
	double d = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));

	//Now calculate the distance from the center of each circle to the center
	//of the line which connects the intersection points.
	double a = (r1 - r2 + (d * d)) / (2 * d);
	double b = (r2 - r1 + (d * d)) / (2 * d);


	//MAYBE A TEST FOR EXACT OVERLAP? 

	//calculate the point P2 which is the center of the line which 
	//connects the intersection points
	double p2X, p2Y;

	p2X = x1 + a * (x2 - x1) / d;
	p2Y = y1 + a * (y2 - y1) / d;

	//calculate first point
	double h1 = sqrt((r1 * r1) - (a * a));

	p3X = p2X - h1 * (y2 - y1) / d;
	p3Y = p2Y + h1 * (x2 - x1) / d;


	//calculate second point
	double h2 = sqrt((r2 * r2) - (a * a));

	p4X = p2X + h2 * (y2 - y1) / d;
	p4Y = p2Y - h2 * (x2 - x1) / d;

	return true;

}

// Tests to see if two circles overlap and if so calculates the area
// defined by the union
inline double TwoCirclesIntersectionArea(double x1, double y1, double r1,
	double x2, double y2, double r2)
{
	//first calculate the intersection points
	double iX1, iY1, iX2, iY2;

	if (!TwoCirclesIntersectionPoints(x1, y1, r1, x2, y2, r2, iX1, iY1, iX2, iY2))
	{
		return 0.0; //no overlap
	}

	//calculate the distance between the circle centers
	double d = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));

	// find the angles given that A and B are the two circle centers
	// and C and D are the intersection points
	double CBD = 2 * acos((r2*r2 + d*d - r1*r1) / (r2 * d * 2));

	double CAD = 2 * acos((r1*r1 + d*d - r2*r2) / (r1 * d * 2));


	// Then we find the segment of each of the circles cut off by the 
	// chord CD, by taking the area of the sector of the circle BCD and
	// subtracting the area of triangle BCD. Similarly we find the area
	// of the sector ACD and subtract the area of triangle ACD.

	double area = 0.5f*CBD*r2*r2 - 0.5f*r2*r2*sin(CBD) +
		0.5f*CAD*r1*r1 - 0.5f*r1*r1*sin(CAD);

	return area;
}

// given the radius, calculates the area of a circle
inline double CircleArea(double radius)
{
	return pi * radius * radius;
}

// returns true if the point p is within the radius of the given circle
inline bool getIsPointInCircle(Vector2 center, double radius, Vector2 point)
{
	double distanceFromCenterSquared = (point - center).getLengthSquared();

	if (distanceFromCenterSquared < (radius*radius))
	{
		return true;
	}

	return false;
}

// returns true if the line segment AB intersects with a circle at position P with radius radius
inline bool doLineSegmentAndCircleIntersect(Vector2 A, Vector2 B, Vector2 P, double radius)
{
	// first determine the distance from the center of the circle to
	// the line segment (working in distance squared space)
	double DistToLineSq = DistToLineSegmentSq(A, B, P);

	if (DistToLineSq < radius*radius)
	{
		return true;
	}

	else
	{
		return false;
	}

}

// given a line segment AB and a circle position and radius
// determines if there is an intersection and stores the position of the closest intersection in the reference IntersectionPoint
// returns false if no intersection point is found
inline bool getLineSegmentCircleClosestIntersectionPoint(Vector2 A, Vector2 B, Vector2 pos, double radius, Vector2& intersectionPoint)
{
	Vector2 toBNorm = Vector2::getNormalized(B - A);

	// move the circle into the local space defined by the vector B-A with origin at A
	Vector2 LocalPos = getTransformedPointToLocalSpace(pos, toBNorm, toBNorm.getPerpendicular(), A);

	bool ipFound = false;

	// if the local position + the radius is negative then the circle lays behind
	// point A so there is no intersection possible. If the local x pos minus the 
	// radius is greater than length A-B then the circle cannot intersect the line segment
	if ((LocalPos.x + radius >= 0) && ((LocalPos.x - radius)*(LocalPos.x - radius) <= Vector2::getDistanceSquared(B, A)))
	{
		// if the distance from the x axis to the object's position is less than its radius then there is a potential intersection.
		if (fabs(LocalPos.y) < radius)
		{
			// now to do a line/circle intersection test. The center of the 
			// circle is represented by A, B. The intersection points are 
			// given by the formulae x = A +/-sqrt(r^2-B^2), y=0. We only 
			// need to look at the smallest positive value of x.
			double a = LocalPos.x;
			double b = LocalPos.y;

			double ip = a - sqrt(radius*radius - b*b);

			if (ip <= 0)
			{
				ip = a + sqrt(radius*radius - b*b);
			}

			ipFound = true;

			intersectionPoint = A + toBNorm*ip;
		}
	}

	return ipFound;
}
