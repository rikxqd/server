#include "common.h"

namespace Collision
{

	Vector2::Vector2() 
		: m_x(0)
		, m_y(0) 
	{
	}
	Vector2::Vector2(float x, float y) 
		: m_x(x)
		, m_y(y) 
	{
	}
	Vector2::~Vector2()
	{
	}

	Vector3::Vector3() 
		: m_x(0)
		, m_y(0)
		, m_z(0)
	{
	}
	Vector3::Vector3(float x, float y, float z) : m_x(x), m_y(y), m_z(z)
	{
	}
	Vector3::~Vector3()
	{
	}

	Line::Line() 
	{
	}
	Line::Line(PointPtr a, PointPtr b) 
		: m_a(a)
		, m_b(b)
	{
	}
	Line::Line(float x1, float y1, float x2, float y2)
	{
		m_a = new Vector2(x1, y1);
		m_b = new Vector2(x2, y2);
	}
	Line::~Line()
	{
	}

	Shape::Shape() 
	{
	}
	Shape::~Shape()
	{
	}

	Circle::Circle() 
	{
	}
	Circle::Circle(PointPtr c, float r)
		: m_c(c)
		, m_r(r) 
	{
	}
	Circle::Circle(float x, float y, float r)
	{
		m_c = new Vector2(x, y);
		m_r = r;
	}
	Circle::~Circle() 
	{
	}

	Polygon::Polygon()
	{
	}
	Polygon::Polygon(std::vector<PointPtr>& points)
	{
		m_vectexs = points;
	}
	Polygon::~Polygon() 
	{
	}

	Sector::Sector() 
	{
	}
	Sector::Sector(float c_x, float c_y, float c_r, float d_x, float d_y, float r)
	{
		m_c = new Circle(c_x, c_y, c_r);
		m_d = new Vector2(d_x, d_y);
		m_r = r;
	}
	Sector::Sector(CirclePtr c, DirectionPtr d, float r) 
		: m_c(c)
		, m_d(d)
		, m_r(r) 
	{
	}
	Sector::~Sector() 
	{
	}

}// End of Collision