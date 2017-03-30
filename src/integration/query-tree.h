#include "geometry-collection.h"

class QueryTree {
    vector<string> root;
    vector<string> leftFilter;
    PointCollection leftDataPoint;
    RectangleCollection leftDataRect;
    vector<string> rightFilter;
    PointCollection rightDataPoint;
    RectangleCollection rightDataRect;
};
