#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/geometries/box.hpp>
#include <boost/geometry/index/rtree.hpp>

// Header file for SpatialIndexInterface
#include "../integration/spatial-index-interface.h"
// to store queries results
#include <vector>
// just for output
#include <iostream>
#include <sstream>
#include <fstream>
#include <cstring>

#include <boost/foreach.hpp>
using namespace std;
namespace bg = boost::geometry;
namespace bgi = boost::geometry::index;

typedef bg::model::point<float, 2, bg::cs::cartesian> boostpoint;
typedef bg::model::box<boostpoint> boostbox;
typedef std::pair<boostbox, unsigned> boostvalue;

class PointDataIndex{
	private:
		bgi::rtree< boostpoint, bgi::linear<16> > rtreeObj;
	
	
	public:
		PointDataIndex() {}
    	
    	void createIndex(PointCollection points){
        	
			cout<<"create index point impl"<<endl;
			
			vector<Point> p;
			vector<boostpoint> packedPoints;
			
			int sizeOfColl = points.getSize();

			for(int k=0;k<sizeOfColl;k++){
				p = points.getNext();
			
				for(int i=0;i<p.size();i++){
				vector<float> vect;
				
				vect = p.at(i).getCoordinates();
				//rtreeinst.insert(boostpoint(vect.at(0),vect.at(1)));
				
				packedPoints.push_back(boostpoint(vect.at(0),vect.at(1)));
				
				
				}
			
			}
			
			bgi::rtree< boostpoint, bgi::linear<16> > rtreeinst(packedPoints);
			

			
			cout<<"##################################"<<endl<<endl;
			cout<<"Indexed "<<rtreeinst.size()<<endl;
			rtreeObj = rtreeinst;
			
		
		}
		bool deleteIndex(){
			rtreeObj.clear();
			return true;
		}
		PointCollection searchPoint(Rectangle r){
			
			std::vector<boostpoint> query_result;

			cout<<"In search point"<<endl;
		vector<float> vect = r.getCoordinates();

			
			rtreeObj.query(bgi::intersects(boostbox(boostpoint(vect.at(0),vect.at(1)),boostpoint(vect.at(2),vect.at(3)))), std::back_inserter(query_result));
			float x1,y1;
			vector<Point> returning;

			//    std::cout << bg::wkt<point>(point(0, 0)) << std::endl;
			//PointCollection points;
			    
			PointCollection *result=new PointCollection();

			cout<<query_result.size()<<endl;
			for(int x=0;x<query_result.size();x++){
				x1 = query_result.at(x).get<0>();
				y1 = query_result.at(x).get<1>();
				
							
				Point temp(x1,y1);

				result->insert(temp);

			}

			//PointCollection points(" "," ",0,returning);

			cout<<"Points result"<<result->getSize()<<endl;
			return *result;
		}
		
		bool update(PointCollection points){
			bool r = deleteIndex();
			createIndex(points);
			return r;
		}
		
};

/////////////////////////////////////////////////////

class RectangleDataIndex{

	private:
		bgi::rtree< boostvalue, bgi::quadratic<16> > rtreeObj;
	
	
	public:
		RectangleDataIndex(){
		}
		
		void createIndex(RectangleCollection rects){
			
			
			cout<<"create index rect impl"<<endl;
			
			vector<Rectangle> r;
			//if(rects!=NULL)
			vector<boostvalue> boxes;
			
			int sizeOfColl = rects.getSize();

			for(int k=0;k<sizeOfColl;k++){

				r = rects.getNext();
			
				for(int i=0;i<r.size();i++){
					vector<float> vect;
				
					vect = r.at(i).getCoordinates();
				
					boostbox b(boostpoint(vect.at(0), vect.at(1)), boostpoint(vect.at(2),vect.at(3)));

        			//rtreeinst.insert(std::make_pair(b, i));	
					boxes.push_back(std::make_pair(b,i));
			
				}

			}

			bgi::rtree< boostvalue, bgi::quadratic<16> > rtreeinst(boxes);
							
			cout<<"##################################"<<endl<<endl;
			cout<<"Inserted "<<rtreeinst.size()<<" rectangles in R tree"<<endl;
			rtreeObj = rtreeinst;
			
		}
		
		bool deleteIndex(){
			rtreeObj.clear();
			return true;
		}
		
		
		RectangleCollection searchRectangle(Rectangle r){
			
			//RectangleCollection rc;
			vector<float> vect = r.getCoordinates();
			
			std::vector<boostvalue> result_s;
    		rtreeObj.query(bgi::intersects(boostbox(boostpoint(vect.at(0),vect.at(1)),boostpoint(vect.at(2),vect.at(3)))), std::back_inserter(result_s));

    		std::vector<Rectangle> rects;

    		RectangleCollection *result=new RectangleCollection();
			
    		BOOST_FOREACH(boostvalue const& v, result_s){
				float x1 = bg::get<bg::min_corner,0>(v.first); 
    			float y1 = bg::get<bg::min_corner,1>(v.first);
    			float x2 = v.first.max_corner().get<0>();
    			float y2 = v.first.max_corner().get<1>();
    		
    			Rectangle temp(x1,y1,x2,y2);
				rects.push_back(temp);

				result->insert(temp);



			}

			cout<<"Size of result "<<result->getSize()<<endl;

			return *result;
		}
		
		
		bool update(RectangleCollection rects){
			bool r = deleteIndex();
			createIndex(rects);
			return r;
		}

};
