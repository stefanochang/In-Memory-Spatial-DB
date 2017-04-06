#ifndef DATASTORAGE_H
#define DATASTORAGE_H

#include "ds_datatypes.h"
#include "ds_constants.h"
#include "../integration/geometry.h"

class list
{
	protected:
	int curr_id;
	record* head;
	short type;
	int count;

	void initList() {
		head == NULL;
		curr_id = 0;
	}
public:
	list();
	list(int type);
	~list();


	record * initRecord(int id, geometry * geom, record * next, record * previous);

	void appendLast(geometry *geom);

	void appendFirst(geometry *geom);

	void appendSortedX(geometry *geom);

	void appendSortedY(geometry *geom);

	int deleteByUUID(int id);

	Point* getPointByUUID(string table_name, int objectId);

	Rectangle* getRectangleByUUID(string table_name, int objectId);

	PointPoint* getPointPointByUUID(string table_name, int objectId);

	PointRectangle* getPointRectangleByUUID(string table_name, int objectId);

	RectangleRectangle* getRectangleRectangleByUUID(string table_name, int objectId);

	record * getHead();

	short getType();

	int getSize();

	bool isEmpty();
};

class PointCollection : public list {
    vector<Point> points;
    string name, databaseName;
    int collectionStructure;
  public:
    PointCollection();
    PointCollection(string, string, int, vector<Point>);
    Point getById(int);
    vector<Point> getNext(int n=1, int transaction_id=1);
    int insert(Point);
    int insertBulk(PointCollection);
    int remove(Point);
    int removeById(int);  // size of PointCollection
    string getDBName();
    string getTableName();
};

class RectangleCollection : public list {
    vector<Rectangle> rectangles;
    string name, databaseName;
    int collectionStructure;
  public:
    RectangleCollection();
    RectangleCollection(string, string, int, vector<Rectangle>);
    Rectangle getById(int);
    vector<Rectangle> getNext(int n=1, int transaction_id=1);
    int insert(Rectangle);
    int insertBulk(RectangleCollection);
    int remove(Rectangle);
    int removeById(int);
    string getDBName();
    string getTableName();
};

class PointPointCollection : public list {
    vector<PointPoint> pointPoints;
    string name, databaseName;
    int collectionStructure;
  public:
    PointPointCollection();
    PointPointCollection(string, string, int, vector<PointPoint>);
    PointPoint getById(int);
    vector<PointPoint> getNext(int n=1, int transaction_id=1);
    int insert(PointPoint);
    int insertBulk(PointPointCollection);
    string getDBName();
    string getTableName();
};

class PointRectangleCollection : public list {
    vector<PointRectangle> pointRectangles;
    string name, databaseName;
    int collectionStructure;
  public:
    PointRectangleCollection();
    PointRectangleCollection(string, string, int, vector<PointRectangle>);
    PointRectangle getById(int);
    vector<PointRectangle> getNext(int n=1, int transaction_id=1);
    int insert(PointRectangle);
    int insertBulk(PointRectangleCollection);
    string getDBName();
    string getTableName();
};

class RectangleRectangleCollection : public list {
    vector<RectangleRectangle> rectangleRectangles;
    string name, databaseName;
    int collectionStructure;
  public:
    RectangleRectangleCollection();
    RectangleRectangleCollection(string, string, int, vector<RectangleRectangle>);
    RectangleRectangle getById(int);
    vector<RectangleRectangle> getNext(int n=1,int transaction_id=1);
    int insert(RectangleRectangle);
    int insertBulk(RectangleRectangleCollection);
    string getDBName();
    string getTableName();
};

//Initial data load supported for Points and Rectangles
int loadData(string dbName, string tableName, int geomtype, string filepath, int collectionStruct);

// Insert a single point
bool insertData(list *pointsRepo, Point pointToInsert);

//insert a single rectangle
bool insertData(list *rectanglesRepo, Rectangle rectangleToInsert);


//insert a single pointpoint
bool insertData(list *pointpointrepo, PointPoint pntpntToInsert);


//insert a single PointRectangle
bool insertData(list *recpointrepo, PointRectangle pntrectangleToInsert);

//insert a single RectangleRectangle
bool insertData(list *recrectanglesRepo, RectangleRectangle recrectangleToInsert);

//insert a list of items
bool insertDataBulk(list *repo, list geometryToInsert);


//delete item with id equals geomid
bool deleteData(list repo, int geomId);

#endif
