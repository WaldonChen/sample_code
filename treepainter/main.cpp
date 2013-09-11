#include "btree_painter/btree_painter.hpp"

#include <iostream>
#include <sstream>
using std::cout;
using std::ostringstream;

// // use the internal BTreeNode of namespace 'btree_painter'
// using btree_painter::BTreeNode;

// Or use custom binary tree
// It's must implement three method:
//		const BinaryTreeNode *get_left()
//		const BinaryTreeNode *get_right()
//		string get_name()
template <typename T>
class BinaryTreeNode
{
public:
	BinaryTreeNode(const T &data, BinaryTreeNode *left,
			BinaryTreeNode *right)
		: data_(data), left_(left), right_(right) {}

	const BinaryTreeNode *get_left() const { return left_; }
	const BinaryTreeNode *get_right() const { return right_; }
	string get_name() const;

private:
	T data_;
	BinaryTreeNode *left_;
	BinaryTreeNode *right_;
};

template <typename T>
string BinaryTreeNode<T>::get_name() const
{
	ostringstream buf;
	buf << data_;
	return buf.str();
}

typedef BinaryTreeNode<string> *BTree;

// typedef BTreeNode<int> *BTree;

/* BTree buildBTree()
{
	BTree bt0 = new BTreeNode<int>(14, NULL, NULL);
	BTree bt1 = new BTreeNode<int>(18, NULL, NULL);
	BTree bt2 = new BTreeNode<int>(16, bt0, bt1);
	BTree bt3 = new BTreeNode<int>(12, bt1, NULL);
	// BTree bt6 = new BTreeNode<int>(14, NULL, NULL);
	BTree bt4 = new BTreeNode<int>(13, bt3, NULL);
	BTree bt5 = new BTreeNode<int>(10, bt2, bt4);

	return bt5;
} */

BTree buildStringBTree()
{
	BTree bt0 = new BinaryTreeNode<string>("hello\nworld\na!", NULL, NULL);
	BTree bt1 = new BinaryTreeNode<string>("18", NULL, bt0);
	BTree bt2 = new BinaryTreeNode<string>("16", bt0, bt1);
	BTree bt3 = new BinaryTreeNode<string>("j12", bt1, NULL);
	// BTree bt6 = new BTreeNode<string>(14, NULL, NULL);
	BTree bt4 = new BinaryTreeNode<string>("d13", bt3, NULL);
	BTree bt7 = new BinaryTreeNode<string>("ssd\ndds", bt4, bt2);
	BTree bt5 = new BinaryTreeNode<string>("ROOT", bt2, bt7);

	return bt5;
}

int main()
{
	BTree btree = buildStringBTree();

	// cout << *btree << endl;
	cout << btree_painter::PaintBTree(btree);

	// getchar();
	return 0;
}


