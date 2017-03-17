
#include "headers/metastore.h"

int main() {
  MetaStore metastore = MetaStore();
  metastore.put_metadata("test", METADATA_NUMBER_OF_ROWS, 10);

  list table_head = list();
  metastore.put_metadata("test", table_head);

  metastore.put_metadata("test", METADATA_DATATYPE, TYPE_RECTANGLE);

  cout<<metastore.get_metadata("test", METADATA_DATATYPE)<<"\n";
  cout<<metastore.get_metadata("test", METADATA_NUMBER_OF_ROWS)<<"\n";

  return 0;
}
