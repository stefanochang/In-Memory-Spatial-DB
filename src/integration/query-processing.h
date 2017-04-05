#ifndef DATA_STORAGE_H
#include "../data-storage/data-storage.h"
#endif

#ifndef QUERY_PROCESSING_H
#define QUERY_PROCESSING_H

class QueryTree {
    vector<string> root;
    vector<vector<string>> leftBranch;
    PointCollection leftDataPoint;
    RectangleCollection leftDataRect;
    vector<vector<string>> rightBranch;
    PointCollection rightDataPoint;
    RectangleCollection rightDataRect;
//    SpatialIndexInterface rightIndexedObject;
//	  SpatialIndexInterface leftIndexedObject;

public:
    QueryTree();
    void setRoot(vector<string>);
    void setLeftFilter(vector<vector<string>>);
    void setLeftPoints(PointCollection);
    void setLeftRectangles(RectangleCollection);
//    void setLeftIndexedObject(SpatialIndexInterface);
    void setRightFilter(vector<vector<string>>);
    void setRightPoints(PointCollection);
    void setRightRectangles(RectangleCollection);
//    void setRightIndexedObject(SpatialIndexInterface);
	const vector<vector<string> >& getLeftBranch() const;
	const PointCollection& getLeftDataPoint() const;
	const RectangleCollection& getLeftDataRect() const;
//	  SpatialIndexInterface getLeftIndexedObject() const;
	const vector<vector<string> >& getRightBranch() const;
	const PointCollection& getRightDataPoint() const;
	const RectangleCollection& getRightDataRect() const;
//	 SpatialIndexInterface getRightIndexedObject() const;
	const vector<string>& getRoot() const;
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
    //static bool isOverlapping (Point point1, Point point2);
    static double getDistance (Point point1, Point point2);
    static double getDistance (Point point1, Rectangle rec);

};

class RectangleOperations{
public:
    static bool isIntersecting (Rectangle rec1, Rectangle rec2);

    static bool isEqual (Rectangle rec1, Rectangle rec2);
    static bool isDisjoint (Rectangle rec1, Rectangle rec2);
    static bool isWithin (Rectangle rec1, Rectangle rec2);
    //static bool isOverlapping (Rectangle rec1, Rectangle rec2);
    static double getDistance (Rectangle rec1, Rectangle rec2);
    //static double getArea (Rectangle rec1);

};

class OperatorDictionary {
public:
	bool applyFilterBy (vector<string> filterDetails, Point inputPoint);
	bool applyFilterBy (vector<string> filterDetails, Rectangle inputRect);
	bool applyOperator (vector<string> filterDetails, Point inputPoint);
	bool applyOperator (vector<string> filterDetails, Rectangle inputRect);
};

class QueryProcessing {

private:
	OperatorDictionary opDict;

public:

	QueryResult processQuery (QueryTree qTree);

	PointCollection materializeBranch (vector<vector<string>> filter, PointCollection data);

	RectangleCollection materializeBranch (vector<vector<string>> filter, RectangleCollection data);

	PointPointCollection rangeJoin (PointCollection leftData, vector<vector<string>> filter, PointCollection rightData);

	RectangleRectangleCollection rangeJoin (
			RectangleCollection leftData, vector<vector<string>> filter, RectangleCollection rightData);

	PointRectangleCollection rangeJoin (
			PointCollection leftData, vector<vector<string>> filter, RectangleCollection rightData);

	PointPointCollection knnJoin (
			vector<string> root, PointCollection leftData, vector<vector<string>> filter, PointCollection rightData);

	RectangleRectangleCollection knnJoin (
			vector<string> root, RectangleCollection leftData, vector<vector<string>> filter, RectangleCollection rightData);

	PointRectangleCollection knnJoin (
			vector<string> root, PointCollection leftData, vector<vector<string>> filter, RectangleCollection rightData);

	PointPointCollection distanceJoin (vector<string> root, PointCollection leftData,
			vector<vector<string>> filter, PointCollection rightData);

	RectangleRectangleCollection distanceJoin (vector<string> root, RectangleCollection leftData,
			vector<vector<string>> filter, RectangleCollection rightData);

	PointRectangleCollection distanceJoin (vector<string> root, PointCollection leftData,
			vector<vector<string>> filter, RectangleCollection rightData);

};

#endif