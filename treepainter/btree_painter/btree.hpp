#ifndef _BTREEPAINTER_BTREE_H_
#define _BTREEPAINTER_BTREE_H_

#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
using std::endl;
using std::string;
using std::ostream;
using std::ostringstream;

namespace btreepainter
{
template<typename T>
class BTreeNode
{
public:
	BTreeNode() : left(NULL), right(NULL) { }
	BTreeNode(const T &data);
	BTreeNode(const T &data, BTreeNode *_left, BTreeNode *_right);
	~BTreeNode() {};

	string getName();

	T &getData() { return data; }
	/* BTreeNode *&getLeft() { return left; }
	BTreeNode *&getRight() { return right; } */

	/* void setLeft(const BTreeNode *l) { left = l; }
	void setRight(const BTreeNode *r) { right = r; } */
	void setData(const T &d) { data = d; }

public:
	BTreeNode *left;
	BTreeNode *right;

private:
	T data;
};

template <typename T>
BTreeNode<T>::BTreeNode(const T &_data)
	: data(_data), left(NULL), right(NULL)
{
}

template <typename T>
BTreeNode<T>::BTreeNode(const T &_data, BTreeNode *_left, BTreeNode *_right)
	: data(_data), left(_left), right(_right)
{
}

template <typename T>
string BTreeNode<T>::getName()
{
	ostringstream buf;
	buf << data;
	return buf.str();
}

template <typename T>
void BTreeOutImpl(ostream &os, BTreeNode<T> &bt,
		const int level = 0)
{
	int i = 0, cur_level = level;
	while (i++ < level)
	{
		os << "   ";
	}

	os << "-\"" << bt.getData() << "\""<< endl;
	if (bt.left != NULL && bt.right != NULL)
	{
		BTreeOutImpl(os, *bt.left, level + 1);
		BTreeOutImpl(os, *bt.right, level + 1);
	}
	else if (bt.left != NULL && bt.right == NULL)
	{
		BTreeOutImpl(os, *bt.left, level + 1);
		os << "\n";
	}
	else if (bt.left == NULL && bt.right != NULL)
	{
		os << "\n";
		BTreeOutImpl(os, *bt.right, level + 1);
	}
	else
	{
	}
}

template <typename T>
ostream &operator<<(ostream &os, BTreeNode<T> &bt)
{
	BTreeOutImpl<T>(os, bt, 0);
	return os;
}

};

#endif
