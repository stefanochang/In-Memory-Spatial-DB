#include "constants.h"
#include "list.h"
#include<string>
#include<sstream>
#include <iostream>
#include <map>
using namespace std;

class MetaData {
  private:
    unsigned int number_of_rows;
    list table_head;
    short type_of_data;

    std::string int_to_string(unsigned int number) {
      std::stringstream out;
      out << number;
      return out.str();
    }

  public:
    void put_metadata(std::string key, unsigned int value) {
      if(key == METADATA_NUMBER_OF_ROWS) {
        number_of_rows = value;
      } else if(key == METADATA_DATATYPE) {
        type_of_data = (short)value;
      }
    }

    void put_metadata(list value) {
      table_head = value;
    }

    void put_metadata(std::string key, std::string value) {

    }

    std::string get_metadata(std::string key) {
      if(key == METADATA_NUMBER_OF_ROWS) {
        return int_to_string(number_of_rows);
      } else if(key == METADATA_DATATYPE) {
        return int_to_string(type_of_data);
      }
    }

    list get_table_head() {
      return table_head;
    }
};

class MetaStore {
  private:
    std::map<std::string, MetaData> metastore;

    void init_table_meta_data(std::string table_name) {
      metastore[table_name] = MetaData();
      metastore[table_name].put_metadata(METADATA_NUMBER_OF_ROWS, 0);
    }

  public:
    void put_metadata(std::string table_name, std::string key, std::string value) {
      if(key.empty() || value.empty()) {
        throw;
      }

      if(metastore.find(table_name) == metastore.end()) {
        init_table_meta_data(table_name);
      }

      metastore[table_name].put_metadata(key, value);
    }

    void put_metadata(std::string table_name, std::string key, unsigned int value) {
      if(key.empty()) {
        throw;
      }

      if(metastore.find(table_name) == metastore.end()) {
        init_table_meta_data(table_name);
      }

      metastore[table_name].put_metadata(key, value);
    }

    void put_metadata(std::string table_name, list table_head) {
      if(metastore.find(table_name) == metastore.end()) {
        init_table_meta_data(table_name);
      }

      metastore[table_name].put_metadata(table_head);
    }

    std::string get_metadata(std::string table_name, std::string key) {
      if(metastore.find(table_name) == metastore.end()) {
        throw;
      }

      return metastore[table_name].get_metadata(key);
    }

    list get_table_head(std::string table_name) {
      if(metastore.find(table_name) == metastore.end()) {
        throw;
      }

      return metastore[table_name].get_table_head();
    }
};
