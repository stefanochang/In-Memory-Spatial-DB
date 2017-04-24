#ifndef INTEGRATION_HELPER_H
#include "integration-helper.h"
#endif

#include <iostream>

using namespace std;



int main() {
    while(1) {
        string query, cmd;
        cout << endl << "Enter your query: ";
        getline (cin, query);
        vector<string> query_tokens = split(query, " "); 

        if(query_tokens[0].compare("LOAD") == 0) {            
            processLoadQuery(query_tokens);
        } else  if(query_tokens[0].compare("CREATE") == 0) {
            processIndexQuery(query_tokens);      
        } else if(query_tokens[0].compare("SELECT") == 0) {    
            processSelectQuery(query_tokens, query);            
        } else if(query_tokens[0].compare("INSERT") == 0) {
            processInsertQuery(query_tokens);
        } else if(query_tokens[0].compare("EXIT") == 0) {
            exit(0);
        } else {
            cout << "ERROR: Invalid command" << endl;        
        }
    }
    return 0;
}
