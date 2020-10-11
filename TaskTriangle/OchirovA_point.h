#pragma once

namespace OchirovA
{
	class CPoint
	{
	private:
		double m_x, m_y, m_z;

	public:
		CPoint() : m_x(0.0), m_y(0.0), m_z(0.0) {}
		CPoint(double x, double y, double z) : m_x(x), m_y(y), m_z(z) {}

		double getX() const;
		double getY() const;
		double getZ() const;
	};
}
