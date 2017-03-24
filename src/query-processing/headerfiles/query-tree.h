#include <string>
#include "geometry.h"

class QueryTree {
public:
	vector<string> root;
	vector<vector<string>> leftFilter;
    GeometryCollection leftData;
    vector<vector<string>> rightFilter;
    GeometryCollection rightData;
};
