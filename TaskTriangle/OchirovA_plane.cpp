#include "OchirovA_plane.h"
#include "OchirovA_intersection.h"

using namespace OchirovA;

CPlane::CPlane(const CTriangle& triangle)
{
	m_a = det(triangle.getPointB().getY() - triangle.getPointA().getY(),
		triangle.getPointC().getY() - triangle.getPointA().getY(),
		triangle.getPointB().getZ() - triangle.getPointA().getZ(),
		triangle.getPointC().getZ() - triangle.getPointA().getZ());

	m_b = -det(triangle.getPointB().getX() - triangle.getPointA().getX(),
		triangle.getPointC().getX() - triangle.getPointA().getX(),
		triangle.getPointB().getZ() - triangle.getPointA().getZ(),
		triangle.getPointC().getZ() - triangle.getPointA().getZ());

	m_c = det(triangle.getPointB().getX() - triangle.getPointA().getX(),
		triangle.getPointC().getX() - triangle.getPointA().getX(),
		triangle.getPointB().getY() - triangle.getPointA().getY(),
		triangle.getPointC().getY() - triangle.getPointA().getY());

	m_d = -triangle.getPointA().getX() * m_a
		- triangle.getPointA().getY() * m_b
		- triangle.getPointA().getZ() * m_c;
}

double OchirovA::CPlane::getA() const
{
	return this->m_a;
}

double OchirovA::CPlane::getB() const
{
	return this->m_b;
}

double OchirovA::CPlane::getC() const
{
	return this->m_c;
}

double OchirovA::CPlane::getD() const
{
	return this->m_d;
}
