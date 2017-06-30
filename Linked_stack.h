#ifndef LINKED_STACK_H
#define LINKED_STACK_H

#include "utility.h" 
typedef Stack_entry Node_entry;

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


class Stack{
	public:
	//  Standard Stack methods
		Stack();
		bool empty() const;
		Error_code push(const Stack_entry &item);
		Error_code pop();
		Error_code top(Stack_entry &item) const;
	//  Safety features for linked structures
	    ~Stack();
	    Stack(const Stack &original);
	    void operator=(const Stack &original);
	protected:
		Node*top_node;
};

Stack::Stack()
{
	top_node = NULL;
}

Error_code Stack::push(const Stack_entry &item)
/*Pre:  None.
  Post: Stack_entry item is added to the top of the Stack; returns success or returns
        a code of overflow if dynamic memory is exhausted.*/
{
	Node *new_top = new Node(item, top_node);
	if (new_top == NULL) return overflow;
	top_node = new_top;
	return success;
}

Error_code Stack::pop()
/*Pre:  None.
  Post: The top of the Stack is removed. If the Stack is empty the method returns
        underflow ; otherwise it returns success.*/
{
	Node *old_top = top_node;
	if(top_node == NULL) return underflow;
	top_node = old_top->next;
	delete old_top;
	return success;
}

Error_code Stack::top(Stack_entry &item) const
/*Pre:  None.
  Post: Entry at the top of the Stack is written to Stack_entry item. If the Stack 

        is empty the method returns underflow; otherwise it returns success.*/
{
	if(top_node == NULL) return underflow;
	item = top_node->entry;
	return success;
 }
 
bool Stack::empty() const
{
 	return top_node == NULL;
}

Stack::~Stack()       //  Destructor
/*Post: The Stack is cleared. */
{
	while(!empty())  pop();
}

void Stack::operator=(const Stack &original)  // Overload assignment
/*Post: The Stack is reset as a copy of Stack original. */
{
	Node *new_top, *new_copy, *original_node = original.top_node;
	if (original_node == NULL) new_top = NULL;
	else{                // Duplicate the linked nodes.
	    new_copy = new_top = new Node(original_node->entry);
	    while (original_node->next != NULL){
	    	original_node = original_node->next;
	    	new_copy->next = new Node(original_node->entry);
	    	new_copy = new_copy->next;
		}
	}
	while (!empty())  pop();
	top_node = new_top;
}

Stack::Stack(const Stack &original)  // copy constructor
/*Post: The Stack is initialized as a copy of Stack original. */
{
	Node *new_copy, *original_node = original.top_node;
	if (original_node == NULL) top_node = NULL;
	else{                // Duplicate the linked nodes.
		top_node = new_copy = new Node(original_node->entry);
		while (original_node->next != NULL){
			original_node = original_node->next;
			new_copy->next = new Node(original_node->entry);
			new_copy = new_copy->next;
		}
	}
}

#endif
