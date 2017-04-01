#include <iostream>

using namespace std;

class PointOperations{
public:
	static bool isIntersecting (Point point, Rectangle rec){
		return boost::geometry::intersects(point, rec);
	}

	static bool isEqual (Point point1, Point point2){
		return boost::geometry::equals(point1, point2);
	}

	static bool isDisjoint (Point point1, Point point2){
		return boost::geometry::disjoint(point1, point2);
	}

	static bool isWithin (Point point, Rectangle rec){
		return boost::geometry::within(point, rec);
	}

	static bool isOverlapping (Point point1, Point point2){
		return boost::geometry::overlaps(point1,point2);
	}

	static bool isOverlapping (Point point, Rectangle rec){
		return boost::geometry::overlaps(point,rec);
	}

	static double getDistance (Point point1, Point point2){
		return boost::geometry::distance(point1, point2);
	}
	static double getDistance (Point point, Rectangle rec){
		return boost::geometry::distance(point, rec);
	}
};
