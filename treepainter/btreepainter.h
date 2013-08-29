#ifndef _BTREEPAINTER_H_
#define _BTREEPAINTER_H_

#include "bpainttree.h"
#include "canvas.h"

#include <string>
#include <sstream>

using std::string;
using std::ostringstream;

namespace btreepainter
{

template <typename T>
string PaintTree(const T bt)
{
	BPaintTree bpt;
	ostringstream buf;

	btreepainter::BuildBPaintTree<BTreeNode<string> >(bpt, bt);
	Canvas paint(bpt->getData().getSubTreeWidth(),
			bpt->getData().getSubTreeHeight());
	paint.DrawBPaintTree(bpt);
	buf << paint;
	return buf.str();
}

};
#endif
