#include <iostream>
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/geometries/box.hpp>
#include <boost/foreach.hpp>
#include "geometry.h"

using namespace std;
namespace bg = boost::geometry;
namespace bgi = boost::geometry::index;

using namespace std;

class PointOperations{
public:
	static bool isIntersecting (Point p, Rectangle rec){

		return boost::geometry::intersects(point(p.x, p.y), box(point(rec.x1,rec.y1), point(rec.x2,rec.y2)));
	}

	static bool isEqual (Point point1, Point point2){
		return boost::geometry::equals(point1, point2);
	}

	static bool isDisjoint (Point point1, Point point2){
		return boost::geometry::disjoint(point(point1.x, point1.y), point(point2.x, point2.y));
	}

	static bool isWithin (Point point, Rectangle rec){
		return boost::geometry::within(point(point.x, point.y), box(point(rec.x1,rec.y1), point(rec.x2,rec.y2)));
	}

	static bool isOverlapping (Point point1, Point point2){
		return boost::geometry::overlaps(point(point1.x, point1.y), point(point2.x, point2.y));
	}

	static bool isOverlapping (Point point, Rectangle rec){
		return boost::geometry::overlaps(point(point.x, point.y),box(point(rec.x1,rec.y1), point(rec.x2,rec.y2)));
	}

	static double getDistance (Point point1, Point point2){
		return boost::geometry::distance(point(point1.x, point1.y), point(point2.x, point2.y));
	}
	static double getDistance (Point point, Rectangle rec){
		return boost::geometry::distance(point(point.x, point.y), box(point(rec.x1,rec.y1), point(rec.x2,rec.y2)));
	}

};
