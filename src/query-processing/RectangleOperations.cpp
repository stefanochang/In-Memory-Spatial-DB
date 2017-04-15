//
// Created by raha on 3/26/17.
//

#include <iostream>
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/geometries/box.hpp>
#include <boost/foreach.hpp>
#include <vector>
#include <boost/geometry/algorithms/intersects.hpp>
#include <boost/geometry/algorithms/equals.hpp>
#include <boost/geometry/algorithms/overlaps.hpp>
#include <boost/geometry/algorithms/distance.hpp>

#include "../integration/query-processing.h"


using namespace std;
namespace bg = boost::geometry;
typedef bg::model::point<float, 2, bg::cs::cartesian> point;
typedef bg::model::box<point> box;


bool RectangleOperations::isIntersecting (Rectangle rec1, Rectangle rec2){

return boost::geometry::intersects(box(point(rec1.getCoordinates().at(0),rec1.getCoordinates().at(1)), point(rec1.getCoordinates().at(2),rec1.getCoordinates().at(3))), box(point(rec2.getCoordinates().at(0),rec2.getCoordinates().at(1)), point(rec2.getCoordinates().at(2),rec2.getCoordinates().at(3))));
}

bool RectangleOperations::isEqual (Rectangle rec1, Rectangle rec2){
return boost::geometry::equals(box(point(rec1.getCoordinates().at(0),rec1.getCoordinates().at(1)), point(rec1.getCoordinates().at(2),rec1.getCoordinates().at(3))), box(point(rec2.getCoordinates().at(0),rec2.getCoordinates().at(1)), point(rec2.getCoordinates().at(2),rec2.getCoordinates().at(3))));
}

bool RectangleOperations::isDisjoint (Rectangle rec1, Rectangle rec2){
return boost::geometry::disjoint(box(point(rec1.getCoordinates().at(0),rec1.getCoordinates().at(1)), point(rec1.getCoordinates().at(2),rec1.getCoordinates().at(3))), box(point(rec2.getCoordinates().at(0),rec2.getCoordinates().at(1)), point(rec2.getCoordinates().at(2),rec2.getCoordinates().at(3))));
}

bool RectangleOperations::isWithin (Rectangle rec1, Rectangle rec2){
return boost::geometry::within(box(point(rec1.getCoordinates().at(0),rec1.getCoordinates().at(1)), point(rec1.getCoordinates().at(2),rec1.getCoordinates().at(3))), box(point(rec2.getCoordinates().at(0),rec2.getCoordinates().at(1)), point(rec2.getCoordinates().at(2),rec2.getCoordinates().at(3))));
}

bool RectangleOperations::isOverlapping (Rectangle rec1, Rectangle rec2){
return boost::geometry::overlaps(box(point(rec1.getCoordinates().at(0),rec1.getCoordinates().at(1)), point(rec1.getCoordinates().at(2),rec1.getCoordinates().at(3))), box(point(rec2.getCoordinates().at(0),rec2.getCoordinates().at(1)), point(rec2.getCoordinates().at(2),rec2.getCoordinates().at(3))));
}

double RectangleOperations::getDistance (Rectangle rec1, Rectangle rec2){
	float rect1CentroidX = (rec1.getCoordinates().at(0)+rec1.getCoordinates().at(2))/2;
	float rect1CentroidY = (rec1.getCoordinates().at(1)+rec1.getCoordinates().at(3))/2;
	float rect2CentroidX = (rec2.getCoordinates().at(0)+rec2.getCoordinates().at(2))/2;
	float rect2CentroidY = (rec2.getCoordinates().at(1)+rec2.getCoordinates().at(3))/2;
	return boost::geometry::distance(point(rect1CentroidX, rect1CentroidY), point(rect2CentroidX, rect2CentroidY));
}

double RectangleOperations::getArea (Rectangle rec1){
return boost::geometry::area(box(point(rec1.getCoordinates().at(0),rec1.getCoordinates().at(1)), point(rec1.getCoordinates().at(2),rec1.getCoordinates().at(3))));
}
   
