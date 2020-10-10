#pragma once
#include "OchirovA_triangle.h"

namespace OchirovA
{
	class CPlane
	{
	private:
		double m_a, m_b, m_c, m_d;

	public:
		CPlane(const CTriangle& triangle);

		double getA() const;
		double getB() const;
		double getC() const;
		double getD() const;
	};
}
