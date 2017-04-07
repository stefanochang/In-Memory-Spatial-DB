#ifndef DATASTORAGE_H
#include "data-storage.h"
#endif
#ifndef CATALOG_H
#include "../integration/catalog.h"
#endif
#include <map>
using namespace std;
map<int, ds_record *> getmap;

GeometryCollection::GeometryCollection() {
  initGeometryCollection();
}
GeometryCollection::GeometryCollection(int type){
  initGeometryCollection();
  this->type = type;

}
GeometryCollection::~GeometryCollection()	{
  /*ds_record *tmp1,*tmp;
  tmp = head;
  if(head != NULL)
  {
    int numItems = getSize();
    for(int i=0;i<numItems; i++)
    {
      tmp = head->next;
      free(head);
      head = tmp;
    }
  }*/
}

void GeometryCollection::initGeometryCollection(){
  from = head = NULL;
  curr_id = count = 0;
  type = 0;
  collectionStructure = 10;
}
ds_record * GeometryCollection::initRecord(int id, ds_geometry * geom, ds_record * next, ds_record * previous) {
  ds_record * newRecord = (ds_record *)malloc(sizeof(ds_record));
  newRecord->id = id;
  newRecord->geom = geom;
  newRecord->next = next;
  newRecord->prev = previous;

  newRecord->isDeleted = false;
  newRecord->inDegree = 0;

  return newRecord;
}

void GeometryCollection::appendLast(ds_geometry *geom)
{
  if(head == NULL)
  {
    head = initRecord(curr_id++, geom, head, head);
    head->next = head;
    head->prev = head;
  }
  else
  {
    ds_record *tmp_head,*previous;
    tmp_head = initRecord(curr_id++, geom, head, head);
    previous = head->prev;
    tmp_head->next = head;
    tmp_head->prev = head->prev;
    previous->next = tmp_head;
    head->prev = tmp_head;
  }
  count++;
}

void GeometryCollection::appendFirst(ds_geometry *geom)
{
  if(head == NULL)
  {
    head = initRecord(curr_id++, geom, head, head);
    // 	head->next = head;
    // 	head->prev = head;
    // 	head = (record *)malloc(sizeof(record));
    // 	head->id = curr_id++;
    // 	head->isDeleted = false;
    // 	head->inDegree = 0;
    // 	head->geom = geom;
  }
  else
  {
    ds_record* tmp = initRecord(curr_id++, geom, head, head->prev);
    head->prev = tmp;
    head = tmp;
    // record *tmp_head = (record *)malloc(sizeof(record));
    // tmp_head->prev = head->prev;
    // head->prev = tmp_head;
    // tmp_head->next = head;
    // tmp_head->id = curr_id++;
    // tmp_head->isDeleted = false;
    // tmp_head->inDegree = 0;
    // tmp_head->geom = geom;
    // head = tmp_head;
  }
  count++;
}

void  GeometryCollection::append(ds_geometry *geom) {
  switch(collectionStructure) {
    case COLLECTION_STRUCT_UNSORTED:
      appendLast(geom);
      break;
    case COLLECTION_STRUCT_SORTEDX:
      appendSortedX(geom);
      break;
    case COLLECTION_STRUCT_SORTEDY:
      appendSortedY(geom);
      break;
    default:
      appendLast(geom);
  }
}

void GeometryCollection::appendSortedX(ds_geometry *geom)
{
  if(head == NULL)
  {
    head = initRecord(curr_id++, geom, head, head);
    head->next = head;
    head->prev = head;
  }
  else
  {
    ds_record* newNode = initRecord(curr_id++, geom, NULL, NULL);
    ds_record* current = head;
    ds_record* previous = head->prev;
    while(current->next != head)
    {
      if(current->geom->pnt->x > newNode->geom->pnt->x)
      {
        newNode->next = current;
        previous->next = newNode;
        newNode->prev = previous;
        current->prev = newNode;
        break;
      }
      previous = current;
      current = current->next;
    }
    if(current->next == head)
    {
      appendLast(geom);
      free(newNode);
    }
  }
  count++;
}

void GeometryCollection::appendSortedY(ds_geometry *geom)
{
  if(head == NULL)
  {
    head = initRecord(curr_id++, geom, head, head);
    head->next = head;
    head->prev = head;
  }
  else
  {
    ds_record* newNode = initRecord(curr_id++, geom, NULL, NULL);
    ds_record* current = head;
    ds_record* previous = head->prev;
    while(current->next != head)
    {
      if(current->geom->pnt->y > newNode->geom->pnt->y)
      {
        newNode->next = current;
        previous->next = newNode;
        newNode->prev = previous;
        current->prev = newNode;
        break;
      }
      previous = current;
      current = current->next;
    }
    if(current->next == head)
    {
      appendLast(geom);
      free(newNode);
    }
  }
  count++;
}

int GeometryCollection::deleteByUUID(int id)
{
  if(head == NULL)
  {
    return -1;
  }
  else
  {
    ds_record* current = head;
    ds_record* previous = head->prev;
    ds_record* temp = head;
    while(current->next != head)
    {
      if(current->id == id)
      {
        if(current->inDegree <= 0)
        {
          temp = current;
          previous->next = current->next;
          current = current->next;
          current->prev = previous;
          free(temp);
          count--;
          return 1;
        }
        else
        {
          current->isDeleted = true;
          count--;
        }
      }
      previous = current;
      current = current->next;
    }
    if(current->next == head)
    {
      if(current->id == id)
      {
        if(current->inDegree <= 0)
        {
          temp = current;
          previous->next = current->next;
          current = current->next;
          current->prev = previous;
          free(temp);
          count--;
          return 1;
        }
        else
        {
          current->isDeleted = true;
          count--;
        }
      }
    }
  }
  return -1;
}

Point* GeometryCollection::getPointByUUID(string table_name, int objectId)
{
  //place-holder for call to metadata table to get head
  //place-holder for assigning received head to the head variable
  if(head == NULL)
  {
    return NULL;
  }
  else
  {
    ds_record *temp = head;
    do
    {
      if(temp->id == objectId && temp->isDeleted == false)
      {
        float x = temp->geom->pnt->x;
        float y = temp->geom->pnt->y;
        Point* pt = new Point(x, y);
        return pt;
      }
      temp = temp->next;
    }while(temp != head);
    return NULL;
  }
}

Rectangle* GeometryCollection::getRectangleByUUID(string table_name, int objectId)
{
  //place-holder for call to metadata table to get head
  //place-holder for assigning received head to the head variable
  if(head == NULL)
  {
    return NULL;
  }
  else
  {
    ds_record *temp=head;
    do
    {
      if(temp->id == objectId && temp->isDeleted == false)
      {
        float x1 = temp->geom->rec->top_x;
        float y1 = temp->geom->rec->top_y;
        float x2 = temp->geom->rec->bottom_x;
        float y2 = temp->geom->rec->bottom_y;
        Rectangle* rec = new Rectangle(x1, y1, x2, y2);
        return rec;
      }
      temp = temp->next;
    }while(temp != head);
    return NULL;
  }
}

PointPoint* GeometryCollection::getPointPointByUUID(string table_name, int objectId)
{
  //place-holder for call to metadata table to get head
  //place-holder for assigning received head to the head variable
  if(head == NULL)
  {
    return NULL;
  }
  else
  {
    while(head != NULL)
    {
      if(head->id == objectId && head->isDeleted == false)
      {
        float x1 = head->geom->pntpnt->point1.x;
        float y1 = head->geom->pntpnt->point1.y;
        float x2 = head->geom->pntpnt->point2.x;
        float y2 = head->geom->pntpnt->point2.y;
        PointPoint* pt = new PointPoint(x1, y1, x2, y2);
        return pt;
      }
      head = head->next;
    }
    return NULL;
  }
}

PointRectangle* GeometryCollection::getPointRectangleByUUID(string table_name, int objectId)
{
  //place-holder for call to metadata table to get head
  //place-holder for assigning received head to the head variable
  if(head == NULL)
  {
    return NULL;
  }
  else
  {
    while(head != NULL)
    {
      if(head->id == objectId && head->isDeleted == false)
      {
        float x1 = head->geom->pntrec->point1.x;
        float y1 = head->geom->pntrec->point1.y;
        float x2 = head->geom->pntrec->rec.top_x;
        float y2 = head->geom->pntrec->rec.top_y;
        float x3 = head->geom->pntrec->rec.bottom_x;
        float y3 = head->geom->pntrec->rec.bottom_y;
        PointRectangle* ptrec = new PointRectangle(x1, y1, x2, y2, x3, y3);
        return ptrec;
      }
      head = head->next;
    }
    return NULL;
  }
}

RectangleRectangle* GeometryCollection::getRectangleRectangleByUUID(string table_name, int objectId)
{
  //place-holder for call to metadata table to get head
  //place-holder for assigning received head to the head variable
  if(head == NULL)
  {
    return NULL;
  }
  else
  {
    while(head != NULL)
    {
      if(head->id == objectId && head->isDeleted == false)
      {
        float x1 = head->geom->recrec->rec1.top_x;
        float y1 = head->geom->recrec->rec1.top_y;
        float x2 = head->geom->recrec->rec1.bottom_x;
        float y2 = head->geom->recrec->rec1.bottom_y;
        float x3 = head->geom->recrec->rec2.top_x;
        float y3 = head->geom->recrec->rec2.top_y;
        float x4 = head->geom->recrec->rec2.bottom_x;
        float y4 = head->geom->recrec->rec2.bottom_y;
        RectangleRectangle* recrec = new RectangleRectangle(x1, y1, x2, y2, x3, y3, x4, y4);
        return recrec;
      }
      head = head->next;
    }
    return NULL;
  }
}

ds_record * GeometryCollection::getHead() {
  return head;
}

short GeometryCollection::getType() {
  return type;
}

int GeometryCollection::getSize()	{
  return count;
}

bool GeometryCollection::isEmpty() {
  return  head == NULL;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// POINT COLLECTION
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PointCollection::PointCollection()
: GeometryCollection(TYPE_POINT) {}

PointCollection::PointCollection(string name, string databaseName, int collectionStructure, vector<Point> points)
: GeometryCollection(TYPE_POINT) {
  this->name = name;
  this->databaseName = databaseName;
  this->collectionStructure = collectionStructure;

  vector<Point>::iterator it;
  for(it=points.begin() ; it < points.end(); it++ ) {
    insertData(this,*it);
  }
}

Point PointCollection::getById(int id) {
  Point *pnt;
  pnt = getPointByUUID(this->name, id);
  return *pnt;
}

vector<Point> PointCollection::getNext(int n, int transactionId) {
  vector<Point> points;
  Point *newPoint;
  int rdcnt=n;
  if(from == NULL)
  {
    from = head;
  }
  do
  {
    if(from->isDeleted)
      continue;
    newPoint = new Point(from->geom->pnt->x, from->geom->pnt->y);
    points.push_back(*newPoint);
    free(newPoint);
    from = from->next;
    rdcnt--;
  }while(from != head && rdcnt > 0);
  return points; // change name if wrapper function name changes
}

int PointCollection::insert(Point pnt) {
  return insertData(this,pnt);
}

int PointCollection::insertBulk(PointCollection collection) {
  return insertDataBulk(this, collection);
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
: GeometryCollection(TYPE_RECTANGLE) {}

RectangleCollection::RectangleCollection(string name, string databaseName, int collectionStructure, vector<Rectangle> rectangles)
: GeometryCollection(TYPE_RECTANGLE) {
  this->name = name;
  this->databaseName = databaseName;
  this->collectionStructure = collectionStructure;
  vector<Rectangle>::iterator it;
  for(it=rectangles.begin() ; it < rectangles.end(); it++ ) {
    insertData(this,*it);
  }
}

Rectangle RectangleCollection::getById(int id) {
  Rectangle *rec = getRectangleByUUID(this->name, id);
  return *rec;
}

vector<Rectangle> RectangleCollection::getNext(int n, int transactionId) {
  vector<Rectangle> rectangles;
  Rectangle *newRectangle;
  int rdcnt=n;
  if(from == NULL)
  {
    from = head;
  }
  do
  {
    if(from->isDeleted)
     continue;
    newRectangle = new Rectangle(from->geom->rec->top_x, from->geom->rec->top_y,from->geom->rec->bottom_x, from->geom->rec->bottom_y);
    rectangles.push_back(*newRectangle);
    free(newRectangle);
    from = from->next;
  }while(from != head && rdcnt > 0);
  return rectangles; // change name if wrapper function name changes
}

// insertData wrapper required to pass string table name and geometry
int RectangleCollection::insert(Rectangle rec) {
  return insertData(this,rec);
}

int RectangleCollection::insertBulk(RectangleCollection collection) {
  return insertDataBulk(this, collection);
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
    pntcollection = new PointCollection();
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
    rectanglecollection = new RectangleCollection();
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
