#include "datatypes.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

class list
{
  int curr_id;
  record* head;
  public:
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

  void appendLast(geometry *geom)
  {
    if(head == NULL)
    {
      head = (record *)malloc(sizeof(record));
      head->geom = geom;
      head->id = curr_id++;
      head->next = head;
      head->prev = head;
    }
    else
    {
      record* tmp_head = head->prev;
      tmp_head->next = (record *)malloc(sizeof(record));
      record* tmp = tmp_head->next;
      tmp->next = head;
      tmp->prev = tmp_head;
      tmp->id = curr_id++;
      tmp->geom = geom;
    }
  }

	void appendFirst(geometry *geom)
  {
		if(head == NULL)
		{
			head = (record *)malloc(sizeof(record));
			head->next = head;
			head->prev = head;
			head->id = curr_id++;
			head->geom = geom;
		}
		else
		{
			record *tmp_head = (record *)malloc(sizeof(record));
			tmp_head->prev = head->prev;
      head->prev = tmp_head;
			tmp_head->next = head;
			tmp_head->id = curr_id++;
			tmp_head->geom = geom;
			head = tmp_head;
		}
	}

  void appendSortedX(geometry *geom)
  {
    if(head == NULL)
		{
			head = (record *)malloc(sizeof(record));
			head->next = head;
			head->prev = head;
			head->id = curr_id++;
			head->geom = geom;
		}
    else
    {
      record* newNode = (record *)malloc(sizeof(record));
      newNode->geom = geom;
      record* current = head;
      record* previous = head->prev;
      while(current->next != head)
      {
         if(current->geom->pnt->x > newNode->geom->pnt->x)
         {
           newNode->next = current;
           previous->next = newNode;
           newNode->prev = previous;
           current->prev = newNode;
           break;
         }
         previous = current;
         current = current->next;
      }
      if(current->next == head)
      {
        appendLast(geom);
        free(newNode);
      }
    }
  }

  void appendSortedY(geometry *geom)
  {
    if(head == NULL)
		{
			head = (record *)malloc(sizeof(record));
			head->next = head;
			head->prev = head;
			head->id = curr_id++;
			head->geom = geom;
		}
    else
    {
      record* newNode = (record *)malloc(sizeof(record));
      newNode->geom = geom;
      record* current = head;
      record* previous = head->prev;
      while(current->next != head)
      {
         if(current->geom->pnt->y > newNode->geom->pnt->y)
         {
           newNode->next = current;
           previous->next = newNode;
           newNode->prev = previous;
           current->prev = newNode;
           break;
         }
         previous = current;
         current = current->next;
      }
      if(current->next == head)
      {
        appendLast(geom);
        free(newNode);
      }
    }
  }

};
