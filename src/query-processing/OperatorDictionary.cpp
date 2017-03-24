/*
 * OperatorExec.cpp
 *
 *  Created on: Mar 16, 2017
 *      Author: tejal
 */

#include <iostream>
#include <vector>
#include "headerfiles/geometry.h"

typedef GeometryCollection (*FunctionPointerType)(vector<vector<string>> filter, int opPosition, GeometryCollection data);

class Operator {

public:
	GeometryCollection getNext(vector<vector<string>> filter, int opPosition, GeometryCollection data) {
		GeometryCollection gc;
		return gc;
	}

};

class OperatorDictionary {
public:
	Operator* getPointerToGetNext (string operatorName);
};

class KNN {

private:
	OperatorDictionary* opDict;

public:

	GeometryCollection getNext(vector<vector<string>> filter, int opPosition, GeometryCollection data) {
		GeometryCollection result, input;
		//vector<Geometry> (*pointerToGetNext)(vector<vector<string>> filter);
		Operator* op = opDict->getPointerToGetNext(filter[opPosition][0]);
		if (opPosition==0) {
			input = data.getNext(1);
		}
		else {
			input = op->getNext(filter, opPosition-1, data);
		}
		while (!input.isEmpty()) {
			for (int i=0;i<input.size();i++) {
				Geometry geo = input.get(i);
				if (true) {
					result.insert(geo);
				}
			}
			if (opPosition==0) {
				input = data.getNext(1);
			}
			else {
				input = op->getNext(filter, opPosition-1, data);
			}
		}
		return result;
	}

};

class Range {

private:
	OperatorDictionary* opDict;

public:

	GeometryCollection getNext(vector<vector<string>> filter, int opPosition, GeometryCollection data) {
		GeometryCollection result, input;
		//vector<Geometry> (*pointerToGetNext)(vector<vector<string>> filter);
		Operator* op = opDict->getPointerToGetNext(filter[opPosition][0]);
		if (opPosition==0) {
			input = data.getNext(1);
		}
		else {
			input = op->getNext(filter, opPosition-1, data);
		}
		while (!input.isEmpty()) {
			for (int i=0;i<input.size();i++) {
				Geometry geo = input.get(i);
				if (true) {
					result.insert(geo);
				}
			}
			if (opPosition==0) {
				input = data.getNext(1);
			}
			else {
				input = op->getNext(filter, opPosition-1, data);
			}
		}
		return result;
	}

};

class FilterBy : Operator{

private:
	OperatorDictionary* opDict;

public:

	GeometryCollection getNext(vector<vector<string>> filter, int opPosition, GeometryCollection data) {
		float compareVal = stod(filter[opPosition+1][3]);
		string operatorName = filter[opPosition+1][2];

		GeometryCollection result, input;
		//FunctionPointerType (*pointerToGetNext)(vector<vector<string>> filter);
		Operator* op = opDict->getPointerToGetNext(filter[opPosition][0]);
		if (opPosition==0) {
			input = data.getNext(1);
		}
		else {
			input = op->getNext(filter, opPosition-1, data);
		}
		while (!input.isEmpty()) {
			for (int i=0;i<input.size();i++) {
				Geometry geo = input.get(i);
				float metricVal = 0; // get area value here
				if(operatorName == "gt" && metricVal > compareVal)
					result.insert(geo);
				else if(operatorName == "ge" && metricVal >= compareVal)
					result.insert(geo);
				else if(operatorName == "lt" && metricVal < compareVal)
					result.insert(geo);
				else if(operatorName == "le"&& metricVal <= compareVal)
					result.insert(geo);
				else if(operatorName == "eq" && metricVal == compareVal)
					result.insert(geo);
			}
			if (opPosition==0) {
				input = data.getNext(1);
			}
			else {
				input = op->getNext(filter, opPosition-1, data);
			}
		}
		return result;
	}

};

inline Operator* OperatorDictionary::getPointerToGetNext (string operatorName) {
	// switch case logic
	if (operatorName == "filterBy"){
		Operator* fb = (Operator*) new FilterBy();
		return fb;
	}
	else {
		Operator* fb =(Operator*) new FilterBy();
		return fb;
	}
}

