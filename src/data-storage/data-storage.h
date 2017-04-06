#ifndef DATASTORAGE_H
#define DATASTORAGE_H

#include "ds_datatypes.h"
#include "ds_constants.h"
#include "../integration/geometry.h"

class GeometryCollection
{
	protected:
	int curr_id;
	record* head;
	short type;
	int count;

	void initGeometryCollection() {
		head == NULL;
		curr_id = 0;
	}
public:
	GeometryCollection();
	GeometryCollection(int type);
	~GeometryCollection();


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

class PointCollection : public GeometryCollection {
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

class RectangleCollection : public GeometryCollection {
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

class PointPointCollection : public GeometryCollection {
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

class PointRectangleCollection : public GeometryCollection {
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

class RectangleRectangleCollection : public GeometryCollection {
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
bool insertData(GeometryCollection *pointsRepo, Point pointToInsert);

//insert a single rectangle
bool insertData(GeometryCollection *rectanglesRepo, Rectangle rectangleToInsert);


//insert a single pointpoint
bool insertData(GeometryCollection *pointpointrepo, PointPoint pntpntToInsert);


//insert a single PointRectangle
bool insertData(GeometryCollection *recpointrepo, PointRectangle pntrectangleToInsert);

//insert a single RectangleRectangle
bool insertData(GeometryCollection *recrectanglesRepo, RectangleRectangle recrectangleToInsert);

//insert a GeometryCollection of items
bool insertDataBulk(GeometryCollection *repo, GeometryCollection geometryToInsert);


//delete item with id equals geomid
bool deleteData(GeometryCollection repo, int geomId);

#endif
