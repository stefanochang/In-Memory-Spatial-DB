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
    QueryTree(PointCollection leftPoints, vector<string> leftFilter);
    QueryTree(RectangleCollection leftRects, vector<string> leftFilter);
    QueryTree(SpatialIndexInterface leftIndexedObject, vector<string> leftFilter);
    QueryTree(PointCollection leftPoints, vector<string> leftFilter, vector<string> root);
    QueryTree(RectangleCollection leftRects, vector<string> leftFilter, vector<string> root);    
    QueryTree(SpatialIndexInterface leftIndexedObject, vector<string> leftFilter, vector<string> root);
    QueryTree(PointCollection leftPoints, vector<string> leftFilter, vector<string> root, PointCollection rightPoints,  vector<string> rightFilter);
    QueryTree(RectangleCollection leftRects, vector<string> leftFilter, vector<string> root, PointCollection rightPoints,  vector<string> rightFilter);
    QueryTree(SpatialIndexInterface leftIndexedObject, vector<string> leftFilter, vector<string> root, PointCollection rightPoints,  vector<string> rightFilter);
    QueryTree(PointCollection leftPoints, vector<string> leftFilter, vector<string> root, RectangleCollection rightRects,  vector<string> rightFilter);
    QueryTree(RectangleCollection leftRects, vector<string> leftFilter, vector<string> root, RectangleCollection rightRects,  vector<string> rightFilter);
    QueryTree(SpatialIndexInterface leftIndexedObject, vector<string> leftFilter, vector<string> root, RectangleCollection rightRects,  vector<string> rightFilter);
    QueryTree(SpatialIndexInterface leftIndexedObject, vector<string> leftFilter, vector<string> root, SpatialIndexInterface rightIndexedObject,  vector<string> rightFilter);
};
