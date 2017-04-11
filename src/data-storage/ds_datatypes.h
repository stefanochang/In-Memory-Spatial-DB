

struct ds_point{
	int id;
	float x;
	float y;
};
typedef struct ds_point ds_point;

struct ds_rectangle{
	int id;
	float top_x;
	float top_y;
	float bottom_x;
	float bottom_y;
};
typedef struct ds_rectangle ds_rectangle;

struct ds_pointpoint{
	int id;
	ds_point point1;
	ds_point point2;
};
typedef struct ds_pointpoint ds_pointpoint;

struct ds_pointrectangle{
	int id;
	ds_point point;
	ds_rectangle rec;
};
typedef struct ds_pointrectangle ds_pointrectangle;

struct ds_rectanglerectangle{
	ds_rectangle rec1;
	ds_rectangle rec2;
};
typedef struct ds_rectanglerectangle ds_rectanglerectangle;
