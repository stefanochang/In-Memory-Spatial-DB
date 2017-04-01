	#include "ds_datatypes.h"
	#include <stdlib.h>
	#include "ds_constants.h"
	#include <string.h>
	#include <map>

	using namespace std;
	std::map<int, record *>getmap;
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
			list(int type)
			{
					head = NULL;
					this->type = type;
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
			    record* temp = head;
			    while(current->next != head)
			    {
			       if(current->id == id)
			       {
			         if(current->inDegree <= 0)
							 {
								 temp = current;
				         previous->next = current->next;
				         current = current->next;
				         current->prev = previous;
				         free(temp);
				         return 1;
							 }
							 else
							 {
								 current->isDeleted = true;
							 }
			       }
			       previous = current;
			       current = current->next;
			    }
			    if(current->next == head)
			    {
			      if(current->id == id)
			      {
							if(current->inDegree <= 0)
							{
								temp = current;
								previous->next = current->next;
								current = current->next;
								current->prev = previous;
								free(temp);
								return 1;
							}
							else
							{
								current->isDeleted = true;
							}
			      }
			    }
			  }
			  return -1;
			}

			Point* getPointByUUID(string table_name, int objectId)
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
			      if(head->id == objectId && head->isDeleted == false)
			      {
			        float x = head->geom->pnt->x;
			        float y = head->geom->pnt->y;
			        Point* pt = new Point(x, y);
			        return pt;
			      }
			      head = head->next;
			    }
			    return NULL;
			  }
			}

			Rectangle* getRectangleByUUID(string table_name, int objectId)
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
			      if(head->id == objectId && head->isDeleted == false)
			      {
			        float x1 = head->geom->rec->top_x;
			        float y1 = head->geom->rec->top_y;
			        float x2 = head->geom->rec->bottom_x;
			        float y2 = head->geom->rec->bottom_y;
			        Rectangle* rec = new Rectangle(x1, y1, x2, y2);
			        return rec;
			      }
			      head = head->next;
			    }
			    return NULL;
			  }
			}

			PointPoint* getPointPointByUUID(string table_name, int objectId)
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
			      if(head->id == objectId && head->isDeleted == false)
			      {
			        float x1 = head->geom->pntpnt->point1.x;
			        float y1 = head->geom->pntpnt->point1.y;
			        float x2 = head->geom->pntpnt->point2.x;
			        float y2 = head->geom->pntpnt->point2.y;
			        PointPoint* pt = new PointPoint(x1, y1, x2, y2);
			        return pt;
			      }
			      head = head->next;
			    }
			    return NULL;
			  }
			}

			PointRectangle* getPointRectangleByUUID(string table_name, int objectId)
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
			      if(head->id == objectId && head->isDeleted == false)
			      {
			        float x1 = head->geom->pntrec->point1.x;
			        float y1 = head->geom->pntrec->point1.y;
			        float x2 = head->geom->pntrec->rec.top_x;
			        float y2 = head->geom->pntrec->rec.top_y;
			        float x3 = head->geom->pntrec->rec.bottom_x;
			        float y3 = head->geom->pntrec->rec.bottom_y;
			        PointRectangle* ptrec = new PointRectangle(x1, y1, x2, y2, x3, y3);
			        return ptrec;
			      }
			      head = head->next;
			    }
			    return NULL;
			  }
			}

			RectangleRectangle* getRectangleRectangleByUUID(string table_name, int objectId)
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
			      if(head->id == objectId && head->isDeleted == false)
			      {
			        float x1 = head->geom->recrec->rec1.top_x;
			        float y1 = head->geom->recrec->rec1.top_y;
			        float x2 = head->geom->recrec->rec1.bottom_x;
			        float y2 = head->geom->recrec->rec1.bottom_y;
			        float x3 = head->geom->recrec->rec2.top_x;
			        float y3 = head->geom->recrec->rec2.top_y;
			        float x4 = head->geom->recrec->rec2.bottom_x;
			        float y4 = head->geom->recrec->rec2.bottom_y;
			        RectangleRectangle* recrec = new RectangleRectangle(x1, y1, x2, y2, x3, y3, x4, y4);
			        return recrec;
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
		void *getnext(int n, int transactionId)
		{
			record *from;
			Point **pnts;
			Rectangle **recs;
			PointPoint **pntpnt;
			PointRectangle **pntrec;
			RectangleRectangle **recrec;
			int rdcnt=0;
			if(getmap.find(transactionId) != getmap.end())
			{
				from = 	getmap.find(transactionId)->second;
				from->inDegree--;
			}
			else
			{
				from = head;
			}
			while(rdcnt < n and from != head->prev)
			{
				if(from->isDeleted)
					continue;
				switch(type)
				{
					case TYPE_POINT:
						pnts[rdcnt++] = new Point(from->geom->pnt->x, from->geom->pnt->y);
					break;
					case TYPE_RECTANGLE:
						recs[rdcnt++] = new Rectangle(from->geom->rec->top_x, from->geom->rec->top_y,from->geom->rec->bottom_x, from->geom->rec->bottom_y);
					break;
					case TYPE_POINTPOINT:
						pntpnt[rdcnt++] = new PointPoint(from->geom->pntpnt->point1.x, from->geom->pntpnt->point1.y, from->geom->pntpnt->point2.x, from->geom->pntpnt->point2.y);
					break;
					case TYPE_POINTRECTANGLE:
						pntrec[rdcnt++] = new PointRectangle(from->geom->pntrec->point1.x, from->geom->pntrec->point1.y, from->geom->pntrec->rec.top_x, from->geom->pntrec->rec.top_y,from->geom->pntrec->rec.bottom_x, from->geom->pntrec->rec.bottom_y);
					break;
					case TYPE_RECTANGLERECTANGLE:
						recrec[rdcnt++] = new RectangleRectangle(from->geom->recrec->rec1.top_x, from->geom->recrec->rec1.top_y,from->geom->recrec->rec1.bottom_x, from->geom->recrec->rec1.bottom_y, from->geom->recrec->rec2.top_x, from->geom->recrec->rec2.top_y,from->geom->recrec->rec2.bottom_x, from->geom->recrec->rec2.bottom_y);
					break;
				}
				from = from->next;
			}
			getmap.erase(transactionId);
			if(from != head->prev)
			{
				getmap[transactionId] = from;
			}
			if(type == TYPE_POINT)
			{
				return *pnts;
			}
			if(type == TYPE_RECTANGLE)
			{
				return *recs;
			}
			if(type == TYPE_POINTPOINT)
			{
				return *pntpnt;
			}
			if(type == TYPE_POINTRECTANGLE)
			{
				return *pntrec;
			}
			return *recrec;
		}

		bool isEmpty() {
			return  head == NULL;
		}
	};
