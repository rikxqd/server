#ifndef _COMMON_H_
#define _COMMON_H_

#include <vector>
#include "public.h"
#include "utility/share_ptr.h"


namespace Collision
{

	class Vector2 : public RefCounter
	{
	public:
		Vector2();
		Vector2(float x, float y);
		~Vector2();

		float m_x;
		float m_y;
	};
	typedef SharePtr<Vector2> Vector2Ptr, PointPtr, DirectionPtr;

	class Vector3 : public RefCounter
	{
	public:
		Vector3();
		Vector3(float x, float y, float z);
		~Vector3();

		float m_x;
		float m_y;
		float m_z;
	};
	typedef SharePtr<Vector3> Vector3Ptr;

	class Line : public RefCounter
	{
	public:
		Line();
		Line(PointPtr a, PointPtr b);
		Line(float x1, float y1, float x2, float y2);
		~Line();

		PointPtr m_a;
		PointPtr m_b;
	};
	typedef SharePtr<Line> LinePtr;

	class Shape : public RefCounter
	{
	public:
		Shape();
		virtual ~Shape();
	};

	class Circle : public Shape
	{
	public:
		Circle();
		Circle(PointPtr c, float r);
		Circle(float x, float y, float r);
		~Circle();

		PointPtr m_c;
		float m_r;
	};
	typedef SharePtr<Circle> CirclePtr;

	class Polygon : public Shape
	{
	public:
		Polygon();
		Polygon(std::vector<PointPtr>& points);
		~Polygon();

		std::vector<PointPtr> m_vectexs;
	};
	typedef SharePtr<Polygon> PolygonPtr;

	class Sector
	{
	public:
		Sector();
		Sector(float c_x, float c_y, float c_r, float d_x, float d_y, float r);
		Sector(CirclePtr c, DirectionPtr d, float r);
		~Sector();

		CirclePtr m_c;
		DirectionPtr m_d;
		float m_r;
	};
	typedef SharePtr<Sector> SectorPtr;

}// End of Collision

#endif//_COMMON_H_

