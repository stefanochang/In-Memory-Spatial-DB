#include "datatypes.h"
#include <stdlib.h>

using namespace std;

class list
{
	int curr_id;
	record* head;
	short type;

 	public:
	list():head(NULL), type(type)
  	{
    		curr_id = 0;
  	}
  	~list()
  	{
    		record *tmp1,*tmp;
		if(head != NULL)
		{
			tmp1 = head;
			head = head->next;
	    		while(head != tmp1)
	    		{
	      			tmp = head->next;
				free(head);
				head = tmp;
	    		}
			free(head);
		}
  	}

  	void appendLast(geometry *geom)
  	{
    		if(head == NULL)
    		{
      			head = (record *)malloc(sizeof(record));
      			head->geom = geom;
      			head->id = curr_id++;
			head->isDeleted = false;
			head->inDegree = 0;
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
		      tmp->isDeleted = false;
		      tmp->inDegree = 0;
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
			head->isDeleted = false;
			head->inDegree = 0;
			head->geom = geom;
		}
		else
		{
			record *tmp_head = (record *)malloc(sizeof(record));
			tmp_head->prev = head->prev;
      			head->prev = tmp_head;
			tmp_head->next = head;
			tmp_head->id = curr_id++;
			tmp_head->isDeleted = false;
			tmp_head->inDegree = 0;
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
			head->isDeleted = false;
			head->inDegree = 0;
		}
    		else
    		{
		      record* newNode = (record *)malloc(sizeof(record));
		      newNode->geom = geom;
		      newNode->id = curr_id++;
		      newNode->isDeleted = false;
		      newNode->inDegree = 0;
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
			head->isDeleted = false;
			head->inDegree = 0;
		}
    		else
    		{
		      record* newNode = (record *)malloc(sizeof(record));
		      newNode->geom = geom;
		      newNode->id = curr_id++;
		      newNode->isDeleted = false;
		      newNode->inDegree = 0;
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

  int deleteByUUID(int id)
  {
    if(head == NULL)
		{
			return -1;
		}
    else
    {
      record* current = head;
      record* previous = head->prev;
      while(current->next != head)
      {
         if(current->id == id)
         {
           previous->next = current->next;
           current = current->next;
           current->prev = previous;
           return 1;
         }
         previous = current;
         current = current->next;
      }
      if(current->next == head)
      {
        if(current->id == id)
        {
          previous->next = head;
          head->prev = previous;
          return 1;
        }
      }
    }
    return -1;
  }

	void* getPointByUUID(char table_name[], int objectId)
	{
		//place-holder for call to metadata table to get head
		//place-holder for assigning received head to the head variable
		if(head == NULL)
		{
			return NULL;
		}
		else
		{
			while(head != NULL)
			{
				if(head->id == objectId)
				{
					point* pt = (point *)malloc(sizeof(point));
					pt->x = head->geom->pnt->x;
					pt->y = head->geom->pnt->y;
					return pt;
				}
				head = head->next;
			}
			return NULL;
		}
	}

	record * getHead() {
		return head;
	}

	short getType() {
		return type;
	}
};
