#ifndef _BTREEPAINTER_BPAINTERTREE_H_
#define _BTREEPAINTER_BPAINTERTREE_H_

#include "btree.h"

#include <iostream>
#include <ostream>
#include <string>

using std::string;
using std::ostream;

namespace btreepainter
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
	HAS_LEFT,
	HAS_RIGHT,
	HAS_BOTH,
	HAS_NOCHILD
};

/**
 * Point
 */
class Point
{
public:
	Point() : x(-1), y(-1) {}
	Point(const int _x, const int _y) : x(_x), y(_y) {}
	~Point() {}

	Point operator+(const Point &p2);

public:
	int x, y;
};

bool operator==(const Point &p1, const Point &p2);
std::ostream& operator<<(std::ostream &os, const Point &p);

const Point INVALID_POINT(-1, -1);

/**
 * BPaintTreeInfo
 */
class BPaintTreeInfo
{
public:
	BPaintTreeInfo();
	~BPaintTreeInfo() { }

	void CalcuNodeSizeAndSonLocation(const BPaintTreeInfo *left,
							const BPaintTreeInfo *right);
	// string toString();

	/** getter */
	inline enum SonRole getSonRole() const { return sonRole; }
	inline enum FatherRole getFatherRole() const { return fatherRole; }
	inline int getWidth() const { return width; }
	inline int getHeight() const { return height; }
	inline int getSubTreeWidth() const { return subTreeWidth; }
	inline int getSubTreeHeight() const { return subTreeHeight; }
	inline Point getLocationLeft() const { return locationLeft; }
	inline Point getLocationRight() const { return locationRight; }
	inline const string& getName() const { return name; }

	/** setter */
	inline void setSonRole(const enum SonRole role) { sonRole = role; }
	inline void setFatherRole(const enum FatherRole role) { fatherRole = role; }
	inline void setWidth(const int w) { width = w; }
	inline void setHeight(const int h) { height = h; }
	inline void setSubTreeWidth(const int sw) { subTreeWidth = sw; }
	inline void setSubTreeHeight(const int sh) { subTreeHeight = sh; }
	inline void setLocationLeft(const Point &pt) { locationLeft = pt; }
	inline void setLocationRight(const Point &pt) { locationRight = pt; }
	inline void setName(const string& str) { name = str; }

private:
	/** The role of this node as a son. */
	enum SonRole sonRole;

	/** The role of this node as parent. */
	enum FatherRole fatherRole;

	/** The width and height of this node. */
	int width, height;

	/** The width and height of the subTreeWidth
	 * which consist of this node and it's sons.
	 */
	int subTreeWidth, subTreeHeight;

	/** Related location of left and right son in the subtree */
	Point locationLeft, locationRight;

	/** The string of the BPaintTreeNode display on the canvas. */
	string name;
};

ostream &operator<<(ostream &os, const BPaintTreeInfo &info);

typedef BTreeNode<BPaintTreeInfo> BPaintTreeNode;
typedef BPaintTreeNode *BPaintTree;

template <typename T>
void BuildBPaintTreeImpl(BPaintTree &bpt, T *bt)
{
	if (bt == NULL)
	{
		return;
	}

	bpt = new BPaintTreeNode();

	BuildBPaintTreeImpl(bpt->left, bt->left);
	BuildBPaintTreeImpl(bpt->right, bt->right);

	BPaintTreeInfo bpt_info = BPaintTreeInfo();
	bpt_info.setName(bt->getName());

	if (bpt->left != NULL && bpt->right != NULL)
	{
		bpt_info.setFatherRole(HAS_BOTH);
		bpt->left->getData().setSonRole(LEFT_SON);
		bpt->right->getData().setSonRole(RIGHT_SON);
		bpt_info.CalcuNodeSizeAndSonLocation(&(bpt->left->getData()),
					&(bpt->right->getData()));
	}
	else if (bpt->left != NULL && bpt->right == NULL)
	{
		bpt_info.setFatherRole(HAS_LEFT);
		bpt->left->getData().setSonRole(LEFT_SON);
		bpt_info.CalcuNodeSizeAndSonLocation(&(bpt->left->getData()), NULL);
	}
	else if (bpt->left == NULL && bpt->right != NULL)
	{
		bpt_info.setFatherRole(HAS_RIGHT);
		bpt->right->getData().setSonRole(RIGHT_SON);
		bpt_info.CalcuNodeSizeAndSonLocation(NULL, &(bpt->right->getData()));
	}
	else
	{
		bpt_info.setFatherRole(HAS_NOCHILD);
		bpt_info.CalcuNodeSizeAndSonLocation(NULL, NULL);
	}

	bpt->setData(bpt_info);
}

/**
 * Build the BPaintTree of a BTree
 */
template <typename T>
void BuildBPaintTree(BPaintTree &bpt, T *bt)
{
	BuildBPaintTreeImpl(bpt, bt);
	if (bpt != NULL)
	{
		bpt->getData().setSonRole(ROOT);
	}
}

void CalcuStringSize(const string &str, int &width, int &height);
};
#endif
