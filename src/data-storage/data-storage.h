#ifndef DATASTORAGE_H
#define DATASTORAGE_H

#include "ds_datatypes.h"
#include "ds_constants.h"
#include "../integration/geometry.h"

class GeometryCollection
{
	protected:
	int curr_id;
	ds_record* head;
	ds_record* from;
	short type;
	int count;
	int collectionStructure;
public:
	GeometryCollection();
	GeometryCollection(int type);
	~GeometryCollection();

	void initGeometryCollection();
	ds_record * initRecord(int id, ds_geometry * geom, ds_record * next, ds_record * previous);

	void appendLast(ds_geometry *geom);

	void appendFirst(ds_geometry *geom);

	void append(ds_geometry *geom);

	void appendSortedX(ds_geometry *geom);

	void appendSortedY(ds_geometry *geom);

	int deleteByUUID(int id);

	Point* getPointByUUID(string table_name, int objectId);

	Rectangle* getRectangleByUUID(string table_name, int objectId);

	PointPoint* getPointPointByUUID(string table_name, int objectId);

	PointRectangle* getPointRectangleByUUID(string table_name, int objectId);

	RectangleRectangle* getRectangleRectangleByUUID(string table_name, int objectId);

	ds_record * getHead();

	short getType();

	int getSize();

	bool isEmpty();
};

class PointCollection : public GeometryCollection {
    vector<Point> points;
    string name, databaseName;
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
