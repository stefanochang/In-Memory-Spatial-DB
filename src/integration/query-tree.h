#include <string>
#include "geometry.h"

class QueryTree {
    string* root;
    string* leftFilter;
    PointCollection leftDataPoint;
    RectangleCollection leftDataRect;
    string* rightFilter;
    PointCollection rightDataPoint;
    RectangleCollection rightDataRect;
};
