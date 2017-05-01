#ifndef DATA_STORAGE_H
#include "../data-storage/data-storage.h"
#endif

#ifndef SPATIALINDEXINTERFACE_H
#define SPATIALINDEXINTERFACE_H



class SpatialIndexInterface
{
public:
    virtual PointCollection searchPoint(Rectangle, PointCollection*) = 0;
    virtual RectangleCollection searchRectangle(Rectangle, RectangleCollection*) = 0;
    virtual void createIndex(PointCollection) = 0;
    virtual void createIndex(RectangleCollection) = 0;
    virtual bool update(PointCollection) = 0;
    virtual bool update(RectangleCollection) = 0;
    virtual bool deleteIndex() = 0;
};

#endif