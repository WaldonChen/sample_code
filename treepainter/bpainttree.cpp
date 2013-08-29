#include "bpainttree.h"

#include <string>
#include <ostream>
#include <sstream>

using std::string;
using std::ostream;
using std::ostringstream;

namespace btreepainter
{

Point Point::operator+(const Point &p2)
{
	if (*this == INVALID_POINT || p2 == INVALID_POINT)
	{
		return INVALID_POINT;
	}
	Point p1(x + p2.x, y + p2.y);
	return p1;
}

bool operator==(const Point &p1, const Point &p2)
{
	if (p1.x == p2.x && p1.y == p2.y)
	{
		return true;
	}
	return false;
}

std::ostream& operator<<(std::ostream &os, const Point &p)
{
	os << "(" << p.x << ", " << p.y << ")";
	return os;
}

BPaintTreeInfo::BPaintTreeInfo()
	: sonRole(SON_ROLE_NONE), fatherRole(FATHER_ROLE_NONE),
	  width(0), height(0), subTreeWidth(0), subTreeHeight(0),
	  locationLeft(INVALID_POINT), locationRight(INVALID_POINT)
{
}

ostream &operator<<(ostream &os, const BPaintTreeInfo &info)
{
	os << "Node: " << info.getName() << " SonRole: " << info.getSonRole()
		<< " FatherRole: " << info.getFatherRole() << " (W,H): ("
		<< info.getWidth() << ", " << info.getHeight() << ") (W,H)': ("
		<< info.getSubTreeWidth() << ", " << info.getSubTreeHeight()
		<< ") LocLeft: " << info.getLocationLeft() << " LocRight: "
		<< info.getLocationRight();
	return os;
}

/**
string BPaintTreeInfo::toString()
{
	ostringstream buf;
	buf << "Node: " << name << " SonRole: " << sonRole << " FatherRole: " << fatherRole
		<< " (W,H): (" << width << ", " << height << ") (W,H)': (" << subTreeWidth << ", "
		<< subTreeHeight << ") LocLeft: " << locationLeft << " LocRight: " << locationRight;
	return buf.str();
}
*/

void CalcuStringSize(const string &str, int &width, int &height)
{
	int max_width = 0;
	int cur_width = 0;
	int lines = 1;
	int str_len = str.length();
	string::size_type i;

	for (i = 0; i < str_len; ++i)
	{
		if (str[i] == '\n')
		{
			lines++;
			if (max_width < cur_width)
			{
				max_width = cur_width;
			}
			cur_width = 0;
		}
		cur_width++;
	}
	height = lines;
	width = std::max(cur_width, max_width);
}

void BPaintTreeInfo::CalcuNodeSizeAndSonLocation(const BPaintTreeInfo *left,
							const BPaintTreeInfo *right)
{
	int left_width, left_height, right_width, right_height;
	int l = 2, lr_width;

	left_width = left == NULL ? 0 : left->subTreeWidth;
	left_height = left == NULL ? 0 : left->subTreeHeight;
	right_width = right == NULL ? 0 : right->subTreeWidth;
	right_height = right == NULL ? 0 : right->subTreeHeight;

	CalcuStringSize(name, width, height);
	width = (width | 0x01) + 2;
	height += 2;
	/* width = (str.length() | 0x01) + 2;
	height = 3; */
	if (left == NULL && right == NULL)
	{
		subTreeWidth = width;
		subTreeHeight = height;
		locationLeft = INVALID_POINT;
		locationRight = INVALID_POINT;
		return;
	}

	if (!((left_width + right_width) & 0x01))
	{
		l = 1;
	}
	lr_width = left_width + right_width + l;

	locationLeft.y = height + 1;
	locationRight.y = height + 1;
	if (width > lr_width)
	{
		locationLeft.x += (width - lr_width) >> 1;
		locationRight.x += (width - lr_width) >> 1 + l;
	}
	else
	{
		locationLeft.x = 0;
		locationRight.x = left_width + l;
	}
	subTreeWidth = std::max(width, lr_width);
	subTreeHeight = std::max(left_height, right_height) + height + 1;

	if (left != NULL && right == NULL)
	{
		locationRight = INVALID_POINT;
	}
	else if (left == NULL && right != NULL)
	{
		locationLeft = INVALID_POINT;
	}
}

};
