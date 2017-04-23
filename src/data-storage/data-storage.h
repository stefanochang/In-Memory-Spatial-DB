#ifndef DATASTORAGE_H
#define DATASTORAGE_H

#include "ds_datatypes.h"
#include "ds_constants.h"
#include "../integration/geometry.h"

bool recoverData();
bool evaluate(string collection,string op,  vector<string>);

class PointCollection{
    vector<ds_point> points;
    string name, databaseName;
		int recordId;
		int getNextAt;
    char collectionStructure;
    Point convertStructToObj(ds_point);
    ds_point * convertObjToStruct(Point);
    int insertBulk(vector<Point>);
  public:
    PointCollection();
    PointCollection(string, string, char, vector<Point>);
    Point getById(int);
    vector<Point> getNext(int n=1, int transaction_id=1);
    char getCollectionStructure();
    int insert(Point);
    int insertSortedX(ds_point);
    int insertSortedY(ds_point);
    int insertBulk(PointCollection);
		bool isEmpty();
		int getSize();
    int remove(Point);
    int removeById(int);  // size of PointCollection
    string getDBName();
    string getTableName();
    int switchStorageStructure(char);
};

class RectangleCollection {
    vector<ds_rectangle> rectangles;
    string name, databaseName;
		int recordId;
		int getNextAt;
    char collectionStructure;
    Rectangle convertStructToObj(ds_rectangle);
    ds_rectangle * convertObjToStruct(Rectangle);
    int insertBulk(vector<Rectangle>);
  public:
    RectangleCollection();
    RectangleCollection(string, string, char, vector<Rectangle>);
    Rectangle getById(int);
    vector<Rectangle> getNext(int n=1, int transaction_id=1);
    char getCollectionStructure();
		bool isEmpty();
		int getSize();
    int insert(Rectangle);
    int insertSortedX(ds_rectangle);
    int insertSortedY(ds_rectangle);
    int insertBulk(RectangleCollection);
    int remove(Rectangle);
    int removeById(int);
    string getDBName();
    string getTableName();
    int switchStorageStructure(char);
};

class PointPointCollection {
    vector<ds_pointpoint> pointPoints;
    string name, databaseName;
    int recordId;
		int getNextAt;
    char collectionStructure;
    PointPoint convertStructToObj(ds_pointpoint);
    ds_pointpoint * convertObjToStruct(PointPoint);
    int insertBulk(vector<PointPoint>);
  public:
    PointPointCollection();
    PointPointCollection(string, string, char, vector<PointPoint>);
    PointPoint getById(int);
    vector<PointPoint> getNext(int n=1, int transaction_id=1);
    char getCollectionStructure();
    int insert(PointPoint);
    int insertBulk(PointPointCollection);
		bool isEmpty();
    int getSize();
    int remove(PointPoint);
    int removeById(int);
    string getDBName();
    string getTableName();
};

class PointRectangleCollection {
    vector<ds_pointrectangle> pointRectangles;
    string name, databaseName;
    int recordId;
		int getNextAt;
    char collectionStructure;
    PointRectangle convertStructToObj(ds_pointrectangle);
    ds_pointrectangle * convertObjToStruct(PointRectangle);
    int insertBulk(vector<PointRectangle>);
  public:
    PointRectangleCollection();
    PointRectangleCollection(string, string, char, vector<PointRectangle>);
    PointRectangle getById(int);
    vector<PointRectangle> getNext(int n=1, int transaction_id=1);
    char getCollectionStructure();
    int insert(PointRectangle);
    int insertBulk(PointRectangleCollection);
		bool isEmpty();
    int getSize();
    int remove(PointRectangle);
    int removeById(int);
    string getDBName();
    string getTableName();
};

class RectangleRectangleCollection {
    vector<ds_rectanglerectangle> rectangleRectangles;
    string name, databaseName;
    int recordId;
		int getNextAt;
    char collectionStructure;
    RectangleRectangle convertStructToObj(ds_rectanglerectangle);
    ds_rectanglerectangle * convertObjToStruct(RectangleRectangle);
    int insertBulk(vector<RectangleRectangle>);
  public:
    RectangleRectangleCollection();
    RectangleRectangleCollection(string, string, char, vector<RectangleRectangle>);
    RectangleRectangle getById(int);
    vector<RectangleRectangle> getNext(int n=1,int transaction_id=1);
    char getCollectionStructure();
    int insert(RectangleRectangle);
    int insertBulk(RectangleRectangleCollection);
		bool isEmpty();
    int getSize();
    int remove(RectangleRectangle);
    int removeById(int);
    string getDBName();
    string getTableName();
};



//Initial data load supported for Points and Rectangles
int loadData(string dbName, string tableName, int geomtype, string filepath, char collectionStruct);
/*
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
