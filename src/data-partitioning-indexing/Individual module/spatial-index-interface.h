#include "geometry-collection.h"
class SpatialIndexInterface
{
	public:
	PointCollection searchPoint(Rectangle);
	RectangleCollection searchRectangle(Rectangle);
	void createIndex(PointCollection);
	void createIndex(RectangleCollection);
	bool update(PointCollection);
	bool update(RectangleCollection);
	bool deleteIndex();
};

