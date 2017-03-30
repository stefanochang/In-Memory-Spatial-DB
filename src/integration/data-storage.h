#include "geometry-collection.h"

bool loadData(string, string, string, string, int);
bool insertData(PointCollection, Point);
bool insertData(RectangleCollection, Rectangle);
bool insertDataBulk(PointCollection, PointCollection);
bool insertDataBulk(RectangleCollection, RectangleCollection);
bool deletePoint(PointCollection, Point);
bool deleteRectangle(RectangleCollection, Rectangle);
Point getPointByUUID(string, int);
Rectangle getRaectangleByUUID(string, int);
PointPoint getPointPointByUUID(string, int);
PointRectangle getPointRectangleByUUID(string, int);
RectangleRectangle getRectangleRectangleByUUID(string, int);
