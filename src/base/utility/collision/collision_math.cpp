#include "collision_math.h"
#include "common.h"
#include "public.h"


namespace Collision
{
	namespace Math
	{
		Vector3Ptr GetLineFormula(LinePtr line)
		{
			float a = line->m_b->m_y - line->m_a->m_y;
			float b = line->m_a->m_x - line->m_b->m_x;
			float c = line->m_b->m_x * line->m_a->m_y - line->m_a->m_x * line->m_b->m_y;
			return new Vector3(a, b, c);
		}

		bool IsCircleIntersectWhitLineSegment(CirclePtr circle, LinePtr line)
		{
			DirectionPtr ac = new Vector2(circle->m_c->m_x - line->m_a->m_x, circle->m_c->m_y - line->m_a->m_y);
			DirectionPtr ab = new Vector2(line->m_b->m_x - line->m_a->m_x, line->m_b->m_y - line->m_a->m_y);
			DirectionPtr bc = new Vector2(circle->m_c->m_x - line->m_b->m_x, circle->m_c->m_y - line->m_b->m_y);
			DirectionPtr ba = new Vector2(line->m_a->m_x - line->m_b->m_x, line->m_a->m_y - line->m_b->m_y);

			float ua = ac->m_x * ab->m_x + ac->m_y * ab->m_y;
			float ub = bc->m_x * ba->m_x + bc->m_y * ba->m_y;

			float x0 = 0.f;
			float y0 = 0.f;
			if (ua <= 0)
			{
				x0 = line->m_a->m_x;
				y0 = line->m_a->m_y;
			}
			else if (ub <= 0)
			{
				x0 = line->m_b->m_x;
				y0 = line->m_b->m_y;
			}
			else
			{
				Vector3Ptr v = GetLineFormula(line);
				float len_square = SQUARE(v->m_x * circle->m_c->m_x + v->m_y * circle->m_c->m_y + v->m_z) / ((SQUARE(v->m_x) + SQUARE(v->m_y)));
				return len_square <= SQUARE(circle->m_r);
			}

			return SQUARE(circle->m_c->m_x - x0) + SQUARE(circle->m_c->m_y - y0) <= SQUARE(circle->m_r);
		}

		float EvaluatePointToLine(PointPtr point, LinePtr line)
		{
			Vector3Ptr v = GetLineFormula(line);
			return v->m_x * point->m_x + v->m_y * point->m_y + v->m_z;
		}

		PointPtr GetCenterInArcOfSector(SectorPtr sector)
		{
			float x = sector->m_c->m_c->m_x + sector->m_d->m_x * sector->m_c->m_r;
			float y = sector->m_c->m_c->m_y + sector->m_d->m_y * sector->m_c->m_r;
			return new Vector2(x, y);
		}
	}
}// End of Collision