#include "QueryTree.h"

class QueryResult {
    int resultType;
    PointCollection pointCollection;
    RectangleCollection rectangleCollection;
    PointPointCollection pointPointCollection;
    RectangleRectangleCollection rectangleRectangleCollection;
    PointRectangleCollection pointRectangleCollection;
    public:
        QueryResult(int, PointCollection);
        QueryResult(int, RectangleCollection);
        QueryResult(int, PointPointCollection);
        QueryResult(int, RectangleRectangleCollection);
        QueryResult(int, PointRectangleCollection); 
};

QueryResult processQuery(QueryTree);
