#ifndef DATASTORAGE_H
#define DATASTORAGE_H

#include "ds_datatypes.h"
#include "ds_constants.h"
#include "../integration/geometry.h"

/* ************************************************************************************* *\
    CSE 591 - Advances in Databases - Spring 2017 - Project - Data Storage Module
   -------------------------------------------------------------------------------

   File: data-storage.h

    This header file contains all collection and API details for the data storage
    module. Include this file in the project to use all data storage features.

    Relavant files
        - data-storage.cpp: All method implementations are done here
        - main.cpp: All test cases are defined here
        - constants.cpp: All constants are defined here
        - ds_datatypes.cpp: All internal structures are defined here

    This module currently supports the following spatial geometry types:
        - Point: Defined by an X and Y coordinate
        - Rectangle: Defined by 2 points namely the left bottom and right top
        - PointPoint: Pair type defined by 2 points
        - RectangleRectangle: Pair type defined by 2 rectangles
        - PointRectangle: Pair type defined by a point and a rectangle

    The documentation for the collections API is detailed in the PointCollection only
    since the other collections follow a very similar pattern. The "Geometry" placeholder
    is used to refer to individual geometry types.

    There are other functions common across all the collections which are declared after
    all the collections have been declared. The documentation for the same is provided.

    -- Ajay Kulkarni, Anuran Duttaroy, Dhanashree Adhikari, Nilam Bari, Omkar Kaptan --

\* ************************************************************************************* */

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// POINT COLLECTION
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class PointCollection{

    /* ************************************************************************************* *\
        Point Collection Variables:
        - points: 
            The vector containing the points in the collection. The elements are of type 
            ds_point which is a struct representation for the points
        - name:
            The name for this collection
        - databaseName:
            The database this collection is a part of
        - recordId
            Auto incrementing record id for new elements being inserted into the collection
        - getNextAt
            Position marker to resume getNext from when a transaction invokes getNext
        - collectionStructure
            The method of data organization within the collection
    \* ************************************************************************************* */

    vector<ds_point> points;
    string name, databaseName;
	int recordId;
	int getNextAt;
    char collectionStructure;

    /* ************************************************************************************* *\
        Point Collection Methods
    \* ************************************************************************************* */

    /* Convert between the Geometry Object type and the internal structure representation */
    Point convertStructToObj(ds_point);
    ds_point * convertObjToStruct(Point);

    /* Bulk insert an entire vector into the collection */
    int insertBulk(vector<Point>);
  public:
    /* 
        Constructors to initialize a collection
        - Default constructor which initilizes variables to defaults
        - Parameterized constructor to initialize collection and database name, data representation
            and initial geometry elements that should be inserted in the new collection
    */
    PointCollection();
    PointCollection(string, string, char, vector<Point>);

    /* Get a geometry object from the collection by ID */
    Point getById(int);

    /* Get next "n" points from the collection (n >= 1) */
    vector<Point> getNext(int n=1, int transaction_id=1);

    /* Get character representation of the collection element origanization */
    char getCollectionStructure();

    /*
        Methods for insertion into the collection
        - insert(Point)
            insert a single point into the collection while retaining the data organization
        - insertSortedX(ds_point)
            insert a single point into the collection in a X sorted fashion
        - insertSortedY(ds_point)
            insert a single point into the collection in a Y sorted fashion
        - insertBulk(PointCollection)
            insert all points in a given collection into this collection
    */
    int insert(Point);
    int insertSortedX(ds_point);
    int insertSortedY(ds_point);
    int insertBulk(PointCollection);

    /* Check if collection is empty */
	bool isEmpty();

    /* Get count of elements in the collection */
	int getSize();

    /* Remove a given point by specifying the point or its ID */
    int remove(Point);
    int removeById(int);

    /* Get name of database this collection belongs to */
    string getDBName();

    /* Get name of collection */
    string getTableName();

    /* Switch the storage structure to the required form */
    int switchStorageStructure(char);
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RECTANGLE COLLECTION
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// POINTPOINT COLLECTION
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// POINTRECTANGLE COLLECTION
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RECTANGLERECTANGLE COLLECTION
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// COMMON FUNCTIONS
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool write_log(string command);

/* Create a collection and load data into it from the given file */
int loadData(string dbName, string tableName, int geomtype, string filepath, char collectionStruct);

/* Recover data in case of a system failure */
bool recoverData();

bool evaluate(string collection,string op,  vector<string>);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif
