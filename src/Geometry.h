#include <iostream>
#include <string>

using namespace std;

class Rectangle {
    float x1, y1, x2, y2;
    int id;
  public:
    Rectangle(float, float, float, float);
    int getId();
    float* getCoordinates();
    Rectangle getEnvelope();    
};

class Point {
    float x, y;
    int id;
  public:
    Point(float, float);
    int getId();
    float* getCoordinates();
    Rectangle getEnvelope();
};

class PointPoint {
    float x1, y1, x2, y2;
    int id;
  public:
    PointPoint(float, float, float, float);
    int getId();
    float* getCoordinates();
    Point* getPoints();
};

class PointRectangle {
    float x1, y1, x2, y2, x3, y3;
    int id;
  public:
    PointRectangle(float, float, float, float, float, float);
    int getId();
    float* getCoordinates();
    Point getPoint();
    Rectangle getRectangle();
};


class RectangleRectangle {
    float x1, y1, x2, y2, x3, y3, x4, y4;
    int id;
  public:
    RectangleRectangle(float, float, float, float, float, float, float, float);
    int getId();
    float* getCoordinates();
    Rectangle* getRectangles();
};

class PointCollection {
    Point* points;    
    string name, databaseName; 
    int collectionStructure;
  public:
    PointCollection(string, string, int, Point*);
    Point getById(int id);
    Point* getNext(int n=1);
    int insert(Point point);
    int remove(Point point);
};

class RectangleCollection {
    Rectangle* rectangles;    
    string name, databaseName; 
    int collectionStructure;
  public:
    RectangleCollection(string, string, int, Rectangle*);
    Rectangle getById(int id);
    Rectangle* getNext(int n=1);
    int insert(Rectangle rectangle);
    int remove(Rectangle rectangle);
};

class PointPointCollection {
    PointPoint* pointPoints;    
    string name, databaseName; 
    int collectionStructure;
  public:
    PointPointCollection(string, string, int, PointPoint*);
    PointPoint getById(int id);
    PointPoint* getNext(int n=1);
};

class PointRectangleCollection {
    PointRectangle* pointRectangles;    
    string name, databaseName; 
    int collectionStructure;
  public:
    PointRectangleCollection(string, string, int, PointRectangle*);
    PointRectangle getById(int id);
    PointRectangle* getNext(int n=1);
};

class RectangleRectangleCollection {
    RectangleRectangle* rectangleRectangles;    
    string name, databaseName; 
    int collectionStructure;
  public:
    RectangleRectangleCollection(string, string, int, RectangleRectangle*);
    RectangleRectangle getById(int id);
    RectangleRectangle* getNext(int n=1);
};
