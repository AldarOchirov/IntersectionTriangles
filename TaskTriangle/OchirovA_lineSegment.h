#pragma once

#include "OchirovA_point.h"

namespace OchirovA
{
	class CLineSegment
	{
	private:
		CPoint m_a, m_b;

	public:
		CLineSegment(const CPoint& firstPoint, const CPoint& secondPoint)
			: m_a(firstPoint), m_b(secondPoint) {}

		CPoint getPointA() const;
		CPoint getPointB() const;
	};
}
