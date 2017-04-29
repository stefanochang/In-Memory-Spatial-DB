
#ifndef DATA_STORAGE_H
#include "../integration/catalog.h"
#endif

#ifndef QUERY_PROCESSING_H
#define QUERY_PROCESSING_H

#define INVALID 0
#define TYPE_POINT 1
#define TYPE_RECTANGLE 2
#define TYPE_POINTPOINT 3
#define TYPE_POINTRECTANGLE 4
#define TYPE_RECTANGLERECTANGLE 5
#define POINT "POINT"
#define RECTANGLE "RECTANGLE"
#define POINTPOINT "POINTPOINT"
#define POINTRECTANGLE "POINTRECTANGLE"
#define RECTANGLERECTANGLE "RECTANGLERECTANGLE"
#define DB_NAME ""

#define NO_INDEX '1'
#define SPATIAL_INDEX '2'
#define DATA_INDEX '3'

#define NO_JOIN '1'
#define RANGE_JOIN '2'
#define KNN_JOIN '3'
#define DISTANCE_JOIN '4'
#define NO_JOIN_SI 'A'
#define RANGE_JOIN_SI 'B'
#define KNN_JOIN_SI 'C'
#define DISTANCE_JOIN_SI 'D'
#define NO_JOIN_DI 'E'
#define RANGE_JOIN_DI 'F'
#define KNN_JOIN_DI 'G'
#define DISTANCE_JOIN_DI 'H'

#define FILTER_BY_AREA_LT 'a'
#define FILTER_BY_AREA_LE 'b'
#define FILTER_BY_AREA_EQ 'c'
#define FILTER_BY_AREA_GT 'd'
#define FILTER_BY_AREA_GE 'e'

#define FILTER_BY_DISTANCE_LT 'f'
#define FILTER_BY_DISTANCE_LE 'g'
#define FILTER_BY_DISTANCE_EQ 'h'
#define FILTER_BY_DISTANCE_GT 'i'
#define FILTER_BY_DISTANCE_GE 'j'

#define KNN 11
#define OBJECTS_IN_RANGE 12

using namespace std;

class Filter {
public:
	Filter();
	Filter(char& filterType, vector<float>& inputParams);
	char filterType;
	vector<float> inputParams;
};

class QueryTree {
    char rootType;
    float rootParam;
    char lIndexType;
    char rIndexType;
    vector<Filter> leftBranch;
    PointCollection leftDataPoint;
    RectangleCollection leftDataRect;
    vector<Filter> rightBranch;
    PointCollection rightDataPoint;
    RectangleCollection rightDataRect;

public:
    QueryTree();
    void setRootType(char);
    void setRootParam(float);
    void setLIndexType(char);
    void setRIndexType(char);
    void setLeftFilter(vector<Filter>);
    void setLeftPoints(PointCollection);
    void setLeftRectangles(RectangleCollection);
    void setRightFilter(vector<Filter>);
    void setRightPoints(PointCollection);
    void setRightRectangles(RectangleCollection);
	const vector<Filter>& getLeftBranch() const;
	const PointCollection& getLeftDataPoint() const;
	const RectangleCollection& getLeftDataRect() const;
	const vector<Filter>& getRightBranch() const;
	const PointCollection& getRightDataPoint() const;
	const RectangleCollection& getRightDataRect() const;
	const char& getRootType() const;
	const float& getRootParam() const;
	const char& getLIndexType() const;
	const char& getRIndexType() const;
};

class QueryResult {
    int resultType;
    PointCollection pointCollection;
    RectangleCollection rectangleCollection;
    PointPointCollection pointPointCollection;
    RectangleRectangleCollection rectangleRectangleCollection;
    PointRectangleCollection pointRectangleCollection;
    bool status;
public:
	QueryResult();
	const PointCollection& getPointCollection();
	void setPointCollection(const PointCollection& pointCollection);
	const PointPointCollection& getPointPointCollection();
	void setPointPointCollection(const PointPointCollection& pointPointCollection);
	const PointRectangleCollection& getPointRectangleCollection();
	void setPointRectangleCollection(const PointRectangleCollection& pointRectangleCollection);
	const RectangleCollection& getRectangleCollection();
	void setRectangleCollection(const RectangleCollection& rectangleCollection);
	const RectangleRectangleCollection& getRectangleRectangleCollection();
	void setRectangleRectangleCollection(const RectangleRectangleCollection& rectangleRectangleCollection);
	int getResultType();
	void setResultType(int resultType);
	bool isStatus();
	void setStatus(bool status);
};

class PointOperations{
public:
    static bool isIntersecting (Point p, Rectangle rec);
    static bool isEqual (Point point1, Point point2);
    static bool isDisjoint (Point point1, Point point2);
    static bool isWithin (Point point1, Rectangle rec);
    static bool isOverlapping (Point point1, Point point2);
    static bool isOverlapping (Point point1, Rectangle rec);
    static double getDistance (Point point1, Point point2);
    static double getDistance (Point point1, Rectangle rec);

};

class RectangleOperations{
public:
    static bool isIntersecting (Rectangle rec1, Rectangle rec2);
    static bool isEqual (Rectangle rec1, Rectangle rec2);
    static bool isDisjoint (Rectangle rec1, Rectangle rec2);
    static bool isWithin (Rectangle rec1, Rectangle rec2);
    static bool isOverlapping (Rectangle rec1, Rectangle rec2);
    static double getDistance (Rectangle rec1, Rectangle rec2);
    static double getArea (Rectangle rec1);

};

class OperatorDictionary {
public:
	bool applyFilterBy (Filter filterDetails, Point inputPoint);
	bool applyFilterBy (Filter filterDetails, Rectangle inputRect);
	bool checkIfInRange(Filter rangeFilter, Point inputPoint);
	bool checkIfInRange(Filter rangeFilter, Rectangle inputRect);
	bool applyOperator (Filter filterDetails, Point inputPoint);
	bool applyOperator (Filter filterDetails, Rectangle inputRect);
};

class QueryProcessing {

private:
	OperatorDictionary opDict;
	SpatialIndexInterface* lIndexptr;
	SpatialIndexInterface* rIndexptr;
	Catalog* catalogptr;

public:

	QueryProcessing ();

	QueryResult processQuery (QueryTree qTree);

	PointCollection materializeBranch (QueryTree qTree, vector<Filter> filter, PointCollection data, char side);

	RectangleCollection materializeBranch (QueryTree qTree, vector<Filter> filter, RectangleCollection data, char side);

	PointPointCollection rangeJoin (PointCollection leftData, vector<Filter> filter, PointCollection rightData);

	RectangleRectangleCollection rangeJoin (
			RectangleCollection leftData, vector<Filter> filter, RectangleCollection rightData);

	PointRectangleCollection rangeJoin (
			PointCollection leftData, vector<Filter> filter, RectangleCollection rightData);

	RectangleRectangleCollection rangeJoinWithIndex (RectangleCollection leftData,
				vector<Filter> filter, RectangleCollection rightData, SpatialIndexInterface* indexptr);

	PointRectangleCollection rangeJoinWithIndex (PointCollection leftData,
				vector<Filter> filter, RectangleCollection rightData, SpatialIndexInterface* indexptr);

	PointPointCollection knnJoin (
			float k, PointCollection leftData, vector<Filter> filter, PointCollection rightData);

	RectangleRectangleCollection knnJoin (
			float k, RectangleCollection leftData, vector<Filter> filter, RectangleCollection rightData);

	PointRectangleCollection knnJoin (
			float k, PointCollection leftData, vector<Filter> filter, RectangleCollection rightData);

	PointRectangleCollection knnJoin (
				float k, RectangleCollection leftData, vector<Filter> filter, PointCollection rightData);

	PointPointCollection distanceJoin (float distThresh, PointCollection leftData,
			vector<Filter> filter, PointCollection rightData);

	RectangleRectangleCollection distanceJoin (float distThresh, RectangleCollection leftData,
			vector<Filter> filter, RectangleCollection rightData);

	PointRectangleCollection distanceJoin (float distThresh, PointCollection leftData,
			vector<Filter> filter, RectangleCollection rightData);

	vector<Point> getKnnPointsFromPoint (int k, Point inputPoint, vector<Point> inputPoints);

	vector<Point> getKnnPointsFromRectangle (int k, Rectangle inputRect, vector<Point> inputPoints);

	vector<Rectangle> getKnnRectanglesFromPoint (int k, Point inputPoint, vector<Rectangle> inputRectangles);

	vector<Rectangle> getKnnRectanglesFromRectangle (int k, Rectangle inputRect, vector<Rectangle> inputRectangles);

	PointPointCollection sweepBasedJoin (PointCollection leftData, PointCollection rightData, bool onX);
};

#endif
