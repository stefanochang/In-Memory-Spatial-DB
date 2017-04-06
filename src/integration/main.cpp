#ifndef QUERY_PROCESSING_H
#include "query-processing.h"
#endif

#ifndef CATALOG_H
#include "catalog.h"
#endif

#include <iostream>
#include <vector>
#include <string.h>

using namespace std;
int get_geom_type_from_string(string geom) {
    if(geom.compare("POINT") == 0) return 1;
    if(geom.compare("RECTANGLE") == 0) return 2;
    cout << "Invalid Parameter for geometry type.\n"; 
    return -1;
}

bool is_param_sufficient(vector<string> tokens, int required_params) {
    if(tokens.size() < required_params) {
        cout << "Insufficient Parameters\n";   
        return false;
    }
    return true;
}

vector<string> split(string str, string sep) {
    size_t pos = 0;
    string token;
    vector<string> arr;
    while ((pos = str.find(sep)) != string::npos) {
        token = str.substr(0, pos);
        str.erase(0, pos + sep.length());
        arr.push_back(token);
    }
    arr.push_back(str);
    return arr;
}

vector<vector<string> > get_predicates_from_string(string predicates) {
    vector<string> left_params = split(predicates, "|");
    vector<vector<string> > predicate_vector;
    for(int i=1; i< left_params.size(); i++) {
        predicate_vector.push_back(split(left_params[i], ":"));   
    }
    
    return predicate_vector;
}


void print_query_result(QueryResult resultset) {
    int resultType = resultset.getResultType();
    if (resultType == TYPE_POINT) {      
        PointCollection pc = resultset.getPointCollection(); 
        int size = pc.getSize();
        cout << "ResultSet size: " << size << endl;
                for (int i=0; i< pc.getSize(); i++) {
            vector<Point> point = pc.getNext(1);
            vector<float> coords = point[0].getCoordinates();
            cout << coords[0] << " " << coords[1] << endl;
        }
    }
    else {
        cout << "ERROR: Unknown Collection Type." << endl;
    }
}


int main() {
    while(1) {
        string query, cmd;
        cout << endl << "Please, enter your query: ";
        getline (cin, query);
        vector<string> query_tokens = split(query, " "); 

        if(query_tokens[0].compare("LOAD") == 0) {            
            if(is_param_sufficient(query_tokens, 6)) { 
                int collection_structure = 2;
                loadData(query_tokens[1], query_tokens[2], get_geom_type_from_string(query_tokens[3]), query_tokens[4], collection_structure);                 
                cout << "Loaded " << query_tokens[3] << " data collection into " << query_tokens[1] << "." << query_tokens[2] <<
                 " from " << query_tokens[4] << endl; 
                cout << "The Catalog now has " << Catalog::Instance()->getCatalogSize() << " entries." << endl;
            }
        }  else  if(query_tokens[0].compare("CREATE") == 0) {
            if(is_param_sufficient(query_tokens, 3)) {
                if(query_tokens[1].compare("SPATIAL-INDEX")) {
                    //Class name unknown.
                } else if(query_tokens[1].compare("DATA-INDEX")) {
                    //Class name unknown.
                } else {
                    cout << "Invalid index type.\n";                             
                }

            }      
        } else if(query_tokens[0].compare("SELECT") == 0) {    
            string query_param = query.substr(7);
            int left_param_end = query_param.find("]"); 
            string left_branch = query_param.substr(1, left_param_end-1);  
            vector<vector<string> > left_filter_param = get_predicates_from_string(left_branch);
            
            QueryTree* qTree = new QueryTree();
            QueryResult* qResult = new QueryResult();
            QueryProcessing* qProcess = new QueryProcessing();

            vector<string> rootnull = { "" };
            vector<vector<string> > leftfilternull;
            leftfilternull.push_back(rootnull);
            vector<vector<string> > rightfilternull;
            rightfilternull.push_back(rootnull);
                        
            vector<string> left_collection_details = split(left_branch.substr(0, left_branch.find("|")), " ");
            if(left_collection_details[0].compare("POINT") == 0) {
                PointCollection* pc = Catalog::Instance()->getPointCollectionByName(left_collection_details[1], left_collection_details[2]);
                qTree->setLeftPoints(*pc);
            } else {
                RectangleCollection* rc = Catalog::Instance()->getRectangleCollectionByName(left_collection_details[1], left_collection_details[2]);
                qTree->setLeftRectangles(*rc);
            }
            
            qTree->setLeftFilter(left_filter_param);
            qTree->setRoot(rootnull);
            // int root_param_end = query_param.substr(left_param_end+3).find("]");            
            // string root = query_param.substr(left_param_end+3, root_param_end);
            // vector<string> root_filter_param = split(root, ":");
            // qTree->setRoot(root_filter_param);

            // int right_param_end = query_param.substr(left_param_end+root_param_end+6).find("]"); 
            // string right_branch = query_param.substr(left_param_end+root_param_end+6, right_param_end);            
            
            // vector<string> right_collection_details = split(right_branch.substr(0, right_branch.find("|")), " ");
            // if(right_collection_details[0].compare("POINT") == 0) {
            //     // qTree->setRightPoints(Catalog::Instance()->getPointCollectionByName(right_collection_details[1], right_collection_details[2]));
            // } else if(right_collection_details[0].compare("RECTANGLE") == 0) {
            //     // qTree->setRightRectangles(Catalog::Instance()->getRectangleCollectionByName(right_collection_details[1], right_collection_details[2]));
            // }
            // vector<vector<string> > right_filter_param = get_predicates_from_string(right_branch);
            // qTree->setRightFilter(right_filter_param);
            print_query_result(qProcess->processQuery(*qTree));
            
            

        } else if(query_tokens[0].compare("EXIT") == 0) {
            exit(0);
        } else {
            cout << "ERROR: Invalid command" << endl;        
        }
    }
    return 0;
}
