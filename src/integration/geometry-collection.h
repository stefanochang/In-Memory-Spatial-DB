#include<vector>
#include "geometry.h"
using namespace std;

class PointCollection {
    vector<Point> points;    
    string name, databaseName; 
    int collectionStructure;
  public:
    PointCollection();
    PointCollection(string, string, int, vector<Point>);
    Point getById(int);
    vector<Point> getNext(int n=1);
    int insert(Point);
    int insertBulk(PointCollection);
    bool isEmpty();
    int remove(Point);
    int removeById(int);
    int getSize();  // size of PointCollection
    string getDBName();
    string getTableName();
};

class RectangleCollection {
    vector<Rectangle> rectangles;    
    string name, databaseName; 
    int collectionStructure;
  public:
    RectangleCollection();
    RectangleCollection(string, string, int, vector<Rectangle>);
    Rectangle getById(int);
    vector<Rectangle> getNext(int n=1);
    int insert(Rectangle);
    int insertBulk(RectangleCollection);
    int remove(Rectangle);
    int removeById(int);
    bool isEmpty();
    int getSize();
    string getDBName();
    string getTableName();
};

class PointPointCollection {
    vector<PointPoint> pointPoints;    
    string name, databaseName; 
    int collectionStructure;
  public:
    PointPointCollection();
    PointPointCollection(string, string, int, vector<PointPoint>);
    PointPoint getById(int);
    vector<PointPoint> getNext(int n=1);
    int insert(PointPoint);
    int insertBulk(PointPointCollection);
    bool isEmpty();
    int getSize();
    string getDBName();
    string getTableName();
};

class PointRectangleCollection {
    vector<PointRectangle> pointRectangles;    
    string name, databaseName; 
    int collectionStructure;
  public:
    PointRectangleCollection();
    PointRectangleCollection(string, string, int, vector<PointRectangle>);
    PointRectangle getById(int);
    vector<PointRectangle> getNext(int n=1);
    int insert(PointRectangle);
    int insertBulk(PointRectangleCollection);
    bool isEmpty();
    int getSize();
    string getDBName();
    string getTableName();
};

class RectangleRectangleCollection {
    vector<RectangleRectangle> rectangleRectangles;    
    string name, databaseName; 
    int collectionStructure;
  public:
    RectangleRectangleCollection();
    RectangleRectangleCollection(string, string, int, vector<RectangleRectangle>);
    RectangleRectangle getById(int);
    vector<RectangleRectangle> getNext(int n=1);
    int insert(RectangleRectangle);
    int insertBulk(RectangleRectangleCollection);
    bool isEmpty();
    int getSize();
    string getDBName();
    string getTableName();
};
