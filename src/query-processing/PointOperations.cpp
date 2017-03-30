#include <iostream>
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/geometries/box.hpp>
#include <boost/foreach.hpp>
#include "geometry.h"
#include <vector>

using namespace std;
namespace bg = boost::geometry;
namespace bgi = boost::geometry::index;

using namespace std;

class PointOperations{
public:
	static bool isIntersecting (Point p, Rectangle rec){

		return boost::geometry::intersects(point(p.getCoordinates().at(0), p.getCoordinates().at(1)), box(point(rec.getCoordinates().at(0),rec.getCoordinates().at(1)), point(rec.getCoordinates().at(2),rec.getCoordinates().at(3))));
	}

	static bool isEqual (Point point1, Point point2){
		return boost::geometry::equals(point1, point2);
	}

	static bool isDisjoint (Point point1, Point point2){
		return boost::geometry::disjoint(point(point1.getCoordinates().at(0), point1.getCoordinates().at(1)), point(point2.getCoordinates().at(0), point2.getCoordinates().at(1)));
	}

	static bool isWithin (Point point, Rectangle rec){
		return boost::geometry::within(point(point.getCoordinates().at(0), point.getCoordinates().at(1)), box(point(rec.getCoordinates().at(0),rec.getCoordinates().at(1)), point(rec.getCoordinates().at(2),rec.getCoordinates().at(3))));
	}

	static bool isOverlapping (Point point1, Point point2){
		return boost::geometry::overlaps(point(point1.getCoordinates().at(0), point1.getCoordinates().at(1)), point(point2.getCoordinates().at(2), point2.getCoordinates().at(3)));
	}

	static bool isOverlapping (Point point, Rectangle rec){
		return boost::geometry::overlaps(point(point.getCoordinates().at(0), point.getCoordinates().at(1)),box(point(rec.getCoordinates().at(0),rec.getCoordinates().at(1)), point(rec.getCoordinates().at(2),rec.getCoordinates().at(3))));
	}

	static double getDistance (Point point1, Point point2){
		return boost::geometry::distance(point(point1.getCoordinates().at(0), point1.getCoordinates().at(1)), point(point2.getCoordinates().at(2), point2.getCoordinates().at(3)));
	}
	static double getDistance (Point point, Rectangle rec){
		return boost::geometry::distance(point(point.getCoordinates().at(0), point.getCoordinates().at(1)), box(point(rec.getCoordinates().at(0),rec.getCoordinates().at(1)), point(rec.getCoordinates().at(2),rec.getCoordinates().at(3))));
	}

};
