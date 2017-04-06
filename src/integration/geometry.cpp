#include "geometry.h"
#include <vector>
using namespace std;

Rectangle::Rectangle(float topleft_x, float topleft_y, float bottomright_x, float bottomright_y) {
	x1 = topleft_x;
	y1 = topleft_y;
	x2 = bottomright_x;
	y2 = bottomright_y;
}

int Rectangle::getId() {
	return id;
}

void Rectangle::setId(int id) {
        this->id = id;
}

vector<float> Rectangle::getCoordinates() {
	vector<float> coords = {x1, y1, x2, y2};
	return coords;
}

// float Rectangle::getVal(int i) const {
//     switch (i){
//         case 0: return x1;
//         case 1: return y1;
//         case 2: return x2;
//         case 3: return y2;
//         default: return -1;
//     }
// }

Point::Point( float x, float y) {
        this->x = x;
	this->y = y;
}

int Point::getId() {
        return id;
}

void Point::setId(int id) {
        this->id = id;
}

vector<float> Point::getCoordinates() {
        vector<float> coords = {x, y};
        return coords;
}
// float Point::getX() const { return x; }
// float Point::getY() const { return y; }

PointPoint::PointPoint( float x1, float y1, float x2, float y2) {
        this->x1 = x1;
        this->y1 = y1;
        this->x2 = x2;
        this->y2 = y2;          
}

int PointPoint::getId() {
        return id;
}

void PointPoint::setId(int id) {
        this->id = id;
}

vector<float> PointPoint::getCoordinates() {
        vector<float> coords = {x1, y1, x2, y2};
        return coords;
        
}

vector<Point> PointPoint::getPoints() {
	Point p1 = Point(x1,y1);
	Point p2 = Point(x2,y2);
	vector<Point> points = {p1, p2};
	return points;
}

PointRectangle::PointRectangle(float x1, float y1, float x2, float y2, float x3, float y3) {
        this->x1 = x1;
        this->y1 = y1;
        this->x2 = x2;
        this->y2 = y2;          
        this->x3 = x3;
        this->y3 = y3;
}

int PointRectangle::getId() {
        return id;
}

void PointRectangle::setId(int id) {
        this->id = id;
}

vector<float> PointRectangle::getCoordinates() {
        vector<float> coords = {x1, y1, x2, y2, x3, y3};
        return coords;
}

Point PointRectangle::getPoint() {
        return Point(x1,y1);
}

Rectangle PointRectangle::getRectangle() {
	return Rectangle(x2, y2, x3, y3);
}

RectangleRectangle::RectangleRectangle(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4) {
        this->x1 = x1;
        this->y1 = y1;
        this->x2 = x2;
        this->y2 = y2;          
        this->x3 = x3;
        this->y3 = y3;
        this->x4 = x4;
        this->y4 = y4;

}

int RectangleRectangle::getId() {
        return id;
}

void RectangleRectangle::setId(int id) {
        this->id = id;
}

vector<float> RectangleRectangle::getCoordinates() {
        vector<float> coords = {x1, y1, x2, y2, x3, y3, x4, y4};
        return coords;
}

vector<Rectangle> RectangleRectangle::getRectangles() {
        Rectangle r1 = Rectangle(x1, y1, x2, y2);
        Rectangle r2 = Rectangle(x3, y3, x4, y4);
        vector<Rectangle> rectangles = {r1, r2};
        return rectangles;
}
