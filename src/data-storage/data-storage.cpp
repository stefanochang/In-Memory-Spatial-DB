#ifndef DATASTORAGE_H
#include "data-storage.h"
#endif
#ifndef CATALOG_H
#include "../integration/catalog.h"
#endif
#include <algorithm>
using namespace std;
#include <iostream>
#include <fstream>
#include <sys/time.h>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// HELPER FUNCTIONS
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool write_log(string command) {
  timeval tv;
  gettimeofday(&tv, 0);

  fstream log_file;
  log_file.open("command_log.txt",fstream::app);
  if(log_file << &tv << " : " << command << std::endl) {
    log_file.close();
    return true;
  }
  else {
    log_file.close();
    return false;
  }
}

// Function to return time in Microseconds precesion

// double dtime ()
// {
//     struct timeval tv;
//     gettimeofday (&tv, NULL);
//     Microseconds precesion
//     return ((tv.tv_sec + ((double) tv.tv_usec / 1000000.0)));
// }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// POINT COLLECTION
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class XCompare
{
public:
  bool operator()(const ds_point &first, const ds_point &second) const
  {
    return first.x < second.x;
  }
};

class YCompare
{
public:
  bool operator()(const ds_point &first, const ds_point &second) const
  {
    return first.y < second.y;
  }
};

class XRectCompare
{
public:
  bool operator()(const ds_rectangle &first, const ds_rectangle &second) const
  {
    return (first.top_x + first.bottom_x) < (second.top_x + second.bottom_x);
  }
};

class YRectCompare
{
public:
  bool operator()(const ds_rectangle &first, const ds_rectangle &second) const
  {
    return (first.top_y + first.bottom_y) < (second.top_y + second.bottom_y);
  }
};

PointCollection::PointCollection(){
  recordId = 0;
  getNextAt = 0;
  getNextAt = 0;
  name = "";
  databaseName = "";
  collectionStructure = COLLECTION_STRUCT_UNSORTED;
}

PointCollection::PointCollection(string name, string databaseName, char collectionStructure, vector<Point> pointsToInsert)
:PointCollection() {
  this->name = name;
  this->databaseName = databaseName;
  this->collectionStructure = collectionStructure;
  recordId = 0;
  vector<Point>::iterator it;
  for(it=pointsToInsert.begin() ; it < pointsToInsert.end(); it++ ) {
    insert(*it);
  }
}

Point PointCollection::convertStructToObj(ds_point pointStruct) {
  float x = pointStruct.x;
  float y = pointStruct.y;
  Point *point = new Point(x, y);
  point->setId(pointStruct.id);
  return *point;
}

ds_point * PointCollection::convertObjToStruct(Point point) {
  vector<float> coordinates = point.getCoordinates();
  ds_point *newPoint = (ds_point *)malloc(sizeof(ds_point));

  newPoint->x = coordinates[0];
  newPoint->y = coordinates[1];
  return newPoint;
}

Point PointCollection::getById(int findId) {
  //Point *pnt;
  vector<ds_point>::iterator it;
  for(it=points.begin() ; it < points.end(); it++ )
  {
    if(it->id == findId)
    {
      return convertStructToObj(*it);
    }
  }
}

vector<Point> PointCollection::getNext(int n, int transactionId) {
  vector<Point> pointsReturned;
  //Point *newPoint;
  int rdcnt=n;
  while( (getNextAt < points.size()) && (rdcnt > 0) )
  {
    //newPoint = new Point(points.at(getNextAt).x, points.at(getNextAt).y);
    //newPoint->setId(points.at(getNextAt).id);
    Point newPoint = convertStructToObj(points.at(getNextAt));
    pointsReturned.push_back(newPoint);
    getNextAt++;
    rdcnt--;
  }
  if(getNextAt >= points.size())
  {
    getNextAt = 0;
  }
  return pointsReturned; // change name if wrapper function name changes
}

char PointCollection::getCollectionStructure() {
  return collectionStructure;
}

int PointCollection::insert(Point pnt) {
  ds_point *newPoint = convertObjToStruct(pnt);
  newPoint->id = recordId++;
  if(collectionStructure == COLLECTION_STRUCT_UNSORTED){
    points.push_back(*newPoint);
    std::string log_entry = "PointCollection::insert(" + this->name + ", " + this->databaseName + ", " + std::to_string(this->collectionStructure) + ", " + std::to_string(newPoint->id) + ", " + std::to_string(newPoint->x) + ", " + std::to_string(newPoint->y) + ")";
    write_log(log_entry);
    free(newPoint);
    return 1;
  }
  else if(collectionStructure == COLLECTION_STRUCT_SORTEDX){
    insertSortedX(*newPoint);
    free(newPoint);
    return 1;
  }
  else if(collectionStructure == COLLECTION_STRUCT_SORTEDY){
    insertSortedY(*newPoint);
    free(newPoint);
    return 1;
  }
}


int PointCollection::insertSortedX(ds_point point) {
  auto it = std::lower_bound( points.begin(), points.end(), point, XCompare());
  points.insert( it, point);
  std::string log_entry = "PointCollection::insertSortedX(" + this->name + ", " + this->databaseName + ", " + std::to_string(this->collectionStructure) + ", " + std::to_string(point.id) + ", " + std::to_string(point.x) + ", " + std::to_string(point.y) + ")";
  write_log(log_entry);
  return 1;
}

int PointCollection::insertSortedY(ds_point point) {
  auto it = std::lower_bound( points.begin(), points.end(), point, YCompare());
  points.insert( it, point);
  std::string log_entry = "PointCollection::insertSortedY(" + this->name + ", " + this->databaseName + ", " + std::to_string(this->collectionStructure) + ", " + std::to_string(point.id) + ", " + std::to_string(point.x) + ", " + std::to_string(point.y) + ")";
  write_log(log_entry);
  return 1;

}




int PointCollection::insertBulk(PointCollection collection) {
  vector<Point> pointsToInsert = collection.getNext(collection.getSize());
  return insertBulk(pointsToInsert);
}

int PointCollection::insertBulk(vector<Point> ptsToInsert) {
  vector<Point>::iterator it;
  for(it=ptsToInsert.begin() ; it < ptsToInsert.end(); it++ ) {
    insert(*it);
  }

  return 1;
}

int PointCollection::remove(Point point) {
  return removeById(point.getId());
}

int PointCollection::removeById(int deleteId) {
  vector<ds_point>::iterator it;
  for(it=points.begin() ; it < points.end(); it++ ) {
    if(it->id == deleteId)
    {
      std::string log_entry = "PointCollection::removeById(" + this->name + ", " + this->databaseName + ", " + std::to_string(this->collectionStructure) + ", " + std::to_string(it->id) + ", " + std::to_string(it->x) + ", " + std::to_string(it->y) + ")";
      points.erase(it);
      write_log(log_entry);
      return 1;
    }
  }
  return 0;
}

bool PointCollection::isEmpty() {
  return points.size()==0;
}

string PointCollection::getDBName() {
  return databaseName;
}

string PointCollection::getTableName() {
  return name;
}

int PointCollection::getSize() {
  return points.size();
}

int PointCollection::switchStorageStructure(char newStructure)
{
  collectionStructure = newStructure;
  if(newStructure == COLLECTION_STRUCT_UNSORTED)
  {
    return 1;
  }
  if(newStructure == COLLECTION_STRUCT_SORTEDX)
  {
    sort(points.begin(), points.end(),XCompare());
    return 1;
  }
  sort(points.begin(), points.end(),YCompare());
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RECTANGLE COLLECTION
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

RectangleCollection::RectangleCollection(){
  recordId = 0;
  getNextAt = 0;
  collectionStructure = COLLECTION_STRUCT_UNSORTED;
}

RectangleCollection::RectangleCollection(string name, string databaseName, char collectionStructure, vector<Rectangle> recsToInsert)
:RectangleCollection() {
  this->name = name;
  this->databaseName = databaseName;
  this->collectionStructure = collectionStructure;
  recordId = 0;
  insertBulk(recsToInsert);
}

Rectangle RectangleCollection::convertStructToObj(ds_rectangle recStruct) {
  float top_x = recStruct.top_x;
  float top_y = recStruct.top_y;
  float bottom_x = recStruct.bottom_x;
  float bottom_y = recStruct.bottom_y;
  Rectangle *rectangle = new Rectangle(top_x, top_y, bottom_x, bottom_y);
  rectangle->setId(recStruct.id);
  return *rectangle;
}

ds_rectangle * RectangleCollection::convertObjToStruct(Rectangle rectangle) {
  ds_rectangle *newRectangle = (ds_rectangle *)malloc(sizeof(ds_rectangle));

  vector<float> coordinates = rectangle.getCoordinates();

  newRectangle->top_x = coordinates[0];
  newRectangle->top_y = coordinates[1];
  newRectangle->bottom_x = coordinates[2];
  newRectangle->bottom_y = coordinates[3];

  return newRectangle;
}

Rectangle RectangleCollection::getById(int findId) {
  vector<ds_rectangle>::iterator it;
  for(it=rectangles.begin() ; it < rectangles.end(); it++ )
  {
    if(it->id == findId)
    {
      return convertStructToObj(*it);
    }
  }
}

vector<Rectangle> RectangleCollection::getNext(int n, int transactionId) {
  vector<Rectangle> recsReturned;
  //Rectangle *newRec;
  int rdcnt=n;
  while( (getNextAt < rectangles.size()) && (rdcnt > 0) )
  {
    Rectangle newRectangle = convertStructToObj(rectangles.at(getNextAt));
    recsReturned.push_back(newRectangle);
    getNextAt++;
    rdcnt--;
  }
  if(getNextAt >= rectangles.size())
  {
    getNextAt = 0;
  }
  return recsReturned; // change name if wrapper function name changes
}

char RectangleCollection::getCollectionStructure() {
  return collectionStructure;
}

int RectangleCollection::insert(Rectangle rec) {
  ds_rectangle *newRec = convertObjToStruct(rec);
  newRec->id = recordId++;
  if(collectionStructure == COLLECTION_STRUCT_UNSORTED){
    rectangles.push_back(*newRec);
    free(newRec);
    return 1;
  }
  else if(collectionStructure == COLLECTION_STRUCT_SORTEDX){
    insertSortedX(*newRec);
    return 1;
  }
  else if(collectionStructure == COLLECTION_STRUCT_SORTEDY){
    insertSortedY(*newRec);
    return 1;
  }
}


int RectangleCollection::insertSortedX(ds_rectangle rectangle) {
  auto it = std::lower_bound( rectangles.begin(), rectangles.end(), rectangle, XRectCompare());
  rectangles.insert( it, rectangle);
  return 1;
}

int RectangleCollection::insertSortedY(ds_rectangle rectangle) {
  auto it = std::lower_bound( rectangles.begin(), rectangles.end(), rectangle, YRectCompare());
  rectangles.insert( it, rectangle);
  return 1;

}

int RectangleCollection::insertBulk(RectangleCollection collection) {
  vector<Rectangle> recsToInsert = collection.getNext(collection.getSize());
  return insertBulk(recsToInsert);
}

int RectangleCollection::insertBulk(vector<Rectangle> recsToInsert) {
  vector<Rectangle>::iterator it;
  for(it=recsToInsert.begin() ; it < recsToInsert.end(); it++ ) {
    insert(*it);
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

bool RectangleCollection::isEmpty() {
  return rectangles.size()==0;
}

string RectangleCollection::getDBName() {
  return databaseName;
}

string RectangleCollection::getTableName() {
  return name;
}

int RectangleCollection::getSize() {
  return rectangles.size();
}

int RectangleCollection::switchStorageStructure(char newStructure)
{
  collectionStructure = newStructure;
  if(newStructure == COLLECTION_STRUCT_UNSORTED)
  {
    return 1;
  }
  if(newStructure == COLLECTION_STRUCT_SORTEDX)
  {
    sort(rectangles.begin(), rectangles.end(),XRectCompare());
    return 1;
  }
  sort(rectangles.begin(), rectangles.end(),YRectCompare());
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// POINTPOINT COLLECTION
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

PointPointCollection::PointPointCollection(){
  recordId = 0;
  getNextAt = 0;
  collectionStructure = COLLECTION_STRUCT_UNSORTED;
}

PointPointCollection::PointPointCollection(string name, string databaseName, char collectionStructure, vector<PointPoint> recsToInsert)
:PointPointCollection() {
  this->name = name;
  this->databaseName = databaseName;
  this->collectionStructure = collectionStructure;
  recordId = 0;
  insertBulk(recsToInsert);
}

PointPoint PointPointCollection::convertStructToObj(ds_pointpoint recStruct) {
  float x1 = recStruct.point1.x;
  float y1 = recStruct.point1.y;
  float x2 = recStruct.point2.x;
  float y2 = recStruct.point2.y;
  PointPoint *pointPoint = new PointPoint(x1, y1, x2, y2);
  pointPoint->setId(recStruct.id);
  return *pointPoint;
}

ds_pointpoint * PointPointCollection::convertObjToStruct(PointPoint pointPoint) {
  ds_pointpoint *newPointPoint = (ds_pointpoint *)malloc(sizeof(ds_pointpoint));

  vector<float> coordinates = pointPoint.getCoordinates();

  newPointPoint->point1.x = coordinates[0];
  newPointPoint->point1.y = coordinates[1];
  newPointPoint->point2.x = coordinates[2];
  newPointPoint->point2.y = coordinates[3];

  return newPointPoint;
}

PointPoint PointPointCollection::getById(int findId) {
  vector<ds_pointpoint>::iterator it;
  for(it=pointPoints.begin() ; it < pointPoints.end(); it++ )
  {
    if(it->id == findId)
    {
      return convertStructToObj(*it);
    }
  }
}

vector<PointPoint> PointPointCollection::getNext(int n, int transactionId) {
  vector<PointPoint> recsReturned;
  int rdcnt=n;
  while( (getNextAt < pointPoints.size()) && (rdcnt > 0) )
  {
    PointPoint newPointPoint = convertStructToObj(pointPoints.at(getNextAt));
    recsReturned.push_back(newPointPoint);
    getNextAt++;
    rdcnt--;
  }
  if(getNextAt >= pointPoints.size())
  {
    getNextAt = 0;
  }
  return recsReturned; // change name if wrapper function name changes
}

char PointPointCollection::getCollectionStructure() {
  return collectionStructure;
}

int PointPointCollection::insert(PointPoint rec) {
  ds_pointpoint *newPointPoint = convertObjToStruct(rec);
  newPointPoint->id = recordId++;
  pointPoints.push_back(*newPointPoint);
  free(newPointPoint);
  return 1;
}

int PointPointCollection::insertBulk(PointPointCollection collection) {
  vector<PointPoint> recsToInsert = collection.getNext(collection.getSize());
  return insertBulk(recsToInsert);
}

int PointPointCollection::insertBulk(vector<PointPoint> recsToInsert) {
  vector<PointPoint>::iterator it;
  for(it=recsToInsert.begin() ; it < recsToInsert.end(); it++ ) {
    insert(*it);
  }

  return 1;
}

int PointPointCollection::remove(PointPoint rec) {
  return removeById(rec.getId());
}

int PointPointCollection::removeById(int deleteId) {
  vector<ds_pointpoint>::iterator it;
  for(it=pointPoints.begin() ; it < pointPoints.end(); it++ ) {
    if(it->id == deleteId)
    {
      pointPoints.erase(it);
      return 1;
    }
  }
  return 0;
}

bool PointPointCollection::isEmpty() {
  return pointPoints.size()==0;
}

string PointPointCollection::getDBName() {
  return databaseName;
}

string PointPointCollection::getTableName() {
  return name;
}

int PointPointCollection::getSize() {
  return pointPoints.size();
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RECTANGLERECTANGLE COLLECTION
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

RectangleRectangleCollection::RectangleRectangleCollection(){
  recordId = 0;
  getNextAt = 0;
  collectionStructure = COLLECTION_STRUCT_UNSORTED;
}

RectangleRectangleCollection::RectangleRectangleCollection(string name, string databaseName, char collectionStructure, vector<RectangleRectangle> recsToInsert)
:RectangleRectangleCollection() {
  this->name = name;
  this->databaseName = databaseName;
  this->collectionStructure = collectionStructure;
  recordId = 0;
  insertBulk(recsToInsert);
}

RectangleRectangle RectangleRectangleCollection::convertStructToObj(ds_rectanglerectangle recRecStruct) {
  float x11 = recRecStruct.rec1.top_x;
  float y11 = recRecStruct.rec1.top_y;
  float x12 = recRecStruct.rec1.bottom_x;
  float y12 = recRecStruct.rec1.bottom_y;

  float x21 = recRecStruct.rec2.top_x;
  float y21 = recRecStruct.rec2.top_y;
  float x22 = recRecStruct.rec2.bottom_x;
  float y22 = recRecStruct.rec2.bottom_y;

  RectangleRectangle *rectangleRectangle = new RectangleRectangle(x11, y11, x12, y12, x21, y21, x22, y22);
  rectangleRectangle->setId(recRecStruct.id);
  return *rectangleRectangle;
}

ds_rectanglerectangle * RectangleRectangleCollection::convertObjToStruct(RectangleRectangle rectangleRectangle) {
  ds_rectanglerectangle *newRectangleRectangle = (ds_rectanglerectangle *)malloc(sizeof(ds_rectanglerectangle));

  vector<float> coordinates = rectangleRectangle.getCoordinates();

  newRectangleRectangle->rec1.top_x = coordinates[0];
  newRectangleRectangle->rec1.top_y = coordinates[1];
  newRectangleRectangle->rec1.bottom_x = coordinates[2];
  newRectangleRectangle->rec1.bottom_y = coordinates[3];

  newRectangleRectangle->rec2.top_x = coordinates[4];
  newRectangleRectangle->rec2.top_y = coordinates[5];
  newRectangleRectangle->rec2.bottom_x = coordinates[6];
  newRectangleRectangle->rec2.bottom_y = coordinates[7];

  return newRectangleRectangle;
}

RectangleRectangle RectangleRectangleCollection::getById(int findId) {
  vector<ds_rectanglerectangle>::iterator it;
  for(it=rectangleRectangles.begin() ; it < rectangleRectangles.end(); it++ )
  {
    if(it->id == findId)
    {
      return convertStructToObj(*it);
    }
  }
}

vector<RectangleRectangle> RectangleRectangleCollection::getNext(int n, int transactionId) {
  vector<RectangleRectangle> recsReturned;
  int rdcnt=n;
  while( (getNextAt < rectangleRectangles.size()) && (rdcnt > 0) )
  {
    RectangleRectangle newRectangleRectangle = convertStructToObj(rectangleRectangles.at(getNextAt));
    recsReturned.push_back(newRectangleRectangle);
    getNextAt++;
    rdcnt--;
  }
  if(getNextAt >= rectangleRectangles.size())
  {
    getNextAt = 0;
  }
  return recsReturned; // change name if wrapper function name changes
}

char RectangleRectangleCollection::getCollectionStructure() {
  return collectionStructure;
}

int RectangleRectangleCollection::insert(RectangleRectangle rec) {
  ds_rectanglerectangle *newRecRec = convertObjToStruct(rec);
  newRecRec->id = recordId++;
  rectangleRectangles.push_back(*newRecRec);
  free(newRecRec);
  return 1;
}

int RectangleRectangleCollection::insertBulk(RectangleRectangleCollection collection) {
  vector<RectangleRectangle> recsToInsert = collection.getNext(collection.getSize());
  return insertBulk(recsToInsert);
}

int RectangleRectangleCollection::insertBulk(vector<RectangleRectangle> recsToInsert) {
  vector<RectangleRectangle>::iterator it;
  for(it=recsToInsert.begin() ; it < recsToInsert.end(); it++ ) {
    insert(*it);
  }

  return 1;
}

int RectangleRectangleCollection::remove(RectangleRectangle rec) {
  return removeById(rec.getId());
}

int RectangleRectangleCollection::removeById(int deleteId) {
  vector<ds_rectanglerectangle>::iterator it;
  for(it=rectangleRectangles.begin() ; it < rectangleRectangles.end(); it++ ) {
    if(it->id == deleteId)
    {
      rectangleRectangles.erase(it);
      return 1;
    }
  }
  return 0;
}

bool RectangleRectangleCollection::isEmpty() {
  return rectangleRectangles.size()==0;
}

string RectangleRectangleCollection::getDBName() {
  return databaseName;
}

string RectangleRectangleCollection::getTableName() {
  return name;
}

int RectangleRectangleCollection::getSize() {
  return rectangleRectangles.size();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// POINTRECTANGLE COLLECTION
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PointRectangleCollection::PointRectangleCollection(){
  recordId = 0;
  getNextAt = 0;
  collectionStructure = COLLECTION_STRUCT_UNSORTED;
}

PointRectangleCollection::PointRectangleCollection(string name, string databaseName, char collectionStructure, vector<PointRectangle> recsToInsert)
:PointRectangleCollection() {
  this->name = name;
  this->databaseName = databaseName;
  this->collectionStructure = collectionStructure;
  recordId = 0;
  insertBulk(recsToInsert);
}

PointRectangle PointRectangleCollection::convertStructToObj(ds_pointrectangle pointRecStruct) {
  float x1 = pointRecStruct.point.x;
  float y1 = pointRecStruct.point.y;
  float x2 = pointRecStruct.rec.top_x;
  float y2 = pointRecStruct.rec.top_y;
  float x3 = pointRecStruct.rec.bottom_x;
  float y3 = pointRecStruct.rec.bottom_y;
  PointRectangle *pointRectangle = new PointRectangle(x1, y1, x2, y2, x3, y3);
  pointRectangle->setId(pointRecStruct.id);
  return *pointRectangle;
}

ds_pointrectangle * PointRectangleCollection::convertObjToStruct(PointRectangle pointRectangle) {
  ds_pointrectangle *newPointRectangle = (ds_pointrectangle *)malloc(sizeof(ds_pointrectangle));

  vector<float> coordinates = pointRectangle.getCoordinates();

  newPointRectangle->point.x = coordinates[0];
  newPointRectangle->point.y = coordinates[1];
  newPointRectangle->rec.top_x = coordinates[2];
  newPointRectangle->rec.top_y = coordinates[3];
  newPointRectangle->rec.bottom_x = coordinates[4];
  newPointRectangle->rec.bottom_y = coordinates[5];

  return newPointRectangle;
}

PointRectangle PointRectangleCollection::getById(int findId) {
  vector<ds_pointrectangle>::iterator it;
  for(it=pointRectangles.begin() ; it < pointRectangles.end(); it++ )
  {
    if(it->id == findId)
    {
      return convertStructToObj(*it);
    }
  }
}

vector<PointRectangle> PointRectangleCollection::getNext(int n, int transactionId) {
  vector<PointRectangle> recsReturned;
  int rdcnt=n;
  while( (getNextAt < pointRectangles.size()) && (rdcnt > 0) )
  {
    PointRectangle newPointRectangle = convertStructToObj(pointRectangles.at(getNextAt));
    recsReturned.push_back(newPointRectangle);
    getNextAt++;
    rdcnt--;
  }
  if(getNextAt >= pointRectangles.size())
  {
    getNextAt = 0;
  }
  return recsReturned; // change name if wrapper function name changes
}

char PointRectangleCollection::getCollectionStructure() {
  return collectionStructure;
}

int PointRectangleCollection::insert(PointRectangle rec) {
  ds_pointrectangle *newPointRec = convertObjToStruct(rec);
  newPointRec->id = recordId++;
  pointRectangles.push_back(*newPointRec);
  free(newPointRec);
  return 1;
}

int PointRectangleCollection::insertBulk(PointRectangleCollection collection) {
  vector<PointRectangle> recsToInsert = collection.getNext(collection.getSize());
  return insertBulk(recsToInsert);
}

int PointRectangleCollection::insertBulk(vector<PointRectangle> recsToInsert) {
  vector<PointRectangle>::iterator it;
  for(it=recsToInsert.begin() ; it < recsToInsert.end(); it++ ) {
    insert(*it);
  }

  return 1;
}

int PointRectangleCollection::remove(PointRectangle rec) {
  return removeById(rec.getId());
}

int PointRectangleCollection::removeById(int deleteId) {
  vector<ds_pointrectangle>::iterator it;
  for(it=pointRectangles.begin() ; it < pointRectangles.end(); it++ ) {
    if(it->id == deleteId)
    {
      pointRectangles.erase(it);
      return 1;
    }
  }
  return 0;
}

bool PointRectangleCollection::isEmpty() {
  return pointRectangles.size()==0;
}

string PointRectangleCollection::getDBName() {
  return databaseName;
}

string PointRectangleCollection::getTableName() {
  return name;
}

int PointRectangleCollection::getSize() {
  return pointRectangles.size();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// FUNCTIONS OUTSIDE COLLECTIONS
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int loadData(string dbName, string tableName, int geomtype, string filepath, char collectionStruct) {
  FILE *fp;
  CatalogItem *catItem;
  fp = fopen(filepath.c_str(), "r");
  if(fp == NULL)
  {
    return 0;
  }
  if(geomtype == TYPE_POINT) {
    float x, y;
    PointCollection * collection = new PointCollection(dbName, tableName, collectionStruct, vector<Point>());
    while(fscanf(fp, "%f,%f\n", &x, &y) == 2)
    {
      Point newPoint = Point(x, y);
      collection->insert(newPoint);
    }
    catItem = new CatalogItem(dbName, tableName, collectionStruct, collection);
  } else if(geomtype == TYPE_RECTANGLE) {
    float x1, y1, x2, y2;
    RectangleCollection * collection = new RectangleCollection(dbName, tableName, collectionStruct, vector<Rectangle>());
    while(fscanf(fp, "%f,%f,%f,%f\n", &x1, &y1, &x2, &y2) == 4)
    {
      Rectangle rectangle = Rectangle(x1, y1, x2, y2);
      collection->insert(rectangle);
    }
    catItem = new CatalogItem(dbName, tableName, collectionStruct, collection);
  } else if(geomtype == TYPE_POINTPOINT) {
    float x1, y1, x2, y2;
    PointPointCollection * collection = new PointPointCollection(dbName, tableName, collectionStruct, vector<PointPoint>());
    while(fscanf(fp, "%f,%f,%f,%f\n", &x1, &y1, &x2, &y2) == 4)
    {
      PointPoint pointPoint = PointPoint(x1, y1, x2, y2);
      collection->insert(pointPoint);
    }
    catItem = new CatalogItem(dbName, tableName, collectionStruct, collection);
  } else if(geomtype == TYPE_POINTRECTANGLE) {
    float x1, y1, x2, y2, x3, y3;
    PointRectangleCollection  * collection = new PointRectangleCollection(dbName, tableName, collectionStruct, vector<PointRectangle>());
    while(fscanf(fp, "%f,%f,%f,%f,%f,%f\n", &x1, &y1, &x2, &y2, &x3, &y3) == 6)
    {
      PointRectangle pointRectangle = PointRectangle(x1, y1, x2, y2, x3, y3);
      collection->insert(pointRectangle);
    }
    catItem = new CatalogItem(dbName, tableName, collectionStruct, collection);
  } else if(geomtype == TYPE_RECTANGLERECTANGLE) {
    float x1, y1, x2, y2, x3, y3, x4, y4;
    RectangleRectangleCollection * collection = new RectangleRectangleCollection(dbName, tableName, collectionStruct, vector<RectangleRectangle>());
    while(fscanf(fp, "%f,%f,%f,%f,%f,%f,%f,%f\n", &x1, &y1, &x2, &y2, &x3, &y3, &x4, &y4) == 8)
    {
      RectangleRectangle rectangleRectangle = RectangleRectangle(x1, y1, x2, y2, x3, y3, x4, y4);
      collection->insert(rectangleRectangle);
    }
    catItem = new CatalogItem(dbName, tableName, collectionStruct, collection);
  } else {
    return -1;
  }
  Catalog::Instance()->insert(catItem);
  return 1;
}
