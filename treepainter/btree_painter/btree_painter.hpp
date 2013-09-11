#ifndef _BTREEPAINTER_H_
#define _BTREEPAINTER_H_

#include "paint_tree.hpp"
#include "canvas.hpp"

#include <string>
#include <sstream>

using std::string;
using std::ostringstream;

namespace btree_painter
{

template <typename T>
string PaintBTree(T *bt)
{
	PaintTree bpt;
	ostringstream buf;

	BuildPaintTree<T>(bpt, bt);
	Canvas paint(bpt->get_data().subtree_width_,
			bpt->get_data().subtree_height_);
	paint.DrawPaintTree(bpt);
	DestoryPaintTree(bpt);
	buf << paint;
	return buf.str();
}

};
#endif
