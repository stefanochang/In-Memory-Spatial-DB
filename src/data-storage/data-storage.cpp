#ifndef DATASTORAGE_H
#include "data-storage.h"
#endif
using namespace std;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// POINT COLLECTION
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

PointCollection::PointCollection(){
  recordId = 0;
  getNextAt = 0;

}

PointCollection::PointCollection(string name, string databaseName, int collectionStructure, vector<Point> pointsToInsert)
:PointCollection()
{
  this->name = name;
  this->databaseName = databaseName;
  recordId = 0;
  vector<Point>::iterator it;
  ds_point *newPoint;
  for(it=pointsToInsert.begin() ; it < pointsToInsert.end(); it++ ) {
    newPoint = (ds_point *)malloc(sizeof(ds_point));
    newPoint->id = recordId++;
    newPoint->x = it->getCoordinates()[0];
    newPoint->y = it->getCoordinates()[1];
    points.push_back(*newPoint);
    free(newPoint);
  }
}

Point PointCollection::getById(int findId) {
  Point *pnt;
  vector<ds_point>::iterator it;
  for(it=points.begin() ; it < points.end(); it++ )
  {
    if(it->id == findId)
    {
      pnt = new Point(it->x, it->y);
      pnt->setId(it->id);
      return *pnt;
    }
  }
}

vector<Point> PointCollection::getNext(int n, int transactionId) {
  vector<Point> pointsReturned;
  Point *newPoint;
  int rdcnt=n;
  while( (getNextAt < points.size()) && (rdcnt > 0) )
  {
    newPoint = new Point(points.at(getNextAt).x, points.at(getNextAt).y);
    newPoint->setId(points.at(getNextAt).id);
    pointsReturned.push_back(*newPoint);
    free(newPoint);
    getNextAt++;
    rdcnt--;
  }
  if(getNextAt >= points.size())
  {
    getNextAt = 0;
  }
  return pointsReturned; // change name if wrapper function name changes
}

int PointCollection::insert(Point pnt) {
  ds_point *newPoint = (ds_point *)malloc(sizeof(ds_point));
  newPoint->id = recordId;
  newPoint->x = pnt.getCoordinates()[0];
  newPoint->y = pnt.getCoordinates()[1];
  points.push_back(*newPoint);
  free(newPoint);
  return 1;
}

int PointCollection::insertBulk(PointCollection collection) {
  vector<Point> pointsToInsert = collection.getNext(collection.getSize());
  vector<Point>::iterator it;
  ds_point *newPoint;
  for(it=pointsToInsert.begin() ; it < pointsToInsert.end(); it++ ) {
    newPoint = (ds_point *)malloc(sizeof(ds_point));
    newPoint->id = recordId++;
    newPoint->x = it->getCoordinates()[0];
    newPoint->y = it->getCoordinates()[1];
    points.push_back(*newPoint);
    free(newPoint);
  }
}

int PointCollection::remove(Point point) {
  return removeById(point.getId());
}

int PointCollection::removeById(int deleteId) {
  vector<ds_point>::iterator it;
  for(it=points.begin() ; it < points.end(); it++ ) {
    if(it->id == deleteId)
    {
      points.erase(it);
      return 1;
    }
  }
  return 0;
}

bool PointCollection::isEmpty()
{
  return points.size()==0;
}

string PointCollection::getDBName()
{
  return databaseName;
}

string PointCollection::getTableName()
{
  return name;
}

int PointCollection::getSize()
{
  return points.size();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RECTANGLE COLLECTION
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


RectangleCollection::RectangleCollection(){
  recordId = 0;
  getNextAt = 0;

}

RectangleCollection::RectangleCollection(string name, string databaseName, int collectionStructure, vector<Rectangle> recsToInsert)
:RectangleCollection()
{
  this->name = name;
  this->databaseName = databaseName;
  recordId = 0;
  vector<Rectangle>::iterator it;
  ds_rectangle *newRec;
  for(it=recsToInsert.begin() ; it < recsToInsert.end(); it++ ) {
    newRec = (ds_rectangle *)malloc(sizeof(ds_rectangle));
    newRec->id = recordId++;
    newRec->top_x = it->getCoordinates()[0];
    newRec->top_y = it->getCoordinates()[1];
    newRec->bottom_x = it->getCoordinates()[2];
    newRec->bottom_y = it->getCoordinates()[3];
    rectangles.push_back(*newRec);
    free(newRec);
  }
}

Rectangle RectangleCollection::getById(int findId) {
  Rectangle *rec;
  vector<ds_rectangle>::iterator it;
  for(it=rectangles.begin() ; it < rectangles.end(); it++ )
  {
    if(it->id == findId)
    {
      rec = new Rectangle(it->top_x, it->top_y, it->bottom_x, it->bottom_y);
      rec->setId(it->id);
      return *rec;
    }
  }
}

vector<Rectangle> RectangleCollection::getNext(int n, int transactionId) {
  vector<Rectangle> recsReturned;
  Rectangle *newRec;
  int rdcnt=n;
  while( (getNextAt < rectangles.size()) && (rdcnt > 0) )
  {
    newRec = new Rectangle(rectangles.at(getNextAt).top_x, rectangles.at(getNextAt).top_y, rectangles.at(getNextAt).bottom_x, rectangles.at(getNextAt).bottom_y);
    newRec->setId(rectangles.at(getNextAt).id);
    recsReturned.push_back(*newRec);
    free(newRec);
    getNextAt++;
    rdcnt--;
  }
  if(getNextAt >= rectangles.size())
  {
    getNextAt = 0;
  }
  return recsReturned; // change name if wrapper function name changes
}

int RectangleCollection::insert(Rectangle rec) {
  ds_rectangle *newRec = (ds_rectangle *)malloc(sizeof(ds_rectangle));
  newRec->id = recordId++;
  newRec->top_x = rec.getCoordinates()[0];
  newRec->top_y = rec.getCoordinates()[1];
  newRec->bottom_x = rec.getCoordinates()[2];
  newRec->bottom_y = rec.getCoordinates()[3];
  rectangles.push_back(*newRec);
  free(newRec);
  return 1;
}

int RectangleCollection::insertBulk(RectangleCollection collection) {
  vector<Rectangle> recsToInsert = collection.getNext(collection.getSize());
  vector<Rectangle>::iterator it;
  ds_rectangle *newRec;
  for(it=recsToInsert.begin() ; it < recsToInsert.end(); it++ ) {
    newRec = (ds_rectangle *)malloc(sizeof(ds_rectangle));
    newRec->id = recordId++;
    newRec->top_x = it->getCoordinates()[0];
    newRec->top_y = it->getCoordinates()[1];
    newRec->bottom_x = it->getCoordinates()[2];
    newRec->bottom_y = it->getCoordinates()[3];
    rectangles.push_back(*newRec);
    free(newRec);
  }
  return 1;
}

int RectangleCollection::remove(Rectangle rec) {
  return removeById(rec.getId());
}

int RectangleCollection::removeById(int deleteId) {
  vector<ds_rectangle>::iterator it;
  for(it=rectangles.begin() ; it < rectangles.end(); it++ ) {
    if(it->id == deleteId)
    {
      rectangles.erase(it);
      return 1;
    }
  }
  return 0;
}

bool RectangleCollection::isEmpty()
{
  return rectangles.size()==0;
}

string RectangleCollection::getDBName()
{
  return databaseName;
}

string RectangleCollection::getTableName()
{
  return name;
}

int RectangleCollection::getSize()
{
  return rectangles.size();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// POINTPOINT COLLECTION
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
PointPointCollection::PointPointCollection()
: GeometryCollection(TYPE_POINTPOINT) {}

PointPointCollection::PointPointCollection(string name, string databaseName, int collectionStructure, vector<PointPoint> pointpoints)
: GeometryCollection(TYPE_POINTPOINT) {
  this->name = name;
  this->databaseName = databaseName;
  this->collectionStructure = collectionStructure;
}

PointPoint PointPointCollection::getById(int id) {
  PointPoint *pntpnt = getPointPointByUUID(this->name, id);
  return *pntpnt;
}

int PointPointCollection::insert(PointPoint pntpnt) {
  return insertData(this,pntpnt);
}

int PointPointCollection::insertBulk(PointPointCollection collection) {
  return insertDataBulk(this, collection);
}

vector<PointPoint> PointPointCollection::getNext(int n, int transactionId) {
  vector<PointPoint> points;
  PointPoint *newPoint;
  ds_record *from;
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
: GeometryCollection(TYPE_RECTANGLERECTANGLE) {}

RectangleRectangleCollection::RectangleRectangleCollection(string name, string databaseName, int collectionStructure, vector<RectangleRectangle> rectanglerectangle)
: GeometryCollection(TYPE_RECTANGLERECTANGLE) {
  this->name = name;
  this->databaseName = databaseName;
  this->collectionStructure = collectionStructure;
}

RectangleRectangle RectangleRectangleCollection::getById(int id) {
  RectangleRectangle *recrec = getRectangleRectangleByUUID(this->name, id);
  return *recrec;
}

int RectangleRectangleCollection::insert(RectangleRectangle recrec) {
  return insertData(this,recrec);
}

int RectangleRectangleCollection::insertBulk(RectangleRectangleCollection collection) {
  return insertDataBulk(this, collection);
}

vector<RectangleRectangle> RectangleRectangleCollection::getNext(int n, int transactionId) {
  vector<RectangleRectangle> recrecs;
  RectangleRectangle *newRectangle;
  ds_record *from;
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
: GeometryCollection(TYPE_POINTRECTANGLE) {}

PointRectangleCollection::PointRectangleCollection(string name, string databaseName, int collectionStructure, vector<PointRectangle> pointrectangles)
: GeometryCollection(TYPE_POINTRECTANGLE) {
  this->name = name;
  this->databaseName = databaseName;
  this->collectionStructure = collectionStructure;
}

PointRectangle PointRectangleCollection::getById(int id) {
  PointRectangle *pntrec = getPointRectangleByUUID(this->name, id);
  return *pntrec;
}

int PointRectangleCollection::insert(PointRectangle pntrec) {
  return insertData(this,pntrec);
}

int PointRectangleCollection::insertBulk(PointRectangleCollection collection) {
  return insertDataBulk(this, collection);
}

vector<PointRectangle> PointRectangleCollection::getNext(int n, int transactionId) {
  vector<PointRectangle> pointrecs;
  PointRectangle *newRectangle;
  ds_record *from;
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


int loadData(string dbName, string tableName, int geomtype, string filepath, int collectionStruct)
{
  FILE *fp;
  float x, y, x1, y1;
  ds_geometry *g;
  ds_point *pnt;
  ds_rectangle *rct;
  PointCollection *pntcollection;
  RectangleCollection *rectanglecollection;
  CatalogItem *catItem;
  fp = fopen(filepath.c_str(), "r");
  if(fp == NULL)
  {
    return 0;
  }
  if(geomtype == TYPE_POINT)
  {
    pntcollection = new PointCollection(dbName, tableName, collectionStruct, {});
    while(fscanf(fp, "%f,%f\n", &x, &y) == 2)
    {
      g = (ds_geometry *)malloc(sizeof(ds_geometry));
      pnt = (ds_point *)malloc(sizeof(ds_point));
      pnt->x = x;
      pnt->y = y;
      g->pnt = pnt;
      pntcollection->append(g);
    }
    catItem = new CatalogItem(dbName, tableName, collectionStruct, (PointCollection *)pntcollection);
  }
  else if(geomtype == TYPE_RECTANGLE)
  {
    rectanglecollection = new RectangleCollection(dbName, tableName, collectionStruct, {});
    while(fscanf(fp, "%f,%f,%f,%f\n", &x, &y, &x1, &y1) == 4)
    {
      g = (ds_geometry *)malloc(sizeof(ds_geometry));
      rct = (ds_rectangle *)malloc(sizeof(ds_rectangle));
      rct->top_x = x;
      rct->top_y = y;
      rct->bottom_x = x1;
      rct->bottom_y = y1;
      g->rec = rct;
      rectanglecollection->append(g);
    }
    catItem = new CatalogItem(dbName, tableName, collectionStruct, (RectangleCollection *)rectanglecollection);
  }
  else
  {
    return -1;
  }
  Catalog::Instance()->insert(catItem);
  // instance.insert(catItem);
  return 1;
}

// Insert a single ds_point
bool insertData(GeometryCollection *pointsRepo, Point pointToInsert)
{
  ds_geometry *g;
  ds_point *pnt;
  g = (ds_geometry *)malloc(sizeof(ds_geometry));
  pnt = (ds_point *)malloc(sizeof(ds_point));
  g->pnt = pnt;
  g->pnt->x = pointToInsert.getCoordinates()[0];
  g->pnt->y = pointToInsert.getCoordinates()[1];
  pointsRepo->append(g);
  return true;
}

//insert a single rectangle
bool insertData(GeometryCollection *rectanglesRepo, Rectangle rectangleToInsert)
{
  ds_geometry *g;
  ds_rectangle *rec;
  g = (ds_geometry *)malloc(sizeof(ds_geometry));
  rec = (ds_rectangle *)malloc(sizeof(ds_rectangle));
  g->rec = rec;
  g->rec->top_x = rectangleToInsert.getCoordinates()[0];
  g->rec->top_y = rectangleToInsert.getCoordinates()[1];
  g->rec->bottom_x = rectangleToInsert.getCoordinates()[2];
  g->rec->bottom_y = rectangleToInsert.getCoordinates()[3];
  rectanglesRepo->append(g);
  return true;
}


//insert a single pointpoint
bool insertData(GeometryCollection *pointpointrepo, PointPoint pntpntToInsert)
{
  ds_geometry *g;
  ds_pointpoint *pntpnt;
  g = (ds_geometry *)malloc(sizeof(ds_geometry));
  pntpnt = (ds_pointpoint *)malloc(sizeof(ds_pointpoint));
  g->pntpnt = pntpnt;
  g->pntpnt->point1.x = pntpntToInsert.getCoordinates()[0];
  g->pntpnt->point1.y = pntpntToInsert.getCoordinates()[1];
  g->pntpnt->point2.x = pntpntToInsert.getCoordinates()[2];
  g->pntpnt->point2.y = pntpntToInsert.getCoordinates()[3];
  pointpointrepo->append(g);
  return true;
}

//insert a single PointRectangle
bool insertData(GeometryCollection *recpointrepo, PointRectangle pntrectangleToInsert)
{
  ds_geometry *g;
  ds_pointrectangle *pntrec;
  g = (ds_geometry *)malloc(sizeof(ds_geometry));
  pntrec = (ds_pointrectangle *)malloc(sizeof(ds_pointrectangle));
  g->pntrec = pntrec;
  g->pntrec->point1.x = pntrectangleToInsert.getCoordinates()[0];
  g->pntrec->point1.y = pntrectangleToInsert.getCoordinates()[1];
  g->pntrec->rec.top_x = pntrectangleToInsert.getCoordinates()[2];
  g->pntrec->rec.top_y = pntrectangleToInsert.getCoordinates()[3];
  g->pntrec->rec.bottom_x = pntrectangleToInsert.getCoordinates()[4];
  g->pntrec->rec.bottom_y = pntrectangleToInsert.getCoordinates()[5];
  recpointrepo->append(g);
  return true;
}

//insert a single RectangleRectangle
bool insertData(GeometryCollection *recrectanglesRepo, RectangleRectangle recrectangleToInsert)
{
  ds_geometry *g;
  ds_rectanglerectangle *recrec;
  g = (ds_geometry *)malloc(sizeof(ds_geometry));
  recrec = (ds_rectanglerectangle *)malloc(sizeof(ds_rectanglerectangle));
  g->recrec = recrec;
  g->recrec->rec1.top_x = recrectangleToInsert.getCoordinates()[0];
  g->recrec->rec1.top_y = recrectangleToInsert.getCoordinates()[1];
  g->recrec->rec1.bottom_x = recrectangleToInsert.getCoordinates()[2];
  g->recrec->rec1.bottom_y = recrectangleToInsert.getCoordinates()[3];
  g->recrec->rec2.top_x = recrectangleToInsert.getCoordinates()[4];
  g->recrec->rec2.top_y = recrectangleToInsert.getCoordinates()[5];
  g->recrec->rec2.bottom_x = recrectangleToInsert.getCoordinates()[6];
  g->recrec->rec2.bottom_y = recrectangleToInsert.getCoordinates()[7];
  recrectanglesRepo->append(g);
  return true;
}

//insert a GeometryCollection of items
bool insertDataBulk(GeometryCollection *repo, GeometryCollection geometryToInsert)
{
  ds_record * geometryToInsertPointer = geometryToInsert.getHead();

  do{
    switch(repo->getType()) {
      case TYPE_POINT: insertData(repo, *(new Point(geometryToInsertPointer->geom->pnt->x, geometryToInsertPointer->geom->pnt->y))); break;
      case TYPE_RECTANGLE: insertData(repo, *(new Rectangle(geometryToInsertPointer->geom->rec->top_x, geometryToInsertPointer->geom->rec->top_y,geometryToInsertPointer->geom->rec->bottom_x, geometryToInsertPointer->geom->rec->bottom_y))); break;
      case TYPE_RECTANGLERECTANGLE: insertData(repo, *(new RectangleRectangle(geometryToInsertPointer->geom->recrec->rec1.top_x, geometryToInsertPointer->geom->recrec->rec1.top_y,geometryToInsertPointer->geom->recrec->rec1.bottom_x, geometryToInsertPointer->geom->recrec->rec1.bottom_y, geometryToInsertPointer->geom->recrec->rec2.top_x, geometryToInsertPointer->geom->recrec->rec2.top_y,geometryToInsertPointer->geom->recrec->rec2.bottom_x, geometryToInsertPointer->geom->recrec->rec2.bottom_y))); break;
      case TYPE_POINTPOINT: insertData(repo, *(new PointPoint(geometryToInsertPointer->geom->pntpnt->point1.x, geometryToInsertPointer->geom->pntpnt->point1.y, geometryToInsertPointer->geom->pntpnt->point2.x, geometryToInsertPointer->geom->pntpnt->point2.y))); break;
      case TYPE_POINTRECTANGLE: insertData(repo, *(new PointRectangle(geometryToInsertPointer->geom->pntrec->point1.x, geometryToInsertPointer->geom->pntrec->point1.y, geometryToInsertPointer->geom->pntrec->rec.top_x, geometryToInsertPointer->geom->pntrec->rec.top_y,geometryToInsertPointer->geom->pntrec->rec.bottom_x, geometryToInsertPointer->geom->pntrec->rec.bottom_y))); break;
      default: return false;
    }

    geometryToInsertPointer = geometryToInsertPointer->next;
  }while(geometryToInsertPointer != geometryToInsert.getHead());
  return true;
}

//delete item with id equals geomid
bool deleteData(GeometryCollection repo, int geomId){
  return repo.deleteByUUID(geomId);
}
*/
