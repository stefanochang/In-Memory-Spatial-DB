#include "query-tree.h"

QueryTree::setLeftPoints(PointCollection leftPoints) {
	this->leftDataPoint = leftPoints;
}

QueryTree::setLeftRectangles(RectangleCollection leftRects) {
	this->leftDataRect = leftRects;
}

QueryTree::setLeftIndexedObject(SpatialIndexInterface leftIndexedObject) {
	this->leftIndexedObject = leftIndexedObject;
}

QueryTree::setLeftFilter(vector<string> leftFilter) {
	this->leftFilter = leftFilter;
}

QueryTree::setRoot(vector<string> root) {
	this->root = root;
}

QueryTree::setRightPoints(PointCollection rightPoints) {
	this->rightDataPoint = rightPoints;
}

QueryTree::setRightRectangles(RectangleCollection rightRects) {
	this->rightDataRect = rightRects;
}

QueryTree::setRightIndexedObject(SpatialIndexInterface rightIndexedObject) {
	this->rightIndexedObject = rightIndexedObject;
}

QueryTree::setRightFilter(vector<string> rightFilter) {
	this->rightFilter = rightFilter;
}