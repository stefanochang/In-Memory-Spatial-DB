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
    void setRoot(vector<string>);
    void setLeftFilter(vector<string>);
    void setLeftPoints(PointCollection);
    void setLeftRectangles(RectangleCollection);
    void setLeftIndexedObject(SpatialIndexInterface);
    void setRightFilter(vector<string>);
    void setRightPoints(PointCollection);
    void setRightRectangles(RectangleCollection);
    void setRightIndexedObject(SpatialIndexInterface);
};
