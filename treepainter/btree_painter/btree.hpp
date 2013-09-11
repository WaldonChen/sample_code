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

namespace btree_painter
{

/** Binary tree node. */
template<typename T>
class BTreeNode
{
public:
	BTreeNode() : left_(NULL), right_(NULL) { }
	BTreeNode(const T &data);
	BTreeNode(const T &data, BTreeNode *left, BTreeNode *right);
	~BTreeNode() {};

	string get_name() const;
	const BTreeNode *get_left() const { return left_; }
	const BTreeNode *get_right() const { return right_; }

	T &get_data() { return data_; }
	void set_data(const T &d) { data_ = d; }

public:
	/** Left child of this node. */
	BTreeNode *left_;

	/** Right child of this node. */
	BTreeNode *right_;

private:
	/** The data storaged in this node. */
	T data_;
};

/** Constructes a BTreeNode with data. */
template <typename T>
BTreeNode<T>::BTreeNode(const T &data)
	: data_(data), left_(NULL), right_(NULL)
{
}

/** Construct a BTreeNode with data, pointer of children. */
template <typename T>
BTreeNode<T>::BTreeNode(const T &data, BTreeNode *left, BTreeNode *right)
	: data_(data), left_(left), right_(right)
{
}

/** Returns the name of this node.
 * The type of 'data' must override operator '<<' .
 */
template <typename T>
string BTreeNode<T>::get_name() const
{
	ostringstream buf;
	buf << data_;
	return buf.str();
}

/** Actual implementation of operator '<<' override of binary tree.
 *
 * @tparam T @see BTreeNode
 * @param os ostream&
 * @param bt binary tree pointer
 * @param level the level of node '*bt' in the binary tree
 */
template <typename T>
void BTreeOutputImpl(ostream &os, BTreeNode<T> &bt,
		const int level = 0)
{
	int i = 0;
	int cur_level = level;

	// 1. print space in front of current node.
	while (i < level)
	{
		os << "   ";
		++i;
	}

	// 2. print current node.
	os << "-\"" << bt.get_data() << "\""<< endl;

	// 3. print left and/or right subtree.
	if (bt.left_ != NULL && bt.right_ != NULL)
	{
		BTreeOutputImpl(os, *bt.left_, level + 1);
		BTreeOutputImpl(os, *bt.right_, level + 1);
	}
	else if (bt.left_ != NULL && bt.right_ == NULL)
	{
		BTreeOutputImpl(os, *bt.left_, level + 1);
		os << "\n";	// right subtree is empty
	}
	else if (bt.left_ == NULL && bt.right_ != NULL)
	{
		os << "\n"; // left subtree is empty
		BTreeOutputImpl(os, *bt.right_, level + 1);
	}
	else
	{
		// leaf node, do nothing in step 3
	}
}

/** Overrides operator '<<' of BTreeNode.
 *
 * @tparam T @see BTreeNode
 * @param os ostream&
 * @param bt binary tree pointer
 *
 * @return ostream&
 */
template <typename T>
ostream &operator<<(ostream &os, BTreeNode<T> &bt)
{
	BTreeOutputImpl<T>(os, bt,
					0); // node 'bt' is level 0 in the binary tree
	return os;
}

};

#endif
