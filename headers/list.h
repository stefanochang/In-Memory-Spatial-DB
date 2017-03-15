#include "../headers/structs.h"
#include <iostream>
using namespace std;

class list
{
  int curr_id;
  record* head;
  list():head(NULL)
  {
    curr_id = 0;
  }
  ~list()
  {
    record* tmp;
    for(;head;head = tmp)
    {
      tmp = head->next;
      delete head;
    }
  }

  void append(geometry geom)
  {
    if(head == NULL)
    {
      head = new record();
      head->geom = geom;
      head->id = curr_id++;
      head->next = NULL;
      head->prev = NULL;
    }
    else
    {
      record* tmp_head = head;
      while(tmp_head->next)
      {
        tmp_head = tmp_head->next;
      }
      tmp_head->next = new record();
      record* tmp = tmp_head->next;
      tmp->next = NULL;
      tmp->prev = tmp_head;
      tmp->id = curr_id++;
      tmp->geom = geom;
    }
  }
};
