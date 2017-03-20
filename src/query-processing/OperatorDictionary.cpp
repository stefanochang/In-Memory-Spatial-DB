/*
 * OperatorExec.cpp
 *
 *  Created on: Mar 16, 2017
 *      Author: tejal
 */

#include <iostream>
#include <vector>
#include "Geometry.h"

typedef vector<Geometry> (*FunctionPointerType)(vector<vector<string>> filter, int position);

class OperatorDictionary {

public:
	/*
	 * This function will return the pointer to the getNext function
	 * of the operator passed as input to it
	 */
	FunctionPointerType getPointerToGetNext (string operatorName) {
		// switch case logic
	}

};

