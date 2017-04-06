

struct ds_point{
	float x;
	float y;
};
typedef struct ds_point ds_point;
struct ds_rectangle{
	float top_x;
	float top_y;
	float bottom_x;
	float bottom_y;
};
typedef struct ds_rectangle ds_rectangle;

struct ds_pointpoint{
	ds_point point1;
	ds_point point2;
};
typedef struct ds_pointpoint ds_pointpoint;

struct ds_pointrectangle{
	ds_point point1;
	ds_rectangle rec;
};
typedef struct ds_pointrectangle ds_pointrectangle;

struct ds_rectanglerectangle{
	ds_rectangle rec1;
	ds_rectangle rec2;
};
typedef struct ds_rectanglerectangle ds_rectanglerectangle;

union ds_geometry{
	ds_point *pnt;
	ds_rectangle *rec;
	ds_pointpoint *pntpnt;
	ds_pointrectangle *pntrec;
	ds_rectanglerectangle *recrec;
};
typedef union ds_geometry ds_geometry;

struct ds_record{
	int id;
	bool isDeleted;
	int inDegree;
	ds_geometry *geom;
	struct ds_record *next;
	struct ds_record *prev;
};
typedef struct ds_record ds_record;
