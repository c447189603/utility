#ifndef EXTENDED_QUEUE_H
#define EXTENDED_QUEUE_H

#include "queue.h"
class Extended_queue:public Queue{
	public:
		bool full() const;
		int size() const;
		void clear();
		Error_code serve_and_retrieve(Queue_entry &item);
};

bool Extended_queue::full() const
{
	return count == maxqueue;
}

void Extended_queue::clear()
{
	count = 0;
	rear = maxqueue - 1;
 	front = 0;
}

int Extended_queue::size() const
{
	return count;
}

Error_code Extended_queue::serve_and_retrieve(Queue_entry &item)
{
	if (count <= 0) return underflow;
	item = entry[front];
	count--;
	front = ((front + 1) == maxqueue) ? 0 : (front + 1);
	return success;
}


