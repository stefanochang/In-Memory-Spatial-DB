int loadData(string dbName, string tableName, int geomtype, string filepath, int collectionStruct)
{
	FILE *fp;
	float x, y;
	geometry *g;
	point *pnt;
	list l;
	fp = fopen(filepath.c_str(), "r");
	if(fp == NULL)
	{
		return 0;
	}
	while(fscanf(fp, "%f,%f\n", &x, &y) == 2)
	{
		printf("x:%f    y:%f\n",x,y);
		g = (geometry *)malloc(sizeof(geometry));
		pnt = (point *)malloc(sizeof(point));
		g->pnt = pnt;
		l.appendLast(g);
	}
	
	return 1;
}
