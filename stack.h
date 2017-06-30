#ifndef STACK_H
#define STACK_H

#include "utility.h"
const int maxstack = 10;            // small value for testing

class Stack{
	public:
		Stack();
		bool empty() const;
		Error_code pop();
		Error_code top(Stack_entry &item) const;
		Error_code push(const Stack_entry &item);
	private:
		int count;
		Stack_entry entry[maxstack];	
};


Error_code Stack::push(const Stack_entry &item)
/*Pre:  None.
  Post: If the Stack is not full, item is added to the top of the Stack. If the Stack is
   full, an Error_code of overflow is returned and the Stack is left unchanged. */
{
	Error_code outcome = success;
	if (count >= maxstack)
	  outcome = overflow;
	else
	  entry[count++] = item;
	return outcome;
}

Error_code Stack::pop()
/*Pre:  None.
  Post: If the Stack is not empty, the top of the Stack is removed. If the Stack is
   empty, an Error_code of underflow is returned. */
{
	Error_code outcome = success;
	if (count == 0)
	  outcome = underflow;
	else 
	  --count;
	return outcome;
}

Error_code Stack::top(Stack_entry &item) const
/*Pre:  None.
  Post: If the Stack is not empty, the top of the Stack is returned in item. If the Stack
   is empty an Error_code of underflow is returned. */
{
	Error_code outcome = success;
	if (count == 0)
	  outcome = underflow;
	else
	  item = entry[count - 1];
	return outcome;
}

bool Stack::empty() const
/*Pre:  None.
  Post: If the Stack is empty, true is returned. Otherwise false is returned. */
{
	bool outcome = true;
	if (count > 0)
	  outcome = false;
	return outcome;
}

Stack::Stack()
/*Pre:  None.
  Post: The Stack is initialized to be empty. */
{
	count = 0;
}

#endif
