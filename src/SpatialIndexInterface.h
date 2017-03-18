#include "Geometry.h"

class SpatialIndexInterface
{
	public:
	Point* search(Rectangle, PointCollection);
	Rectangle* search(Rectangle, RectangleCollection);
	void createIndex(PointCollection);
	void createIndex(RectangleCollection);
	int update();
	int deleteIndex();
};
