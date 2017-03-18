#include "geometry.h"

class SpatialIndexInterface
{
	public:
	Point* search(Rectangle, PointCollection);
	Rectangle* search(Rectangle, RectangleCollection);
	void createIndex(PointCollection);
	void createIndex(RectangleCollection);
	bool update();
	bool deleteIndex();
};
