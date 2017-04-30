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

/* ************************************************************************************* *\
    CSE 591 - Advances in Databases - Spring 2017 - Project - Data Storage Module
    -------------------------------------------------------------------------------

    File: data-storage.cpp

    This file contains function definitions which are declared in the data-storage.h file

    -- Ajay Kulkarni, Anuran Duttaroy, Dhanashree Adhikari, Nilam Bari, Omkar Kaptan --

\* ************************************************************************************* */

bool recoveryMode = false;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// HELPER FUNCTIONS
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool write_log(string command) {
  if(!recoveryMode){
	  timeval tv;
	  gettimeofday(&tv, 0);

	  fstream log_file;
	  log_file.open("command_log.txt",fstream::app);
	  if(log_file << &tv << ":" << command <<"NR:"<< std::endl) {
	    log_file.close();
	    return true;
	  }
	  else {
	    log_file.close();
	    return false;
	  }
   }
   else{
   	  timeval tv;
	  gettimeofday(&tv, 0);

	  fstream log_file;
	  log_file.open("command_log.txt",fstream::app);
	  if(log_file << &tv << ":" << command <<"YR:"<< std::endl) {
	    log_file.close();
	    return true;
	  }
	  else {
	    log_file.close();
	    return false;
	  }
   }
}

bool recoverData(){
  recoveryMode = true;
  ifstream log_file;
  string line;
  bool count=false;
  log_file.open("command_log.txt",fstream::app);
  while ( getline (log_file,line, ':') ){
      if(count && line != "" && line.length()>3 && line.substr(line.length()-2,2) =="NR"){
        string collection = line.substr(0,line.find_first_of(".",0));
        string op = line.substr(line.find_first_of(".",0)+1,line.find_first_of("(",0)-line.find_first_of(".",0)-1);
        string param = line.substr(line.find_first_of("(",0)+1, line.find_first_of(")",0)-line.find_first_of("(",0)-1);
        string next;
        vector<string> result;
        for (string::const_iterator it = param.begin(); it != param.end(); it++) {
        // If we've hit the terminal character
          if (*it == ',') {
            // If we have some characters accumulated
            if (!next.empty()) {
                // Add them to the result vector
                result.push_back(next);
                next.clear();
            }
            else{
                result.push_back("NA");
            }
          }
          else{
            // Accumulate the next character into the sequence
            next += *it;
          }
        }
        if (!next.empty()){
          result.push_back(next);
        }
        evaluate(collection, op, result);
        count = false;
      }
      else{
        count = true;
      }
    }
    log_file.close();
    recoveryMode = false;
}

bool evaluate(string collection,string op,  vector<string> param){
 if(collection == "point"){
   PointCollection *pc;
   if(param[0]=="NA" && param[1] == "NA"){
      cout << "pass";
      return 1;
   }
   else{
      pc = Catalog::Instance()->getPointCollectionByName(param[0], param[1]);
      if(pc == NULL){
         pc = new PointCollection(param[0], param[1], stoi(param[2]), vector<Point>());
         CatalogItem *catItem = new CatalogItem(param[0], param[1], stoi(param[2]), pc);
	 Catalog::Instance()->insert(catItem);
      }
   }
   if(op == "switchStorageStructure"){
     pc->switchStorageStructure(stoi(param[3]));
     cout<< "Switching point storage structure in Recovery Mode: "<<param[2]<<" to "<<param[3]<<"\n";
     return 1;
   }

   Point *p = new Point(stof(param[4]),stof(param[5]));
   p->setId(stoi(param[3]));

   if(op == "insertSortedY" || op =="insertSortedX" || op =="insert"){
     pc->insert(*p);
     cout<< "Inserting point in Recovery Mode: " <<p->getCoordinates()[0]<<" , "<<p->getCoordinates()[1] <<"\n";
     return 1;
   }
   if(op == "removeById"){
     pc->removeById(stoi(param[3]));
     cout<< "Deleting point in Recovery Mode: " <<param[3]<<"\n";
     return 1;
   }  
 }
 else if(collection == "rectangle"){
   RectangleCollection *rc;
   if(param[0]=="NA" && param[1] == "NA"){
      cout << "pass";
      return 1;
   }
   else{
      rc = Catalog::Instance()->getRectangleCollectionByName(param[0], param[1]);
      if(rc == NULL){
         rc = new RectangleCollection(param[0], param[1], stoi(param[2]), vector<Rectangle>());
         CatalogItem *catItem = new CatalogItem(param[0], param[1], stoi(param[2]), rc);
	 Catalog::Instance()->insert(catItem);
      }
   }
   
   if(op == "switchStorageStructure"){
     rc->switchStorageStructure(stoi(param[3]));
     cout<< "Switching point storage structure in Recovery Mode: "<<param[2]<<" to "<<param[3]<<"\n";
     return 1;
   }
   Rectangle *r = new Rectangle(stof(param[4]),stof(param[5]),stof(param[6]),stof(param[7]));
   r->setId(stoi(param[3]));

   if(op == "insertSortedY" || op =="insertSortedX" || op =="insert"){
     rc->insert(*r);
     cout<< "Inserting rectangle in Recovery Mode: " <<r->getCoordinates()[0]<<" , "<<r->getCoordinates()[1] <<r->getCoordinates()[2]<<" , "<<r->getCoordinates()[3] <<"\n";
     return 1;
   }
   if(op == "removeById"){
     rc->removeById(stoi(param[3]));
     cout<< "Deleting rectangle in Recovery Mode: " <<param[3]<<"\n";
     return 1;
   }
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

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// POINT COLLECTION
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

PointCollection::PointCollection(){
  recordId = 1;
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
  int id;
  //cout << pnt.getId();
  if(pnt.getId() == 0)
    id = recordId++;
  else
    id = pnt.getId();
  ds_point *newPoint = convertObjToStruct(pnt);
  newPoint->id = id;
  if(collectionStructure == COLLECTION_STRUCT_SORTEDX){
    insertSortedX(*newPoint);
    free(newPoint);
    return 1;
  }
  else if(collectionStructure == COLLECTION_STRUCT_SORTEDY){
    insertSortedY(*newPoint);
    free(newPoint);
    return 1;
  }
  else{
    points.push_back(*newPoint);
    std::string log_entry = "point.insert(" + this->name + "," + this->databaseName + "," + std::to_string(this->collectionStructure) + "," + std::to_string(newPoint->id) + "," + std::to_string(newPoint->x) + "," + std::to_string(newPoint->y) + ")";
    write_log(log_entry);
    free(newPoint);
    return 1;
  }
}


int PointCollection::insertSortedX(ds_point point) {
  auto it = std::lower_bound( points.begin(), points.end(), point, XCompare());
  points.insert( it, point);
  std::string log_entry = "point.insertSortedX(" + this->name + "," + this->databaseName + "," + std::to_string(this->collectionStructure) + "," + std::to_string(point.id) + "," + std::to_string(point.x) + "," + std::to_string(point.y) + ")";
  write_log(log_entry);
  return 1;
}

int PointCollection::insertSortedY(ds_point point) {
  auto it = std::lower_bound( points.begin(), points.end(), point, YCompare());
  points.insert( it, point);
  std::string log_entry = "point.insertSortedY(" + this->name + "," + this->databaseName + "," + std::to_string(this->collectionStructure) + "," + std::to_string(point.id) + "," + std::to_string(point.x) + "," + std::to_string(point.y) + ")";
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
      std::string log_entry = "point.removeById(" + this->name + "," + this->databaseName + "," + std::to_string(this->collectionStructure) + "," + std::to_string(it->id) + "," + std::to_string(it->x) + "," + std::to_string(it->y) + ")";
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
  std::string log_entry = "point.switchStorageStructure(" + this->name + "," + this->databaseName + "," + std::to_string(this->collectionStructure) +","+std::to_string(newStructure) +")";
  write_log(log_entry);
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
  recordId = 1;
  getNextAt = 0;
  collectionStructure = COLLECTION_STRUCT_UNSORTED;
}

RectangleCollection::RectangleCollection(string name, string databaseName, char collectionStructure, vector<Rectangle> recsToInsert)
:RectangleCollection() {
  this->name = name;
  this->databaseName = databaseName;
  this->collectionStructure = collectionStructure;
  recordId = 1;
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
  //newRec->id = recordId++;
  int id;
  if(rec.getId() == 0)
    id = recordId++;
  else
    id = rec.getId();
  newRec->id = id;
  if(collectionStructure == COLLECTION_STRUCT_UNSORTED){
    rectangles.push_back(*newRec);
    std::string log_entry = "rectangle.insert(" + this->name + "," + this->databaseName + "," + std::to_string(this->collectionStructure) + "," + std::to_string(newRec->id) + "," + std::to_string(newRec->top_x) + "," + std::to_string(newRec->top_y) + "," + std::to_string(newRec->bottom_x) + "," + std::to_string(newRec->bottom_y) + ")";
    write_log(log_entry);
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
  std::string log_entry = "rectangle.insertSortedX(" + this->name + "," + this->databaseName + "," + std::to_string(this->collectionStructure) + "," + std::to_string(rectangle.id) + "," + std::to_string(rectangle.top_x) + "," + std::to_string(rectangle.top_y) + "," + std::to_string(rectangle.bottom_x) + "," + std::to_string(rectangle.bottom_y) + ")";
  write_log(log_entry);
  return 1;
}

int RectangleCollection::insertSortedY(ds_rectangle rectangle) {
  auto it = std::lower_bound( rectangles.begin(), rectangles.end(), rectangle, YRectCompare());
  rectangles.insert( it, rectangle);
  std::string log_entry = "rectangle.insertSortedY(" + this->name + "," + this->databaseName + "," + std::to_string(this->collectionStructure) + "," + std::to_string(rectangle.id) + "," + std::to_string(rectangle.top_x) + "," + std::to_string(rectangle.top_y) + "," + std::to_string(rectangle.bottom_x) + "," + std::to_string(rectangle.bottom_y) + ")";
  write_log(log_entry);
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
      std::string log_entry = "rectangle.removeById(" + this->name + "," + this->databaseName + "," + std::to_string(this->collectionStructure) + "," + std::to_string(it->id) + "," + std::to_string(it->top_x) + "," + std::to_string(it->top_y) + "," + std::to_string(it->bottom_x) + "," + std::to_string(it->bottom_y) + ")";
      rectangles.erase(it);
      write_log(log_entry);
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
  
  std::string log_entry = "rectangle.switchStorageStructure(" + this->name + "," + this->databaseName + "," + std::to_string(this->collectionStructure) +","+std::to_string(newStructure) +")";
  write_log(log_entry);
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
  recordId = 1;
  getNextAt = 0;
  collectionStructure = COLLECTION_STRUCT_UNSORTED;
}

PointPointCollection::PointPointCollection(string name, string databaseName, char collectionStructure, vector<PointPoint> recsToInsert)
:PointPointCollection() {
  this->name = name;
  this->databaseName = databaseName;
  this->collectionStructure = collectionStructure;
  recordId = 1;
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
  std::string log_entry = "pointpoint.insert(" + this->name + "," + this->databaseName + "," + std::to_string(this->collectionStructure) + "," + std::to_string(newPointPoint->id) + "," + std::to_string(newPointPoint->point1.x) + "," + std::to_string(newPointPoint->point1.y) + "," + std::to_string(newPointPoint->point2.x) + "," + std::to_string(newPointPoint->point2.y) + ")";
  write_log(log_entry);
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
      std::string log_entry = "pointpoint.removeById(" + this->name + "," + this->databaseName + "," + std::to_string(this->collectionStructure) + "," + std::to_string(it->id) + "," + std::to_string(it->point1.x) + "," + std::to_string(it->point1.y) + "," + std::to_string(it->point2.x) + "," + std::to_string(it->point2.y) + ")";
      pointPoints.erase(it);
      write_log(log_entry);
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
  recordId = 1;
  getNextAt = 0;
  collectionStructure = COLLECTION_STRUCT_UNSORTED;
}

RectangleRectangleCollection::RectangleRectangleCollection(string name, string databaseName, char collectionStructure, vector<RectangleRectangle> recsToInsert)
:RectangleRectangleCollection() {
  this->name = name;
  this->databaseName = databaseName;
  this->collectionStructure = collectionStructure;
  recordId = 1;
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
  std::string log_entry = "rectanglerectangle.insert(" + this->name + "," + this->databaseName + "," + std::to_string(this->collectionStructure) + "," + std::to_string(newRecRec->id) + "," + std::to_string(newRecRec->rec1.top_x) + "," + std::to_string(newRecRec->rec1.top_y) + "," + std::to_string(newRecRec->rec1.bottom_x) + "," + std::to_string(newRecRec->rec1.bottom_y) + "," + std::to_string(newRecRec->rec2.top_x) + "," + std::to_string(newRecRec->rec2.top_y) + "," + std::to_string(newRecRec->rec2.bottom_x) + "," + std::to_string(newRecRec->rec2.bottom_y) + ")";
  write_log(log_entry);
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
      std::string log_entry = "rectanglerectangle.removeById(" + this->name + "," + this->databaseName + "," + std::to_string(this->collectionStructure) + "," + std::to_string(it->id) + "," + std::to_string(it->rec1.top_x) + "," + std::to_string(it->rec1.top_y) + "," + std::to_string(it->rec1.bottom_x) + "," + std::to_string(it->rec1.bottom_y) + "," + std::to_string(it->rec2.top_x) + "," + std::to_string(it->rec2.top_y) + "," + std::to_string(it->rec2.bottom_x) + "," + std::to_string(it->rec2.bottom_y) + ")";
      rectangleRectangles.erase(it);
      write_log(log_entry);
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
  recordId = 1;
  getNextAt = 0;
  collectionStructure = COLLECTION_STRUCT_UNSORTED;
}

PointRectangleCollection::PointRectangleCollection(string name, string databaseName, char collectionStructure, vector<PointRectangle> recsToInsert)
:PointRectangleCollection() {
  this->name = name;
  this->databaseName = databaseName;
  this->collectionStructure = collectionStructure;
  recordId = 1;
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
  std::string log_entry = "pointrectangle.insert(" + this->name + "," + this->databaseName + "," + std::to_string(this->collectionStructure) + "," + std::to_string(newPointRec->id) + "," + std::to_string(newPointRec->point.x) + "," + std::to_string(newPointRec->point.y) + "," + std::to_string(newPointRec->rec.top_x) + "," + std::to_string(newPointRec->rec.top_y) + "," + std::to_string(newPointRec->rec.bottom_x) + "," + std::to_string(newPointRec->rec.bottom_y) + ")";
  write_log(log_entry);
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
      std::string log_entry = "pointrectangle.insert(" + this->name + "," + this->databaseName + "," + std::to_string(this->collectionStructure) + "," + std::to_string(it->id) + "," + std::to_string(it->point.x) + "," + std::to_string(it->point.y) + "," + std::to_string(it->rec.top_x) + "," + std::to_string(it->rec.top_y) + "," + std::to_string(it->rec.bottom_x) + "," + std::to_string(it->rec.bottom_y) + ")";
      pointRectangles.erase(it);
      write_log(log_entry);
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
