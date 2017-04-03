//============================================================================
// Name        : init.cpp
// Author      : Nikhil Vementala
// Version     :
// Copyright   : May Copy
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <boost/version.hpp>

#include "OperationTestCases.h"

using namespace std;

int main() {
	cout << "Query Processing Module\n\n";
	cout << "Boost Library Version : " << BOOST_LIB_VERSION << endl;

	cout << "\n ***** Testing Point Operations ***** \n";
	pointOperationTests();

	cout << "\n ***** Testing Rectangle Operations ***** \n";
	rectOperationTests();

	cout << "\n ***** Testing Query Processing methods ***** \n";
	queryProcessingTests();

	cout << "\n ***** Program Ended ***** \n";
	return 0;
}

//cout << ( pointOperationTests() == 0 ? "SUCCESS\n" : "FAILED\n" );
//cout << ( rectOperationTests() == 0 ? "SUCCESS\n" : "FAILED\n" );
//cout << ( queryProcessingTests() == 0 ? "SUCCESS\n" : "FAILED\n" );
