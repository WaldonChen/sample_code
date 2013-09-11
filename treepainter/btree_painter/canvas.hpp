#ifndef _BTREEPAINTER_CANVAS_H_
#define _BTREEPAINTER_CANVAS_H_

#include "paint_tree.hpp"

#include <vector>
#include <ostream>
using std::cout;
using std::vector;
using std::ostream;

namespace btree_painter
{

/** ─│┌└┐┘├┤┬┴┼ */
const char *kHORIZON = "─";
const char *kVERTICAL = "│";
const char *kACROSS = "┼";
const char *kT_LEFT = "├";
const char *kT_RIGHT = "┤";
const char *kT_NORMAL = "┬";
const char *kT_INVERSION = "┴";
const char *kCURVE_ES = "┌";
const char *kCURVE_EN = "└";
const char *kCURVE_WS = "┐";
const char *kCURVE_WN = "┘";

/**
 * Canvas
 */
class Canvas
{
public:
	Canvas(const int width, const int height);
	~Canvas();

	// inline bool DrawPosition(const string &str, const int x, const int y);
	inline bool DrawPoint(const char* str, const int x, const int y);
	inline bool DrawText(const string &str, const Position p) { DrawText(str, p.x, p.y); }
	bool DrawText(const string &str, const int x, const int y);
	bool DrawRect(const Position p, const int width, const int height,
					enum SonRole son_role, enum FatherRole father_role);
	bool DrawConnection(const Position &p1, const Position &p2);
	bool DrawConnection(const Position &p1, const Position &p2, const Position &p3);
	void DrawPaintTree(const PaintTree bpt);

	inline vector<vector<string*> > *get_canvas() const { return canvas_; }

private:
	void DrawPaintTreeImpl(const PaintTree bpt, const Position start_point);

private:
	int width_, height_;
	vector<vector<string*> > *canvas_;
};

Canvas::Canvas(const int width, const int height)
	: width_(width), height_(height)
{
	int i = 0;
	canvas_ = new vector<vector<string*> >();

	(*canvas_).resize(height);
	for (i = 0; i < height; ++i)
	{
		(*canvas_)[i].resize(width);
	}
}

Canvas::~Canvas()
{
	int i = 0, j = 0;

	for (i = 0; i < height_; ++i)
	{
		for (j = 0; j < width_; ++j)
		{
			string *str = (*canvas_)[i][j];
			if (str != NULL)
			{
				delete str;
			}
		}
	}
	delete canvas_;
}


inline bool Canvas::DrawPoint(const char *str, const int x, const int y)
{
	if (x > width_ || y > height_)
		return false;
	if ((*canvas_)[y][x] != NULL)
		return false;
	(*canvas_)[y][x] = new string(str);
	return true;
}

bool Canvas::DrawText(const string &str, int x, int y)
{
	string::size_type i = 0;
	int cursor_x = 0, line = 0;
	int str_w, str_h;

	CalculateStringSize(str, str_w, str_h);
	if (x + str_w > width_ || y + str_h > height_)
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

bool Canvas::DrawRect(const Position p, const int width, const int height,
					enum SonRole sonRole, enum FatherRole faRole)
{
	int i, j;

	DRAW_POINT(kCURVE_ES, p.x, p.y);
	for (i = p.x + 1; i < p.x + (width >> 1); ++i)
	{
		DRAW_POINT(kHORIZON, i, p.y);
	}
	if (sonRole != ROOT)
	{
		DRAW_POINT(kT_INVERSION, i++, p.y);
	}
	else
	{
		DRAW_POINT(kHORIZON, i++, p.y);
	}
	for (; i < p.x + width - 1; ++i)
	{
		DRAW_POINT(kHORIZON, i, p.y);
	}
	DRAW_POINT(kCURVE_WS, i, p.y);
	for (j = p.y + 1; j < p.y + height - 1; ++j)
	{
		DRAW_POINT(kVERTICAL, i, j);
	}
	DRAW_POINT(kCURVE_WN, i--, j);
	for (; i > p.x + (width >> 1); --i)
	{
		DRAW_POINT(kHORIZON, i, j);
	}
	if (faRole == HAS_NOCHILD)
	{
		DRAW_POINT(kHORIZON, i--, j);
	}
	else
	{
		DRAW_POINT(kT_NORMAL, i--, j);
	}
	for (; i > p.x; --i)
	{
		DRAW_POINT(kHORIZON, i, j);
	}
	DRAW_POINT(kCURVE_EN, i, j--);
	for (; j > p.y; j--)
	{
		DRAW_POINT(kVERTICAL, i, j);
	}
	return true;
}

bool Canvas::DrawConnection(const Position &p1, const Position &p2)
{
	int i;

	if (p1.x > p2.x)
	{
		DRAW_POINT(kCURVE_WN, p1.x, p1.y);
		for (i = p1.x - 1; i > p2.x; --i)
		{
			DRAW_POINT(kHORIZON, i, p1.y);
		}
		DRAW_POINT(kCURVE_ES, i, p1.y);
	}
	else if (p1.x < p2.x)
	{
		DRAW_POINT(kCURVE_EN, p1.x, p1.y);
		for (i = p1.x + 1; i < p2.x; ++i)
		{
			DRAW_POINT(kHORIZON, i, p1.y);
		}
		DRAW_POINT(kCURVE_WS, i, p1.y);
	}
	else
	{
		DRAW_POINT(kVERTICAL, p1.x, p1.y);
	}
}

bool Canvas::DrawConnection(const Position &p1, const Position &p2, const Position &p3)
{
	int i;

	if (p2 == kInvalidPosition && p3 != kInvalidPosition)
	{
		return DrawConnection(p1, p3);
	}
	else if (p2 != kInvalidPosition && p3 == kInvalidPosition)
	{
		return DrawConnection(p1, p2);
	}
	else if (p2 == kInvalidPosition && p3 == kInvalidPosition)
	{
		return false;
	}

	DRAW_POINT(kT_INVERSION, p1.x, p1.y);
	for (i = p1.x - 1; i > p2.x; --i)
	{
		DRAW_POINT(kHORIZON, i, p1.y);
	}
	DRAW_POINT(kCURVE_ES, i, p1.y);

	for (i = p1.x + 1; i < p3.x; ++i)
	{
		DRAW_POINT(kHORIZON, i, p1.y);
	}
	DRAW_POINT(kCURVE_WS, i, p1.y);
}

/** Draw PaintTree at a position
 *
 * @param bpt the information tree of the binary tree that be painted
 * @param start_point the original position
 */
void Canvas::DrawPaintTreeImpl(const PaintTree bpt, const Position start_point)
{
	if (bpt == NULL)
	{
		return;
	}

	PaintTreeInfo &bpt_info = bpt->get_data();
	// the drawing position of current node
	Position draw_point(start_point);
	// connection position of parent node, left son, and right son.
	Position p1, p2, p3;

	/** Draw left and right subtree. */
	DrawPaintTreeImpl(bpt->left_, bpt_info.left_subtree_location_ + start_point);
	DrawPaintTreeImpl(bpt->right_, bpt_info.right_subtree_location_ + start_point);

	/** Draw current point and connection. */
	draw_point.x += (bpt_info.subtree_width_ - bpt_info.width_) >> 1;
	DrawRect(draw_point, bpt_info.width_, bpt_info.height_,
			bpt_info.son_role_, bpt_info.father_role_);
	DrawText(bpt_info.name_, draw_point.x + 1, draw_point.y + 1);

	p1.x = draw_point.x + (bpt_info.width_ >> 1);
	p1.y = start_point.y + bpt_info.height_;
	p2 = bpt_info.left_subtree_location_ + start_point;
	p3 = bpt_info.right_subtree_location_ + start_point;
	if (bpt_info.father_role_ == HAS_BOTH)
	{
		p2.x += (bpt->left_->get_data().subtree_width_ >> 1);
		p2.y += bpt->left_->get_data().height_;
		p3.x += (bpt->right_->get_data().subtree_width_ >> 1);
		p3.y += bpt->right_->get_data().height_;
	}
	else if (bpt_info.father_role_ == ONLY_LEFT)
	{
		p2.x += bpt->left_->get_data().subtree_width_ >> 1;
		p2.y += bpt->left_->get_data().subtree_height_;
		p3 = kInvalidPosition;
	}
	else if (bpt_info.father_role_ == ONLY_RIGHT)
	{
		p3.x += bpt->right_->get_data().subtree_width_ >> 1;
		p3.y += bpt->right_->get_data().subtree_height_;
		p2 = kInvalidPosition;
	}
	DrawConnection(p1, p2, p3);
	// std::cout << bpt->get_data() << endl;
}

void Canvas::DrawPaintTree(const PaintTree bpt)
{
	if (canvas_ == NULL || bpt == NULL)
	{
		return;
	}
	Position start_point(0, 0);
	DrawPaintTreeImpl(bpt, start_point);
}

std::ostream &operator<<(std::ostream &os, const Canvas &paint)
{
	vector<vector<string *> >::iterator iter = paint.get_canvas()->begin();
	vector<vector<string *> >::iterator iter_end = paint.get_canvas()->end();

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

#endif
