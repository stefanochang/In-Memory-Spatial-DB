#include <string>
#include<vector>
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

