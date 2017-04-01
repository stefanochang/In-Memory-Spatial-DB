#include "query-tree.h"

void QueryTree::setLeftPoints(PointCollection leftPoints) {
	this->leftDataPoint = leftPoints;
}

void QueryTree::setLeftRectangles(RectangleCollection leftRects) {
	this->leftDataRect = leftRects;
}

void QueryTree::setLeftIndexedObject(SpatialIndexInterface leftIndexedObject) {
	this->leftIndexedObject = leftIndexedObject;
}

void QueryTree::setLeftFilter(vector<string> leftFilter) {
	this->leftFilter = leftFilter;
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

void QueryTree::setRightIndexedObject(SpatialIndexInterface rightIndexedObject) {
	this->rightIndexedObject = rightIndexedObject;
}

void QueryTree::setRightFilter(vector<string> rightFilter) {
	this->rightFilter = rightFilter;
}