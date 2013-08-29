#ifndef _BTREEPAINTER_CANVAS_H_
#define _BTREEPAINTER_CANVAS_H_

#include "bpainttree.h"

#include <vector>
#include <ostream>
using std::vector;
using std::ostream;

namespace btreepainter
{
/**
 * Canvas
 */
class Canvas
{
public:
	Canvas(const int w, const int h);
	~Canvas();

	// inline bool DrawPoint(const string &str, const int x, const int y);
	inline bool DrawPoint(const char* str, const int x, const int y);
	inline bool DrawText(const string &str, const Point p) { DrawText(str, p.x, p.y); }
	bool DrawText(const string &str, const int x, const int y);
	bool DrawRect(const Point p, const int width, const int height,
					enum SonRole sonRole, enum FatherRole faRole);
	bool DrawConnection(const Point &p1, const Point &p2);
	bool DrawConnection(const Point &p1, const Point &p2, const Point &p3);
	void DrawBPaintTree(const BPaintTree bpt);

	inline vector<vector<string*> > *getCanvas() const { return canvas; }

private:
	void DrawBPaintTreeImpl(const BPaintTree bpt, const Point startPt);

private:
	int width, height;
	vector<vector<string*> > *canvas;
};

std::ostream &operator<<(std::ostream &os, const Canvas &paint);

};

#endif
