/*
 * QueryProcessing.cpp
 *
 *  Created on: Mar 16, 2017
 *      Author: tejal
 */

#include <iostream>
#include <vector>
#include "query-tree.h"
#include "query-processing.h"
#include "geometry.h"
#include "OperatorDictionary.cpp"

#define NULL    ((void *)0)

using namespace std;

class QueryProcessing {

private:
	OperatorDictionary opDict;

	QueryResult processQuery (QueryTree qTree) {
		QueryResult queryResult = new QueryResult();
		vector<string> root = qTree.root;
		vector<vector<string>> leftFilter = qTree.leftFilter;
		vector<vector<string>> rightFilter = qTree.rightFilter;
		PointCollection leftDataPoint = qTree.leftDataPoint;
		RectangleCollection leftDataRect = qTree.leftDataRect;
		PointCollection rightDataPoint = qTree.rightDataPoint;
		RectangleCollection rightDataRect = qTree.rightDataRect;

		if (leftDataPoint != NULL && leftDataRect == NULL) {
			PointCollection leftResult = materializeBranch(leftFilter, leftDataPoint);
			if (root[0] == "") {
				queryResult.setPointCollection(leftResult);
			}
		} else if (leftDataPoint == NULL && leftDataRect != NULL) {
			RectangleCollection leftResult = materializeBranch(leftFilter, leftDataRect);
			if (root[0] == "") {
				queryResult.setRectangleCollection(leftResult);
			}
		}

		return queryResult;
	}

	PointCollection materializeBranch (vector<vector<string>> filter, PointCollection data) {
		// initialize result
		PointCollection result;
		vector<Point> points = data.getNext(1);
		while (points) {
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

	RectangleCollection materializeBranch (vector<vector<string>> filter, RectangleCollection data) {
		// initialize result
		RectangleCollection result;
		vector<Rectangle> rects = data.getNext(1);
		while (rects) {
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

	PointPointCollection rangeJoin (PointCollection leftData, vector<vector<string>> filter, PointCollection rightData) {
		return NULL;
	}

	RectangleRectangleCollection rangeJoin (RectangleCollection leftData, vector<vector<string>> filter, RectangleCollection rightData) {
		return NULL;
	}

	PointRectangleCollection rangeJoin (PointCollection leftData, vector<vector<string>> filter, RectangleCollection rightData) {
		return NULL;
	}

	PointPointCollection knnJoin (vector<string> root, PointCollection leftData, vector<vector<string>> filter, PointCollection rightData) {
		return NULL;
	}

	RectangleRectangleCollection knnJoin (vector<string> root, RectangleCollection leftData, vector<vector<string>> filter, RectangleCollection rightData) {
		return NULL;
	}

	PointRectangleCollection knnJoin (vector<string> root, PointCollection leftData, vector<vector<string>> filter, RectangleCollection rightData) {
		return NULL;
	}

	PointPointCollection distanceJoin (PointCollection leftData, vector<vector<string>> filter, PointCollection rightData) {
		return NULL;
	}

	RectangleRectangleCollection distanceJoin (RectangleCollection leftData, vector<vector<string>> filter, RectangleCollection rightData) {
		return NULL;
	}

	PointRectangleCollection distanceJoin (PointCollection leftData, vector<vector<string>> filter, RectangleCollection rightData) {
		return NULL;
	}

};
