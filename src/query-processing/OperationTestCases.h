/*
 * PointOperationsTest.h
 *
 *  Created on: Apr 3, 2017
 *      Author: hduser
 */

#ifndef QUERY_PROCESSING_OPERATIONTESTCASES_H_
#define QUERY_PROCESSING_OPERATIONTESTCASES_H_

#include <iostream>
#include <boost/version.hpp>
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/geometries/box.hpp>
#include <boost/foreach.hpp>

#include "../integration/query-processing.h"

using namespace std;

bool pointOperationTests();
int pointOperationTestsDummy();

bool rectOperationTests();

bool queryProcessingTests();

#endif /* QUERY_PROCESSING_OPERATIONTESTCASES_H_ */
