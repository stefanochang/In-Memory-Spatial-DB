#include "query-tree.h"

class QueryResult {
    int resultType;
    PointCollection pointCollection;
    RectangleCollection rectangleCollection;
    PointPointCollection pointPointCollection;
    RectangleRectangleCollection rectangleRectangleCollection;
    PointRectangleCollection pointRectangleCollection;
    bool status;    
public:
        QueryResult(int, PointCollection);
        QueryResult(int, RectangleCollection);
        QueryResult(int, PointPointCollection);
        QueryResult(int, RectangleRectangleCollection);
        QueryResult(int, PointRectangleCollection);
	QueryResult(int, bool); 
};

QueryResult processQuery(QueryTree);
