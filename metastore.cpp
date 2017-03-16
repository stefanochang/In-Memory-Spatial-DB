#include<metastore.h>
#include<list.h>
#include<constants.h>

class MetaData {
  private:
    unsigned int number_of_rows;
    list *table_head;
    std:string type_of_data;

  public:
    void put_metadata(std::string key, unsigned int value) {
      if(key == METADATA_NUMBER_OF_ROWS) {
        number_of_rows = value;
      }
    }

    void put_metadata(std::string key, list *value) {
      table_head = value;
    }

    void put_metadata(std::string key, std::string value) {
      type_of_data = value;
    }
};

class MetaStore {
  private:
    void init_table_meta_data(std::map<std::string, std::map> *map, std::string table_name) {
      metastore[table_name] = MetaData();
      metastore[table_name].put_metadata(METADATA_NUMBER_OF_ROWS, 0)
    }

  public:
    void put_metadata(std::string table_name, std::string key, std:string value) {
      if(table_name == NULL || key == NULL || value == NULL) {
        throw;
      }

      if(metastore[table_name] == NULL) {
        init_table_meta_data()
      }

      metastore[table_name].put_metadata(key, value);
    }
};
