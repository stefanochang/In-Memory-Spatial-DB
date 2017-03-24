#include "query-tree.h"

class QueryResult {
    int resultType;
    PointCollection pointCollection;
    RectangleCollection rectangleCollection;
    PointPointCollection pointPointCollection;
    RectangleRectangleCollection rectangleRectangleCollection;
    PointRectangleCollection pointRectangleCollection;
    bool status;    

public:
	QueryResult(int, PointCollection);
	QueryResult(int, RectangleCollection);
	QueryResult(int, PointPointCollection);
	QueryResult(int, RectangleRectangleCollection);
	QueryResult(int, PointRectangleCollection);
	QueryResult(int, bool);
	QueryResult();

	const PointCollection& getPointCollection() const {
		return pointCollection;
	}

	void setPointCollection(const PointCollection& pointCollection) {
		this->pointCollection = pointCollection;
	}

	const PointPointCollection& getPointPointCollection() const {
		return pointPointCollection;
	}

	void setPointPointCollection(
			const PointPointCollection& pointPointCollection) {
		this->pointPointCollection = pointPointCollection;
	}

	const PointRectangleCollection& getPointRectangleCollection() const {
		return pointRectangleCollection;
	}

	void setPointRectangleCollection(
			const PointRectangleCollection& pointRectangleCollection) {
		this->pointRectangleCollection = pointRectangleCollection;
	}

	const RectangleCollection& getRectangleCollection() const {
		return rectangleCollection;
	}

	void setRectangleCollection(
			const RectangleCollection& rectangleCollection) {
		this->rectangleCollection = rectangleCollection;
	}

	const RectangleRectangleCollection& getRectangleRectangleCollection() const {
		return rectangleRectangleCollection;
	}

	void setRectangleRectangleCollection(
			const RectangleRectangleCollection& rectangleRectangleCollection) {
		this->rectangleRectangleCollection = rectangleRectangleCollection;
	}

	int getResultType() const {
		return resultType;
	}

	void setResultType(int resultType) {
		this->resultType = resultType;
	}

	bool isStatus() const {
		return status;
	}

	void setStatus(bool status) {
		this->status = status;
	}
};

QueryResult processQuery(QueryTree);
