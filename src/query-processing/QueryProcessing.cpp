/*
 * QueryProcessing.cpp
 *
 *  Created on: Mar 16, 2017
 *      Author: tejal
 */

#include <iostream>
#include <vector>
#include "QueryTree.h"
using namespace std;

class QueryProcessing {

	void processQuery (QueryTree qTree) {
		string root = qTree->root;
		vector<string> leftFilter = qTree->leftFilter;
		vector<string> rightFilter = qTree->rightFilter;
		//GeometryCollection leftData = qTree->leftData;
		//GeometryCollection rightData = qTree->rightData;

	}

	vector materializeBranch (vector<string> filter) {

	}

};
