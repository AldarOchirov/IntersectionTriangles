#include "OchirovA_lineSegment.h"

using namespace OchirovA;

CPoint CLineSegment::getPointA() const
{
	return this->m_a;
}

CPoint CLineSegment::getPointB() const
{
	return this->m_b;
}