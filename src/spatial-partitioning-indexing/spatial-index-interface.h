#include "geometry.h"

class SpatialIndexInterface
{
	public:
	vector<Point> search(Rectangle);
	vector<Rectangle> searchRectangle(Rectangle);
	void createIndex(PointCollection,float, float);
	void createIndex(RectangleCollection, float, float);
	bool update(PointCollection,float, float);
	bool update(RectangleCollection,float, float);
	bool deleteIndex();
};
