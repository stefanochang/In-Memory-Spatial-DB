#include <iostream>
#include <string>
#include <map>
#include <vector>

#include "../integration/query-processing.h"

using namespace std;

class RectangleOperationsTest {
public:
	RectangleOperationsTest() {

	}
	RectangleOperationsTest(Rectangle rec1, Rectangle rec2) {

	}
	static void isIntersectingTest(Rectangle rec1, Rectangle rec2, bool expectedOutput) {
		//bool expectedOutput;
		bool actualOutput;
		actualOutput = RectangleOperations::isIntersecting(rec1, rec2);
        //actualOutput = isIntersecting(rec1, rec2);

        //cout << actualOutput<<endl;
		if (expectedOutput == actualOutput) {
			cout << "Working Fine"<<endl;
		} else {
			cout << "Not Working"<<endl;
		}

	}
	static void isEqualTest(Rectangle rec1, Rectangle rec2, bool expectedOutput) {
		//bool expectedOutput;
		bool actualOutput;
		actualOutput = RectangleOperations::isEqual(rec1, rec2);
        //actualOutput = isEqual(rec1, rec2);

        //cout << actualOutput<<endl;
		if (expectedOutput == actualOutput) {
			cout << "Working Fine"<<endl;
		} else {
			cout << "Not Working"<<endl;
		}

	}
	static void isDisjointTest(Rectangle rec1, Rectangle rec2, bool expectedOutput) {
		//bool expectedOutput;
		bool actualOutput;
		actualOutput = RectangleOperations::isDisjoint(rec1, rec2);
        //actualOutput = isDisjoint(rec1, rec2);

        //cout << actualOutput<<endl;
		if (expectedOutput == actualOutput) {
			cout << "Working Fine"<<endl;
		} else {
			cout << "Not Working"<<endl;
		}

	}
	static void isWithinTest(Rectangle rec1, Rectangle rec2, bool expectedOutput) {
		//bool expectedOutput;
		bool actualOutput;
        actualOutput = RectangleOperations::isWithin(rec1, rec2);

        //actualOutput = isWithin(rec1, rec2);
        //cout << actualOutput<<endl;

		if (expectedOutput == actualOutput) {
			cout << "Working Fine"<<endl;
		} else {
			cout << "Not Working"<<endl;
		}

	}

	static void isOverlappingTest(Rectangle rec1, Rectangle rec2, bool expectedOutput) {
		//bool expectedOutput;
		bool actualOutput;
		actualOutput = RectangleOperations::isOverlapping(rec1, rec2);
        //actualOutput = isOverlapping(rec1, rec2);
        //cout << actualOutput<<endl;


        if (expectedOutput == actualOutput) {
			cout << "Working Fine"<<endl;
		} else {
			cout << "Not Working"<<endl;
		}

	}
	static void getDistanceTest(Rectangle rec1, Rectangle rec2, bool expectedOutput) {
		//float expectedOutput;
		float actualOutput;
		actualOutput = RectangleOperations::getDistance(rec1, rec2);
        //actualOutput = getDistance(rec1, rec2);
        cout << actualOutput<<endl;

        if (expectedOutput == actualOutput) {
			cout << "Working Fine"<<endl;
		} else {
			cout << "Not Working"<<endl;
		}

	}
    static void getAreaTest(Rectangle rec1, double expectedOutput) {
        //float expectedOutput;
        double actualOutput;
        actualOutput = RectangleOperations::getArea(rec1);
        //actualOutput = getArea(rec1);
        //cout << actualOutput<<endl;

        if (expectedOutput == actualOutput) {
            cout << "Working Fine"<<endl;
        } else {
            cout << "Not Working"<<endl;
        }

    }

};
int rectOperationTests() {
	Rectangle rec1 (0, 0, 3, 1);
	Rectangle rec2 (2, 0, 5, 2);
    Rectangle rec3 (0, 0, 1, 3);
    Rectangle rec4 (0, 0, 2, 2);
    Rectangle rec5 (5, 0, 7, 2);

    RectangleOperationsTest::isIntersectingTest(rec1, rec1, true);
    RectangleOperationsTest::isIntersectingTest(rec1, rec2, true);
    RectangleOperationsTest::isEqualTest(rec1, rec1,true);
    RectangleOperationsTest::isEqualTest(rec1, rec2,false);
    RectangleOperationsTest::isDisjointTest(rec1, rec1, false);
    RectangleOperationsTest::isWithinTest(rec1, rec1, true);
    RectangleOperationsTest::isWithinTest(rec1, rec2, false);
    RectangleOperationsTest::isOverlappingTest(rec1, rec2, true);
    RectangleOperationsTest::isOverlappingTest(rec1, rec1, true);
    RectangleOperationsTest::getDistanceTest(rec1, rec1, 0);
    RectangleOperationsTest::getDistanceTest(rec2, rec5, 5);
    RectangleOperationsTest::getAreaTest(rec4, 4);
	return 0;
}
