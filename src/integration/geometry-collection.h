#include <vector>
#include "geometry.h"
#include "../data-storage/list.h"
using namespace std;

class PointCollection : public list{
    vector<Point> points;    
    string name, databaseName; 
    int collectionStructure;
  public:
    PointCollection();
    PointCollection(string, string, int, vector<Point>);
    Point getById(int);
    vector<Point> getNext(int n=1);
    int insert(Point);
    int remove(Point);
    int removeById(int);
};

class RectangleCollection : public list{
    vector<Rectangle> rectangles;    
    string name, databaseName; 
    int collectionStructure;
  public:
    RectangleCollection();
    RectangleCollection(string, string, int, vector<Rectangle>);
    Rectangle getById(int);
    vector<Rectangle> getNext(int n=1);
    int insert(Rectangle);
    int remove(Rectangle);
    int removeById(int);
};

class PointPointCollection : public list{
    vector<PointPoint> pointPoints;    
    string name, databaseName; 
    int collectionStructure;
  public:
    PointPointCollection();
    PointPointCollection(string, string, int, vector<PointPoint>);
    PointPoint getById(int);
    vector<PointPoint> getNext(int n=1);
};

class PointRectangleCollection : public list{
    vector<PointRectangle> pointRectangles;    
    string name, databaseName; 
    int collectionStructure;
  public:
    PointRectangleCollection();
    PointRectangleCollection(string, string, int, vector<PointRectangle>);
    PointRectangle getById(int);
    vector<PointRectangle> getNext(int n=1);
};

class RectangleRectangleCollection : public list{
    vector<RectangleRectangle> rectangleRectangles;    
    string name, databaseName; 
    int collectionStructure;
  public:
    RectangleRectangleCollection();
    RectangleRectangleCollection(string, string, int, vector<RectangleRectangle>);
    RectangleRectangle getById(int);
    vector<RectangleRectangle> getNext(int n=1);
};
