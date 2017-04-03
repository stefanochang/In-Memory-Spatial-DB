/*
 * QueryResult.cpp
 *
 *  Created on: Mar 31, 2017
 *      Author: vnikhil
 */

#include "../integration/query-processing.h"

QueryResult::QueryResult() {

}

const PointCollection& QueryResult::getPointCollection() {
	return pointCollection;
}

void QueryResult::setPointCollection(const PointCollection& pointCollection) {
	this->pointCollection = pointCollection;
}

const PointPointCollection& QueryResult::getPointPointCollection() {
	return pointPointCollection;
}

void QueryResult::setPointPointCollection(
		const PointPointCollection& pointPointCollection) {
	this->pointPointCollection = pointPointCollection;
}

const PointRectangleCollection& QueryResult::getPointRectangleCollection() {
	return pointRectangleCollection;
}

void QueryResult::setPointRectangleCollection(
		const PointRectangleCollection& pointRectangleCollection) {
	this->pointRectangleCollection = pointRectangleCollection;
}

const RectangleCollection& QueryResult::getRectangleCollection() {
	return rectangleCollection;
}

void QueryResult::setRectangleCollection(
		const RectangleCollection& rectangleCollection) {
	this->rectangleCollection = rectangleCollection;
}

const RectangleRectangleCollection& QueryResult::getRectangleRectangleCollection() {
	return rectangleRectangleCollection;
}

void QueryResult::setRectangleRectangleCollection(
		const RectangleRectangleCollection& rectangleRectangleCollection) {
	this->rectangleRectangleCollection = rectangleRectangleCollection;
}

int QueryResult::getResultType() {
	return resultType;
}

void QueryResult::setResultType(int resultType) {
	this->resultType = resultType;
}

bool QueryResult::isStatus() {
	return status;
}

void QueryResult::setStatus(bool status) {
	this->status = status;
}
