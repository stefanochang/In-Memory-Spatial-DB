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
	static bool isIntersecting (geometry::Point p, Rectangle rec){

		return boost::geometry::intersects(point(p.x, p.y), box(point(rec.x1,rec.y1), point(rec.x2,rec.y2)));
	}

	static bool isEqual (geometry::Point point1, geometry::Point point2){
		return boost::geometry::equals(point1, point2);
	}

	static bool isDisjoint (geometry::Point point1, geometry::Point point2){
		return boost::geometry::disjoint(point(point1.x, point1.y), point(point2.x, point2.y));
	}

	static bool isWithin (geometry::Point point, Rectangle rec){
		return boost::geometry::within(point(point.x, point.y), rec);
	}

	static bool isOverlapping (geometry::Point point1, geometry::Point point2){
		return boost::geometry::overlaps(point(point1.x, point1.y), point(point2.x, point2.y));
	}

	static bool isOverlapping (geometry::Point point, Rectangle rec){
		return boost::geometry::overlaps(point(point.x, point.y),rec);
	}

	static double getDistance (geometry::Point point1, geometry::Point point2){
		return boost::geometry::distance(point(point1.x, point1.y), point(point2.x, point2.y));
	}
	static double getDistance (geometry::Point point, Rectangle rec){
		return boost::geometry::distance(point(point.x, point.y), rec);
	}

};
