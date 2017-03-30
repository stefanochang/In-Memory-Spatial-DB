/*
 * OperatorExec.cpp
 *
 *  Created on: Mar 16, 2017
 *      Author: tejal
 */

#include <iostream>
#include <vector>
#include "geometry.h"
#include "PointOperations.cpp"

using namespace std;

class OperatorDictionary {

public:

	PointOperations po;

	bool applyFilterBy (vector<string> filterDetails, Point inputPoint) {
		bool isCriterionSatisfied = false;
		float compareVal = stod(filterDetails[3]);
		string operatorName = filterDetails[2];

		if (filterDetails[1] == "distance") {
			float metricVal = po.getDistance(inputPoint,
					Point(stod(filterDetails[4]),stod(filterDetails[5])));
			if(operatorName == "gt" && metricVal > compareVal)
				isCriterionSatisfied = true;
			else if(operatorName == "ge" && metricVal >= compareVal)
				isCriterionSatisfied = true;
			else if(operatorName == "lt" && metricVal < compareVal)
				isCriterionSatisfied = true;
			else if(operatorName == "le"&& metricVal <= compareVal)
				isCriterionSatisfied = true;
			else if(operatorName == "eq" && metricVal == compareVal)
				isCriterionSatisfied = true;
		}
		return isCriterionSatisfied;
	}

	bool applyFilterBy (vector<string> filterDetails, Rectangle inputRect) {
		bool isCriterionSatisfied = false;
		float compareVal = stod(filterDetails[3]);
		string operatorName = filterDetails[2];

		if (filterDetails[1] == "distance") {
			float metricVal = po.getDistance(Point(stod(filterDetails[4]),stod(filterDetails[5])), inputRect);
			if(operatorName == "gt" && metricVal > compareVal)
				isCriterionSatisfied = true;
			else if(operatorName == "ge" && metricVal >= compareVal)
				isCriterionSatisfied = true;
			else if(operatorName == "lt" && metricVal < compareVal)
				isCriterionSatisfied = true;
			else if(operatorName == "le"&& metricVal <= compareVal)
				isCriterionSatisfied = true;
			else if(operatorName == "eq" && metricVal == compareVal)
				isCriterionSatisfied = true;
		}
		return isCriterionSatisfied;
	}

	bool applyOperator (vector<string> filterDetails, Point inputPoint) {
		if (filterDetails[0] == "filterBy") {
			return applyFilterBy(filterDetails, inputPoint);
		}
		else {
			return false;
		}
	}

	bool applyOperator (vector<string> filterDetails, Rectangle inputRect) {
		if (filterDetails[0] == "filterBy") {
			return applyFilterBy(filterDetails, inputRect);
		}
		else {
			return false;
		}
	}
};
