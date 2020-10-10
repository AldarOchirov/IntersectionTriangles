#pragma once

#include <utility>
#include "OchirovA_lineSegment.h"
#include "OchirovA_plane.h"
#include "OchirovA_point.h"
#include "OchirovA_triangle.h"

namespace OchirovA
{
	const static double s_EPSILON = 0.0e-12;
	double det(double a11, double a12, double a21, double a22);
	bool pointOnLineSegment(double parameter);
	std::pair<CPoint, double> getLinePlaneIntersect(const CPlane& plane, const CPoint& firstPoint, const CPoint& secondPoint);
	bool hasIntersectProjectionX(const CTriangle& triangle, const CLineSegment& lineSegment);
	bool hasIntersectProjectionY(const CTriangle& triangle, const CLineSegment& lineSegment);
	bool hasIntersectProjectionZ(const CTriangle& triangle, const CLineSegment& lineSegment);

	bool hasIntersectProjectionX(const CTriangle& triangle, const CPoint& point);
	bool hasIntersectProjectionY(const CTriangle& triangle, const CPoint& point);
	bool hasIntersectProjectionZ(const CTriangle& triangle, const CPoint& point);

	bool hasIntersect(const CTriangle& triangle, const CLineSegment& lineSegment);
	bool hasIntersect(const CTriangle& triangle, const CPoint& point);
	bool hasIntersect(const CTriangle& triangle, const CPlane& plane, const CPoint& firstPoint, const CPoint& secondPoint);
	bool separateSecondTrinagleOnLineSegments(const CTriangle& firstTriangle, const CTriangle& secondTriangle);
	bool hasIntersect(double t1[], double t2[]); //start function
}