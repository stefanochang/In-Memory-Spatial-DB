#include "rtree-implementation.cpp"
#include <typeinfo>

class DataIndexingWrapper:public SpatialIndexInterface{
	
	
	public:
		
		PointDataIndex P;
		RectangleDataIndex R;
		
		void createIndex(PointCollection points){
			
			cout<<"R Tree create index point"<<endl;
			P.createIndex(points);
			
			
		}	
		void createIndex(RectangleCollection rects){
			
			
			cout<<"R Tree create index rectangle"<<endl;
			R.createIndex(rects);
		}
	
		PointCollection searchPoint(Rectangle r,PointCollection *dummy){
			
			
			cout<<"R Tree search point"<<endl;
			PointCollection p=P.searchPoint(r);
			return p;
				
		}
		RectangleCollection searchRectangle(Rectangle r, RectangleCollection *dummy){
			
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

	//DataIndexingWrapper d;
	
	Point *p;
	p=new Point(1,1);

	PointCollection *pointcollection=new PointCollection();

	pointcollection->insert(*p);

	p = new Point(2,2);

	pointcollection->insert(*p);


	p = new Point(3,3);
	
	pointcollection->insert(*p);

	p = new Point(4,4);
	
	pointcollection->insert(*p);

	// std::vector<Point> v;
	// int s = pointcollection->getSize();


	// for(int i=0;i<s;i++)
	// {
	// 	v = pointcollection->getNext();
	// 	vector<float> points = v.at(0).getCoordinates();
	// 	cout<<points.at(0)<<"  "<<points.at(1)<<endl;

		

	// }

	SpatialIndexInterface *sp;
	sp = new DataIndexingWrapper();

	sp->createIndex(*pointcollection);

	Rectangle *r = new Rectangle(0,0,2,2);

//	PointCollection res = sp->searchPoint(*r);


//	cout<<"Hello"<<" "<<res.getSize()<<endl;
	return 0;
}
