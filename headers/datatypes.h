

typedef struct point{
	float x;
	float y;
}point;

typedef struct rectangle{
	float top_x;
	float top_y;
	float bottom_x;
	float bottom_y;
}rectangle;

typedef struct pointpoint{
	point point1;
	point point2;
}pointpoint;

typedef struct pointrectangle{
	point point1;
	rectangle rec;
}pointrectangle;

typedef struct recrec{
	rectangle rec1;
	rectangle rec2;
}rectanglerectangle;

typedef union geometry{
	point *pnt;
	rectangle *rec;
	pointrectangle *prec;
	rectanglerectangle *recrec;
}geometry;

typedef struct record{
	int id;
	geometry geom;
	struct record *next;
	struct record *prev;
}record;
