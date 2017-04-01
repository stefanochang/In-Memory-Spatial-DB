

struct point{
	float x;
	float y;
};
typedef struct point point;
struct rectangle{
	float top_x;
	float top_y;
	float bottom_x;
	float bottom_y;
};
typedef struct rectangle rectangle;

struct pointpoint{
	point point1;
	point point2;
};
typedef struct pointpoint pointpoint;

struct pointrectangle{
	point point1;
	rectangle rec;
};
typedef struct pointrectangle pointrectangle;

struct rectanglerectangle{
	rectangle rec1;
	rectangle rec2;
};
typedef struct rectanglerectangle rectanglerectangle;

union geometry{
	point *pnt;
	rectangle *rec;
	pointpoint *pntpnt;
	pointrectangle *pntrec;
	rectanglerectangle *recrec;
};
typedef union geometry geometry;

struct record{
	int id;
	bool isDeleted;
	int inDegree;
	geometry *geom;
	struct record *next;
	struct record *prev;
};
typedef struct record record;
