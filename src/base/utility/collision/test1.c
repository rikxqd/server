#ifndef __CIRCLE_FAN_INTERSECTION_H__
#define __CIRCLE_FAN_INTERSECTION_H__

#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Vector2
{
	float x;
	float y;
} Vector2, Point, Direction;

typedef struct Vector3
{
	float x;
	float y;
	float z;
} Vector3;

typedef struct Circle
{
	Point c;
	float r;
} Circle;

typedef struct Line
{
	Point a;
	Point b;
} Line;

typedef struct Sector
{
	Circle c;
	Direction d;
	float r;
} Sector;

typedef struct Polygon
{
	int n;
	Point* v;
} Polygon;

#define SQUARE(x) ((x)*(x))
#define MIN(x, y) ((x) < (y) ? (x) : (y))
#define MAX(x, y) ((x) > (y) ? (x) : (y))

Vector3 GetLineFormula(Line* line)
{
 	float a = line->b.y - line->a.y;
	float b = line->a.x - line->b.x;
	float c = line->b.x * line->a.y - line->a.x * line->b.y;
	Vector3 vector3 = { a, b, c };
	return vector3;
}

bool IsCircleIntersectWhitLineSegment(Circle* circle, Line* line)
{
	Direction ac = { circle->c.x - line->a.x, circle->c.y - line->a.y };
	Direction ab = { line->b.x - line->a.x, line->b.y - line->a.y };
	Direction bc = { circle->c.x - line->b.x, circle->c.y - line->b.y };
	Direction ba = { line->a.x - line->b.x, line->a.y - line->b.y };

	float ua = ac.x * ab.x + ac.y * ab.y;
	float ub = bc.x * ba.x + bc.y * ba.y;

	float x0 = 0.f;
	float y0 = 0.f;
	if (ua <= 0)
	{
		x0 = line->a.x;
		y0 = line->a.y;
	}
	else if (ub <= 0)
	{
		x0 = line->b.x;
		y0 = line->b.y;
	}
	else
	{
		Vector3 v = GetLineFormula(line);
		float len_square = SQUARE(v.x * circle->c.x + v.y * circle->c.y + v.z) / ((SQUARE(v.x) + SQUARE(v.y)));
		return len_square <= SQUARE(circle->r);
	}

	return SQUARE(circle->c.x - x0) + SQUARE(circle->c.y - y0) <= SQUARE(circle->r);
}


float EvaluatePointToLine(Point point, Line* line)
{
	Vector3 v = GetLineFormula(line);
	return v.x * point.x + v.y * point.y + v.z;
}


Point GetCenterInArcOfSector(Sector* sector)
{
	float x = sector->c.c.x + sector->d.x * sector->c.r;
	float y = sector->c.c.y + sector->d.y * sector->c.r;
	Point res = { x, y };
	return res;
}

void PrintCircle(Circle c, bool b)
{
	printf("circle(%f, %f, %f, \"%s\");\n", c.c.x, c.c.y, c.r, b ? "red" : "blue");
}

Sector* CreateSector(Circle c, Direction d, float r)
{
	float m = sqrt(SQUARE(d.x) + SQUARE(d.y));
	Sector* sector = NULL;
	if (m > 0.00001f)
	{
		sector = (Sector*)malloc(sizeof(Sector));
		sector->c = c;
		sector->d.x = d.x / m;
		sector->d.y = d.y / m;
		sector->r = r;
	}
	return sector;
}

bool IsCircleIntersectFan(Circle* circle, Sector* sector)
{
	if (SQUARE(circle->c.x - sector->c.c.x) + SQUARE(circle->c.y - sector->c.c.y) > SQUARE(sector->c.r + circle->r))
		return false;

	//printf("circle(%f, %f, %f, \"%s\");\n", sector->c.c.x, sector->c.c.y, 5.f, "yellow");
	Point center_of_arc = GetCenterInArcOfSector(sector);
	//printf("circle(%f, %f, %f, \"%s\");\n", center_of_arc.x, center_of_arc.y, 5.f, "yellow");
	float vx = center_of_arc.x - sector->c.c.x;
	float vy = center_of_arc.y - sector->c.c.y;

	//assert(sector->r > 0.00001f && sector->r < 3.1416f);

	float h = sector->r * 0.5f;
	float c = cosf(h);
	float s = sinf(h);
	//printf("cosf:%f\n", c);
	//printf("sinf:%f\n", s);
	Point vertex_a = { sector->c.c.x + (vx * c - vy * s), sector->c.c.y + (vy * c + vx * s) };
	Point vertex_b = { sector->c.c.x + (vx * c + vy * s), sector->c.c.y + (vy * c - vx * s) };
	//printf("circle(%f, %f, %f, \"%s\");\n", vertex_a.x, vertex_a.y, 5.f, "yellow");
	//printf("circle(%f, %f, %f, \"%s\");\n", vertex_b.x, vertex_b.y, 5.f, "yellow");

	Line line_a = { sector->c.c, vertex_a };
	Line line_b = { sector->c.c, vertex_b };

	float ca = EvaluatePointToLine(circle->c, &line_a);
	float ba = EvaluatePointToLine(vertex_b, &line_a);
	float cb = EvaluatePointToLine(circle->c, &line_b);
	float ab = EvaluatePointToLine(vertex_a, &line_b);

	if (0 <= c)
	{
		if (0 <= ca * ba && 0 <= cb * ab)
			return true;
	}
	else
	{
		if (0 >= ca * ba || 0 >= cb * ab)
			return true;
	}

	if (IsCircleIntersectWhitLineSegment(circle, &line_a))
		return true;
	if (IsCircleIntersectWhitLineSegment(circle, &line_b))
		return true;

	return false;
}

void PrintPoint(Point point, const char* color)
{
	printf("circle(%f, %f, %f, \"%s\");\n", point.x, point.y, 5.f, color);
}

bool IsInSector(Point point, Sector* sector)
{
	Point center_of_arc = GetCenterInArcOfSector(sector);
	float vx = center_of_arc.x - sector->c.c.x;
	float vy = center_of_arc.y - sector->c.c.y;

	float h = sector->r * 0.5f;
	float c = cosf(h);
	float s = sinf(h);
	Point vertex_a = { sector->c.c.x + (vx * c - vy * s), sector->c.c.y + (vy * c + vx * s) };
	Point vertex_b = { sector->c.c.x + (vx * c + vy * s), sector->c.c.y + (vy * c - vx * s) };
	PrintPoint(vertex_a, "black");
	PrintPoint(vertex_b, "black");

	Line line_a = { sector->c.c, vertex_a };
	Line line_b = { sector->c.c, vertex_b };

	float ca = EvaluatePointToLine(point, &line_a);
	float ba = EvaluatePointToLine(vertex_b, &line_a);
	float cb = EvaluatePointToLine(point, &line_b);
	float ab = EvaluatePointToLine(vertex_a, &line_b);

	if (0 <= c)
	{
		if (0 <= ca * ba && 0 <= cb * ab)
			return true;
	}
	else
	{
		if (0 >= ca * ba || 0 >= cb * ab)
			return true;
	}

	return false;
}

void GetEnclosingRectangleOfSector(Sector* sector, Point* down_left, Point* up_right)
{
	Point center_of_arc = GetCenterInArcOfSector(sector);
	float vx = center_of_arc.x - sector->c.c.x;
	float vy = center_of_arc.y - sector->c.c.y;
	float h = sector->r * 0.5f;
	float c = cosf(h);
	float s = sinf(h);
	Point vertex_a = { sector->c.c.x + (vx * c - vy * s), sector->c.c.y + (vy * c + vx * s) };
	Point vertex_b = { sector->c.c.x + (vx * c + vy * s), sector->c.c.y + (vy * c - vx * s) };

	Point up = { sector->c.c.x, sector->c.c.y + sector->c.r };
	Point down = { sector->c.c.x, sector->c.c.y - sector->c.r };
	Point left = { sector->c.c.x - sector->c.r, sector->c.c.y };
	Point right = { sector->c.c.x + sector->c.r, sector->c.c.y };

	up_right->y = IsInSector(up, sector) ? up.y : MAX(MAX(vertex_a.y, vertex_b.y), sector->c.c.y);
	down_left->y = IsInSector(down, sector) ? down.y : MIN(MIN(vertex_a.y, vertex_b.y), sector->c.c.y);
	up_right->x = IsInSector(right, sector) ? right.x : MAX(MAX(vertex_a.x, vertex_b.x), sector->c.c.x);
	down_left->x = IsInSector(left, sector) ? left.x : MIN(MIN(vertex_a.x, vertex_b.x), sector->c.c.x);

	PrintPoint(center_of_arc, "black");
	PrintPoint(sector->c.c, "black");
	PrintPoint(vertex_a, "black");
	PrintPoint(vertex_b, "black");

	PrintPoint(up, IsInSector(up, sector) ? "red" : "yellow");
	PrintPoint(down, IsInSector(down, sector) ? "red" : "yellow");
	PrintPoint(left, IsInSector(left, sector) ? "red" : "yellow");
	PrintPoint(right, IsInSector(right, sector) ? "red" : "yellow");
}

Polygon* CreatePolygon(int n, Point* v)
{
	Polygon* polygon = (Polygon*)malloc(sizeof(Polygon));
	polygon->n = n;
	polygon->v = (Point*)malloc(n * sizeof(Point));
	memcpy(polygon->v, v, n * sizeof(Point));
	return polygon;
}

void DeletePolygon(Polygon** polygon)
{
	Polygon* temp = *polygon;
	free(temp->v);
	free(temp);
	temp = NULL;
}

bool PointInPolygon(Polygon* polygon, Point* point)
{
	int i, j;
	bool c = false;
	for (i = 0, j = polygon->n - 1; i < polygon->n; j = i++)
	{
		float y1 = polygon->v[i].y;
		float x1 = polygon->v[i].x;
		float y2 = polygon->v[j].y;
		float x2 = polygon->v[j].x;
		if (((y1 > point->y) != (y2 > point->y)))
		{
			if ((point->x < (x2 - x1) * (point->y - y1) / (y2 - y1) + x1))
				c = !c;
		}
	}

	return c;
}

void PrintLine(Line line)
{
	printf("line(%f, %f, %f, %f);\n", line.a.x, line.a.y, line.b.x, line.b.y);
}

void PrintPolygon(Polygon* polygon)
{
	for (int i = 0, j = polygon->n - 1; i < polygon->n; j = i++)
	{
		Line line = { { polygon->v[i].x, polygon->v[i].y },{ polygon->v[j].x, polygon->v[j].y} };
		PrintLine(line);
	}
}

bool IsCircleIntersectPolygon(Circle* circle, Polygon* polygon)
{
	if (PointInPolygon(polygon, &circle->c))
		return true;

	for (int i = 0, j = polygon->n - 1; i < polygon->n; j = i++)
	{
		Line line = { { polygon->v[i].x, polygon->v[i].y },{ polygon->v[j].x, polygon->v[j].y } };
		if (IsCircleIntersectWhitLineSegment(circle, &line))
			return true;
	}

	return false;
}

void TestSector()
{
	Circle c = { { 400.f, 320.f }, 300.f };
	Direction d = { -1.f, -1.f };
	Sector* sector = CreateSector(c, d, 5.f);
	if (NULL == sector)
		return;

	Point down_left = { 0 };
	Point up_right = { 0 };
	GetEnclosingRectangleOfSector(sector, &down_left, &up_right);
	printf("rectangle(%f, %f, %f, %f);\n", down_left.x, down_left.y, up_right.x - down_left.x, up_right.y - down_left.y);

	Circle circle[20] = { 0 };
	for (int i = 0; i < 20; ++i)
	{
		float x = (rand() % (800 * 10000) / 10000.f);
		float y = (rand() % (640 * 10000) / 10000.f);
		float r = 20.f;
		circle[i].c.x = x;
		circle[i].c.y = y;
		circle[i].r = r;
	}

	for (int i = 0; i < 20; ++i)
	{
		//PrintCircle(circle[i], IsCircleIntersectFan(&circle[i], sector));
	}
}

Polygon* list;

void TestPolygon()
{
	Point point[7] = {
		{ 100, 100 },
		{ 100, 600 },
		{ 200, 600 },
		//{ 200, 350 },
		{ 500, 350 },
		{ 500, 600 },
		{ 600, 600 },
		{ 600, 100 },
	};

	Polygon* polygon = CreatePolygon(7, point);
	PrintPolygon(polygon);

/*
	for (int i = 0; i < 50; ++i)
	{
		Point point = { (rand() % (800 * 10000) / 10000.f), (rand() % (640 * 10000) / 10000.f) };
		printf("circle(%f, %f, %f, \"%s\");\n", point.x, point.y, 5.f, PointInPolygon(&polygon, &point) ? "red" : "yellow");
	}*/

	Circle circle[200] = { 0 };
	for (int i = 0; i < 200; ++i)
	{
		float x = (rand() % (800 * 10000) / 10000.f);
		float y = (rand() % (640 * 10000) / 10000.f);
		float r = 20.f;
		circle[i].c.x = x;
		circle[i].c.y = y;
		circle[i].r = r;
	}

	for (int i = 0; i < 200; ++i)
	{
		PrintCircle(circle[i], IsCircleIntersectPolygon(&circle[i], polygon));
	}

	DeletePolygon(&polygon);
}

int main(int argc, char** argv)
{
	//TestSector();
	TestPolygon();

	return 0;
}

#endif // __CIRCLE_FAN_INTERSECTION_H__
