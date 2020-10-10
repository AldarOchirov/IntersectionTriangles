#pragma once
#include "OchirovA_point.h"

namespace OchirovA
{
	class CTriangle
	{
	private:
		CPoint m_a, m_b, m_c;

	public:
		CTriangle(const CPoint& firstPoint, const CPoint& secondPoint, const CPoint& thirdPoint) 
			: m_a(firstPoint), m_b(secondPoint), m_c(thirdPoint) {}

		CPoint getPointA() const;
		CPoint getPointB() const;
		CPoint getPointC() const;
	};
}
