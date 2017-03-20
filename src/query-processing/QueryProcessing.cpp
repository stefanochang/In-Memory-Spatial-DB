/*
 * QueryProcessing.cpp
 *
 *  Created on: Mar 16, 2017
 *      Author: tejal
 */

#include <iostream>
#include <vector>
#include "QueryTree.h"
#include "Geometry.h"
#include "GeometryCollection.h"
#include "OperatorDictionary.h"

using namespace std;

class QueryProcessing {

private:
	OperatorDictionary opDict;

	void processQuery (QueryTree qTree) {
		string root = qTree->root;
		vector<string> leftFilter = qTree->leftFilter;
		vector<string> rightFilter = qTree->rightFilter;
		GeometryCollection leftData = qTree->leftData;
		GeometryCollection rightData = qTree->rightData;

	}

	vector<Geometry> materializeBranch (vector<vector<string>> filter) {
		// initialize result
		vector<Geometry> result;
		// get function for next operator to execute
		vector<Geometry> (*pointerToGetNext)(vector<vector<string>> filter);
		pointerToGetNext = opDict.getPointerToGetNext(filter[0]);
		// get output from first level of filter and add output to result set

	}

};
