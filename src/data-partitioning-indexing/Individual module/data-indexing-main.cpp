#include "rtree-implementation.cpp"
#include <typeinfo>
class DataIndexingWrapper:public SpatialIndexInterface{
	
	
	public:
		
		PointSpatialIndexR P;
		RectangleSpatialIndexR R;
		
		void createIndex(PointCollection points){
			
			cout<<"R Tree create index point"<<endl;
			P.createIndex(points);
			
			
		}	
		void createIndex(RectangleCollection rects){
			
			
			cout<<"R Tree create index rectangle"<<endl;
			R.createIndex(rects);
		}
	
		PointCollection searchPoint(Rectangle r){
			
			
			cout<<"R Tree search point"<<endl;
			PointCollection p=P.searchPoint(r);
			return p;
				
		}
		RectangleCollection searchRectangle(Rectangle r){
			
			cout<<"R Tree search rect"<<endl;
			RectangleCollection rc = R.searchRectangle(r);
			return rc;
		}
		
		bool update(PointCollection p){
			
			cout<<"R Tree update index point"<<endl;
			bool r = P.update(p);
			return r;
		}
		bool update(RectangleCollection p){
			
			cout<<"R Tree update index rect"<<endl;
			bool r = R.update(p);
			return r;
		}
		
		bool deleteIndex(){
			
			cout<<"R Tree delete under construction"<<endl;
			return true;
		}
};

int main(){

	DataIndexingWrapper d;
	Point p(0,0);


	string line;
    	
	
	cout<<"Loading Point dataset "<<endl;
	// Loading point data
	float val = 0.0;
	int i = 0;
    Point p1(0,0);
	ifstream myfile2 ("sample.csv");
	vector<Point> collection;
	if(myfile2.is_open()){
		while(getline(myfile2,line)){
			stringstream ss(line);
			vector<float> vect;
			while (ss >> val)
   			{
        			vect.push_back(val);
					
        			if (ss.peek() == ',')
            				ss.ignore();
            	
    		}
    		Point p2(vect.at(0),vect.at(1));
    		p1=p2;
    		collection.push_back(p1);	
    		
		}

		
		
	}

	PointCollection pc(collection);

	

	d.createIndex(pc);

	Rectangle r(-5,-5,5,5);

	PointCollection result(collection);
	result = d.searchPoint(r);


	//////////////////////////////////////////////////////////////
	// Rectangles


	ifstream myfile ("rectangle.csv");

	cout<<"Loading Rectangle data"<<endl;

	val=0.0;
	i=0;
	Rectangle r1(0,0,0,0);
	std::vector<Rectangle> rectcollection;
	if(myfile.is_open()){
		while(getline(myfile,line)){
			stringstream ss(line);
			vector<float> vect;
			while (ss >> val)
   			{
        		vect.push_back(val);

        		if (ss.peek() == ',')
            		ss.ignore();
            	
    		}
    		
    		Rectangle r2(vect.at(0),vect.at(1),vect.at(2),vect.at(3));
    		r1=r2;
    		rectcollection.push_back(r1);	
    		
		}
	}

	RectangleCollection rclass(rectcollection);

	d.createIndex(rclass);

	//cout<<"Inserted "<<i<<" rectangles in R tree"<<endl;
	Rectangle rr(-156,19,-155,20);
	
	rclass = d.searchRectangle(rr);

	myfile.close();
	myfile2.close();
	

	return 0;
}
