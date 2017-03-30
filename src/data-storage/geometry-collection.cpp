#include "geometry-collection.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// POINT COLLECTION
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PointCollection::PointCollection()
: list() {}

// constructor in list.h required - initialize list from vector based on organization type (x sorted, y sorted)
PointCollection::PointCollection(string name, string databaseName, int collectionStructure, vector<Point> points)
: list(points, collectionStructure) {
  this.name = name;
  this.databaseName = databaseName;
  this.collectionStructure = collectionStructure;
}

Point PointCollection::getById(int id) {
  return getPointByUUID(this.name, id)
}

vector<Point> PointCollection::getNext(int n=1) {
  return getnext(n, 1); // change name if wrapper function name changes
}


// insertData wrapper required to pass string table name and geometry
int PointCollection::insert(Point point) {
  return appendLast(point);
}


// deleteData wrapper required to pass string table name and geometry
int PointCollection::remove(Point point) {
  return deleteByUUID(point->id)
}

int PointCollection::removeById(int id) {
  return deleteByUUID(id);
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RECTANGLE COLLECTION
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

RectangleCollection::RectangleCollection()
: list() {}

// constructor in list.h required - initialize list from vector based on organization type (x sorted, y sorted)
RectangleCollection::RectangleCollection(string name, string databaseName, int collectionStructure, vector<Rectangle> rectangles)
: list(rectangles, collectionStructure) {
  this.name = name;
  this.databaseName = databaseName;
  this.collectionStructure = collectionStructure;
}

Rectangle RectangleCollection::getById(int id) {
  return getPointByUUID(this.name, id)
}

vector<Rectangle> RectangleCollection::getNext(int n=1) {
  return getnext(n, 1); // change name if wrapper function name changes
}

// insertData wrapper required to pass string table name and geometry
int RectangleCollection::insert(Rectangle rectangle) {
  return appendLast(rectangle);
}


// deleteData wrapper required to pass string table name and geometry
int RectangleCollection::remove(Rectangle rectangle) {
  return deleteByUUID(id);
}

int RectangleCollection::removeById(int id) {
  return deleteByUUID(id);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// POINTPOINT COLLECTION
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

PointPointCollection::PointPointCollection()
: list() {}

// constructor in list.h required - initialize list from vector based on organization type (x sorted, y sorted)
PointPointCollection::PointPointCollection(string name, string databaseName, int collectionStructure, vector<PointPoint> pointpoints)
: list(pointpoints, collectionStructure) {
  this.name = name;
  this.databaseName = databaseName;
  this.collectionStructure = collectionStructure;
}

PointPoint PointPointCollection::getById(int id) {
  return getPointByUUID(this.name, id)
}

vector<PointPoint> PointPointCollection::getNext(int n=1) {
  return getnext(n, 1); // change name if wrapper function name changes
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RECTANGLERECTANGLE COLLECTION
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

RectangleRectangleCollection::RectangleRectangleCollection()
: list() {}

// constructor in list.h required - initialize list from vector based on organization type (x sorted, y sorted)
RectangleRectangleCollection::RectangleRectangleCollection(string name, string databaseName, int collectionStructure, vector<PointPoint> pointpoints)
: list(pointpoints, collectionStructure) {
  this.name = name;
  this.databaseName = databaseName;
  this.collectionStructure = collectionStructure;
}

RectangleRectangle RectangleRectangleCollection::getById(int id) {
  return getPointByUUID(this.name, id)
}

vector<RectangleRectangle> RectangleRectangleCollection::getNext(int n=1) {
  return getnext(n, 1); // change name if wrapper function name changes
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// POINTRECTANGLE COLLECTION
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

PointRectangleCollection::PointRectangleCollection()
: list() {}

// constructor in list.h required - initialize list from vector based on organization type (x sorted, y sorted)
PointRectangleCollection::PointRectangleCollection(string name, string databaseName, int collectionStructure, vector<PointRectangle> pointrectangles)
: list(pointrectangles, collectionStructure) {
  this.name = name;
  this.databaseName = databaseName;
  this.collectionStructure = collectionStructure;
}

PointRectangle PointRectangleCollection::getById(int id) {
  return getPointByUUID(this.name, id)
}

vector<PointRectangle> PointRectangleCollection::getNext(int n=1) {
  return getnext(n, 1); // change name if wrapper function name changes
}
