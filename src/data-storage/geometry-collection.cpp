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
  return getNextPoint(n, 1); // change name if wrapper function name changes
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
