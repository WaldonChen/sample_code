#ifndef _BTREEPAINTER_BPAINTERTREE_H_
#define _BTREEPAINTER_BPAINTERTREE_H_

#include "btree.hpp"

#include <iostream>
#include <ostream>
#include <string>

using std::string;
using std::ostream;

namespace btree_painter
{

enum SonRole
{
	SON_ROLE_NONE,
	LEFT_SON,
	RIGHT_SON,
	ROOT
};

enum FatherRole
{
	FATHER_ROLE_NONE,
	ONLY_LEFT,
	ONLY_RIGHT,
	HAS_BOTH,
	HAS_NOCHILD
};

const int kInvalidPositionValue = -1;

/** Position
 */
class Position
{
public:
	Position() : x(kInvalidPositionValue), y(kInvalidPositionValue) {}
	Position(const int _x, const int _y) : x(_x), y(_y) {}
	~Position() {}

	Position operator+(const Position &p2);

public:
	/** coordinate in horizontal direction */
	int x;

	/** coordinate in vertical direction */
	int y;
};

const Position kInvalidPosition(kInvalidPositionValue, kInvalidPositionValue);

bool operator==(const Position &p1, const Position &p2)
{
	if (p1.x == p2.x && p1.y == p2.y)
	{
		return true;
	}
	return false;
}

bool operator!=(const Position &p1, const Position &p2)
{
	return !(p1 == p2);
}

/** overrides operator '+' of Position
 *
 * @param p2 the additional position
 *
 * @return A new position
 */
Position Position::operator+(const Position &p2)
{
	if (*this == kInvalidPosition || p2 == kInvalidPosition)
	{
		return kInvalidPosition;
	}
	Position p1(x + p2.x, y + p2.y);
	return p1;
}

std::ostream& operator<<(std::ostream &os, const Position &p)
{
	os << "(" << p.x << ", " << p.y << ")";
	return os;
}

/** The infomation of a binary tree node that be painted.
 */
class PaintTreeInfo
{
public:
	PaintTreeInfo();
	~PaintTreeInfo() { }

	void CalculatePaintTreeInfo(const PaintTreeInfo *left,
							const PaintTreeInfo *right);

public:
	/** The role of this node as a son. */
	enum SonRole son_role_;

	/** The role of this node as parent. */
	enum FatherRole father_role_;

	/** The width and height of this node. */
	int width_, height_;

	/** The width and height of the subtree_width_
	 * which consist of this node and it's sons.
	 */
	int subtree_width_, subtree_height_;

	/** Related location of left and right son in the subtree */
	Position left_subtree_location_, right_subtree_location_;

	/** The string of the PaintTreeNode display on the canvas. */
	string name_;
};

typedef BTreeNode<PaintTreeInfo> PaintTreeNode;
typedef PaintTreeNode *PaintTree;

PaintTreeInfo::PaintTreeInfo()
	: son_role_(SON_ROLE_NONE), father_role_(FATHER_ROLE_NONE),
	  width_(0), height_(0), subtree_width_(0), subtree_height_(0),
	  left_subtree_location_(kInvalidPosition),
	  right_subtree_location_(kInvalidPosition)
{
}

ostream &operator<<(ostream &os, const PaintTreeInfo &info)
{
	os << "Node: " << info.name_ << " SonRole: " << info.son_role_
		<< " FatherRole: " << info.father_role_ << " (W,H): ("
		<< info.width_ << ", " << info.height_ << ") (W,H)': ("
		<< info.subtree_width_ << ", " << info.subtree_height_
		<< ") LocLeft: " << info.left_subtree_location_ << " LocRight: "
		<< info.right_subtree_location_;
	return os;
}

void CalculateStringSize(const string &str, int &width, int &height);

/** Calculate the PaintTreeInfo of this node with their children.
 *
 * @param left left subtree
 * @param right right subtree
 */
void PaintTreeInfo::CalculatePaintTreeInfo(const PaintTreeInfo *left,
							const PaintTreeInfo *right)
{
	int left_width, left_height, right_width, right_height;
	int l = 2, lr_width;

	// Get size of subtrees.
	left_width = left == NULL ? 0 : left->subtree_width_;
	left_height = left == NULL ? 0 : left->subtree_height_;
	right_width = right == NULL ? 0 : right->subtree_width_;
	right_height = right == NULL ? 0 : right->subtree_height_;

	// Calculate 'name_' size.
	CalculateStringSize(name_, width_, height_);

	// Size of current node.
	width_ = (width_ | 0x01) + 2;
	height_ += 2;

	// Current node is leaf.
	if (left == NULL && right == NULL)
	{
		subtree_width_ = width_;
		subtree_height_ = height_;
		left_subtree_location_ = kInvalidPosition;
		right_subtree_location_ = kInvalidPosition;
		return;
	}

	if (!((left_width + right_width) & 0x01))
	{
		l = 1;
	}
	lr_width = left_width + right_width + l;

	left_subtree_location_.y = height_ + 1;
	right_subtree_location_.y = height_ + 1;
	left_subtree_location_.x = 0;
	right_subtree_location_.x = left_width + l;
	if (width_ > lr_width)
	{
		left_subtree_location_.x += (width_ - lr_width) >> 1;
		right_subtree_location_.x += left_subtree_location_.x;
	}
	subtree_width_ = std::max(width_, lr_width);
	subtree_height_ = std::max(left_height, right_height) + height_ + 1;

	if (left != NULL && right == NULL)
	{
		right_subtree_location_ = kInvalidPosition;
	}
	else if (left == NULL && right != NULL)
	{
		left_subtree_location_ = kInvalidPosition;
	}
}

/** Calculate the width and height of a string.
 *
 * @param str the string be calculated
 * @param[out] width width of the 'str'
 * @param[out] height height of the 'str'
 */
void CalculateStringSize(const string &str, int &width, int &height)
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

/** Actual implementation of BuildPaintTree().
 *
 * @tparam T
 * @param[out] bpt the paint tree generated
 * @param[in] bt the binary tree be painted
 */
template <typename T>
void BuildPaintTreeImpl(PaintTree &bpt, const T *bt)
{
	if (bt == NULL)
	{
		return;
	}

	bpt = new PaintTreeNode();

	BuildPaintTreeImpl(bpt->left_, bt->get_left());
	BuildPaintTreeImpl(bpt->right_, bt->get_right());

	PaintTreeInfo bpt_info = PaintTreeInfo();
	bpt_info.name_ = bt->get_name();

	if (bpt->left_ != NULL && bpt->right_ != NULL)
	{
		bpt_info.father_role_ = HAS_BOTH;
		bpt->left_->get_data().son_role_ = LEFT_SON;
		bpt->right_->get_data().son_role_ = RIGHT_SON;
		bpt_info.CalculatePaintTreeInfo(&(bpt->left_->get_data()),
					&(bpt->right_->get_data()));
	}
	else if (bpt->left_ != NULL && bpt->right_ == NULL)
	{
		bpt_info.father_role_ = ONLY_LEFT;
		bpt->left_->get_data().son_role_ = LEFT_SON;
		bpt_info.CalculatePaintTreeInfo(&(bpt->left_->get_data()),
										NULL);	// right child is NULL
	}
	else if (bpt->left_ == NULL && bpt->right_ != NULL)
	{
		bpt_info.father_role_ = ONLY_RIGHT;
		bpt->right_->get_data().son_role_ = RIGHT_SON;
		bpt_info.CalculatePaintTreeInfo(NULL, // left child is NULL
										&(bpt->right_->get_data()));
	}
	else
	{
		bpt_info.father_role_ = HAS_NOCHILD;
		bpt_info.CalculatePaintTreeInfo(NULL, NULL);
	}

	bpt->set_data(bpt_info);
}

/** Build the PaintTree of a BTree.
 *
 * @tparam T
 * @param bpt the paint tree generated
 * @param bt the binary tree be painted
 */
template <typename T>
void BuildPaintTree(PaintTree &bpt, T *bt)
{
	BuildPaintTreeImpl(bpt, bt);
	if (bpt != NULL)
	{
		bpt->get_data().son_role_ = ROOT;
	}
}

void DestoryPaintTree(PaintTree &bpt)
{
	if (bpt == NULL)
	{
		return;
	}

	DestoryPaintTree(bpt->left_);
	DestoryPaintTree(bpt->right_);

	delete bpt;
	bpt = NULL;
}

};
#endif
