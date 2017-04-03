/*
 * QueryProcessing.cpp
 *
 *  Created on: Mar 16, 2017
 *      Author: tejal
 */

#include <iostream>
#include <vector>
#include "../integration/query-processing.h"

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

using namespace std;


QueryResult QueryProcessing::processQuery (QueryTree qTree) {
	QueryResult queryResult;
	vector<string> root = qTree.getRoot();
	vector<vector<string>> leftFilter = qTree.getLeftBranch();
	vector<vector<string>> rightFilter = qTree.getRightBranch();
	PointCollection leftDataPoint = qTree.getLeftDataPoint();
	RectangleCollection leftDataRect = qTree.getLeftDataRect();
	PointCollection rightDataPoint = qTree.getRightDataPoint();
	RectangleCollection rightDataRect = qTree.getRightDataRect();

	// left data is points
	if (!leftDataPoint.isEmpty() && leftDataRect.isEmpty()) {
		PointCollection leftResult = materializeBranch(leftFilter, leftDataPoint);
		// no right branch
		if (root[0] == "") {
			queryResult.setPointCollection(leftResult);
			queryResult.setResultType(1);
		}
		else {
			// right data is points
			if (!rightDataPoint.isEmpty() && rightDataRect.isEmpty()) {
				PointCollection rightResult = materializeBranch(rightFilter, rightDataPoint);
				if (root[0] == "knnJoin") {
					PointPointCollection distanceJoinResult = knnJoin(root, leftResult, rightFilter, rightResult);
					queryResult.setPointPointCollection(distanceJoinResult);
					queryResult.setResultType(3);
				}
				else if (root[0] == "rangeJoin") {
					PointPointCollection distanceJoinResult = rangeJoin(leftResult, rightFilter, rightResult);
					queryResult.setPointPointCollection(distanceJoinResult);
					queryResult.setResultType(3);
				}
				else if (root[0] == "distanceJoin") {
					PointPointCollection distanceJoinResult = distanceJoin(root, leftResult, rightFilter, rightResult);
					queryResult.setPointPointCollection(distanceJoinResult);
					queryResult.setResultType(3);
				}
			}
			// right data is rectangles
			else if (rightDataPoint.isEmpty() && !rightDataRect.isEmpty()) {
				RectangleCollection rightResult = materializeBranch(rightFilter, rightDataRect);
				if (root[0] == "knnJoin") {
					PointRectangleCollection distanceJoinResult = knnJoin(root, leftResult, rightFilter, rightResult);
					queryResult.setPointRectangleCollection(distanceJoinResult);
					queryResult.setResultType(4);
				}
				else if (root[0] == "rangeJoin") {
					PointRectangleCollection distanceJoinResult = rangeJoin(leftResult, rightFilter, rightResult);
					queryResult.setPointRectangleCollection(distanceJoinResult);
					queryResult.setResultType(4);
				}
				else if (root[0] == "distanceJoin") {
					PointRectangleCollection distanceJoinResult = distanceJoin(root, leftResult, rightFilter, rightResult);
					queryResult.setPointRectangleCollection(distanceJoinResult);
					queryResult.setResultType(4);
				}
			}
		}
	}
	// left data is rectangles
	else if (leftDataPoint.isEmpty() && !leftDataRect.isEmpty()) {
		RectangleCollection leftResult = materializeBranch(leftFilter, leftDataRect);
		// no right branch
		if (root[0] == "") {
			queryResult.setRectangleCollection(leftResult);
			queryResult.setResultType(2);
		}
		else {
			// right data is points
			if (!rightDataPoint.isEmpty() && rightDataRect.isEmpty()) {
				PointCollection rightResult = materializeBranch(rightFilter, rightDataPoint);
				if (root[0] == "knnJoin") {
					PointRectangleCollection distanceJoinResult = knnJoin(root, rightResult, rightFilter, leftResult);
					queryResult.setPointRectangleCollection(distanceJoinResult);
					queryResult.setResultType(4);
				}
				else if (root[0] == "rangeJoin") {
					PointRectangleCollection distanceJoinResult = rangeJoin(rightResult, rightFilter, leftResult);
					queryResult.setPointRectangleCollection(distanceJoinResult);
					queryResult.setResultType(4);
				}
				else if (root[0] == "distanceJoin") {
					PointRectangleCollection distanceJoinResult = distanceJoin(root, rightResult, rightFilter, leftResult);
					queryResult.setPointRectangleCollection(distanceJoinResult);
					queryResult.setResultType(4);
				}
			}
			// right data is rectangles
			else if (rightDataPoint.isEmpty() && !rightDataRect.isEmpty()) {
				RectangleCollection rightResult = materializeBranch(rightFilter, rightDataRect);
				if (root[0] == "knnJoin") {
					RectangleRectangleCollection distanceJoinResult = knnJoin(root, rightResult, rightFilter, leftResult);
					queryResult.setRectangleRectangleCollection(distanceJoinResult);
					queryResult.setResultType(5);
				}
				else if (root[0] == "rangeJoin") {
					RectangleRectangleCollection distanceJoinResult = rangeJoin(rightResult, rightFilter, leftResult);
					queryResult.setRectangleRectangleCollection(distanceJoinResult);
					queryResult.setResultType(5);
				}
				else if (root[0] == "distanceJoin") {
					RectangleRectangleCollection distanceJoinResult = distanceJoin(root, rightResult, rightFilter, leftResult);
					queryResult.setRectangleRectangleCollection(distanceJoinResult);
					queryResult.setResultType(5);
				}
			}
		}

	}
	return queryResult;
}

PointCollection QueryProcessing::materializeBranch (vector<vector<string>> filter, PointCollection data) {
	// initialize result
	PointCollection result;
	vector<Point> points = data.getNext(1);
	while (points.size()!=0) {
		bool passedAllOperators = true;
		for (int i=0;i<filter.size();i++) {
			passedAllOperators = passedAllOperators && opDict.applyOperator(filter[i],points[0]);
		}
		if (passedAllOperators) {
			result.insert(points[0]);
		}
		points = data.getNext(1);
	}
	return result;
}

RectangleCollection QueryProcessing::materializeBranch (vector<vector<string>> filter, RectangleCollection data) {
	// initialize result
	RectangleCollection result;
	vector<Rectangle> rects = data.getNext(1);
	while (rects.size()!=0) {
		bool passedAllOperators = true;
		for (int i=0;i<filter.size();i++) {
			passedAllOperators = passedAllOperators && opDict.applyOperator(filter[i],rects[0]);
		}
		if (passedAllOperators) {
			result.insert(rects[0]);
		}
		rects = data.getNext(1);
	}
	return result;
}

PointPointCollection QueryProcessing::rangeJoin (PointCollection leftData, vector<vector<string>> filter, PointCollection rightData) {
	vector<PointPoint> joinResultVector;
	PointPointCollection distanceJoinResult(POINTPOINT,DB_NAME,TYPE_POINTPOINT,joinResultVector);
	return distanceJoinResult;
}

RectangleRectangleCollection QueryProcessing::rangeJoin (RectangleCollection leftData, vector<vector<string>> filter, RectangleCollection rightData) {
	vector<RectangleRectangle> joinResultVector;
	RectangleRectangleCollection distanceJoinResult(RECTANGLERECTANGLE,DB_NAME,TYPE_RECTANGLERECTANGLE,joinResultVector);
	return distanceJoinResult;
}

PointRectangleCollection QueryProcessing::rangeJoin (PointCollection leftData, vector<vector<string>> filter, RectangleCollection rightData) {
	vector<PointRectangle> joinResultVector;
	PointRectangleCollection distanceJoinResult(POINTRECTANGLE,DB_NAME,TYPE_POINTRECTANGLE,joinResultVector);
	return distanceJoinResult;
}

PointPointCollection QueryProcessing::knnJoin (vector<string> root, PointCollection leftData, vector<vector<string>> filter, PointCollection rightData) {
	vector<PointPoint> joinResultVector;
	PointPointCollection distanceJoinResult(POINTPOINT,DB_NAME,TYPE_POINTPOINT,joinResultVector);
	return distanceJoinResult;
}

RectangleRectangleCollection QueryProcessing::knnJoin (vector<string> root, RectangleCollection leftData, vector<vector<string>> filter, RectangleCollection rightData) {
	vector<RectangleRectangle> joinResultVector;
	RectangleRectangleCollection distanceJoinResult(RECTANGLERECTANGLE,DB_NAME,TYPE_RECTANGLERECTANGLE,joinResultVector);
	return distanceJoinResult;
}

PointRectangleCollection QueryProcessing::knnJoin (vector<string> root, PointCollection leftData, vector<vector<string>> filter, RectangleCollection rightData) {
	vector<PointRectangle> joinResultVector;
	PointRectangleCollection distanceJoinResult(POINTRECTANGLE,DB_NAME,TYPE_POINTRECTANGLE,joinResultVector);
	return distanceJoinResult;
}

PointPointCollection QueryProcessing::distanceJoin (vector<string> root, PointCollection leftData,
		vector<vector<string>> filter, PointCollection rightData) {
	double distThresh = stod(root[1]);
	vector<PointPoint> joinResultVector;
	vector<Point> leftPoints = leftData.getNext(leftData.getSize());
	vector<Point> rightPoints = rightData.getNext(rightData.getSize());
	for (int i=0;i<leftPoints.size();i++) {
		for (int j=0;j<rightPoints.size();j++) {
			if (PointOperations::getDistance(leftPoints[i],rightPoints[j]) <= distThresh) {
				PointPoint pp(leftPoints[i].getCoordinates()[0],leftPoints[i].getCoordinates()[1],
						rightPoints[j].getCoordinates()[0],rightPoints[j].getCoordinates()[1]);
				joinResultVector.insert(joinResultVector.end(),pp);
			}
		}
	}
	PointPointCollection distanceJoinResult(POINTPOINT,DB_NAME,TYPE_POINTPOINT,joinResultVector);
	return distanceJoinResult;
}

RectangleRectangleCollection QueryProcessing::distanceJoin (vector<string> root, RectangleCollection leftData,
		vector<vector<string>> filter, RectangleCollection rightData) {
	double distThresh = stod(root[1]);
	vector<RectangleRectangle> joinResultVector;
	vector<Rectangle> leftRects = leftData.getNext(leftData.getSize());
	vector<Rectangle> rightRects = rightData.getNext(rightData.getSize());
	for (int i=0;i<leftRects.size();i++) {
		for (int j=0;j<rightRects.size();j++) {
			if (RectangleOperations::getDistance(leftRects[i],rightRects[j]) <= distThresh) {
				RectangleRectangle rr(leftRects[i].getCoordinates()[0],leftRects[i].getCoordinates()[1],
						leftRects[i].getCoordinates()[2],leftRects[i].getCoordinates()[3],
						rightRects[j].getCoordinates()[0],rightRects[j].getCoordinates()[1],
						rightRects[j].getCoordinates()[2],rightRects[j].getCoordinates()[3]);
				joinResultVector.insert(joinResultVector.end(),rr);
			}
		}
	}
	RectangleRectangleCollection distanceJoinResult(RECTANGLERECTANGLE,DB_NAME,TYPE_RECTANGLERECTANGLE,joinResultVector);
	return distanceJoinResult;
}

PointRectangleCollection QueryProcessing::distanceJoin (vector<string> root, PointCollection leftData,
		vector<vector<string>> filter, RectangleCollection rightData) {
	double distThresh = stod(root[1]);
	vector<PointRectangle> joinResultVector;
	vector<Point> leftPoints = leftData.getNext(leftData.getSize());
	vector<Rectangle> rightRects = rightData.getNext(rightData.getSize());
	for (int i=0;i<leftPoints.size();i++) {
		for (int j=0;j<rightRects.size();j++) {
			if (PointOperations::getDistance(leftPoints[i],rightRects[j]) <= distThresh) {
				PointRectangle pr(leftPoints[i].getCoordinates()[0],leftPoints[i].getCoordinates()[1],
						rightRects[j].getCoordinates()[0],rightRects[j].getCoordinates()[1],
						rightRects[j].getCoordinates()[2],rightRects[j].getCoordinates()[3]);
				joinResultVector.insert(joinResultVector.end(),pr);
			}
		}
	}
	PointRectangleCollection distanceJoinResult(POINTRECTANGLE,DB_NAME,TYPE_POINTRECTANGLE,joinResultVector);
	return distanceJoinResult;
}
