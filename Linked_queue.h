#ifndef LINKED_QUEUE_H
#define LINKED_QUEUE_H

#include "utility.h"
typedef Queue_entry Node_entry;

struct Node {
	// data members
	Node_entry entry;
	Node *next;
	//constructors
	Node();
	Node(Node_entry item, Node *add_on = NULL);
};


Node::Node()
{
	next = NULL;
}


Node::Node(Node_entry item, Node*add_on)
{
	entry = item;
	next = add_on;
}




class Queue{
	public:
	// standard Queue methods 
		Queue();
		bool empty() const;
		Error_code append(const Queue_entry &item);
		Error_code serve();
		Error_code retrieve(Queue_entry &item) const;
	// safety features for linked structures
	    ~Queue();
	    Queue (const Queue &original);
	    void operator=(const Queue &original);
	    
	protected:
		Node *front, *rear;
};

Queue::Queue()
/*Post: The Queue is initialized to be empty.*/
{
	front = rear = NULL;
}

Error_code Queue::append(const Queue_entry &item)
/*Post: Add item to the rear of the Queue and return a code of success or return
        a code of overflow if dynamic memory is exhausted.*/
{
	Node *new_rear = new Node(item);
	if (new_rear == NULL) return overflow;
	if (rear == NULL) front = rear = new_rear;
	else{
		rear->next = new_rear;
		rear = new_rear;
	}
	return success;
}

Error_code Queue::serve()
/*Post: The front of the Queue is removed. If the Queue is empty, return an 
        Error_code of underflow.*/
{
	if (front == NULL) return underflow;
	Node *old_front = front;
	front = old_front->next;
	if (front == NULL) rear = NULL;
	delete old_front;
	return success;
}

Error_code Queue::retrieve(Queue_entry &item) const
{
	if (front == NULL) return underflow;
	item = front->entry;
	return success;
}

bool Queue::empty() const
{
	return front == NULL;
}

Queue::~Queue()
{
	
}

#endif
