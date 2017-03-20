#include "geometry.h"

class SpatialIndexInterface
{
	public:
	PointCollection search(Rectangle);
    RectangleCollection searchRectangle(Rectangle);
	void createIndex(PointCollection,float, float);
	void createIndex(RectangleCollection, float, float);
	bool update(PointCollection,float, float);
	bool update(RectangleCollection,float, float);
	bool deleteIndex();
};
