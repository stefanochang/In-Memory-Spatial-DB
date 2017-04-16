#include "geometry.h"

class SpatialIndexInterface
{
	public:
	PointCollection search(Rectangle,PointCollection*);
	RectangleCollection search(Rectangle,RectangleCollection*);
	void createIndex(PointCollection);
	void createIndex(RectangleCollection);
	bool update(PointCollection);
	bool update(RectangleCollection);
	bool deleteIndex();
};
