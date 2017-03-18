#include<iostream>
#include "Geometry.h"
#include<string>

int loadData(string, string, string, string, int);
int insertData(PointCollection, Point);
int insertData(RectangleCollection, Rectangle);
int insertDataBulk(PointCollection, PointCollection);
int insertDataBulk(RectangleCollection, RectangleCollection);
int deletePoint(PointCollection, Point);
int deleteRectangle(RectangleCollection, Rectangle);
Point getPointByUUID(string, int);
Rectangle getRaectangleByUUID(string, int);
PointPoint getPointPointByUUID(string, int);
PointRectangle getPointRectangleByUUID(string, int);
RectangleRectangle getRectangleRectangleByUUID(string, int);


