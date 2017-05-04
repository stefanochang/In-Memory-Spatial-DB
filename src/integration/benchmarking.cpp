#ifndef INTEGRATION_HELPER_H
#include "integration-helper.h"
#endif

#include <fstream>
#include <iostream>
#include <string>
#include <numeric>
#include <chrono>

using namespace std;
using namespace std::chrono;

int main(int argc,char *argv[]) {

    string fileName = "sampleQueries.txt";
    bool pauseAfterQueryExec = false;
    if(argc > 1) {
        fileName = argv[1];
    }
    if(argc > 2) {
        pauseAfterQueryExec = strcmp(argv[2], "pause") == 0;
    }
    ifstream testFileReader;
    testFileReader.open(fileName);
    string query;
    if (testFileReader.is_open()) {
        while (!testFileReader.eof()) {
            getline(testFileReader, query);
            cout << "\n\nEXECUTING: " << query << endl;              
            high_resolution_clock::time_point startTime = high_resolution_clock::now();         
            for(int i=0; i<5; i++) {
                parseQuery(query);                
            }
            high_resolution_clock::time_point  endTime = high_resolution_clock::now();
            auto totalTimeTaken = duration_cast<microseconds>(endTime - startTime).count();
            cout << "Execution Time: " << totalTimeTaken << endl;
            if(pauseAfterQueryExec) {
                cin.get();
            }
        }
    }
    testFileReader.close();
    return 0;
}
