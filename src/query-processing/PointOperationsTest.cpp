/*
 * PointOperationsTest.cpp
 *
 *  Created on: Apr 2, 2017
 *      Author: Nikhil Vementala
 */
#include <iostream>
#include "../integration/query-processing.h"
using namespace std;

bool pointOperationTests(){
	Point pt0();
	Point pt1(3,3);
	Point pt2(6,6);
	Point pt3(3,3);

	Rectangle rec0();
	Rectangle rec1(1,1,4,4);
	Rectangle rec2(3,3,9,9);
	Rectangle rec3(5,5,7,7);

	int result = -1;
	int expected = -1;

	result = PointOperations::isIntersecting(pt1,rec1);
	expected = 1;
	cout<< (result == expected ? "Test Case 1 passed\n" : "Test Case 1 failed\n");

	result = PointOperations::isIntersecting(pt1,rec2);
	expected = 1;
	cout<< (result == expected ? "Test Case 2 passed\n" : "Test Case 2 failed\n");

	result = PointOperations::isEqual(pt1,pt2);
	expected = 0;
	cout<< (result == expected ? "Test Case 3 passed\n" : "Test Case 3 failed\n");

	result = PointOperations::isEqual(pt1,pt3);
	expected = 1;
	cout<< (result == expected ? "Test Case 4 passed\n" : "Test Case 4 failed\n");

	result = PointOperations::isDisjoint(pt1,pt2);
	expected = 1;
	cout<< (result == expected ? "Test Case 5 passed\n" : "Test Case 5 failed\n");

	result = PointOperations::isDisjoint(pt1,pt3);
	expected = 0;
	cout<< (result == expected ? "Test Case 6 passed\n" : "Test Case 6 failed\n");

	result = PointOperations::isWithin(pt1,rec1);
	expected = 1;
	cout<< (result == expected ? "Test Case 7 passed\n" : "Test Case 7 failed\n");

	result = PointOperations::isWithin(pt1,rec2);
	expected = 0;
	cout<< (result == expected ? "Test Case 8 passed\n" : "Test Case 8 failed\n");

	result = PointOperations::isWithin(pt1,rec3);
	expected = 0;
	cout<< (result == expected ? "Test Case 9 passed\n" : "Test Case 9 failed\n");

	result = PointOperations::isOverlapping(pt1,rec1);
	expected = 1;
	cout<< (result == expected ? "Test Case 10 passed\n" : "Test Case 10 failed\n");

	result = PointOperations::isOverlapping(pt1,rec2);
	expected = 0;
	cout<< (result == expected ? "Test Case 11 passed\n" : "Test Case 11 failed\n");

	result = PointOperations::isOverlapping(pt1,rec3);
	expected = 0;
	cout<< (result == expected ? "Test Case 12 passed\n" : "Test Case 12 failed\n");

	result = PointOperations::isOverlapping(pt1,pt3);
	expected = 0;
	cout<< (result == expected ? "Test Case 13 passed\n" : "Test Case 13 failed\n");

	result = PointOperations::isOverlapping(pt1,pt2);
	expected = 0;
	cout<< (result == expected ? "Test Case 14 passed\n" : "Test Case 14 failed\n");


	Point pt4(0,5);
	Point pt5(0,5);
	Point pt6(0,9);
	Point pt7(5,5);

	result = PointOperations::getDistance(pt4,pt6);
	expected = 4;
	cout<< (result == expected ? "Test Case 15 passed\n" : "Test Case 15 failed\n");

	result = PointOperations::getDistance(pt4,pt5);
	expected = 0;
	cout<< (result == expected ? "Test Case 16 passed\n" : "Test Case 16 failed\n");

	result = PointOperations::getDistance(pt4,pt7);
	expected = 5;
	cout<< (result == expected ? "Test Case 17 passed\n" : "Test Case 17 failed\n");


	Rectangle rec4(6,6,10,12);
	result = PointOperations::getDistance(pt7,rec4);
	expected = 5;
	cout<< (result == expected ? "Test Case 18 passed\n" : "Test Case 18 failed\n");

	return true;
}

