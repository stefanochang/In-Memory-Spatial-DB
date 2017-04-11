#ifndef DATASTORAGE_H
#define DATASTORAGE_H

#include "ds_datatypes.h"
#include "ds_constants.h"
#include "../integration/geometry.h"

class PointCollection{
    vector<ds_point> points;
    string name, databaseName;
		int recordId;
		int getNextAt;

    Point convertStructToObj(ds_point);
    ds_point * convertObjToStruct(Point);
    int insertBulk(vector<Point>);
  public:
    PointCollection();
    PointCollection(string, string, int, vector<Point>);
    Point getById(int);
    vector<Point> getNext(int n=1, int transaction_id=1);
    int insert(Point);
    int insertBulk(PointCollection);
		bool isEmpty();
		int getSize();
    int remove(Point);
    int removeById(int);  // size of PointCollection
    string getDBName();
    string getTableName();
};

class RectangleCollection {
    vector<ds_rectangle> rectangles;
    string name, databaseName;
		int recordId;
		int getNextAt;

    Rectangle convertStructToObj(ds_rectangle);
    ds_rectangle * convertObjToStruct(Rectangle);
    int insertBulk(vector<Rectangle>);
  public:
    RectangleCollection();
    RectangleCollection(string, string, int, vector<Rectangle>);
    Rectangle getById(int);
    vector<Rectangle> getNext(int n=1, int transaction_id=1);
		bool isEmpty();
		int getSize();
    int insert(Rectangle);
    int insertBulk(RectangleCollection);
    int remove(Rectangle);
    int removeById(int);
    string getDBName();
    string getTableName();
};

class PointPointCollection {
    vector<ds_pointpoint> pointPoints;
    string name, databaseName;
    int recordId;
		int getNextAt;

    PointPoint convertStructToObj(ds_pointpoint);
    ds_pointpoint * convertObjToStruct(PointPoint);
    int insertBulk(vector<PointPoint>);
  public:
    PointPointCollection();
    PointPointCollection(string, string, int, vector<PointPoint>);
    PointPoint getById(int);
    vector<PointPoint> getNext(int n=1, int transaction_id=1);
    int insert(PointPoint);
    int insertBulk(PointPointCollection);
		bool isEmpty();
    int getSize();
    int remove(PointPoint);
    int removeById(int);
    string getDBName();
    string getTableName();
};
/*
class PointRectangleCollection : public GeometryCollection {
    vector<ds_pointrectangle> pointRectangles;
    string name, databaseName;
  public:
    PointRectangleCollection();
    PointRectangleCollection(string, string, int, vector<PointRectangle>);
    PointRectangle getById(int);
    vector<PointRectangle> getNext(int n=1, int transaction_id=1);
    int insert(PointRectangle);
    int insertBulk(PointRectangleCollection);
		bool isEmpty();
    string getDBName();
    string getTableName();
};

class RectangleRectangleCollection : public GeometryCollection {
    vector<ds_rectanglerectangle> rectangleRectangles;
    string name, databaseName;
  public:
    RectangleRectangleCollection();
    RectangleRectangleCollection(string, string, int, vector<RectangleRectangle>);
    RectangleRectangle getById(int);
    vector<RectangleRectangle> getNext(int n=1,int transaction_id=1);
    int insert(RectangleRectangle);
    int insertBulk(RectangleRectangleCollection);
		bool isEmpty();
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
*/
#endif
