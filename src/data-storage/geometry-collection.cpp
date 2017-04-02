<<<<<<< HEAD
=======
//#include "../integration/geometry-collection.h"
>>>>>>> 887e894675d2ad42a01a567d033aa871bc1f4e49
#include "ds_api.h"
#include <map>
std::map<int, record *>getmap;

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

vector<Point> PointCollection::getNext(int n, int transactionId) {
  vector<Point> points;
  Point *newPoint;
  record *from;
  int rdcnt=0;
  if(getmap.find(transactionId) != getmap.end())
  {
    from = 	getmap.find(transactionId)->second;
    from->inDegree--;
  }
  else
  {
    from = head;
  }
  while(rdcnt < n and from != head->prev)
  {
    if(from->isDeleted)
      continue;
    newPoint = new Point(from->geom->pnt->x, from->geom->pnt->y);
    points.push_back(*newPoint);
    free(newPoint);
  }
  return points; // change name if wrapper function name changes
}

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

vector<Rectangle> RectangleCollection::getNext(int n, int transactionId) {
  vector<Rectangle> rectangles;
  Rectangle *newRectangle;
  record *from;
  int rdcnt=0;
  if(getmap.find(transactionId) != getmap.end())
  {
    from = 	getmap.find(transactionId)->second;
    from->inDegree--;
  }
  else
  {
    from = head;
  }
  while(rdcnt < n and from != head->prev)
  {
    if(from->isDeleted)
      continue;
    newRectangle = new Rectangle(from->geom->rec->top_x, from->geom->rec->top_y,from->geom->rec->bottom_x, from->geom->rec->bottom_y);
    rectangles.push_back(*newRectangle);
    free(newRectangle);
  }
  return rectangles; // change name if wrapper function name changes
}

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

vector<PointPoint> PointPointCollection::getNext(int n, int transactionId) {
  vector<PointPoint> points;
  PointPoint *newPoint;
  record *from;
  int rdcnt=0;
  if(getmap.find(transactionId) != getmap.end())
  {
    from = 	getmap.find(transactionId)->second;
    from->inDegree--;
  }
  else
  {
    from = head;
  }
  while(rdcnt < n and from != head->prev)
  {
    if(from->isDeleted)
      continue;
    newPoint = new PointPoint(from->geom->pntpnt->point1.x, from->geom->pntpnt->point1.y, from->geom->pntpnt->point2.x, from->geom->pntpnt->point2.y);
    points.push_back(*newPoint);
    free(newPoint);
  }
  return points; // change name if wrapper function name changes
}

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

vector<RectangleRectangle> RectangleRectangleCollection::getNext(int n, int transactionId) {
  vector<RectangleRectangle> recrecs;
  RectangleRectangle *newRectangle;
  record *from;
  int rdcnt=0;
  if(getmap.find(transactionId) != getmap.end())
  {
    from = 	getmap.find(transactionId)->second;
    from->inDegree--;
  }
  else
  {
    from = head;
  }
  while(rdcnt < n and from != head->prev)
  {
    if(from->isDeleted)
      continue;
    newRectangle = new RectangleRectangle(from->geom->recrec->rec1.top_x, from->geom->recrec->rec1.top_y,from->geom->recrec->rec1.bottom_x, from->geom->recrec->rec1.bottom_y, from->geom->recrec->rec2.top_x, from->geom->recrec->rec2.top_y,from->geom->recrec->rec2.bottom_x, from->geom->recrec->rec2.bottom_y);
    recrecs.push_back(*newRectangle);
    free(newRectangle);
  }
  return recrecs;// change name if wrapper function name changes
}

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

vector<PointRectangle> PointRectangleCollection::getNext(int n, int transactionId) {
  vector<PointRectangle> pointrecs;
  PointRectangle *newRectangle;
  record *from;
  int rdcnt=0;
  if(getmap.find(transactionId) != getmap.end())
  {
    from = 	getmap.find(transactionId)->second;
    from->inDegree--;
  }
  else
  {
    from = head;
  }
  while(rdcnt < n and from != head->prev)
  {
    if(from->isDeleted)
      continue;
    newRectangle = new PointRectangle(from->geom->pntrec->point1.x, from->geom->pntrec->point1.y, from->geom->pntrec->rec.top_x, from->geom->pntrec->rec.top_y,from->geom->pntrec->rec.bottom_x, from->geom->pntrec->rec.bottom_y);
    pointrecs.push_back(*newRectangle);
    free(newRectangle);
  }
  return pointrecs; // change name if wrapper function name changes
}
