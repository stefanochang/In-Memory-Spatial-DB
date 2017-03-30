//
// Created by raha on 3/26/17.
//

#include <iostream>
//#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/geometries/box.hpp>
#include <boost/foreach.hpp>
#include "geometry.h"

using namespace std;
namespace bg = boost::geometry;
namespace bgi = boost::geometry::index;

using namespace std;

class RectangleOperations{
public:
    static bool isIntersecting (Rectangle rec1, Rectangle rec2){

        return boost::geometry::intersects(box(point(rec1.x1,rec1.y1), point(rec1.x2,rec1.y2)), box(point(rec2.x1,rec2.y1), point(rec2.x2,rec2.y2)));
    }

    static bool isEqual (Rectangle rec1, Rectangle rec2){
        return boost::geometry::equals(box(point(rec1.x1,rec1.y1), point(rec1.x2,rec1.y2)), box(point(rec2.x1,rec2.y1), point(rec2.x2,rec2.y2)));
    }

    static bool isDisjoint (Rectangle rec1, Rectangle rec2){
        return boost::geometry::disjoint(box(point(rec1.x1,rec1.y1), point(rec1.x2,rec1.y2)), box(point(rec2.x1,rec2.y1), point(rec2.x2,rec2.y2)));
    }

    static bool isWithin (Rectangle rec1, Rectangle rec2){
        return boost::geometry::within(box(point(rec1.x1,rec1.y1), point(rec1.x2,rec1.y2)), box(point(rec2.x1,rec2.y1), point(rec2.x2,rec2.y2)));
    }

    static bool isOverlapping (Rectangle rec1, Rectangle rec2){
        return boost::geometry::overlaps(box(point(rec1.x1,rec1.y1), point(rec1.x2,rec1.y2)), box(point(rec2.x1,rec2.y1), point(rec2.x2,rec2.y2)));
    }

    static double getDistance (Rectangle rec1, Rectangle rec2){
        return boost::geometry::distance(box(point(rec1.x1,rec1.y1), point(rec1.x2,rec1.y2)), box(point(rec2.x1,rec2.y1), point(rec2.x2,rec2.y2)));
    }
   

};