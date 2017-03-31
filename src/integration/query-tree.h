#include "spatial-index-interface.h"

class QueryTree {
    vector<string> root;
    vector<string> leftFilter;
    PointCollection leftDataPoint;
    RectangleCollection leftDataRect;
    vector<string> rightFilter;
    PointCollection rightDataPoint;
    RectangleCollection rightDataRect;
    SpatialIndexInterface rightIndexedObject;
	SpatialIndexInterface leftIndexedObject;

public:
    QueryTree();
    void set_root(vector<string>);
    void set_left_filter(vector<string>);
    void set_left_points(PointCollection);
    void set_left_rectangles(RectangleCollection);
    void set_left_indexed_object(SpatialIndexInterface);
    void set_right_filter(vector<string>);
    void set_right_points(PointCollection);
    void set_right_rectangles(RectangleCollection);
    void set_right_indexed_object(SpatialIndexInterface);
};
