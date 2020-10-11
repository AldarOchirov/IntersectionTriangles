#include "OchirovA_triangle.h"
#include "OchirovA_intersection.h"

using namespace OchirovA;

CPoint CTriangle::getPointA() const
{
	return this->m_a;
}

CPoint CTriangle::getPointB() const
{
	return this->m_b;
}

CPoint CTriangle::getPointC() const
{
	return this->m_c;
}

bool CTriangle::isPoint() const
{	
	return ((dist(m_a, m_b) <= s_EPSILON) && (dist(m_b, m_c) <= s_EPSILON));
}

std::pair<bool, CLineSegment> CTriangle::isLineSegment() const
{
	if ((dist(m_a, m_b) <= s_EPSILON) && (dist(m_b, m_c) >= s_EPSILON) && (dist(m_a, m_c) >= s_EPSILON))
	{
		CLineSegment lineSegment(m_a, m_c);
		return std::make_pair(true, lineSegment);
	}
	
	if ((dist(m_a, m_b) >= s_EPSILON) && (dist(m_b, m_c) <= s_EPSILON) && (dist(m_a, m_c) >= s_EPSILON))
	{
		CLineSegment lineSegment(m_a, m_c);
		return std::make_pair(true, lineSegment);
	}

	if ((dist(m_a, m_b) >= s_EPSILON) && (dist(m_b, m_c) >= s_EPSILON) && (dist(m_a, m_c) <= s_EPSILON))
	{
		CLineSegment lineSegment(m_a, m_b);
		return std::make_pair(true, lineSegment);
	}

	CLineSegment lineSegment;
	return std::make_pair(false, lineSegment);
}
