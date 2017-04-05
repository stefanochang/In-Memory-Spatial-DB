#include "data-storage.h"
#include <map>
using namespace std;
map<int, record *> getmap;

list::list()/*:head(NULL), type(type)*/ {
  //curr_id = 0;
  initList();
  count = 0;
}
list::list(int type){
  initList();
  //head = NULL;
  this->type = type;
  //curr_id = 0;

}
list::~list()	{
  record *tmp1,*tmp;
  if(head != NULL)
  {
    tmp1 = head;
    head = head->next;
    while(head != tmp1)
    {
      tmp = head->next;
      free(head);
      head = tmp;
      free(head);

    }
  }
}


record * list::initRecord(int id, geometry * geom, record * next, record * previous) {
  record * newRecord = (record *)malloc(sizeof(record));
  newRecord->id = id;
  newRecord->geom = geom;
  newRecord->next = next;
  newRecord->prev = previous;

  newRecord->isDeleted = false;
  newRecord->inDegree = 0;

  return newRecord;
}

void list::appendLast(geometry *geom)
{
  if(head == NULL)
  {
    head = initRecord(curr_id++, geom, head, head); /*(record *)malloc(sizeof(record));
    head->geom = geom;
    head->id = curr_id++;
    head->isDeleted = false;
    head->inDegree = 0;
    head->next = head;
    head->prev = head;*/
  }
  else
  {
    record* tmp_head = head->prev;
    tmp_head->next = initRecord(curr_id++, geom, head, tmp_head); /*(record *)malloc(sizeof(record));
    record* tmp = tmp_head->next;
    tmp->next = head;
    tmp->prev = tmp_head;
    tmp->id = curr_id++;
    tmp->isDeleted = false;
    tmp->inDegree = 0;
    tmp->geom = geom;*/
  }
  count++;
}

void list::appendFirst(geometry *geom)
{
  if(head == NULL)
  {
    head = initRecord(curr_id++, geom, head, head);
    // 	head = (record *)malloc(sizeof(record));
    // 	head->next = head;
    // 	head->prev = head;
    // 	head->id = curr_id++;
    // 	head->isDeleted = false;
    // 	head->inDegree = 0;
    // 	head->geom = geom;
  }
  else
  {
    record* tmp = initRecord(curr_id++, geom, head, head->prev);
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

void list::appendSortedX(geometry *geom)
{
  if(head == NULL)
  {
    head = initRecord(curr_id++, geom, head, head);
    // head = (record *)malloc(sizeof(record));
    // head->next = head;
    // head->prev = head;
    // head->id = curr_id++;
    // head->geom = geom;
    // head->isDeleted = false;
    // head->inDegree = 0;
  }
  else
  {
    // record* newNode = (record *)malloc(sizeof(record));
    // newNode->geom = geom;
    // newNode->id = curr_id++;
    // newNode->isDeleted = false;
    // newNode->inDegree = 0;
    record* newNode = initRecord(curr_id++, geom, NULL, NULL);
    record* current = head;
    record* previous = head->prev;
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

void list::appendSortedY(geometry *geom)
{
  if(head == NULL)
  {
    head = initRecord(curr_id++, geom, head, head);
    // head = (record *)malloc(sizeof(record));
    // head->next = head;
    // head->prev = head;
    // head->id = curr_id++;
    // head->geom = geom;
    // head->isDeleted = false;
    // head->inDegree = 0;
  }
  else
  {
    // record* newNode = (record *)malloc(sizeof(record));
    // newNode->geom = geom;
    // newNode->id = curr_id++;
    // newNode->isDeleted = false;
    // newNode->inDegree = 0;
    record* newNode = initRecord(curr_id++, geom, NULL, NULL);
    record* current = head;
    record* previous = head->prev;
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

int list::deleteByUUID(int id)
{
  if(head == NULL)
  {
    return -1;
  }
  else
  {
    record* current = head;
    record* previous = head->prev;
    record* temp = head;
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

Point* list::getPointByUUID(string table_name, int objectId)
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
        float x = head->geom->pnt->x;
        float y = head->geom->pnt->y;
        Point* pt = new Point(x, y);
        return pt;
      }
      head = head->next;
    }
    return NULL;
  }
}

Rectangle* list::getRectangleByUUID(string table_name, int objectId)
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
        float x1 = head->geom->rec->top_x;
        float y1 = head->geom->rec->top_y;
        float x2 = head->geom->rec->bottom_x;
        float y2 = head->geom->rec->bottom_y;
        Rectangle* rec = new Rectangle(x1, y1, x2, y2);
        return rec;
      }
      head = head->next;
    }
    return NULL;
  }
}

PointPoint* list::getPointPointByUUID(string table_name, int objectId)
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

PointRectangle* list::getPointRectangleByUUID(string table_name, int objectId)
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

RectangleRectangle* list::getRectangleRectangleByUUID(string table_name, int objectId)
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

record * list::getHead() {
  return head;
}

short list::getType() {
  return type;
}

int list::getSize()	{
  return count;
}

bool list::isEmpty() {
  return  head == NULL;
}


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

int PointCollection::insertBulk(PointCollection collection) {
  return insertDataBulk(*this, collection);
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

int RectangleCollection::insertBulk(RectangleCollection collection) {
  return insertDataBulk(*this, collection);
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

int PointPointCollection::insert(PointPoint pntpnt) {
  return insertData(*this,pntpnt);
}

int PointPointCollection::insertBulk(PointPointCollection collection) {
  return insertDataBulk(*this, collection);
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

int RectangleRectangleCollection::insert(RectangleRectangle recrec) {
  return insertData(*this,recrec);
}

int RectangleRectangleCollection::insertBulk(RectangleRectangleCollection collection) {
  return insertDataBulk(*this, collection);
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

int PointRectangleCollection::insert(PointRectangle pntrec) {
  return insertData(*this,pntrec);
}

int PointRectangleCollection::insertBulk(PointRectangleCollection collection) {
  return insertDataBulk(*this, collection);
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


int loadData(string dbName, string tableName, int geomtype, string filepath, int collectionStruct)
{
  FILE *fp;
  float x, y, x1, y1;
  geometry *g;
  point *pnt;
  rectangle *rct;
  PointCollection *pntcollection;
  RectangleCollection *rectanglecollection;
  //CatalogItem *catItem;
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
      g = (geometry *)malloc(sizeof(geometry));
      pnt = (point *)malloc(sizeof(point));
      pnt->x = x;
      pnt->y = y;
      g->pnt = pnt;
      pntcollection->appendLast(g);
    }
    //catItem = new CatalogItem(dbName, tableName, (PointCollection *)pntcollection);
  }
  else if(geomtype == TYPE_RECTANGLE)
  {
    rectanglecollection = new RectangleCollection();
    while(fscanf(fp, "%f,%f,%f,%f\n", &x, &y, &x1, &y1) == 4)
    {
      g = (geometry *)malloc(sizeof(geometry));
      rct = (rectangle *)malloc(sizeof(rectangle));
      rct->top_x = x;
      rct->top_y = y;
      rct->bottom_x = x1;
      rct->bottom_y = y1;
      g->rec = rct;
      rectanglecollection->appendLast(g);
    }
    //catItem = new CatalogItem(dbName, tableName, (RectangleCollection *)rectanglecollection);
  }
  else
  {
    return 0;
  }
  //Catalog.insert(catItem);

  return 1;
}

// Insert a single point
bool insertData(list pointsRepo, Point pointToInsert)
{
  geometry *g;
  point *pnt;
  g = (geometry *)malloc(sizeof(geometry));
  pnt = (point *)malloc(sizeof(point));
  g->pnt = pnt;
  g->pnt->x = pointToInsert.getCoordinates()[0];
  g->pnt->y = pointToInsert.getCoordinates()[1];
  pointsRepo.appendLast(g);
  return true;
}

//insert a single rectangle
bool insertData(list rectanglesRepo, Rectangle rectangleToInsert)
{
  geometry *g;
  rectangle *rec;
  g = (geometry *)malloc(sizeof(geometry));
  rec = (rectangle *)malloc(sizeof(rectangle));
  g->rec = rec;
  g->rec->top_x = rectangleToInsert.getCoordinates()[0];
  g->rec->top_y = rectangleToInsert.getCoordinates()[1];
  g->rec->bottom_x = rectangleToInsert.getCoordinates()[2];
  g->rec->bottom_y = rectangleToInsert.getCoordinates()[3];
  rectanglesRepo.appendLast(g);
  return true;
}


//insert a single pointpoint
bool insertData(list pointpointrepo, PointPoint pntpntToInsert)
{
  geometry *g;
  pointpoint *pntpnt;
  g = (geometry *)malloc(sizeof(geometry));
  pntpnt = (pointpoint *)malloc(sizeof(pointpoint));
  g->pntpnt = pntpnt;
  g->pntpnt->point1.x = pntpntToInsert.getCoordinates()[0];
  g->pntpnt->point1.y = pntpntToInsert.getCoordinates()[1];
  g->pntpnt->point2.x = pntpntToInsert.getCoordinates()[2];
  g->pntpnt->point2.y = pntpntToInsert.getCoordinates()[3];
  pointpointrepo.appendLast(g);
  return true;
}

//insert a single PointRectangle
bool insertData(list recpointrepo, PointRectangle pntrectangleToInsert)
{
  geometry *g;
  pointrectangle *pntrec;
  g = (geometry *)malloc(sizeof(geometry));
  pntrec = (pointrectangle *)malloc(sizeof(pointrectangle));
  g->pntrec = pntrec;
  g->pntrec->point1.x = pntrectangleToInsert.getCoordinates()[0];
  g->pntrec->point1.y = pntrectangleToInsert.getCoordinates()[1];
  g->pntrec->rec.top_x = pntrectangleToInsert.getCoordinates()[2];
  g->pntrec->rec.top_y = pntrectangleToInsert.getCoordinates()[3];
  g->pntrec->rec.bottom_x = pntrectangleToInsert.getCoordinates()[4];
  g->pntrec->rec.bottom_y = pntrectangleToInsert.getCoordinates()[5];
  recpointrepo.appendLast(g);
  return true;
}

//insert a single RectangleRectangle
bool insertData(list recrectanglesRepo, RectangleRectangle recrectangleToInsert)
{
  geometry *g;
  rectanglerectangle *recrec;
  g = (geometry *)malloc(sizeof(geometry));
  recrec = (rectanglerectangle *)malloc(sizeof(rectanglerectangle));
  g->recrec = recrec;
  g->recrec->rec1.top_x = recrectangleToInsert.getCoordinates()[0];
  g->recrec->rec1.top_y = recrectangleToInsert.getCoordinates()[1];
  g->recrec->rec1.bottom_x = recrectangleToInsert.getCoordinates()[2];
  g->recrec->rec1.bottom_y = recrectangleToInsert.getCoordinates()[3];
  g->recrec->rec2.top_x = recrectangleToInsert.getCoordinates()[4];
  g->recrec->rec2.top_y = recrectangleToInsert.getCoordinates()[5];
  g->recrec->rec2.bottom_x = recrectangleToInsert.getCoordinates()[6];
  g->recrec->rec2.bottom_y = recrectangleToInsert.getCoordinates()[7];
  recrectanglesRepo.appendLast(g);
  return true;
}

//insert a list of items
bool insertDataBulk(list repo, list geometryToInsert)
{
  record * geometryToInsertPointer = geometryToInsert.getHead();

  do{
    switch(repo.getType()) {
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
bool deleteData(list repo, int geomId){
  return repo.deleteByUUID(geomId);
}
