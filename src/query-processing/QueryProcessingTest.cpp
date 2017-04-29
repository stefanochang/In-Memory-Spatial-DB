
/*
 * Main.cpp
 *
 *  Created on: Mar 16, 2017
 *      Author: Supriya
 */

#include <string>
#include <iostream>
#include <vector>
#ifndef DATA_INDEXING_H
#include "../data-partitioning-indexing/data-indexing.h"
#endif
#ifndef IN_MEMORY_SPATIAL_DB_SPATIALINDEXIMPL_H
#include "../spatial-partitioning-indexing/SpatialIndexImpl.h"
#endif
#include "../integration/query-processing.h"

#define TYPE_NULL 0
#define TYPE_POINT 1
#define TYPE_RECTANGLE 2
#define TYPE_POINTPOINT 3
#define TYPE_POINTRECTANGLE 4
#define TYPE_RECTANGLERECTANGLE 5

#define NO_JOIN '1'
#define RANGE_JOIN '2'
#define KNN_JOIN '3'
#define DISTANCE_JOIN '4'

#define FILTER_BY_AREA_LT 'a'
#define FILTER_BY_AREA_LE 'b'
#define FILTER_BY_AREA_EQ 'c'
#define FILTER_BY_AREA_GT 'd'
#define FILTER_BY_AREA_GE 'e'
#define NO_FILTER ''

#define FILTER_BY_DISTANCE_LT 'f'
#define FILTER_BY_DISTANCE_LE 'g'
#define FILTER_BY_DISTANCE_EQ 'h'
#define FILTER_BY_DISTANCE_GT 'i'
#define FILTER_BY_DISTANCE_GE 'j'

#define KNN 11
#define OBJECTS_IN_RANGE 12

using namespace std;


bool queryProcessingTests() {


    vector<Filter> filterNull;

	PointCollection ptcolNull;
	RectangleCollection retcolNull;
	/*
	cout<<"\n---------------------------------------------------------------------------------------------\n";
	cout<<"Test 14 : Objects in Range -\n\t Find the Rectangles that are less than distance 2 from Rectangle (0,0,1,1)";
	cout<<"\n---------------------------------------------------------------------------------------------\n";
	{
		QueryTree qTree;
		QueryResult qResult;
		QueryProcessing query;
		qTree.setRootType(NO_JOIN_DI);

		vector<float> inputParams = { 0, 0, 1, 1 };

		char ft=OBJECTS_IN_RANGE;
		Filter f = Filter(ft,inputParams);
		vector<Filter> filter;
		filter.push_back(f);
		qTree.setLeftFilter(filter);

		qTree.setRightFilter(filterNull);

		RectangleCollection retcol;

		cout<<"RECTANGLE DATASET\n";
		for(int i=0;i<6;i++){
			cout<<"("<<i<<","<<i<<"), ("<<i+2<<","<<i+2<<")\n";
			retcol.insert(Rectangle(i,i,i+2,i+2));
		}
		qTree.setLeftRectangles(retcol);

		qTree.setLeftPoints(ptcolNull);
		qTree.setRightPoints(ptcolNull);
		qTree.setRightRectangles(retcolNull);


		SpatialIndexInterface* sp = new DataIndexingWrapper();
		sp->createIndex(retcol);

		CatalogItem *catItem;
		catItem = new CatalogItem("db1", "table1",TYPE_RECTANGLE, retcol);
		Catalog::Instance()->insert(catItem);

		qResult = query.processQuery(qTree);

		if (qResult.getResultType() == TYPE_RECTANGLE){
			RectangleCollection rcoll = qResult.getRectangleCollection();
			cout<<"\nRESULT: RectangeCollection"<<endl;
			for(int i=0;i<rcoll.getSize();i++)
			{
				vector<Rectangle> temp_ptv = rcoll.getNext(1);
				for (Rectangle rt : temp_ptv){
					cout<< "(" << rt.getCoordinates().at(0)<< " ," << rt.getCoordinates().at(1)<< "), ("
						<< rt.getCoordinates().at(2)<< " ," << rt.getCoordinates().at(3)<<")"<<endl;
				}
			}
		}
		else{
			cout << "Fail Test 14"<<endl;
		}

	}


	*/

	cout<<"\n---------------------------------------------------------------------------------------------\n";
	cout<<"Test 1 : FilterBy Distance -\n\t Find the points that are greater than distance 2 from point (0,0)";
	cout<<"\n---------------------------------------------------------------------------------------------\n";
	{
		QueryTree qTree;
		QueryResult qResult;
		QueryProcessing query;
		qTree.setRootType(NO_JOIN);

		vector<float> inputParams = { 2, 0, 0 };

		char ft=FILTER_BY_DISTANCE_GT;
		Filter f = Filter(ft,inputParams);
		vector<Filter> filter;
		filter.push_back(f);
		qTree.setLeftFilter(filter);

		qTree.setRightFilter(filterNull);

		PointCollection ptcol;

		cout<<"POINT DATASET\n";
		for(int i=0;i<5;i++){
			cout<<"(0,"<<i<<")\n";
			ptcol.insert(Point(0,i));
		}
		qTree.setLeftPoints(ptcol);

		qTree.setLeftRectangles(retcolNull);
		qTree.setRightPoints(ptcolNull);
		qTree.setRightRectangles(retcolNull);

		qResult = query.processQuery(qTree);

		if (qResult.getResultType() == TYPE_POINT){
			PointCollection ppcol = qResult.getPointCollection();
			cout<<"\nRESULT: PointCollection"<<endl;
			for(int i=0;i<ppcol.getSize();i++)
			{
				vector<Point> temp_ptv = ppcol.getNext(1);
				for (Point pt : temp_ptv)
					cout<< "( "<< pt.getCoordinates().at(0)<< " ," << pt.getCoordinates().at(1) << " )" <<endl;
			}
		}
		else{
			cout << "Fail Test 1"<<endl;
		}
	}

	cout<<"\n---------------------------------------------------------------------------------------------\n";
	cout<<"Test 2 : FilterBy Distance -\n\t Find the points that are equal to distance 5 from point (0,1)";
	cout<<"\n---------------------------------------------------------------------------------------------\n";
	{
		QueryTree qTree;
		QueryResult qResult;
		QueryProcessing query;
		qTree.setRootType(NO_JOIN);

		vector<float> inputParams = { 5, 0, 1 };

		char ft=FILTER_BY_DISTANCE_EQ;
		Filter f = Filter(ft,inputParams);
		vector<Filter> filter;
		filter.push_back(f);
		qTree.setLeftFilter(filter);

		qTree.setRightFilter(filterNull);

		PointCollection ptcol;

		cout<<"POINT DATASET\n";
		for(int i=4;i<8;i++){
			cout<<"(0,"<<i<<")\n";
			ptcol.insert(Point(0,i));
		}
		qTree.setLeftPoints(ptcol);

		qTree.setLeftRectangles(retcolNull);
		qTree.setRightPoints(ptcolNull);
		qTree.setRightRectangles(retcolNull);

		qResult = query.processQuery(qTree);

		if (qResult.getResultType() == TYPE_POINT){
			PointCollection ppcol = qResult.getPointCollection();
			cout<<"\nRESULT: PointCollection"<<endl;
			for(int i=0;i<ppcol.getSize();i++)
			{
				vector<Point> temp_ptv = ppcol.getNext(1);
				for (Point pt : temp_ptv)
					cout<< "( "<< pt.getCoordinates().at(0)<< " ," << pt.getCoordinates().at(1) << " )" <<endl;
			}
		}
		else{
			cout << "Fail Test 2"<<endl;
		}
	}

	cout<<"\n---------------------------------------------------------------------------------------------\n";
	cout<<"Test 3 : FilterBy Distance -\n\t Find the Rectangles that are less than distance 2 from Rectangle (0,0,1,1)";
	cout<<"\n---------------------------------------------------------------------------------------------\n";
	{
		QueryTree qTree;
		QueryResult qResult;
		QueryProcessing query;
		qTree.setRootType(NO_JOIN);

		vector<float> inputParams = { 2, 0, 0, 1, 1 };

		char ft=FILTER_BY_DISTANCE_LT;
		Filter f = Filter(ft,inputParams);
		vector<Filter> filter;
		filter.push_back(f);
		qTree.setLeftFilter(filter);

		qTree.setRightFilter(filterNull);

		RectangleCollection retcol;

		cout<<"RECTANGLE DATASET\n";
		for(int i=0;i<6;i++){
			cout<<"("<<i<<","<<i<<"), ("<<i+2<<","<<i+2<<")\n";
			retcol.insert(Rectangle(i,i,i+2,i+2));
		}
		qTree.setLeftRectangles(retcol);

		qTree.setLeftPoints(ptcolNull);
		qTree.setRightPoints(ptcolNull);
		qTree.setRightRectangles(retcolNull);

		qResult = query.processQuery(qTree);

		if (qResult.getResultType() == TYPE_RECTANGLE){
			RectangleCollection rcoll = qResult.getRectangleCollection();
			cout<<"\nRESULT: RectangeCollection"<<endl;
			for(int i=0;i<rcoll.getSize();i++)
			{
				vector<Rectangle> temp_ptv = rcoll.getNext(1);
				for (Rectangle rt : temp_ptv){
					cout<< "(" << rt.getCoordinates().at(0)<< " ," << rt.getCoordinates().at(1)<< "), ("
						<< rt.getCoordinates().at(2)<< " ," << rt.getCoordinates().at(3)<<")"<<endl;
				}
			}
		}
		else{
			cout << "Fail Test 3"<<endl;
		}

	}

	cout<<"\n---------------------------------------------------------------------------------------------\n";
	cout<<"Test 4 : Two FilterBy Distance on same collection -\n\t Find the Rectangles that are greater than distance 2 \n\t   from Rectangle (0,0,1,1) and less than distance 4 from (0,0,1,1)\n";
	cout<<"\n---------------------------------------------------------------------------------------------\n";
	{
		QueryTree qTree;
		QueryResult qResult;
		QueryProcessing query;
		qTree.setRootType(NO_JOIN);

		vector<float> inputParams1 = { 2, 0, 0, 1, 1 };

		char ft1=FILTER_BY_DISTANCE_GT;
		Filter f1 = Filter(ft1,inputParams1);

		vector<float> inputParams2 = { 4, 0, 0, 1, 1 };

		char ft2=FILTER_BY_DISTANCE_LT;
		Filter f2 = Filter(ft2,inputParams2);

		vector<Filter> filter;
		filter.push_back(f1);
		filter.push_back(f2);
		qTree.setLeftFilter(filter);

		qTree.setRightFilter(filterNull);

		RectangleCollection retcol;

		cout<<"RECTANGLE DATASET\n";
		for(int i=0;i<5;i++){
			cout<<"("<<i<<","<<i<<"), ("<<i+2<<","<<i+2<<")\n";
			retcol.insert(Rectangle(i,i,i+2,i+2));
		}
		qTree.setLeftRectangles(retcol);

		qTree.setLeftPoints(ptcolNull);
		qTree.setRightPoints(ptcolNull);
		qTree.setRightRectangles(retcolNull);

		qResult = query.processQuery(qTree);

		if (qResult.getResultType() == TYPE_RECTANGLE){
			RectangleCollection rcoll = qResult.getRectangleCollection();
			cout<<"\nRESULT: RectangeCollection"<<endl;
			for(int i=0;i<rcoll.getSize();i++)
			{
				vector<Rectangle> temp_ptv = rcoll.getNext(1);
				for (Rectangle rt : temp_ptv){
					cout<< "(" << rt.getCoordinates().at(0)<< " ," << rt.getCoordinates().at(1)<< "), ("
						<< rt.getCoordinates().at(2)<< " ," << rt.getCoordinates().at(3)<<")"<<endl;
				}
			}
		}
		else{
			cout << "Fail Test 4"<<endl;
		}

	}

	cout<<"\n---------------------------------------------------------------------------------------------\n";
	cout<<"Test 5 : FilterBy Area\n\t Find all the Rectangles that have area greater than 5";
	cout<<"\n---------------------------------------------------------------------------------------------\n";
	{
		QueryTree qTree;
		QueryResult qResult;
		QueryProcessing query;
		qTree.setRootType(NO_JOIN);

		vector<float> inputParams;
		inputParams.push_back(5);

		char ft=FILTER_BY_AREA_GT;
		Filter f = Filter(ft,inputParams);

		vector<Filter> filter;
		filter.push_back(f);

		qTree.setLeftFilter(filter);

		qTree.setRightFilter(filterNull);

		RectangleCollection retcol;

		cout<<"RECTANGLE DATASET\n";
		for(int i=1;i<7;i++){
			cout<<"("<<i<<","<<i<<"), ("<<i+i<<","<<i+i<<")\n";
			retcol.insert(Rectangle(i,i,i+i,i+i));
		}
		qTree.setLeftRectangles(retcol);

		qTree.setLeftPoints(ptcolNull);
		qTree.setRightPoints(ptcolNull);
		qTree.setRightRectangles(retcolNull);

		qResult = query.processQuery(qTree);



		if (qResult.getResultType() == TYPE_RECTANGLE){
			RectangleCollection rcoll = qResult.getRectangleCollection();
			cout<<"\nRESULT: RectangeCollection"<<endl;
			for(int i=0;i<rcoll.getSize();i++)
			{
				vector<Rectangle> temp_ptv = rcoll.getNext(1);
				for (Rectangle rt : temp_ptv){
					cout<< "(" << rt.getCoordinates().at(0)<< " ," << rt.getCoordinates().at(1)<< "), ("
						<< rt.getCoordinates().at(2)<< " ," << rt.getCoordinates().at(3)<<")"<<endl;
				}
			}
		}
		else{
			cout << "Fail Test 5"<<endl;
		}

	}

	cout<<"\n---------------------------------------------------------------------------------------------\n";
	cout<<"Test 6 : Distance Join\n";
	cout<<"\t Filterby left branch all points whose distance is greater than 3 from point (0,0)\n";
    cout<<"\t Filterby right branch all points whose distance is less than 5 from point (0,3)\n";
	cout<<"\t DistanceJoin all points whose distance is less than 5";
	cout<<"\n---------------------------------------------------------------------------------------------\n";
	{
		QueryTree qTree;
		QueryResult qResult;
		QueryProcessing query;
		qTree.setRootType(DISTANCE_JOIN);
		qTree.setRootParam(5);

		vector<float> inputParamsleft = { 3, 0, 0 };

		char fl=FILTER_BY_DISTANCE_GT;
		Filter f_left = Filter(fl,inputParamsleft);

		vector<Filter> filter_left;
		filter_left.push_back(f_left);

		qTree.setLeftFilter(filter_left);

		vector<float> inputParamsright = { 5, 0, 3 };


		char fr=FILTER_BY_DISTANCE_LT;
		Filter f_right = Filter(fr,inputParamsright);

		vector<Filter> filter_right;
		filter_right.push_back(f_right);

		qTree.setRightFilter(filter_right);

		cout<<"POINT DATASET LEFT\t\tPOINT DATASET RIGHT";
		PointCollection ptcolleft,ptcollright;

		for(int i=0;i<5;i++){
			ptcolleft.insert(Point(0,i));
			ptcollright.insert(Point(0,i+2));
			cout<<"\n\t("<<0<<","<<i<<")\t\t\t\t("<<0<<","<<i+2<<")";
		}

		qTree.setLeftPoints(ptcolleft);
		qTree.setRightPoints(ptcollright);

		qTree.setLeftRectangles(retcolNull);
		qTree.setRightRectangles(retcolNull);

		qResult = query.processQuery(qTree);

		if (qResult.getResultType() == TYPE_POINTPOINT){
			PointPointCollection ptcoll = qResult.getPointPointCollection();
			cout<<"\nRESULT: PointPointCollection"<<endl;
			cout << "ResultSet Size : " << ptcoll.getSize() << "\n\n";
			for(int i=0;i<ptcoll.getSize();i++)
			{
				vector<PointPoint> tempt_ppt = ptcoll.getNext(1);
				for ( PointPoint ppt : tempt_ppt){
					cout<< "[(" << ppt.getCoordinates().at(0)<< " ," << ppt.getCoordinates().at(1) <<"),"
						<< "("<< ppt.getCoordinates().at(2)<< " ," << ppt.getCoordinates().at(3) <<") ]"<<endl;
				}
			}
		}
		else{
			cout << "Fail Test 6"<<endl;
		}

	}

	cout<<"\n---------------------------------------------------------------------------------------------\n";
	cout<<"Test 7 : Distance Join\n";
	cout<<"\t Filterby left branch all Rectangle whose area is greater than 10\n";
    cout<<"\t Filterby right branch all Rectangle whose distance is less than 3 from Rectangle ((0,0)(4,4))\n";
	cout<<"\t DistanceJoin all Rectangle whose distance is less than 5";
	cout<<"\n---------------------------------------------------------------------------------------------\n";
	{
		QueryTree qTree;
		QueryResult qResult;
		QueryProcessing query;
		qTree.setRootType(DISTANCE_JOIN);
		qTree.setRootParam(10);

		vector<float> inputParamsleft;
		inputParamsleft.push_back(10);

		char fl=FILTER_BY_AREA_GT;
		Filter f_left = Filter(fl,inputParamsleft);

		vector<Filter> filter_left;
		filter_left.push_back(f_left);

		qTree.setLeftFilter(filter_left);

		vector<float> inputParamsright = { 3, 0, 0, 4, 4 };

		char fr=FILTER_BY_DISTANCE_LT;
		Filter f_right = Filter(fr,inputParamsright);

		vector<Filter> filter_right;
		filter_right.push_back(f_right);

		qTree.setRightFilter(filter_right);

		cout<<"RECTANGLE DATASET LEFT\t\tRECTANGLE DATASET RIGHT";
		RectangleCollection reccolleft,reccollright;

		for(int i=0;i<7;i++){
			reccolleft.insert(Rectangle(0,0,i+1,i+1));
			reccollright.insert(Rectangle(i-1,i-1,i+1,i+1));
			cout<<"\n\t(("<<0<<","<<0<<"),("<<i+1<<","<<i+1<<"))\t\t\t(("<<i-1<<","<<i-1<<"),("<<i+1<<","<<i+1<<"))";
		}

		qTree.setLeftRectangles(reccolleft);
		qTree.setRightRectangles(reccollright);

		qTree.setLeftPoints(ptcolNull);
		qTree.setRightPoints(ptcolNull);

		qResult = query.processQuery(qTree);

		if (qResult.getResultType() == TYPE_RECTANGLERECTANGLE){
			RectangleRectangleCollection retcoll = qResult.getRectangleRectangleCollection();
			cout << "\n\nRESULT: RectangleRectangleCollection";
			cout << "\nResultSet Size : " << retcoll.getSize() << "\n\n";
			for(int i=0;i<retcoll.getSize();i++)
			{
				vector<RectangleRectangle> tempt_rr = retcoll.getNext(1);
				for ( RectangleRectangle rr : tempt_rr){
					cout<< "[((" << rr.getCoordinates().at(0)<< " ," << rr.getCoordinates().at(1) <<"),"
						<< "("<< rr.getCoordinates().at(2)<< " ," << rr.getCoordinates().at(3) <<")) ( "
						<< "("<< rr.getCoordinates().at(4)<< " ," << rr.getCoordinates().at(5) <<"),  "
						<< "("<< rr.getCoordinates().at(6)<< " ," << rr.getCoordinates().at(7) <<")) ]\n";
				}
			}
		}
		else{
			cout << "Fail Test 7"<<endl;
		}

	}
	cout<<"\n---------------------------------------------------------------------------------------------\n";
	cout<<"Test 8 : Range Join - POINT-POINT \n";
	cout<<"\t No Filterby - left branch all Points Collections without any filter\n";
    cout<<"\t Filterby right branch all Points whose distance is less than 6 from Point (0,0)\n";
	cout<<"\n---------------------------------------------------------------------------------------------\n";
	{
		QueryTree qTree;
		QueryResult qResult;
		QueryProcessing query;
		qTree.setRootType(RANGE_JOIN);

		vector<float> inputParamsright = { 6, 0, 0 };

		char fr=FILTER_BY_DISTANCE_LT;
		Filter f_right = Filter(fr,inputParamsright);

		vector<Filter> filter_right;
		filter_right.push_back(f_right);

		qTree.setRightFilter(filter_right);

		cout<<"POINT DATASET LEFT\t\tPOINT DATASET RIGHT";
		PointCollection ptcolleft,ptcollright;

		for(int i=0;i<7;i++){
			ptcolleft.insert(Point(0,i+1));
			ptcollright.insert(Point(0,i+3));
			cout<<"\n\t("<<0<<","<<i+1<<")\t\t\t\t("<<0<<","<<i+3<<")";
		}

		qTree.setLeftPoints(ptcolleft);
		qTree.setRightPoints(ptcollright);

		qTree.setLeftRectangles(retcolNull);
		qTree.setRightRectangles(retcolNull);

		qResult = query.processQuery(qTree);

		if (qResult.getResultType() == TYPE_POINTPOINT){
			PointPointCollection ptcoll = qResult.getPointPointCollection();
			cout<<"\nRESULT: PointPointCollection"<<endl;
			cout << "ResultSet Size : " << ptcoll.getSize() << "\n\n";
			for(int i=0;i<ptcoll.getSize();i++)
			{
				vector<PointPoint> tempt_ppt = ptcoll.getNext(1);
				for ( PointPoint ppt : tempt_ppt){
					cout<< "[(" << ppt.getCoordinates().at(0)<< " ," << ppt.getCoordinates().at(1) <<"),"
						<< "("<< ppt.getCoordinates().at(2)<< " ," << ppt.getCoordinates().at(3) <<") ]"<<endl;
				}
			}
		}
		else{
			cout << "Fail Test 8"<<endl;
		}

	}

	cout<<"\n---------------------------------------------------------------------------------------------\n";
	cout<<"Test 8 b : Range Join - POINT-POINT (Demonstrating Sweep Join) \n";
	cout<<"\t No Filterby - left branch all Points Collections without any filter\n";
	cout<<"\t Filterby right branch all Points whose distance is less than 6 from Point (0,0)\n";
	cout<<"\n---------------------------------------------------------------------------------------------\n";
	{
		QueryTree qTree;
		QueryResult qResult;
		QueryProcessing query;
		qTree.setRootType(RANGE_JOIN);


		vector<float> inputParamsright;
		inputParamsright.push_back(6);
		inputParamsright.push_back(0);
		inputParamsright.push_back(0);

		char fr=FILTER_BY_DISTANCE_LT;
		Filter f_right = Filter(fr,inputParamsright);

		vector<Filter> filter_right;
		filter_right.push_back(f_right);

		qTree.setRightFilter(filter_right);

		cout<<"POINT DATASET LEFT\t\tPOINT DATASET RIGHT";
		vector<Point> pt_null;
		PointCollection ptcolleft("", "", COLLECTION_STRUCT_SORTEDY, pt_null);
		PointCollection ptcollright("", "", COLLECTION_STRUCT_SORTEDY, pt_null);;

		for(int i=0;i<7;i++){
			ptcolleft.insert(Point(0,i+1));
			ptcollright.insert(Point(0,i+3));
			cout<<"\n\t("<<0<<","<<i+1<<")\t\t\t\t("<<0<<","<<i+3<<")";
		}

		qTree.setLeftPoints(ptcolleft);
		qTree.setRightPoints(ptcollright);

		qTree.setLeftRectangles(retcolNull);
		qTree.setRightRectangles(retcolNull);

		qResult = query.processQuery(qTree);

		if (qResult.getResultType() == TYPE_POINTPOINT){
			PointPointCollection ptcoll = qResult.getPointPointCollection();
			cout<<"\nRESULT: PointPointCollection"<<endl;
			cout << "ResultSet Size : " << ptcoll.getSize() << "\n\n";
			for(int i=0;i<ptcoll.getSize();i++)
			{
				vector<PointPoint> tempt_ppt = ptcoll.getNext(1);
				for ( PointPoint ppt : tempt_ppt){
					cout<< "[(" << ppt.getCoordinates().at(0)<< " ," << ppt.getCoordinates().at(1) <<"),"
						<< "("<< ppt.getCoordinates().at(2)<< " ," << ppt.getCoordinates().at(3) <<") ]"<<endl;
				}
			}
		}
		else{
			cout << "Fail Test 8b"<<endl;
		}

	}


	cout<<"\n---------------------------------------------------------------------------------------------\n";
	cout<<"Test 9 : Range Join - RECTANGLE-RECTANGLE \n";
	cout<<"\t Filterby - left branch all Rectangle Collections whose area is less than 7\n";
    cout<<"\t No Filterby right branch all Rectangle collection without any filter\n";
	cout<<"\n---------------------------------------------------------------------------------------------\n";
	{
		QueryTree qTree;
		QueryResult qResult;
		QueryProcessing query;
		qTree.setRootType(RANGE_JOIN);

		vector<float> inputParamsleft;
		inputParamsleft.push_back(7);

		char fr=FILTER_BY_AREA_LT;
		Filter f_left = Filter(fr,inputParamsleft);

		vector<Filter> filter_left;
		filter_left.push_back(f_left);

		qTree.setLeftFilter(filter_left);

		cout<<"RECTANGLE DATASET LEFT\t\tRECTANGLE DATASET RIGHT";
		RectangleCollection reccolleft,reccollright;

		for(int i=1;i<7;i++){
			reccolleft.insert(Rectangle(1,1,2*i,2*i));
			reccollright.insert(Rectangle(i-1,i-1,i+1,i+1));
			cout<<"\n(("<<1<<","<<1<<"),("<<2*i<<","<<2*i<<"))\t\t\t(("<<i-1<<","<<i-1<<"),("<<i+1<<","<<i+1<<"))";
		}

		qTree.setLeftRectangles(reccolleft);
		qTree.setRightRectangles(reccollright);

		qTree.setLeftPoints(ptcolNull);
		qTree.setRightPoints(ptcolNull);

		qResult = query.processQuery(qTree);

		if (qResult.getResultType() == TYPE_RECTANGLERECTANGLE){
			RectangleRectangleCollection retcoll = qResult.getRectangleRectangleCollection();
			cout << "\n\nRESULT: RectangleRectangleCollection";
			cout << "\nResultSet Size : " << retcoll.getSize() << "\n\n";
			for(int i=0;i<retcoll.getSize();i++)
			{
				vector<RectangleRectangle> tempt_rr = retcoll.getNext(1);
				for ( RectangleRectangle rr : tempt_rr){
					cout<< "[ ((" << rr.getCoordinates().at(0)<< " ," << rr.getCoordinates().at(1) <<"),("
						<< rr.getCoordinates().at(2)<< " ," << rr.getCoordinates().at(3) <<")), ("
						<< "("<< rr.getCoordinates().at(4)<< " ," << rr.getCoordinates().at(5) <<"),"
						<< "("<< rr.getCoordinates().at(6)<< " ," << rr.getCoordinates().at(7) <<")) ]\n";
				}
			}
		}
		else{
			cout << "Fail Test 9"<<endl;
		}

	}

	cout<<"\n--------------------------------------------------------------------------------------------------\n";
	cout<<"Test 10 : Range Join - POINT-RECTANGLE \n";
	cout<<"\t Filterby - left branch all Point collection whose distance from rectange ((2,3)(4,5)) is more than 2\n";
	cout<<"\t Filterby - right branch all Rectangle Collections whose distance is less than 7 from point (2,3)\n";
	cout<<"\n--------------------------------------------------------------------------------------------------\n";
	{
		QueryTree qTree;
		QueryResult qResult;
		QueryProcessing query;
		qTree.setRootType(RANGE_JOIN);

		vector<float> inputParamsright = { 7, 2, 3 };

		char fr=FILTER_BY_DISTANCE_LT;
		Filter f_right = Filter(fr,inputParamsright);

		vector<Filter> filter_right;
		filter_right.push_back(f_right);

		qTree.setRightFilter(filter_right);

		vector<float> inputParamsleft = { 2, 2, 3, 4, 5 };

		char fl=FILTER_BY_DISTANCE_GT;
		Filter f_left = Filter(fl,inputParamsleft);

		vector<Filter> filter_left;
		filter_left.push_back(f_left);

		qTree.setLeftFilter(filter_left);

		cout<<"POINT DATASET LEFT\t\tRECTANGLE DATASET RIGHT";
		RectangleCollection reccolright;
		PointCollection ptcolleft;

		for(int i=1;i<7;i++){
			reccolright.insert(Rectangle(1,1,2*i,2*1));
			ptcolleft.insert(Point(i+1,1.5*i));
			cout<<"\n("<<i+1<<","<<1.5*i<<")\t\t\t(("<<1<<","<<1<<"),("<<2*i<<","<<2*i<<"))";
		}

		qTree.setLeftRectangles(retcolNull);
		qTree.setRightRectangles(reccolright);

		qTree.setLeftPoints(ptcolleft);
		qTree.setRightPoints(ptcolNull);

		qResult = query.processQuery(qTree);

		if (qResult.getResultType() == TYPE_POINTRECTANGLE){
			PointRectangleCollection retcoll = qResult.getPointRectangleCollection();
			cout << "\n\nRESULT: PointRectangleCollection";
			cout << "\nResultSet Size : " << retcoll.getSize() << "\n\n";
			for(int i=0;i<retcoll.getSize();i++)
			{
				vector<PointRectangle> tempt_rr = retcoll.getNext(1);
				for ( PointRectangle rr : tempt_rr){
					cout<< "[(" << rr.getCoordinates().at(0)<< " ," << rr.getCoordinates().at(1) <<"), "
						<< "(("<< rr.getCoordinates().at(2)<< " ," << rr.getCoordinates().at(3) <<")("
						<< rr.getCoordinates().at(4)<< " ," << rr.getCoordinates().at(5) <<"))]\n";
				}
			}
		}
		else{
			cout << "Fail Test 10"<<endl;
		}

	}

	cout<<"\n---------------------------------------------------------------------------------------------\n";
	cout<<"Test 11 : KNN Join - POINT-POINT , K=3\n";
	cout<<"\t left branch all Points Collections without any filter\n";
    cout<<"\t right branch all Points Collections without any filter\n";
	cout<<"\n---------------------------------------------------------------------------------------------\n";
	{
		QueryTree qTree;
		QueryResult qResult;
		QueryProcessing query;
		qTree.setRootType(KNN_JOIN);
		qTree.setRootParam(3);

		qTree.setRightFilter(filterNull);
		qTree.setLeftFilter(filterNull);

		cout<<"POINT DATASET LEFT\t\tPOINT DATASET RIGHT";
		PointCollection ptcolleft,ptcollright;

		for(int i=0;i<7;i++){
			ptcolleft.insert(Point(i+2,i+1));
			ptcollright.insert(Point(i,i+3));
			cout<<"\n\t("<<i+2<<","<<i+1<<")\t\t\t\t("<<i<<","<<i+3<<")";
		}

		qTree.setLeftPoints(ptcolleft);
		qTree.setRightPoints(ptcollright);

		qTree.setLeftRectangles(retcolNull);
		qTree.setRightRectangles(retcolNull);

		qResult = query.processQuery(qTree);

		if (qResult.getResultType() == TYPE_POINTPOINT){
			PointPointCollection ptcoll = qResult.getPointPointCollection();
			cout<<"\nRESULT: PointPointCollection"<<endl;
			cout << "ResultSet Size : " << ptcoll.getSize() << "\n\n";
			for(int i=0;i<ptcoll.getSize();i++)
			{
				vector<PointPoint> tempt_ppt = ptcoll.getNext(1);
				for ( PointPoint ppt : tempt_ppt){
					cout<< "[(" << ppt.getCoordinates().at(0)<< " ," << ppt.getCoordinates().at(1) <<"),"
						<< "("<< ppt.getCoordinates().at(2)<< " ," << ppt.getCoordinates().at(3) <<") ]"<<endl;
				}
			}
		}
		else{
			cout << "Fail Test 11"<<endl;
		}

	}

	cout<<"\n---------------------------------------------------------------------------------------------\n";
	cout<<"Test 12 : KNN Join - RECTANGLE-RECTANGLE K=3\n";
	cout<<"\t left branch all Rectangle Collections without any filter\n";
    cout<<"\t right branch all Rectangle Collections without any filter\n";
	cout<<"\n---------------------------------------------------------------------------------------------\n";
	{
		QueryTree qTree;
		QueryResult qResult;
		QueryProcessing query;
		qTree.setRootType(KNN_JOIN);
		qTree.setRootParam(3);

		qTree.setRightFilter(filterNull);
		qTree.setLeftFilter(filterNull);

		cout<<"RECTANGLE DATASET LEFT\t\tRECTANGLE DATASET RIGHT";
		RectangleCollection reccolleft,reccollright;

		for(int i=1;i<7;i++){
			reccolleft.insert(Rectangle(1,1,2*i,2*1));
			reccollright.insert(Rectangle(i-1,i-1,i+1,i+1));
			cout<<"\n(("<<1<<","<<1<<"),("<<2*i<<","<<2*i<<"))\t\t\t(("<<i-1<<","<<i-1<<"),("<<i+1<<","<<i+1<<"))";
		}

		qTree.setLeftRectangles(reccolleft);
		qTree.setRightRectangles(reccollright);

		qTree.setLeftPoints(ptcolNull);
		qTree.setRightPoints(ptcolNull);

		qResult = query.processQuery(qTree);

		if (qResult.getResultType() == TYPE_RECTANGLERECTANGLE){
			RectangleRectangleCollection retcoll = qResult.getRectangleRectangleCollection();
			cout << "\n\nRESULT: RectangleRectangleCollection";
			cout << "\nResultSet Size : " << retcoll.getSize() << "\n\n";
			for(int i=0;i<retcoll.getSize();i++)
			{
				vector<RectangleRectangle> tempt_rr = retcoll.getNext(1);
				for ( RectangleRectangle rr : tempt_rr){
					cout<< "[((" << rr.getCoordinates().at(0)<< " ," << rr.getCoordinates().at(1) <<"),"
						<< "("<< rr.getCoordinates().at(2)<< " ," << rr.getCoordinates().at(3) <<")) ( "
						<< "("<< rr.getCoordinates().at(4)<< " ," << rr.getCoordinates().at(5) <<"),  "
						<< "("<< rr.getCoordinates().at(6)<< " ," << rr.getCoordinates().at(7) <<")) ]\n";
				}
			}
		}
		else{
			cout << "Fail Test 12"<<endl;
		}

	}

	cout<<"\n---------------------------------------------------------------------------------------------\n";
	cout<<"Test 13 : KNN Join - Point-RECTANGLE K=3\n";
	cout<<"\t left branch all Point Collections without any filter\n";
    cout<<"\t right branch all Rectangle Collections without any filter\n";
	cout<<"\n---------------------------------------------------------------------------------------------\n";
	{
		QueryTree qTree;
		QueryResult qResult;
		QueryProcessing query;
		qTree.setRootType(KNN_JOIN);
		qTree.setRootParam(3);

		qTree.setRightFilter(filterNull);
		qTree.setLeftFilter(filterNull);

		cout<<"POINT DATASET LEFT\t\tRECTANGLE DATASET RIGHT";
		RectangleCollection reccolright;
		PointCollection ptcolleft;

		for(int i=1;i<7;i++){
			reccolright.insert(Rectangle(1,1,2*i,2*1));
			ptcolleft.insert(Point(i+1,1.5*i));
			cout<<"\n("<<i+1<<","<<1.5*i<<")\t\t\t(("<<1<<","<<1<<"),("<<2*i<<","<<2*i<<"))";
		}

		qTree.setLeftRectangles(retcolNull);
		qTree.setRightRectangles(reccolright);

		qTree.setLeftPoints(ptcolleft);
		qTree.setRightPoints(ptcolNull);

		qResult = query.processQuery(qTree);

		if (qResult.getResultType() == TYPE_POINTRECTANGLE){
			PointRectangleCollection retcoll = qResult.getPointRectangleCollection();
			cout << "\n\nRESULT: PointRectangleCollection";
			cout << "\nResultSet Size : " << retcoll.getSize() << "\n\n";
			for(int i=0;i<retcoll.getSize();i++)
			{
				vector<PointRectangle> tempt_rr = retcoll.getNext(1);
				for ( PointRectangle rr : tempt_rr){
					cout<< "[(" << rr.getCoordinates().at(0)<< " ," << rr.getCoordinates().at(1) <<"), \t"
						<< "(("<< rr.getCoordinates().at(2)<< " ," << rr.getCoordinates().at(3) <<")("
						<< rr.getCoordinates().at(4)<< " ," << rr.getCoordinates().at(5) <<"))]\n";
				}
			}
		}
		else{
			cout << "Fail Test 13"<<endl;
		}

	}

	cout<<"\n---------------------------------------------------------------------------------------------\n";
	cout<<"Test 14 (Data Index) : Objects in Range -\n\t Find the Rectangles  from Rectangle (0,0,2,2)";
	cout<<"\n---------------------------------------------------------------------------------------------\n";
	{
		QueryTree qTree;
		qTree.setRootType(NO_JOIN_SI);

		vector<float> inputParams = { 0, 0, 2, 2};

		char ft=OBJECTS_IN_RANGE;
		Filter f = Filter(ft,inputParams);
		vector<Filter> filter;
		filter.push_back(f);
		qTree.setLeftFilter(filter);

		qTree.setRightFilter(filterNull);
		vector<Rectangle> tempData2;
 
		for(int i=0;i<6;i++){
			cout<<"("<<i<<","<<i<<"), ("<<i+2<<","<<i+2<<")\n";
			tempData2.push_back(Rectangle(i,i,i+2,i+2));
		}



		qTree.setRightPoints(ptcolNull);
		qTree.setRightRectangles(retcolNull);
		
		RectangleCollection *retcol = new RectangleCollection("table1","db1",COLLECTION_STRUCT_UNSORTED,tempData2);		
		SpatialIndexInterface* sp = new DataIndexingWrapper();
		sp->createIndex(*retcol);
		qTree.setLeftRectangles(*retcol);
		qTree.setLIndexType(DATA_INDEX);
		CatalogItem *catItem;
		catItem = new CatalogItem("db1", "table1",TYPE_RECTANGLE, retcol);
		Catalog::Instance()->insert(catItem);

		CatalogItem* ci = Catalog::Instance()->getCatalogItem("db1","table1");
		ci->addDataIndex(sp);
		cout<< "Before processQuery()"<<endl;
		QueryResult qResult;
		QueryProcessing query;
		qResult = query.processQuery(qTree);

		if (qResult.getResultType() == TYPE_RECTANGLE){
			RectangleCollection rcoll = qResult.getRectangleCollection();
			cout<<"\nRESULT: RectangeCollection"<<endl;
			for(int i=0;i<rcoll.getSize();i++)
			{
				vector<Rectangle> temp_ptv = rcoll.getNext(1);
				for (Rectangle rt : temp_ptv){
					cout<< "(" << rt.getCoordinates().at(0)<< " ," << rt.getCoordinates().at(1)<< "), ("
						<< rt.getCoordinates().at(2)<< " ," << rt.getCoordinates().at(3)<<")"<<endl;
				}
			}
		}
		else if (qResult.getResultType() == TYPE_POINT){
			PointCollection ppcol = qResult.getPointCollection();
			cout<<"\nRESULT: PointCollection"<<endl;
			cout<<"RESULT SIZE : "<< ppcol.getSize() << endl;
			for(int i=0;i<ppcol.getSize();i++)
			{
				vector<Point> temp_ptv = ppcol.getNext(1);
				for (Point pt : temp_ptv)
					cout<< "( "<< pt.getCoordinates().at(0)<< " ," << pt.getCoordinates().at(1) << " )" <<endl;
			}
		}
		else{
			cout << "Fail Test 14"<<endl;
		}
		
	}
	cout<<"\n---------------------------------------------------------------------------------------------\n";
	cout<<"Test 15 (Data Index) : Using Data Index on Point Collection"<<
		   "\n\tObjects in Range -\n\tFind the Points in range of Rectangle (0,0,5,5) ";
	cout<<"\n---------------------------------------------------------------------------------------------\n";
	{
		QueryTree qTree;
		qTree.setRootType(NO_JOIN);

		vector<float> inputParams = { 0, 0, 5, 5};

		char ft=OBJECTS_IN_RANGE;
		Filter f = Filter(ft,inputParams);
		vector<Filter> filter;
		filter.push_back(f);
		qTree.setLeftFilter(filter);
		qTree.setRightFilter(filterNull);
		
		vector<Point> tempData1;
		
		for(int i=0;i<7;i++){
			cout<<"("<<i<<","<<i+1<<")\n";
			tempData1.push_back(Point(i,i+1));
		}

		qTree.setRightPoints(ptcolNull);
		qTree.setRightRectangles(retcolNull);
		
		PointCollection *ptcol = new PointCollection("table","db1",COLLECTION_STRUCT_UNSORTED,tempData1);		
		SpatialIndexInterface* di = new DataIndexingWrapper();
		di->createIndex(*ptcol);
		qTree.setLeftPoints(*ptcol);
		qTree.setLIndexType(DATA_INDEX);
		CatalogItem *catItem;
		catItem = new CatalogItem("db1", "table",TYPE_POINT, ptcol);
		Catalog::Instance()->insert(catItem);

		CatalogItem* ci = Catalog::Instance()->getCatalogItem("db1","table");
		ci->addDataIndex(di);
	
		QueryResult qResult;
		QueryProcessing query;
		qResult = query.processQuery(qTree);

		if (qResult.getResultType() == TYPE_POINT){
			PointCollection ppcol = qResult.getPointCollection();
			cout<<"\nRESULT: PointCollection"<<endl;
			cout<<"RESULT SIZE : "<< ppcol.getSize() << endl;
			for(int i=0;i<ppcol.getSize();i++)
			{
				vector<Point> temp_ptv = ppcol.getNext(1);
				for (Point pt : temp_ptv)
					cout<< "( "<< pt.getCoordinates().at(0)<< " ," << pt.getCoordinates().at(1) << " )" <<endl;
			}
		}
		else{
			cout << "Fail Test 15"<<endl;
		}
	}
	
	cout<<"\n---------------------------------------------------------------------------------------------\n";
	cout<<"Test 16 (Data Index) : Distance Join Using Data Index\n";
	cout<<"\t Point-Point\n";
	cout<<"\t DistanceJoin all points whose distance is less than 5";
	cout<<"\n---------------------------------------------------------------------------------------------\n";
	{
		QueryTree qTree;
		qTree.setRootType(DISTANCE_JOIN);
		qTree.setRootParam(5);

		qTree.setLeftFilter(filterNull);
		qTree.setRightFilter(filterNull);

		cout<<"POINT DATASET LEFT\t\tPOINT DATASET RIGHT";

		
		vector<Point> temp1,temp2;
		
		for(int i=0;i<7;i++){
			cout<<"\n\t("<<0<<","<<i<<")\t\t\t\t("<<0<<","<<i+2<<")";
			temp1.push_back(Point(0,i));
			temp2.push_back(Point(0,i+2));
		}

		qTree.setRightRectangles(retcolNull);
		qTree.setLeftRectangles(retcolNull);
			
		PointCollection *ptcolleft = new PointCollection("table2","db1",COLLECTION_STRUCT_UNSORTED,temp1);		
		SpatialIndexInterface* dileft = new DataIndexingWrapper();
		dileft->createIndex(*ptcolleft);
		qTree.setLeftPoints(*ptcolleft);
		qTree.setLIndexType(DATA_INDEX);
		CatalogItem *catItem1;
		catItem1 = new CatalogItem("db1", "table2",TYPE_POINT, ptcolleft);
		Catalog::Instance()->insert(catItem1);

		CatalogItem* ci_left = Catalog::Instance()->getCatalogItem("db1","table2");
		ci_left->addDataIndex(dileft);

		PointCollection *ptcolright = new PointCollection("table3","db1",COLLECTION_STRUCT_UNSORTED,temp2);		
		SpatialIndexInterface* diright = new DataIndexingWrapper();
		diright->createIndex(*ptcolright);
		qTree.setRightPoints(*ptcolright);
		qTree.setRIndexType(DATA_INDEX);
		CatalogItem *catItem2;
		catItem2 = new CatalogItem("db1", "table3",TYPE_POINT, ptcolright);
		Catalog::Instance()->insert(catItem2);

		CatalogItem* ci_right = Catalog::Instance()->getCatalogItem("db1","table3");
		ci_right->addDataIndex(diright);
		QueryResult qResult;
		QueryProcessing query;
		qResult = query.processQuery(qTree);

		if (qResult.getResultType() == TYPE_POINTPOINT){
			PointPointCollection ptcoll = qResult.getPointPointCollection();
			cout<<"\nRESULT: PointPointCollection"<<endl;
			cout << "ResultSet Size : " << ptcoll.getSize() << "\n\n";
			for(int i=0;i<ptcoll.getSize();i++)
			{
				vector<PointPoint> tempt_ppt = ptcoll.getNext(1);
				for ( PointPoint ppt : tempt_ppt){
					cout<< "[(" << ppt.getCoordinates().at(0)<< " ," << ppt.getCoordinates().at(1) <<"),"
						<< "("<< ppt.getCoordinates().at(2)<< " ," << ppt.getCoordinates().at(3) <<") ]"<<endl;
				}
			}
		}
		else{
			cout << "Fail Test 16"<<endl;
		}
	}

	cout<<"\n---------------------------------------------------------------------------------------------\n";
	cout<<"Test 18 (Spatial Index) : Objects in Range -\n\t Find the Rectangles  from Rectangle (0,0,4,4)";
	cout<<"\n---------------------------------------------------------------------------------------------\n";
	{
		QueryTree qTree;
		qTree.setRootType(NO_JOIN);

		vector<float> inputParams = { 0, 0, 4,4};

		char ft=OBJECTS_IN_RANGE;
		Filter f = Filter(ft,inputParams);
		vector<Filter> filter;
		filter.push_back(f);
		qTree.setLeftFilter(filter);

		qTree.setRightFilter(filterNull);
		vector<Rectangle> tempData2;
 
		for(int i=0;i<6;i++){
			cout<<"("<<i<<","<<i<<"), ("<<i+2<<","<<i+2<<")\n";
			tempData2.push_back(Rectangle(i,i,i+2,i+2));
		}

		qTree.setRightPoints(ptcolNull);
		qTree.setRightRectangles(retcolNull);
		
		RectangleCollection *retcol = new RectangleCollection("stable1","db1",COLLECTION_STRUCT_UNSORTED,tempData2);		
		SpatialIndexInterface* sp = new SpatialIndexImpl();	
		sp->createIndex(*retcol);
		qTree.setLeftRectangles(*retcol);
		qTree.setLIndexType(SPATIAL_INDEX);
		CatalogItem *catItem;
		catItem = new CatalogItem("db1", "stable1",TYPE_RECTANGLE, retcol);
		Catalog::Instance()->insert(catItem);

		CatalogItem* ci = Catalog::Instance()->getCatalogItem("db1","stable1");
		ci->addSpatialIndex(sp);
		cout<< "Before processQuery()"<<endl;
		QueryResult qResult;
		QueryProcessing query;
		qResult = query.processQuery(qTree);

		if (qResult.getResultType() == TYPE_RECTANGLE){
			RectangleCollection rcoll = qResult.getRectangleCollection();
			cout<<"\nRESULT: RectangeCollection"<<endl;
			for(int i=0;i<rcoll.getSize();i++)
			{
				vector<Rectangle> temp_ptv = rcoll.getNext(1);
				for (Rectangle rt : temp_ptv){
					cout<< "(" << rt.getCoordinates().at(0)<< " ," << rt.getCoordinates().at(1)<< "), ("
						<< rt.getCoordinates().at(2)<< " ," << rt.getCoordinates().at(3)<<")"<<endl;
				}
			}
		}
		else if (qResult.getResultType() == TYPE_POINT){
			PointCollection ppcol = qResult.getPointCollection();
			cout<<"\nRESULT: PointCollection"<<endl;
			cout<<"RESULT SIZE : "<< ppcol.getSize() << endl;
			for(int i=0;i<ppcol.getSize();i++)
			{
				vector<Point> temp_ptv = ppcol.getNext(1);
				for (Point pt : temp_ptv)
					cout<< "( "<< pt.getCoordinates().at(0)<< " ," << pt.getCoordinates().at(1) << " )" <<endl;
			}
		}
		else{
			cout << "Fail Test 18"<<endl;
		}
		
	}

	cout<<"\n---------------------------------------------------------------------------------------------\n";
	cout<<"Test 19 (Spatial Index) : Using Spatial Index on Rectangle Collection"<<
		   "\n\tObjects in Range -\n\tFind the Points in range of Rectangle (0,0,5,5) ";
	cout<<"\n---------------------------------------------------------------------------------------------\n";
	{
		QueryTree qTree;
		qTree.setRootType(NO_JOIN);

		vector<float> inputParams = { 0, 0, 5, 5};

		char ft=OBJECTS_IN_RANGE;
		Filter f = Filter(ft,inputParams);
		vector<Filter> filter;
		filter.push_back(f);
		qTree.setLeftFilter(filter);
		qTree.setRightFilter(filterNull);
		
		vector<Point> tempData1;
		
		for(int i=0;i<7;i++){
			cout<<"("<<i<<","<<i+1<<")\n";
			tempData1.push_back(Point(i,i+1));
		}

		qTree.setRightPoints(ptcolNull);
		qTree.setRightRectangles(retcolNull);
		
		PointCollection *ptcol = new PointCollection("stable","db1",COLLECTION_STRUCT_UNSORTED,tempData1);		
		SpatialIndexInterface* di = new SpatialIndexImpl();
		di->createIndex(*ptcol);
		qTree.setLeftPoints(*ptcol);
		qTree.setLIndexType(SPATIAL_INDEX);
		CatalogItem *catItem;
		catItem = new CatalogItem("db1", "stable",TYPE_POINT, ptcol);
		Catalog::Instance()->insert(catItem);

		CatalogItem* ci = Catalog::Instance()->getCatalogItem("db1","stable");
		ci->addSpatialIndex(di);
	
		QueryResult qResult;
		QueryProcessing query;
		qResult = query.processQuery(qTree);

		if (qResult.getResultType() == TYPE_POINT){
			PointCollection ppcol = qResult.getPointCollection();
			cout<<"\nRESULT: PointCollection"<<endl;
			cout<<"RESULT SIZE : "<< ppcol.getSize() << endl;
			for(int i=0;i<ppcol.getSize();i++)
			{
				vector<Point> temp_ptv = ppcol.getNext(1);
				for (Point pt : temp_ptv)
					cout<< "( "<< pt.getCoordinates().at(0)<< " ," << pt.getCoordinates().at(1) << " )" <<endl;
			}
		}
		else{
			cout << "Fail Test 19"<<endl;
		}
	}
	
	cout<<"\n---------------------------------------------------------------------------------------------\n";
	cout<<"Test 20 (Spatial Index) : Distance Join Using Spatial Index\n";
	cout<<"\t Point-Point\n";
	cout<<"\t DistanceJoin all points whose distance is less than 5";
	cout<<"\n---------------------------------------------------------------------------------------------\n";
	{
		QueryTree qTree;
		qTree.setRootType(DISTANCE_JOIN);
		qTree.setRootParam(5);

		qTree.setLeftFilter(filterNull);
		qTree.setRightFilter(filterNull);

		cout<<"POINT DATASET LEFT\t\tPOINT DATASET RIGHT";

		
		vector<Point> temp1,temp2;
		
		for(int i=0;i<7;i++){
			cout<<"\n\t("<<0<<","<<i<<")\t\t\t\t("<<0<<","<<i+2<<")";
			temp1.push_back(Point(0,i));
			temp2.push_back(Point(0,i+2));
		}

		qTree.setRightRectangles(retcolNull);
		qTree.setLeftRectangles(retcolNull);
			
		PointCollection *ptcolleft = new PointCollection("stable2","db1",COLLECTION_STRUCT_UNSORTED,temp1);		
		SpatialIndexInterface* dileft = new SpatialIndexImpl();
		dileft->createIndex(*ptcolleft);
		qTree.setLeftPoints(*ptcolleft);
		qTree.setLIndexType(SPATIAL_INDEX);
		CatalogItem *catItem1;
		catItem1 = new CatalogItem("db1", "stable2",TYPE_POINT, ptcolleft);
		Catalog::Instance()->insert(catItem1);

		CatalogItem* ci_left = Catalog::Instance()->getCatalogItem("db1","stable2");
		ci_left->addSpatialIndex(dileft);

		PointCollection *ptcolright = new PointCollection("table3","db1",COLLECTION_STRUCT_UNSORTED,temp2);		
		SpatialIndexInterface* diright = new SpatialIndexImpl();
		diright->createIndex(*ptcolright);
		qTree.setRightPoints(*ptcolright);
		qTree.setRIndexType(SPATIAL_INDEX);
		CatalogItem *catItem2;
		catItem2 = new CatalogItem("db1", "table3",TYPE_POINT, ptcolright);
		Catalog::Instance()->insert(catItem2);

		CatalogItem* ci_right = Catalog::Instance()->getCatalogItem("db1","table3");
		ci_right->addSpatialIndex(diright);
		QueryResult qResult;
		QueryProcessing query;
		qResult = query.processQuery(qTree);

		if (qResult.getResultType() == TYPE_POINTPOINT){
			PointPointCollection ptcoll = qResult.getPointPointCollection();
			cout<<"\nRESULT: PointPointCollection"<<endl;
			cout << "ResultSet Size : " << ptcoll.getSize() << "\n\n";
			for(int i=0;i<ptcoll.getSize();i++)
			{
				vector<PointPoint> tempt_ppt = ptcoll.getNext(1);
				for ( PointPoint ppt : tempt_ppt){
					cout<< "[(" << ppt.getCoordinates().at(0)<< " ," << ppt.getCoordinates().at(1) <<"),"
						<< "("<< ppt.getCoordinates().at(2)<< " ," << ppt.getCoordinates().at(3) <<") ]"<<endl;
				}
			}
		}
		else{
			cout << "Fail Test 20"<<endl;
		}
	}
   
	cout<<"\n---------------------------------------------------------------------------------------------\n";
	cout<<"Test 17 (Data Index) : Range Join - RECTANGLE-RECTANGLE Using Data Index on Right rectangle collection\n";
	cout<<"\n---------------------------------------------------------------------------------------------\n";
	{
		QueryTree qTree;
		qTree.setRootType(RANGE_JOIN);

		qTree.setLeftFilter(filterNull);
		qTree.setRightFilter(filterNull);

		cout<<"RECTANGLE DATASET LEFT\t\tRECTANGLE DATASET RIGHT";

		vector<Rectangle> right;
		vector<Rectangle> left;
		for(int i=1;i<7;i++){
			left.push_back(Rectangle(1,1,2*i,2*i));
			right.push_back(Rectangle(i-1,i-1,i+1,i+1));
			cout<<"\n(("<<1<<","<<1<<"),("<<2*i<<","<<2*i<<"))\t\t\t(("<<i-1<<","<<i-1<<"),("<<i+1<<","<<i+1<<"))";
		}
		cout<<"\n";
		qTree.setLeftPoints(ptcolNull);
		qTree.setRightPoints(ptcolNull);

	
		RectangleCollection *rtcolleft = new RectangleCollection("table4","db1",COLLECTION_STRUCT_UNSORTED,left);
		SpatialIndexInterface* dileft = new DataIndexingWrapper();
		dileft->createIndex(*rtcolleft);
		qTree.setLeftRectangles(*rtcolleft);
		qTree.setLIndexType(DATA_INDEX);
		CatalogItem *catItem1;
		catItem1 = new CatalogItem("db1", "table4",TYPE_RECTANGLE, rtcolleft);
		Catalog::Instance()->insert(catItem1);
		CatalogItem* ci3 = Catalog::Instance()->getCatalogItem("db1","table4");
		ci3->addDataIndex(dileft);
		
		RectangleCollection *rtcolright2 = new RectangleCollection("table5","db1",COLLECTION_STRUCT_UNSORTED,right);
		SpatialIndexInterface* diright2 = new DataIndexingWrapper();
		diright2->createIndex(*rtcolright2);
		qTree.setRightRectangles(*rtcolright2);
		qTree.setRIndexType(DATA_INDEX);
		CatalogItem *catItem2;
		catItem2 = new CatalogItem("db1", "table5",TYPE_RECTANGLE, rtcolright2);
		Catalog::Instance()->insert(catItem2);
		CatalogItem* ci4 = Catalog::Instance()->getCatalogItem("db1","table5");
		ci4->addDataIndex(diright2);

		QueryResult qResult;
		QueryProcessing query;
		qResult = query.processQuery(qTree);

		if (qResult.getResultType() == TYPE_RECTANGLERECTANGLE){
			RectangleRectangleCollection retcoll = qResult.getRectangleRectangleCollection();
			cout << "\n\nRESULT: RectangleRectangleCollection";
			cout << "\nResultSet Size : " << retcoll.getSize() << "\n\n";
			for(int i=0;i<retcoll.getSize();i++)
			{
				vector<RectangleRectangle> tempt_rr = retcoll.getNext(1);
				for ( RectangleRectangle rr : tempt_rr){
					cout<< "[ ((" << rr.getCoordinates().at(0)<< " ," << rr.getCoordinates().at(1) <<"),("
						<< rr.getCoordinates().at(2)<< " ," << rr.getCoordinates().at(3) <<")), ("
						<< "("<< rr.getCoordinates().at(4)<< " ," << rr.getCoordinates().at(5) <<"),"
						<< "("<< rr.getCoordinates().at(6)<< " ," << rr.getCoordinates().at(7) <<")) ]\n";
				}
			}
		}
		else{
			cout << "Fail Test 17"<<endl;
		}

	}
    
	cout<<"\n---------------------------------------------------------------------------------------------\n";
	cout<<"Test 21 (Spatial Index) : Range Join - RECTANGLE-RECTANGLE Using Spatial Index on Right rectangle collection\n";
	cout<<"\n---------------------------------------------------------------------------------------------\n";
	{
		QueryTree qTree;
		qTree.setRootType(RANGE_JOIN);

		qTree.setLeftFilter(filterNull);
		qTree.setRightFilter(filterNull);

		cout<<"RECTANGLE DATASET LEFT\t\tRECTANGLE DATASET RIGHT";

		vector<Rectangle> right;
		vector<Rectangle> left;
		for(int i=1;i<7;i++){
			left.push_back(Rectangle(1,1,2*i,2*i));
			right.push_back(Rectangle(i-1,i-1,i+1,i+1));
			cout<<"\n(("<<1<<","<<1<<"),("<<2*i<<","<<2*i<<"))\t\t\t(("<<i-1<<","<<i-1<<"),("<<i+1<<","<<i+1<<"))";
		}

		qTree.setLeftPoints(ptcolNull);
		qTree.setRightPoints(ptcolNull);

	
		RectangleCollection *rtcolleft = new RectangleCollection("stable4","db1",COLLECTION_STRUCT_UNSORTED,left);
		SpatialIndexInterface* dileft = new SpatialIndexImpl();
		dileft->createIndex(*rtcolleft);
		qTree.setLeftRectangles(*rtcolleft);
		qTree.setLIndexType(SPATIAL_INDEX);
		CatalogItem *catItem1;
		catItem1 = new CatalogItem("db1", "stable4",TYPE_RECTANGLE, rtcolleft);
		Catalog::Instance()->insert(catItem1);
		CatalogItem* ci3 = Catalog::Instance()->getCatalogItem("db1","stable4");
		ci3->addSpatialIndex(dileft);
		
		RectangleCollection *rtcolright = new RectangleCollection("stable5","db1",COLLECTION_STRUCT_UNSORTED,right);
		SpatialIndexInterface* diright2 = new SpatialIndexImpl();
		diright2->createIndex(*rtcolright);
		qTree.setRightRectangles(*rtcolright);
		qTree.setRIndexType(SPATIAL_INDEX);
		CatalogItem *catItem2;
		catItem2 = new CatalogItem("db1", "stable5",TYPE_RECTANGLE, rtcolright);
		Catalog::Instance()->insert(catItem2);
		CatalogItem* ci4 = Catalog::Instance()->getCatalogItem("db1","stable5");
		ci4->addSpatialIndex(diright2);
		QueryResult qResult;
		QueryProcessing query;
		qResult = query.processQuery(qTree);

		if (qResult.getResultType() == TYPE_RECTANGLERECTANGLE){
			RectangleRectangleCollection retcoll = qResult.getRectangleRectangleCollection();
			cout << "\n\nRESULT: RectangleRectangleCollection";
			cout << "\nResultSet Size : " << retcoll.getSize() << "\n\n";
			for(int i=0;i<retcoll.getSize();i++)
			{
				vector<RectangleRectangle> tempt_rr = retcoll.getNext(1);
				for ( RectangleRectangle rr : tempt_rr){
					cout<< "[ ((" << rr.getCoordinates().at(0)<< " ," << rr.getCoordinates().at(1) <<"),("
						<< rr.getCoordinates().at(2)<< " ," << rr.getCoordinates().at(3) <<")), ("
						<< "("<< rr.getCoordinates().at(4)<< " ," << rr.getCoordinates().at(5) <<"),"
						<< "("<< rr.getCoordinates().at(6)<< " ," << rr.getCoordinates().at(7) <<")) ]\n";
				}
			}
		}
		else{
			cout << "Fail Test 21"<<endl;
		}

	}

}

