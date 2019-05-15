#include "qeue.h"


Qeue initQeue()
{
	Qeue q;
	q.front = 0;
	q.rear = -1;
	q.itemCount = 0;
	return q;
}


int peek(Qeue *q) {
   return q->intArray[q->front];
}

bool isEmpty(Qeue *q) {
   return q->itemCount == 0;
}

bool isFull(Qeue *q) {
   return q->itemCount == MAX;
}

int size(Qeue *q) {
   return q->itemCount;
}  

void insert(Qeue *q, int data) {

   if(!isFull(q)) {
	
      if(q->rear == MAX-1) {
         q->rear = -1;            
      }       

      q->intArray[++q->rear] = data;
      q->itemCount = q->itemCount+1;
   }
}

int removeData(Qeue *q) {
   int data = q->intArray[q->front++];
	
   if(q->front == MAX) {
      q->front = 0;
   }
	
   q->itemCount--;
   return data;  
}
