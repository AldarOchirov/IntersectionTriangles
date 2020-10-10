#include "OchirovA_triangle.h"

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
