#include "canvas.h"

#include <iostream>
#include <vector>
using std::cout;
using std::endl;
using std::vector;

namespace btreepainter
{

/** ─│┌└┐┘├┤┬┴┼ */
const char *HORIZON = "─";
const char *VERTICAL = "│";
const char *ACROSS = "┼";
const char *T_LEFT = "├";
const char *T_RIGHT = "┤";
const char *T_NORMAL = "┬";
const char *T_INVERSION = "┴";
const char *CURVE_ES = "┌";
const char *CURVE_EN = "└";
const char *CURVE_WS = "┐";
const char *CURVE_WN = "┘";

Canvas::Canvas(const int w, const int h)
	: width(w), height(h)
{
	int i = 0;
	canvas = new vector<vector<string*> >();

	(*canvas).resize(h);
	for (i = 0; i < h; ++i)
	{
		(*canvas)[i].resize(w);
	}
}

Canvas::~Canvas()
{
	int i = 0, j = 0;

	for (i = 0; i < height; ++i)
	{
		for (j = 0; j < width; ++j)
		{
			string *str = (*canvas)[i][j];
			if (str != NULL)
			{
				delete str;
			}
		}
	}
	delete canvas;
}

/**
inline bool Canvas::DrawPoint(const string &str, const int x, const int y)
{
	if ((*canvas)[y][x] != NULL)
		return false;
	(*canvas)[y][x] = new string(str);
	return true;
}
*/
inline bool Canvas::DrawPoint(const char *str, const int x, const int y)
{
	if (x > width || y > height)
		return false;
	if ((*canvas)[y][x] != NULL)
		return false;
	(*canvas)[y][x] = new string(str);
	return true;
}

bool Canvas::DrawText(const string &str, int x, int y)
{
	string::size_type i = 0;
	int cursor_x = 0, line = 0;
	int str_w, str_h;

	CalcuStringSize(str, str_w, str_h);
	if (x + str_w > width || y + str_h > height)
	{
		return false;
	}
	for (i = 0; i < str.length(); ++i)
	{
		char ch[2] = {' ', '\0'};

		if (str[i] == '\n')
		{
			cursor_x = 0;
			line++;
			continue;
		}
		ch[0] = str[i];
		DrawPoint(ch, x + cursor_x, y + line);
		cursor_x++;
	}
	return true;
}

#define DRAW_POINT(x, y, z)		\
	if (!DrawPoint(x, y, z)) {	\
		return false;			\
	}

bool Canvas::DrawRect(const Point p, const int width, const int height,
					enum SonRole sonRole, enum FatherRole faRole)
{
	int i, j;

	DRAW_POINT(CURVE_ES, p.x, p.y);
	for (i = p.x + 1; i < p.x + (width >> 1); ++i)
	{
		DRAW_POINT(HORIZON, i, p.y);
	}
	if (sonRole != ROOT)
	{
		DRAW_POINT(T_INVERSION, i++, p.y);
	}
	else
	{
		DRAW_POINT(HORIZON, i++, p.y);
	}
	for (; i < p.x + width - 1; ++i)
	{
		DRAW_POINT(HORIZON, i, p.y);
	}
	DRAW_POINT(CURVE_WS, i, p.y);
	for (j = p.y + 1; j < p.y + height - 1; ++j)
	{
		DRAW_POINT(VERTICAL, i, j);
	}
	DRAW_POINT(CURVE_WN, i--, j);
	for (; i > p.x + (width >> 1); --i)
	{
		DRAW_POINT(HORIZON, i, j);
	}
	if (faRole == HAS_NOCHILD)
	{
		DRAW_POINT(HORIZON, i--, j);
	}
	else
	{
		DRAW_POINT(T_NORMAL, i--, j);
	}
	for (; i > p.x; --i)
	{
		DRAW_POINT(HORIZON, i, j);
	}
	DRAW_POINT(CURVE_EN, i, j--);
	for (; j > p.y; j--)
	{
		DRAW_POINT(VERTICAL, i, j);
	}
	return true;
}

bool Canvas::DrawConnection(const Point &p1, const Point &p2)
{
	int i;

	if (p1.x > p2.x)
	{
		DRAW_POINT(CURVE_WN, p1.x, p1.y);
		for (i = p1.x - 1; i > p2.x; --i)
		{
			DRAW_POINT(HORIZON, i, p1.y);
		}
		DRAW_POINT(CURVE_ES, i, p1.y);
	}
	else if (p1.x < p2.x)
	{
		DRAW_POINT(CURVE_EN, p1.x, p1.y);
		for (i = p1.x + 1; i < p2.x; ++i)
		{
			DRAW_POINT(HORIZON, i, p1.y);
		}
		DRAW_POINT(CURVE_WS, i, p1.y);
	}
	else
	{
		DRAW_POINT(VERTICAL, p1.x, p1.y);
	}
}

bool Canvas::DrawConnection(const Point &p1, const Point &p2, const Point &p3)
{
	int i;

	DRAW_POINT(T_INVERSION, p1.x, p1.y);
	for (i = p1.x - 1; i > p2.x; --i)
	{
		DRAW_POINT(HORIZON, i, p1.y);
	}
	DRAW_POINT(CURVE_ES, i, p1.y);

	for (i = p1.x + 1; i < p3.x; ++i)
	{
		DRAW_POINT(HORIZON, i, p1.y);
	}
	DRAW_POINT(CURVE_WS, i, p1.y);
}

void Canvas::DrawBPaintTreeImpl(const BPaintTree bpt, const Point startPt)
{
	if (bpt == NULL)
	{
		return;
	}
	BPaintTreeInfo &bpt_info = bpt->getData();
	Point drawPt(startPt);
	Point p1, p2, p3;

	/** Draw current point. */
	drawPt.x += (bpt_info.getSubTreeWidth() - bpt_info.getWidth()) >> 1;
	DrawRect(drawPt, bpt_info.getWidth(), bpt_info.getHeight(),
			bpt_info.getSonRole(), bpt_info.getFatherRole());
	DrawText(bpt_info.getName(), drawPt.x + 1, drawPt.y + 1);

	/** Draw left and right subtree. */
	DrawBPaintTreeImpl(bpt->left, bpt_info.getLocationLeft() + startPt);
	DrawBPaintTreeImpl(bpt->right, bpt_info.getLocationRight() + startPt);

	/** Draw connection. */
	p1.x = drawPt.x + (bpt_info.getWidth() >> 1);
	p1.y = drawPt.y + bpt_info.getHeight();
	p2 = bpt_info.getLocationLeft() + startPt;
	p3 = bpt_info.getLocationRight() + startPt;
	if (bpt_info.getFatherRole() == HAS_BOTH)
	{
		p2.x += (bpt->left->getData().getSubTreeWidth() >> 1);
		p2.y += bpt->left->getData().getHeight();
		p3.x += (bpt->right->getData().getSubTreeWidth() >> 1);
		p3.y += bpt->right->getData().getHeight();
		DrawConnection(p1, p2, p3);
	}
	else if (bpt_info.getFatherRole() == HAS_LEFT)
	{
		p2.x += (bpt->left->getData().getWidth()) >> 1;
		p2.y += bpt->left->getData().getHeight();
		DrawConnection(p1, p2);
	}
	else if (bpt_info.getFatherRole() == HAS_RIGHT)
	{
		p3.x += (bpt->right->getData().getWidth() >> 1);
		p3.y += bpt->right->getData().getHeight();
		DrawConnection(p1, p3);
	}
}

void Canvas::DrawBPaintTree(const BPaintTree bpt)
{
	if (canvas == NULL || bpt == NULL)
	{
		return;
	}
	Point startPt(0, 0);
	DrawBPaintTreeImpl(bpt, startPt);
}

std::ostream &operator<<(std::ostream &os, const Canvas &paint)
{
	vector<vector<string *> >::iterator iter = paint.getCanvas()->begin();
	vector<vector<string *> >::iterator iter_end = paint.getCanvas()->end();

	for (; iter != iter_end; ++iter)
	{
		vector<string *> line = *iter;

		vector<string *>::iterator sub_iter = line.begin();
		vector<string *>::iterator sub_iter_end = line.end();
		for (; sub_iter != sub_iter_end; ++sub_iter)
		{
			if (*sub_iter != NULL)
			{
				os << **sub_iter;
			}
			else
			{
				os << " ";
			}
		}
		os << std::endl;
	}
	return os;
}

};
