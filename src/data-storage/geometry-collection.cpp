//#include "../integration/geometry-collection.h"
#include "ds_api.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// POINT COLLECTION
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PointCollection::PointCollection()
: list(TYPE_POINT) {}

// constructor in list.h required - initialize list from vector based on organization type (x sorted, y sorted)
PointCollection::PointCollection(string name, string databaseName, int collectionStructure, vector<Point> points)
: list(TYPE_POINT) {
  this->name = name;
  this->databaseName = databaseName;
  this->collectionStructure = collectionStructure;
}

Point PointCollection::getById(int id) {
  Point *pnt;
  pnt = getPointByUUID(this->name, id);
  return *pnt;
}

/*vector<Point> PointCollection::getNext(int n=1) {
  return getnext(n, 1); // change name if wrapper function name changes
}*/

int PointCollection::insert(Point point) {
  return insertData(*this,point);
}

/*int PointCollection::remove(Point point) {
  return deleteByUUID(point->id)
}*/

int PointCollection::removeById(int id) {
  return deleteByUUID(id);
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RECTANGLE COLLECTION
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

RectangleCollection::RectangleCollection()
: list(TYPE_RECTANGLE) {}

// constructor in list.h required - initialize list from vector based on organization type (x sorted, y sorted)
RectangleCollection::RectangleCollection(string name, string databaseName, int collectionStructure, vector<Rectangle> rectangles)
: list(TYPE_RECTANGLE) {
  this->name = name;
  this->databaseName = databaseName;
  this->collectionStructure = collectionStructure;
}

Rectangle RectangleCollection::getById(int id) {
  Rectangle *rec = getRectangleByUUID(this->name, id);
  return *rec;
}

/*vector<Rectangle> RectangleCollection::getNext(int n=1) {
  return getnext(n, 1); // change name if wrapper function name changes
}*/

// insertData wrapper required to pass string table name and geometry
int RectangleCollection::insert(Rectangle rectangle) {
  return insertData(*this,rectangle);
}


// deleteData wrapper required to pass string table name and geometry
/*int RectangleCollection::remove(Rectangle rectangle) {
  return deleteByUUID(id);
}*/

int RectangleCollection::removeById(int id) {
  return deleteByUUID(id);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// POINTPOINT COLLECTION
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

PointPointCollection::PointPointCollection()
: list(TYPE_POINTPOINT) {}

// constructor in list.h required - initialize list from vector based on organization type (x sorted, y sorted)
PointPointCollection::PointPointCollection(string name, string databaseName, int collectionStructure, vector<PointPoint> pointpoints)
: list(TYPE_POINTPOINT) {
  this->name = name;
  this->databaseName = databaseName;
  this->collectionStructure = collectionStructure;
}

PointPoint PointPointCollection::getById(int id) {
  PointPoint *pntpnt = getPointPointByUUID(this->name, id);
  return *pntpnt;
}

/*vector<PointPoint> PointPointCollection::getNext(int n=1) {
  return getnext(n, 1); // change name if wrapper function name changes
}*/

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RECTANGLERECTANGLE COLLECTION
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

RectangleRectangleCollection::RectangleRectangleCollection()
: list(TYPE_RECTANGLERECTANGLE) {}

// constructor in list.h required - initialize list from vector based on organization type (x sorted, y sorted)
RectangleRectangleCollection::RectangleRectangleCollection(string name, string databaseName, int collectionStructure, vector<RectangleRectangle> rectanglerectangle)
: list(TYPE_RECTANGLERECTANGLE) {
  this->name = name;
  this->databaseName = databaseName;
  this->collectionStructure = collectionStructure;
}

RectangleRectangle RectangleRectangleCollection::getById(int id) {
  RectangleRectangle *recrec = getRectangleRectangleByUUID(this->name, id);
  return *recrec;
}

/*vector<RectangleRectangle> RectangleRectangleCollection::getNext(int n=1) {
  return getnext(n, 1); // change name if wrapper function name changes
}*/

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// POINTRECTANGLE COLLECTION
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

PointRectangleCollection::PointRectangleCollection()
: list(TYPE_POINTRECTANGLE) {}

// constructor in list.h required - initialize list from vector based on organization type (x sorted, y sorted)
PointRectangleCollection::PointRectangleCollection(string name, string databaseName, int collectionStructure, vector<PointRectangle> pointrectangles)
: list(TYPE_POINTRECTANGLE) {
  this->name = name;
  this->databaseName = databaseName;
  this->collectionStructure = collectionStructure;
}

PointRectangle PointRectangleCollection::getById(int id) {
  PointRectangle *pntrec = getPointRectangleByUUID(this->name, id);
  return *pntrec;
}

/*vector<PointRectangle> PointRectangleCollection::getNext(int n=1) {
  return getnext(n, 1); // change name if wrapper function name changes
}*/
