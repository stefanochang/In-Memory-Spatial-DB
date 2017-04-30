#include "../integration/query-processing.h"

Filter::Filter() {

}

Filter::Filter(char filterType, vector<float> inputParams) {
	this->filterType = filterType;
	this->inputParams = inputParams;
}

QueryTree::QueryTree() {

	this->rootType = NO_JOIN;
	this->rootParam = 0.0;
	this->lIndexType = NO_INDEX;
	this->rIndexType = NO_INDEX;

	vector<Filter> filterNull;
	this->leftBranch = filterNull;
	this->rightBranch = filterNull;

	PointCollection ptcolNull;
	this->leftDataPoint = ptcolNull;
	this->rightDataPoint = ptcolNull;

	RectangleCollection retcolNull;
	this->leftDataRect = retcolNull;
	this->rightDataRect = retcolNull;
}

void QueryTree::setLeftPoints(PointCollection leftPoints) {
	this->leftDataPoint = leftPoints;
}

void QueryTree::setLeftRectangles(RectangleCollection leftRects) {
	this->leftDataRect = leftRects;
}

/*void QueryTree::setLeftIndexedObject(SpatialIndexInterface leftIndexedObject) {
	this->leftIndexedObject = leftIndexedObject;
}*/

void QueryTree::setLeftFilter(vector<Filter> leftBranch) {
	this->leftBranch = leftBranch;
}

void QueryTree::setRootType(char rootType) {
	this->rootType = rootType;
}

void QueryTree::setRootParam(float rootParam) {
	this->rootParam = rootParam;
}

void QueryTree::setLIndexType(char lIndexType) {
	this->lIndexType = lIndexType;
}

void QueryTree::setRIndexType(char rIndexType) {
	this->rIndexType = rIndexType;
}

void QueryTree::setRightPoints(PointCollection rightPoints) {
	this->rightDataPoint = rightPoints;
}

void QueryTree::setRightRectangles(RectangleCollection rightRects) {
	this->rightDataRect = rightRects;
}

const vector<Filter>& QueryTree::getLeftBranch() const {
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

const vector<Filter>& QueryTree::getRightBranch() const {
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

const char& QueryTree::getRootType() const {
	return rootType;
}

const float& QueryTree::getRootParam() const {
	return rootParam;
}

const char& QueryTree::getLIndexType() const {
	return lIndexType;
}

const char& QueryTree::getRIndexType() const {
	return rIndexType;
}

/*void QueryTree::setRightIndexedObject(SpatialIndexInterface rightIndexedObject) {
	this->rightIndexedObject = rightIndexedObject;
}*/

void QueryTree::setRightFilter(vector<Filter> rightBranch) {
	this->rightBranch = rightBranch;
}
