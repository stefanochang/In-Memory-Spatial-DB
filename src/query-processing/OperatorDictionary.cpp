/*
 * OperatorDictionary.cpp
 *
 *  Created on: Mar 16, 2017
 *      Author: tejal
 */

#include <iostream>
#include <vector>
#include <string>

#include "../integration/query-processing.h"

using namespace std;

bool OperatorDictionary::applyFilterBy (Filter filterDetails, Point inputPoint) {
	bool isCriterionSatisfied = false;
	double compareVal = filterDetails.inputParams[0];

	double metricVal;
	if (filterDetails.inputParams.size()==5) {
		metricVal = PointOperations::getDistance(inputPoint,
				Rectangle(filterDetails.inputParams[1], filterDetails.inputParams[2],
								filterDetails.inputParams[3], filterDetails.inputParams[4]));
	}
	else {
		metricVal = PointOperations::getDistance(inputPoint,
				Point(filterDetails.inputParams[1],filterDetails.inputParams[2]));
	}
	if(filterDetails.filterType == FILTER_BY_DISTANCE_GT && metricVal > compareVal)
		isCriterionSatisfied = true;
	else if(filterDetails.filterType == FILTER_BY_DISTANCE_GE && metricVal >= compareVal)
		isCriterionSatisfied = true;
	else if(filterDetails.filterType == FILTER_BY_DISTANCE_LT && metricVal < compareVal)
		isCriterionSatisfied = true;
	else if(filterDetails.filterType == FILTER_BY_DISTANCE_LE && metricVal <= compareVal)
		isCriterionSatisfied = true;
	else if(filterDetails.filterType == FILTER_BY_DISTANCE_EQ && metricVal == compareVal)
		isCriterionSatisfied = true;
	return isCriterionSatisfied;
}

bool OperatorDictionary::applyFilterBy (Filter filterDetails, Rectangle inputRect) {
	bool isCriterionSatisfied = false;
	double compareVal = filterDetails.inputParams[0];

	if (filterDetails.filterType >= FILTER_BY_DISTANCE_LT && filterDetails.filterType <= FILTER_BY_DISTANCE_GE) {
		double metricVal;
		if (filterDetails.inputParams.size()==5) {
			metricVal = RectangleOperations::getDistance(inputRect,
					Rectangle(filterDetails.inputParams[1], filterDetails.inputParams[2],
									filterDetails.inputParams[3], filterDetails.inputParams[4]));
		}
		else {
			metricVal = PointOperations::getDistance(Point(filterDetails.inputParams[1],filterDetails.inputParams[2]),
					inputRect);
		}
		if(filterDetails.filterType == FILTER_BY_DISTANCE_GT && metricVal > compareVal)
			isCriterionSatisfied = true;
		else if(filterDetails.filterType == FILTER_BY_DISTANCE_GE && metricVal >= compareVal)
			isCriterionSatisfied = true;
		else if(filterDetails.filterType == FILTER_BY_DISTANCE_LT && metricVal < compareVal)
			isCriterionSatisfied = true;
		else if(filterDetails.filterType == FILTER_BY_DISTANCE_LE && metricVal <= compareVal)
			isCriterionSatisfied = true;
		else if(filterDetails.filterType == FILTER_BY_DISTANCE_EQ && metricVal == compareVal)
			isCriterionSatisfied = true;
	}
	else if (filterDetails.filterType >= FILTER_BY_AREA_LT && filterDetails.filterType <= FILTER_BY_AREA_GE) {
		double metricVal = RectangleOperations::getArea(inputRect);
		if(filterDetails.filterType == FILTER_BY_AREA_GT && metricVal > compareVal)
			isCriterionSatisfied = true;
		else if(filterDetails.filterType == FILTER_BY_AREA_GE && metricVal >= compareVal)
			isCriterionSatisfied = true;
		else if(filterDetails.filterType == FILTER_BY_AREA_LT && metricVal < compareVal)
			isCriterionSatisfied = true;
		else if(filterDetails.filterType == FILTER_BY_AREA_LE && metricVal <= compareVal)
			isCriterionSatisfied = true;
		else if(filterDetails.filterType == FILTER_BY_AREA_EQ && metricVal == compareVal)
			isCriterionSatisfied = true;
	}
	return isCriterionSatisfied;
}

bool OperatorDictionary::checkIfInRange(Filter rangeFilter, Point inputPoint){
	Rectangle rec(rangeFilter.inputParams[0], rangeFilter.inputParams[1],
			rangeFilter.inputParams[2], rangeFilter.inputParams[3]);
	return PointOperations::isWithin(inputPoint, rec) ||
				PointOperations::isOverlapping(inputPoint,rec) ||
						PointOperations::isIntersecting(inputPoint,rec);
}

bool OperatorDictionary::checkIfInRange(Filter rangeFilter, Rectangle inputRect){
	Rectangle rec(rangeFilter.inputParams[0], rangeFilter.inputParams[1],
				rangeFilter.inputParams[2], rangeFilter.inputParams[3]);
	return RectangleOperations::isOverlapping(inputRect,rec) ||
			RectangleOperations::isIntersecting(inputRect,rec) ||
			RectangleOperations::isWithin(inputRect,rec) ||
			RectangleOperations::isWithin(rec,inputRect);
}

bool OperatorDictionary::applyOperator (Filter filterDetails, Point inputPoint) {
	if (filterDetails.filterType == KNN ) {
		return false;
	}
	else if (filterDetails.filterType == OBJECTS_IN_RANGE ) {
		return false;
	}
	else {
		return applyFilterBy(filterDetails, inputPoint);
	}
}

bool OperatorDictionary::applyOperator (Filter filterDetails, Rectangle inputRect) {
	if (filterDetails.filterType == KNN ) {
		return false;
	}
	else if (filterDetails.filterType == OBJECTS_IN_RANGE ) {
		return false;
	}
	else {
		return applyFilterBy(filterDetails, inputRect);
	}
}
