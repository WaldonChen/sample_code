#include "btreepainter.h"

#include <iostream>
using std::cout;

using btreepainter::BTreeNode;

// typedef BTreeNode<int> *BTree;

/* BTree buildBTree()
{
	BTree bt0 = new BTreeNode<int>(14, NULL, NULL);
	BTree bt1 = new BTreeNode<int>(18, NULL, NULL);
	BTree bt2 = new BTreeNode<int>(16, bt0, bt1);
	BTree bt3 = new BTreeNode<int>(12, NULL, NULL);
	// BTree bt6 = new BTreeNode<int>(14, NULL, NULL);
	BTree bt4 = new BTreeNode<int>(13, bt3, NULL);
	BTree bt5 = new BTreeNode<int>(10, bt2, bt4);

	return bt5;
} */

typedef BTreeNode<string> *BTree;

BTree buildStringBTree()
{
	BTree bt0 = new BTreeNode<string>("hello\nworld\na!", NULL, NULL);
	BTree bt1 = new BTreeNode<string>("18", NULL, NULL);
	BTree bt2 = new BTreeNode<string>("16", bt0, bt1);
	BTree bt3 = new BTreeNode<string>("j12", NULL, NULL);
	// BTree bt6 = new BTreeNode<string>(14, NULL, NULL);
	BTree bt4 = new BTreeNode<string>("d13", bt3, NULL);
	BTree bt5 = new BTreeNode<string>("ROOT", bt2, bt4);

	return bt5;
}

int main()
{
	BTree btree = buildStringBTree();

	/* BPaintTree bpt;
	Canvas *paint;
	ostringstream buf;
	string str;

	btreepainter::BuildBPaintTree<BTreeNode<string> >(bpt, btree);

	cout << bpt->getData().toString() << endl;
	cout << "\t" << bpt->left->getData().toString() << endl;
	cout << "\t\t" << bpt->left->left->getData().toString() << endl;
	cout << "\t\t" << bpt->left->right->getData().toString() << endl;
	cout << "\t" << bpt->right->getData().toString() << endl;
	cout << "\t\t" << bpt->right->left->getData().toString() << endl;

	paint = new Canvas(bpt->getData().getSubTreeWidth(),
						bpt->getData().getSubTreeHeight());
	paint->DrawBPaintTree(bpt);
	// paint->print();
	cout << *paint; */
	cout << *btree << endl;
	cout << PaintTree(btree);

	// getchar();
	return 0;
}


