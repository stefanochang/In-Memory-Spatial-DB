#include "query-tree.h"

QueryTree::QueryTree(PointCollection leftPoints, vector<string> leftFilter) {
	this->leftDataPoint = leftPoints;
	this->leftFilter = leftFilter;
}

QueryTree::QueryTree(RectangleCollection leftRects, vector<string> leftFilter) {
	this->leftDataRect = leftRects;
	this->leftFilter = leftFilter;
}

QueryTree::QueryTree(SpatialIndexInterface leftIndexedObject, vector<string> leftFilter) {
	this->leftIndexedObject = leftIndexedObject;
	this->leftFilter = leftFilter;
}

QueryTree::QueryTree(PointCollection leftPoints, vector<string> leftFilter, vector<string> root) {
	this->leftDataPoint = leftPoints;
	this->leftFilter = leftFilter;
	this->root = root;
}

QueryTree::QueryTree(RectangleCollection leftRects, vector<string> leftFilter, vector<string> root) {
	this->leftDataRect = leftRects;
	this->leftFilter = leftFilter;
	this->root = root;
}

QueryTree::QueryTree(SpatialIndexInterface leftIndexedObject, vector<string> leftFilter, vector<string> root) {
	this->leftIndexedObject = leftIndexedObject;
	this->leftFilter = leftFilter;
	this->root = root;
}

QueryTree::QueryTree(PointCollection leftPoints, vector<string> leftFilter, vector<string> root, 
	PointCollection rightPoints,  vector<string> rightFilter) {
	this->leftDataPoint = leftPoints;
	this->leftFilter = leftFilter;
	this->root = root;
	this->rightDataPoint = rightPoints;
	this->rightFilter = rightFilter;
}

QueryTree::QueryTree(RectangleCollection leftRects, vector<string> leftFilter, vector<string> root, 
	PointCollection rightPoints,  vector<string> rightFilter) {
	this->leftDataRect = leftRects;
	this->leftFilter = leftFilter;
	this->root = root;
	this->rightDataPoint = rightPoints;
	this->rightFilter = rightFilter;
}

QueryTree::QueryTree(SpatialIndexInterface leftIndexedObject, vector<string> leftFilter, vector<string> root, 
	PointCollection rightPoints,  vector<string> rightFilter) {
	this->leftIndexedObject = leftIndexedObject;
	this->leftFilter = leftFilter;
	this->root = root;
	this->rightDataPoint = rightPoints;
	this->rightFilter = rightFilter;
}

QueryTree::QueryTree(PointCollection leftPoints, vector<string> leftFilter, vector<string> root, 
	RectangleCollection rightRects,  vector<string> rightFilter) {
	this->leftDataPoint = leftPoints;
	this->leftFilter = leftFilter;
	this->root = root;
	this->rightDataRect = rightRects;
	this->rightFilter = rightFilter;
}

QueryTree::QueryTree(RectangleCollection leftRects, vector<string> leftFilter, vector<string> root, 
	RectangleCollection rightRects,  vector<string> rightFilter) {
	this->leftDataRect = leftRects;
	this->leftFilter = leftFilter;
	this->root = root;
	this->rightDataRect = rightRects;
	this->rightFilter = rightFilter;
}

QueryTree::QueryTree(SpatialIndexInterface leftIndexedObject, vector<string> leftFilter, vector<string> root, 
	RectangleCollection rightRects,  vector<string> rightFilter) {
	this->leftIndexedObject = leftIndexedObject;
	this->leftFilter = leftFilter;
	this->root = root;
	this->rightDataRect = rightRects;
	this->rightFilter = rightFilter;
}

QueryTree::QueryTree(SpatialIndexInterface leftIndexedObject, vector<string> leftFilter, vector<string> root, 
	SpatialIndexInterface rightIndexedObject,  vector<string> rightFilter) {
	this->leftIndexedObject = leftIndexedObject;
	this->leftFilter = leftFilter;
	this->root = root;
	this->rightIndexedObject = rightIndexedObject;
	this->rightFilter = rightFilter;
}