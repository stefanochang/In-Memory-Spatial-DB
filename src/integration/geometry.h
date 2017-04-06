#ifndef GEOMETRY_H
#define GEOMETRY_H
#include <string>
#include <vector>
using namespace std;

class Rectangle {
    float x1, y1, x2, y2;
    int id;
  public:
    Rectangle(float, float, float, float);
    int getId();
    void setId(int);
    vector<float> getCoordinates();
    Rectangle getEnvelope(); 
    float getVal(int i) const {
        switch (i){
            case 0: return x1;
            case 1: return y1;
            case 2: return x2;
            case 3: return y2;
            default: return -1;
        }
    }
};

class Point {
    float x, y;
    int id;
  public:
    Point(float, float);
    int getId();
    void setId(int);
    vector<float> getCoordinates();
    Rectangle getEnvelope();
    float getX() const { return x; }
    float getY() const { return y; }
};

class PointPoint {
    float x1, y1, x2, y2;
    int id;
  public:
    PointPoint(float, float, float, float);
    int getId();
    void setId(int);
    vector<float> getCoordinates();
    vector<Point> getPoints();
};

class PointRectangle {
    float x1, y1, x2, y2, x3, y3;
    int id;
  public:
    PointRectangle(float, float, float, float, float, float);
    int getId();
    void setId(int);
    vector<float> getCoordinates();
    Point getPoint();
    Rectangle getRectangle();
};


class RectangleRectangle {
    float x1, y1, x2, y2, x3, y3, x4, y4;
    int id;
  public:
    RectangleRectangle(float, float, float, float, float, float, float, float);
    int getId();
    void setId(int);
    vector<float> getCoordinates();
    vector<Rectangle> getRectangles();
};

#endif