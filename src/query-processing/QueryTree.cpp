#include "../integration/query-processing.h"

void QueryTree::setLeftPoints(PointCollection leftPoints) {
	this->leftDataPoint = leftPoints;
}

void QueryTree::setLeftRectangles(RectangleCollection leftRects) {
	this->leftDataRect = leftRects;
}

/*void QueryTree::setLeftIndexedObject(SpatialIndexInterface leftIndexedObject) {
	this->leftIndexedObject = leftIndexedObject;
}*/

void QueryTree::setLeftFilter(vector<vector<string>> leftBranch) {
	this->leftBranch = leftBranch;
}

void QueryTree::setRoot(vector<string> root) {
	this->root = root;
}

void QueryTree::setRightPoints(PointCollection rightPoints) {
	this->rightDataPoint = rightPoints;
}

void QueryTree::setRightRectangles(RectangleCollection rightRects) {
	this->rightDataRect = rightRects;
}

const vector<vector<string> >& QueryTree::getLeftBranch() const {
	return leftBranch;
}

const PointCollection& QueryTree::getLeftDataPoint() const {
	return leftDataPoint;
}

const RectangleCollection& QueryTree::getLeftDataRect() const {
	return leftDataRect;
}

/*SpatialIndexInterface QueryTree::getLeftIndexedObject() const {
	return leftIndexedObject;
}*/

const vector<vector<string> >& QueryTree::getRightBranch() const {
	return rightBranch;
}

const PointCollection& QueryTree::getRightDataPoint() const {
	return rightDataPoint;
}

const RectangleCollection& QueryTree::getRightDataRect() const {
	return rightDataRect;
}

/*SpatialIndexInterface QueryTree::getRightIndexedObject() const {
	return rightIndexedObject;
}*/

const vector<string>& QueryTree::getRoot() const {
	return root;
}

/*void QueryTree::setRightIndexedObject(SpatialIndexInterface rightIndexedObject) {
	this->rightIndexedObject = rightIndexedObject;
}*/

void QueryTree::setRightFilter(vector<vector<string>> rightBranch) {
	this->rightBranch = rightBranch;
}
