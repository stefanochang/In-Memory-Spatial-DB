#ifndef DATA_STORAGE_H
#include "../data-storage/data-storage.h"
#endif

#ifndef SPATIALINDEXINTERFACE_H
#define SPATIALINDEXINTERFACE_H



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

#endif