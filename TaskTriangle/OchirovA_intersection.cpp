#include "OchirovA_intersection.h"

using namespace OchirovA;

double OchirovA::dist(const CPoint& firstPoint, const CPoint& secondPoint)
{
	return sqrt((firstPoint.getX() - secondPoint.getX()) * (firstPoint.getX() - secondPoint.getX())
		+ (firstPoint.getY() - secondPoint.getY()) * (firstPoint.getY() - secondPoint.getY())
		+ (firstPoint.getZ() - secondPoint.getZ()) * (firstPoint.getZ() - secondPoint.getZ()));
}

double OchirovA::det(double a11, double a12, double a21, double a22)
{
	return a11 * a22 - a12 * a21;
}

double OchirovA::tripleProduct(const CPoint& firstVector, const CPoint& secondVector, const CPoint& thirdVector)
{
	return firstVector.getX() * secondVector.getY() * thirdVector.getZ()
		+ firstVector.getY() * secondVector.getZ() * thirdVector.getX()
		+ firstVector.getZ() * secondVector.getX() * thirdVector.getY()
		- firstVector.getZ() * secondVector.getY() * thirdVector.getX()
		- firstVector.getY() * secondVector.getX() * thirdVector.getZ()
		- firstVector.getX() * secondVector.getZ() * thirdVector.getY();
}

bool OchirovA::pointOnLineSegment(double parameter)
{
	return (parameter >= 0.0 && parameter <= 1.0);
}

std::pair<bool, double> OchirovA::getLinePlaneIntersect(const CPlane& plane, const CPoint& firstPoint, const CPoint& secondPoint, CPoint& intersectionPoint)
{
	const auto denominator = plane.getA() * (secondPoint.getX() - firstPoint.getX())
		+ plane.getB() * (secondPoint.getY() - firstPoint.getY())
		+ plane.getC() * (secondPoint.getZ() - firstPoint.getZ()); 

	const auto numerator = (plane.getA() * firstPoint.getX()
		+ plane.getB() * firstPoint.getY()
		+ plane.getC() * firstPoint.getZ() + plane.getD());

	if (fabs(denominator) <= s_EPSILON)
	{
		if (fabs(numerator) <= s_EPSILON)
			return std::make_pair(false, s_LINE_IN_PLANE); //line in plane
		else
			return std::make_pair(false, s_LINE_PARALLEL_PLANE); //line parallel to plane
	}

	auto parameter = -numerator / denominator;

	auto x = firstPoint.getX() + parameter * (secondPoint.getX() - firstPoint.getX());
	auto y = firstPoint.getY() + parameter * (secondPoint.getY() - firstPoint.getY());
	auto z = firstPoint.getZ() + parameter * (secondPoint.getZ() - firstPoint.getZ());

	CPoint point(x,y,z);
	intersectionPoint = point;

	return std::make_pair(true, parameter);
}

bool OchirovA::hasIntersectProjectionX(const CTriangle& triangle, const CLineSegment& lineSegment)
{
	auto firstValue = (triangle.getPointA().getY() - lineSegment.getPointA().getY())
		* (lineSegment.getPointB().getZ() - lineSegment.getPointA().getZ())
		- (triangle.getPointA().getZ() - lineSegment.getPointA().getZ())
		* (lineSegment.getPointB().getY() - lineSegment.getPointA().getY());

	auto secondValue = (triangle.getPointB().getY() - lineSegment.getPointA().getY())
		* (lineSegment.getPointB().getZ() - lineSegment.getPointA().getZ())
		- (triangle.getPointB().getZ() - lineSegment.getPointA().getZ())
		* (lineSegment.getPointB().getY() - lineSegment.getPointA().getY());

	auto thirdValue = (triangle.getPointC().getY() - lineSegment.getPointA().getY())
		* (lineSegment.getPointB().getZ() - lineSegment.getPointA().getZ())
		- (triangle.getPointC().getZ() - lineSegment.getPointA().getZ())
		* (lineSegment.getPointB().getY() - lineSegment.getPointA().getY());

	if ((firstValue > 0.0 && secondValue > 0.0 && thirdValue > 0.0)
		|| (firstValue < 0.0 && secondValue < 0.0 && thirdValue < 0.0))
		return false;

	if (fabs(firstValue) <= s_EPSILON)
	{
		double parameter;

		if ((lineSegment.getPointB().getY() - lineSegment.getPointA().getY()) > s_EPSILON)
			parameter = (triangle.getPointA().getY() - lineSegment.getPointA().getY())
			/ (lineSegment.getPointB().getY() - lineSegment.getPointA().getY());
		else
			parameter = (triangle.getPointA().getZ() - lineSegment.getPointA().getZ())
			/ (lineSegment.getPointB().getZ() - lineSegment.getPointA().getZ());

		if (pointOnLineSegment(parameter))
			return true;

		return false;
	}

	if (fabs(secondValue) <= s_EPSILON)
	{
		double parameter;
		if ((lineSegment.getPointB().getY() - lineSegment.getPointA().getY()) > s_EPSILON)
			parameter = (triangle.getPointB().getY() - lineSegment.getPointA().getY())
			/ (lineSegment.getPointB().getY() - lineSegment.getPointA().getY());
		else
			parameter = (triangle.getPointB().getZ() - lineSegment.getPointA().getZ())
			/ (lineSegment.getPointB().getZ() - lineSegment.getPointA().getZ());

		if (pointOnLineSegment(parameter))
			return true;

		return false;
	}

	if (fabs(thirdValue) <= s_EPSILON)
	{
		double parameter;
		if ((lineSegment.getPointB().getY() - lineSegment.getPointA().getY()) > s_EPSILON)
			parameter = (triangle.getPointC().getY() - lineSegment.getPointA().getY())
			/ (lineSegment.getPointB().getY() - lineSegment.getPointA().getY());
		else
			parameter = (triangle.getPointC().getZ() - lineSegment.getPointA().getZ())
			/ (lineSegment.getPointB().getZ() - lineSegment.getPointA().getZ());

		if (pointOnLineSegment(parameter))
			return true;

		return false;
	}

	return true;
}

bool OchirovA::hasIntersectProjectionY(const CTriangle& triangle, const CLineSegment& lineSegment)
{
	auto firstValue = (triangle.getPointA().getX() - lineSegment.getPointA().getX())
		* (lineSegment.getPointB().getZ() - lineSegment.getPointA().getZ())
		- (triangle.getPointA().getZ() - lineSegment.getPointA().getZ())
		* (lineSegment.getPointB().getX() - lineSegment.getPointA().getX());

	auto secondValue = (triangle.getPointB().getX() - lineSegment.getPointA().getX())
		* (lineSegment.getPointB().getZ() - lineSegment.getPointA().getZ())
		- (triangle.getPointB().getZ() - lineSegment.getPointA().getZ())
		* (lineSegment.getPointB().getX() - lineSegment.getPointA().getX());

	auto thirdValue = (triangle.getPointC().getX() - lineSegment.getPointA().getX())
		* (lineSegment.getPointB().getZ() - lineSegment.getPointA().getZ())
		- (triangle.getPointC().getZ() - lineSegment.getPointA().getZ())
		* (lineSegment.getPointB().getX() - lineSegment.getPointA().getX());

	if ((firstValue > 0.0 && secondValue > 0.0 && thirdValue > 0.0)
		|| (firstValue < 0.0 && secondValue < 0.0 && thirdValue < 0.0))
		return false;

	if (fabs(firstValue) <= s_EPSILON)
	{
		double parameter;

		if ((lineSegment.getPointB().getX() - lineSegment.getPointA().getX()) > s_EPSILON)
			parameter = (triangle.getPointA().getX() - lineSegment.getPointA().getX())
			/ (lineSegment.getPointB().getX() - lineSegment.getPointA().getX());
		else
			parameter = (triangle.getPointA().getZ() - lineSegment.getPointA().getZ())
			/ (lineSegment.getPointB().getZ() - lineSegment.getPointA().getZ());

		if (pointOnLineSegment(parameter))
			return true;

		return false;
	}

	if (fabs(secondValue) <= s_EPSILON)
	{
		double parameter;
		if ((lineSegment.getPointB().getX() - lineSegment.getPointA().getX()) > s_EPSILON)
			parameter = (triangle.getPointB().getX() - lineSegment.getPointA().getX())
			/ (lineSegment.getPointB().getX() - lineSegment.getPointA().getX());
		else
			parameter = (triangle.getPointB().getZ() - lineSegment.getPointA().getZ())
			/ (lineSegment.getPointB().getZ() - lineSegment.getPointA().getZ());

		if (pointOnLineSegment(parameter))
			return true;

		return false;
	}

	if (fabs(thirdValue) <= s_EPSILON)
	{
		double parameter;
		if ((lineSegment.getPointB().getX() - lineSegment.getPointA().getX()) > s_EPSILON)
			parameter = (triangle.getPointC().getX() - lineSegment.getPointA().getX())
			/ (lineSegment.getPointB().getX() - lineSegment.getPointA().getX());
		else
			parameter = (triangle.getPointC().getZ() - lineSegment.getPointA().getZ())
			/ (lineSegment.getPointB().getZ() - lineSegment.getPointA().getZ());

		if (pointOnLineSegment(parameter))
			return true;

		return false;
	}

	return true;
}

bool OchirovA::hasIntersectProjectionZ(const CTriangle& triangle, const CLineSegment& lineSegment)
{
	auto firstValue = (triangle.getPointA().getX() - lineSegment.getPointA().getX())
		* (lineSegment.getPointB().getY() - lineSegment.getPointA().getY())
		- (triangle.getPointA().getY() - lineSegment.getPointA().getY())
		* (lineSegment.getPointB().getX() - lineSegment.getPointA().getX());

	auto secondValue = (triangle.getPointB().getX() - lineSegment.getPointA().getX())
		* (lineSegment.getPointB().getY() - lineSegment.getPointA().getY())
		- (triangle.getPointB().getY() - lineSegment.getPointA().getY())
		* (lineSegment.getPointB().getX() - lineSegment.getPointA().getX());

	auto thirdValue = (triangle.getPointC().getX() - lineSegment.getPointA().getX())
		* (lineSegment.getPointB().getY() - lineSegment.getPointA().getY())
		- (triangle.getPointC().getY() - lineSegment.getPointA().getY())
		* (lineSegment.getPointB().getX() - lineSegment.getPointA().getX());

	if ((firstValue > 0.0 && secondValue > 0.0 && thirdValue > 0.0)
		|| (firstValue < 0.0 && secondValue < 0.0 && thirdValue < 0.0))
		return false;

	if (fabs(firstValue) <= s_EPSILON)
	{
		double parameter;

		if ((lineSegment.getPointB().getX() - lineSegment.getPointA().getX()) > s_EPSILON)
			parameter = (triangle.getPointA().getX() - lineSegment.getPointA().getX())
				/ (lineSegment.getPointB().getX() - lineSegment.getPointA().getX());
		else
			parameter = (triangle.getPointA().getY() - lineSegment.getPointA().getY())
				/ (lineSegment.getPointB().getY() - lineSegment.getPointA().getY());

		if (pointOnLineSegment(parameter))
			return true;

		return false;
	}

	if (fabs(secondValue) <= s_EPSILON)
	{
		double parameter;
		if ((lineSegment.getPointB().getX() - lineSegment.getPointA().getX()) > s_EPSILON)
			parameter = (triangle.getPointB().getX() - lineSegment.getPointA().getX())
				/ (lineSegment.getPointB().getX() - lineSegment.getPointA().getX());
		else
			parameter = (triangle.getPointB().getY() - lineSegment.getPointA().getY())
				/ (lineSegment.getPointB().getY() - lineSegment.getPointA().getY());

		if (pointOnLineSegment(parameter))
			return true;

		return false;
	}
	
	if (fabs(thirdValue) <= s_EPSILON)
	{
		double parameter;
		if ((lineSegment.getPointB().getX() - lineSegment.getPointA().getX()) > s_EPSILON)
			parameter = (triangle.getPointC().getX() - lineSegment.getPointA().getX())
				/ (lineSegment.getPointB().getX() - lineSegment.getPointA().getX());
		else
			parameter = (triangle.getPointC().getY() - lineSegment.getPointA().getY())
				/ (lineSegment.getPointB().getY() - lineSegment.getPointA().getY());

		if (pointOnLineSegment(parameter))
			return true;

		return false;
	}
	
	return true;
}

bool OchirovA::hasIntersect(const CTriangle& triangle, const CLineSegment& lineSegment)
{
	if (fabs(triangle.getPointA().getX() - triangle.getPointB().getX()) <= s_EPSILON
		&& fabs(triangle.getPointB().getX() - triangle.getPointC().getX()) <= s_EPSILON)
		return hasIntersectProjectionX(triangle, lineSegment);

	if (fabs(triangle.getPointA().getY() - triangle.getPointB().getY()) <= s_EPSILON
		&& fabs(triangle.getPointB().getY() - triangle.getPointC().getY()) <= s_EPSILON)
		return hasIntersectProjectionY(triangle, lineSegment);

	if (fabs(triangle.getPointA().getZ() - triangle.getPointB().getZ()) <= s_EPSILON
		&& fabs(triangle.getPointB().getZ() - triangle.getPointC().getZ()) <= s_EPSILON)
		return hasIntersectProjectionZ(triangle, lineSegment);

	return hasIntersectProjectionZ(triangle, lineSegment);
}

bool OchirovA::hasIntersectProjectionX(const CTriangle& triangle, const CPoint& point)
{
	auto firstValue = (point.getY() - triangle.getPointA().getY())
		* (triangle.getPointB().getZ() - triangle.getPointA().getZ())
		- (point.getZ() - triangle.getPointA().getZ())
		* (triangle.getPointB().getY() - triangle.getPointA().getY());

	auto secondValue = (point.getY() - triangle.getPointB().getY())
		* (triangle.getPointC().getZ() - triangle.getPointB().getZ())
		- (point.getZ() - triangle.getPointB().getZ())
		* (triangle.getPointC().getY() - triangle.getPointB().getY());

	auto thirdValue = (point.getY() - triangle.getPointC().getY())
		* (triangle.getPointA().getZ() - triangle.getPointC().getZ())
		- (point.getZ() - triangle.getPointC().getZ())
		* (triangle.getPointA().getY() - triangle.getPointC().getY());

	if ((firstValue >= 0.0 && secondValue >= 0.0 && thirdValue >= 0.0)
		|| (firstValue <= 0.0 && secondValue <= 0.0 && thirdValue <= 0.0))
		return true;

	return false;
}

bool OchirovA::hasIntersectProjectionY(const CTriangle& triangle, const CPoint& point)
{
	auto firstValue = (point.getX() - triangle.getPointA().getX())
		* (triangle.getPointB().getZ() - triangle.getPointA().getZ())
		- (point.getZ() - triangle.getPointA().getZ())
		* (triangle.getPointB().getX() - triangle.getPointA().getX());

	auto secondValue = (point.getX() - triangle.getPointB().getX())
		* (triangle.getPointC().getZ() - triangle.getPointB().getZ())
		- (point.getZ() - triangle.getPointB().getZ())
		* (triangle.getPointC().getX() - triangle.getPointB().getX());

	auto thirdValue = (point.getX() - triangle.getPointC().getX())
		* (triangle.getPointA().getZ() - triangle.getPointC().getZ())
		- (point.getZ() - triangle.getPointC().getZ())
		* (triangle.getPointA().getX() - triangle.getPointC().getX());

	if ((firstValue >= 0.0 && secondValue >= 0.0 && thirdValue >= 0.0)
		|| (firstValue <= 0.0 && secondValue <= 0.0 && thirdValue <= 0.0))
		return true;

	return false;
}

bool OchirovA::hasIntersectProjectionZ(const CTriangle& triangle, const CPoint& point)
{
	auto firstValue = (point.getX() - triangle.getPointA().getX())
		* (triangle.getPointB().getY() - triangle.getPointA().getY())
		- (point.getY() - triangle.getPointA().getY())
		* (triangle.getPointB().getX() - triangle.getPointA().getX());

	auto secondValue = (point.getX() - triangle.getPointB().getX())
		* (triangle.getPointC().getY() - triangle.getPointB().getY())
		- (point.getY() - triangle.getPointB().getY())
		* (triangle.getPointC().getX() - triangle.getPointB().getX());

	auto thirdValue = (point.getX() - triangle.getPointC().getX())
		* (triangle.getPointA().getY() - triangle.getPointC().getY())
		- (point.getY() - triangle.getPointC().getY())
		* (triangle.getPointA().getX() - triangle.getPointC().getX());

	if ((firstValue >= 0.0 && secondValue >= 0.0 && thirdValue >= 0.0)
		|| (firstValue <= 0.0 && secondValue <= 0.0 && thirdValue <= 0.0))
		return true;

	return false;
}

bool OchirovA::hasIntersect(const CTriangle& triangle, const CPoint& point)
{
	if (fabs(triangle.getPointA().getX() - triangle.getPointB().getX()) <= s_EPSILON)
	{
		if (fabs(triangle.getPointA().getY() - triangle.getPointB().getY()) <= s_EPSILON)
			return hasIntersectProjectionX(triangle, point);
		else
			return hasIntersectProjectionY(triangle, point);
	}

	if (fabs(triangle.getPointA().getY() - triangle.getPointB().getY()) <= s_EPSILON)
	{
		if (fabs(triangle.getPointA().getZ() - triangle.getPointB().getZ()) <= s_EPSILON)
			return hasIntersectProjectionY(triangle, point);
		else
			return hasIntersectProjectionZ(triangle, point);
	}

	if (fabs(triangle.getPointA().getZ() - triangle.getPointB().getZ()) <= s_EPSILON)
	{
		if (fabs(triangle.getPointA().getX() - triangle.getPointB().getX()) <= s_EPSILON)
			return hasIntersectProjectionZ(triangle, point);
		else
			return hasIntersectProjectionX(triangle, point);
	}

	return hasIntersectProjectionZ(triangle, point);
}

bool OchirovA::hasIntersect(const CTriangle& triangle, const CPlane& plane, const CPoint& firstPoint, const CPoint& secondPoint)
{
	CPoint intersectionPoint;
	auto result = getLinePlaneIntersect(plane, firstPoint, secondPoint, intersectionPoint); //pair <bool, parameter>

	if (!result.first)
	{
		if (fabs(result.second) == s_LINE_PARALLEL_PLANE)
			return false;
		else
			return hasIntersect(triangle, CLineSegment(firstPoint, secondPoint));
	}

	if (pointOnLineSegment(result.second) && hasIntersect(triangle, intersectionPoint))
		return true;

	return false;
}

bool OchirovA::separateSecondTrinagleOnLineSegments(const CTriangle& firstTriangle, const CTriangle& secondTriangle)
{
	CPlane plane(firstTriangle);

	if (hasIntersect(firstTriangle, plane, secondTriangle.getPointA(), secondTriangle.getPointB()))
		return true;

	if (hasIntersect(firstTriangle, plane, secondTriangle.getPointB(), secondTriangle.getPointC()))
		return true;

	if (hasIntersect(firstTriangle, plane, secondTriangle.getPointC(), secondTriangle.getPointA()))
		return true;

	return false;
}

bool OchirovA::hasIntersectProjectionX(const CLineSegment& firstLineSegment, const CLineSegment& secondLineSegment)
{
	auto firstValue = (firstLineSegment.getPointA().getY() - secondLineSegment.getPointA().getY())
		* (secondLineSegment.getPointB().getZ() - secondLineSegment.getPointA().getZ())
		- (firstLineSegment.getPointA().getZ() - secondLineSegment.getPointA().getZ())
		* (secondLineSegment.getPointB().getY() - secondLineSegment.getPointA().getY());

	auto secondValue = (firstLineSegment.getPointB().getY() - secondLineSegment.getPointA().getY())
		* (secondLineSegment.getPointB().getZ() - secondLineSegment.getPointA().getZ())
		- (firstLineSegment.getPointB().getZ() - secondLineSegment.getPointA().getZ())
		* (secondLineSegment.getPointB().getY() - secondLineSegment.getPointA().getY());

	if ((firstValue > 0.0 && secondValue > 0.0)
		|| (firstValue < 0.0 && secondValue < 0.0))
		return false;

	if (fabs(firstValue) <= s_EPSILON)
	{
		double parameter;

		if ((secondLineSegment.getPointB().getY() - secondLineSegment.getPointA().getY()) > s_EPSILON)
			parameter = (firstLineSegment.getPointA().getY() - secondLineSegment.getPointA().getY())
			/ (secondLineSegment.getPointB().getY() - secondLineSegment.getPointA().getY());
		else
			parameter = (firstLineSegment.getPointA().getZ() - secondLineSegment.getPointA().getZ())
			/ (secondLineSegment.getPointB().getZ() - secondLineSegment.getPointA().getZ());

		if (pointOnLineSegment(parameter))
			return true;

		return false;
	}

	if (fabs(secondValue) <= s_EPSILON)
	{
		double parameter;
		if ((secondLineSegment.getPointB().getY() - secondLineSegment.getPointA().getY()) > s_EPSILON)
			parameter = (firstLineSegment.getPointB().getY() - secondLineSegment.getPointA().getY())
			/ (secondLineSegment.getPointB().getY() - secondLineSegment.getPointA().getY());
		else
			parameter = (firstLineSegment.getPointB().getZ() - secondLineSegment.getPointA().getZ())
			/ (secondLineSegment.getPointB().getZ() - secondLineSegment.getPointA().getZ());

		if (pointOnLineSegment(parameter))
			return true;

		return false;
	}

	return true;
}

bool OchirovA::hasIntersectProjectionY(const CLineSegment& firstLineSegment, const CLineSegment& secondLineSegment)
{
	auto firstValue = (firstLineSegment.getPointA().getX() - secondLineSegment.getPointA().getX())
		* (secondLineSegment.getPointB().getZ() - secondLineSegment.getPointA().getZ())
		- (firstLineSegment.getPointA().getZ() - secondLineSegment.getPointA().getZ())
		* (secondLineSegment.getPointB().getX() - secondLineSegment.getPointA().getX());

	auto secondValue = (firstLineSegment.getPointB().getX() - secondLineSegment.getPointA().getX())
		* (secondLineSegment.getPointB().getZ() - secondLineSegment.getPointA().getZ())
		- (firstLineSegment.getPointB().getZ() - secondLineSegment.getPointA().getZ())
		* (secondLineSegment.getPointB().getX() - secondLineSegment.getPointA().getX());

	if ((firstValue > 0.0 && secondValue > 0.0)
		|| (firstValue < 0.0 && secondValue < 0.0))
		return false;

	if (fabs(firstValue) <= s_EPSILON)
	{
		double parameter;

		if ((secondLineSegment.getPointB().getX() - secondLineSegment.getPointA().getX()) > s_EPSILON)
			parameter = (firstLineSegment.getPointA().getX() - secondLineSegment.getPointA().getX())
			/ (secondLineSegment.getPointB().getX() - secondLineSegment.getPointA().getX());
		else
			parameter = (firstLineSegment.getPointA().getZ() - secondLineSegment.getPointA().getZ())
			/ (secondLineSegment.getPointB().getZ() - secondLineSegment.getPointA().getZ());

		if (pointOnLineSegment(parameter))
			return true;

		return false;
	}

	if (fabs(secondValue) <= s_EPSILON)
	{
		double parameter;
		if ((secondLineSegment.getPointB().getX() - secondLineSegment.getPointA().getX()) > s_EPSILON)
			parameter = (firstLineSegment.getPointB().getX() - secondLineSegment.getPointA().getX())
			/ (secondLineSegment.getPointB().getX() - secondLineSegment.getPointA().getX());
		else
			parameter = (firstLineSegment.getPointB().getZ() - secondLineSegment.getPointA().getZ())
			/ (secondLineSegment.getPointB().getZ() - secondLineSegment.getPointA().getZ());

		if (pointOnLineSegment(parameter))
			return true;

		return false;
	}

	return true;
}

bool OchirovA::hasIntersectProjectionZ(const CLineSegment& firstLineSegment, const CLineSegment& secondLineSegment)
{
	auto firstValue = (firstLineSegment.getPointA().getX() - secondLineSegment.getPointA().getX())
		* (secondLineSegment.getPointB().getY() - secondLineSegment.getPointA().getY())
		- (firstLineSegment.getPointA().getY() - secondLineSegment.getPointA().getY())
		* (secondLineSegment.getPointB().getX() - secondLineSegment.getPointA().getX());

	auto secondValue = (firstLineSegment.getPointB().getX() - secondLineSegment.getPointA().getX())
		* (secondLineSegment.getPointB().getY() - secondLineSegment.getPointA().getY())
		- (firstLineSegment.getPointB().getY() - secondLineSegment.getPointA().getY())
		* (secondLineSegment.getPointB().getX() - secondLineSegment.getPointA().getX());

	if ((firstValue > 0.0 && secondValue > 0.0)
		|| (firstValue < 0.0 && secondValue < 0.0))
		return false;

	if (fabs(firstValue) <= s_EPSILON)
	{
		double parameter;

		if ((secondLineSegment.getPointB().getX() - secondLineSegment.getPointA().getX()) > s_EPSILON)
			parameter = (firstLineSegment.getPointA().getX() - secondLineSegment.getPointA().getX())
			/ (secondLineSegment.getPointB().getX() - secondLineSegment.getPointA().getX());
		else
			parameter = (firstLineSegment.getPointA().getY() - secondLineSegment.getPointA().getY())
			/ (secondLineSegment.getPointB().getY() - secondLineSegment.getPointA().getY());

		if (pointOnLineSegment(parameter))
			return true;

		return false;
	}

	if (fabs(secondValue) <= s_EPSILON)
	{
		double parameter;
		if ((secondLineSegment.getPointB().getX() - secondLineSegment.getPointA().getX()) > s_EPSILON)
			parameter = (firstLineSegment.getPointB().getX() - secondLineSegment.getPointA().getX())
			/ (secondLineSegment.getPointB().getX() - secondLineSegment.getPointA().getX());
		else
			parameter = (firstLineSegment.getPointB().getY() - secondLineSegment.getPointA().getY())
			/ (secondLineSegment.getPointB().getY() - secondLineSegment.getPointA().getY());

		if (pointOnLineSegment(parameter))
			return true;

		return false;
	}

	return true;
}

bool OchirovA::hasIntersect(const CLineSegment& firstLineSegment, const CLineSegment& secondLineSegment)
{
	CPoint firstDirectionVector(firstLineSegment.getPointB().getX() - firstLineSegment.getPointA().getX(),
		firstLineSegment.getPointB().getY() - firstLineSegment.getPointA().getY(),
		firstLineSegment.getPointB().getZ() - firstLineSegment.getPointA().getZ());

	CPoint secondDirectionVector(secondLineSegment.getPointB().getX() - secondLineSegment.getPointA().getX(),
		secondLineSegment.getPointB().getY() - secondLineSegment.getPointA().getY(),
		secondLineSegment.getPointB().getZ() - secondLineSegment.getPointA().getZ());

	CPoint thirdVector(secondLineSegment.getPointA().getX() - firstLineSegment.getPointA().getX(),
		secondLineSegment.getPointA().getY() - firstLineSegment.getPointA().getY(),
		secondLineSegment.getPointA().getZ() - firstLineSegment.getPointA().getZ());

	if (fabs(tripleProduct(firstDirectionVector, secondDirectionVector, thirdVector)) > s_EPSILON)
	{
		return false;
	}

	if (fabs(firstLineSegment.getPointA().getX() - firstLineSegment.getPointB().getX()) <= s_EPSILON)
		return hasIntersectProjectionX(firstLineSegment, secondLineSegment);

	if (fabs(firstLineSegment.getPointA().getY() - firstLineSegment.getPointB().getY()) <= s_EPSILON)
		return hasIntersectProjectionY(firstLineSegment, secondLineSegment);

	if (fabs(firstLineSegment.getPointA().getZ() - firstLineSegment.getPointB().getZ()) <= s_EPSILON)
		return hasIntersectProjectionZ(firstLineSegment, secondLineSegment);

	return hasIntersectProjectionZ(firstLineSegment, secondLineSegment);
}

bool OchirovA::hasIntersect(const CLineSegment& lineSegment, const CPoint& point)
{
	const auto lengthLineSegment = dist(lineSegment.getPointA(), lineSegment.getPointB());
	const auto firstLength = dist(lineSegment.getPointA(), point);
	const auto secondLength = dist(lineSegment.getPointB(), point);

	return (fabs(lengthLineSegment - (firstLength + secondLength)) <= s_EPSILON);
}

bool OchirovA::hasIntersect(const CPoint& firstPoint, const CPoint& secondPoint)
{
	return (dist(firstPoint, secondPoint) <= s_EPSILON);
}

bool OchirovA::hasIntersect(double t1[], double t2[])
{
	CPoint pointA1(t1[0], t1[1], t1[2]);
	CPoint pointB1(t1[3], t1[4], t1[5]);
	CPoint pointC1(t1[6], t1[7], t1[8]);

	CPoint pointA2(t2[0], t2[1], t2[2]);
	CPoint pointB2(t2[3], t2[4], t2[5]);
	CPoint pointC2(t2[6], t2[7], t2[8]);

	CTriangle firstTriangle(pointA1, pointB1, pointC1);
	CTriangle secondTriangle(pointA2, pointB2, pointC2);

	if (firstTriangle.isPoint())
	{
		if (secondTriangle.isPoint())
		{
			return hasIntersect(firstTriangle.getPointA(), secondTriangle.getPointA());
		}
		else
		{
			if (auto result = secondTriangle.isLineSegment(); result.first)
			{
				return hasIntersect(result.second, firstTriangle.getPointA());
			}
			else
			{
				return hasIntersect(secondTriangle, firstTriangle.getPointA());
			}
		}
	}

	if (secondTriangle.isPoint())
	{
		if (auto result = firstTriangle.isLineSegment(); result.first)
		{
			return hasIntersect(result.second, secondTriangle.getPointA());
		}
		else
		{
			return hasIntersect(firstTriangle, secondTriangle.getPointA());
		}
	}

	if (auto firstResult = firstTriangle.isLineSegment(); firstResult.first)
	{
		if (auto secondResult = secondTriangle.isLineSegment(); secondResult.first)
		{
			return hasIntersect(firstResult.second, secondResult.second);
		}
		else
		{
			return hasIntersect(secondTriangle, firstResult.second);
		}
	}
	
	if (auto result = secondTriangle.isLineSegment(); result.first)
	{
		return hasIntersect(firstTriangle, result.second);
	}

	if (separateSecondTrinagleOnLineSegments(firstTriangle, secondTriangle))
		return true;

	if (separateSecondTrinagleOnLineSegments(secondTriangle, firstTriangle))
		return true;

	return false;
}