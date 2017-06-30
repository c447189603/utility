#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "utility.h"
template <class Node_entry>
struct Node{
	//  data members
	Node_entry entry;
	Node<Node_entry> *next;
	//  constructors
	Node();
	Node(Node_entry item, Node<Node_entry>* link = NULL);
};

template <class Node_entry>
Node<Node_entry>::Node()
{
	next = NULL;
}

template <class Node_entry>
Node<Node_entry>::Node(Node_entry item, Node<Node_entry>* link)
{
	entry = item;
	next = link;
}


template <class List_entry>
class List{
	public:
	//  Specifications for the methods of the list ADT go here.
		List();
	    int size() const;
	    bool full() const;
	    bool empty() const;
	    void clear();        // sth wrong here
	    void traverse(void (*visit)(List_entry &));
	    Error_code retrieve(int position, List_entry &x) const;
	    Error_code replace(int position, const List_entry &x);
	    Error_code remove(int position, List_entry &x);
	    Error_code insert(int position, const List_entry &x);
	//  The following methods replace compiler-generated defaults.
	    ~List();             // not yet implemented
		List(const List<List_entry> &copy);
		void operator=(const List<List_entry> &copy);
	protected:
	//  Data members for the linked list implementation now follow.
	    int count;
	    Node<List_entry>* head;
	//  The following auxiliary function is used to locate list positions
	    Node<List_entry>* set_position(int position) const;	
};

template <class List_entry>
List<List_entry>::List()
{
	count = 0;
	head = NULL;
}

template <class List_entry>
int List<List_entry>::size() const
{
	return count;
}

template <class List_entry>
bool List<List_entry>::full() const
{
    Node<List_entry>* q = head;
	for (int i = 0; i < count - 1; i++) q = q->next;
	q->next = new Node<List_entry>();
	if (q->next == NULL) return true;
	else return false;
}

template <class List_entry>
bool List<List_entry>::empty() const
{
	return count == 0;
}

template <class List_entry>
void List<List_entry>::clear()
{
	List_entry a;
	while (!empty()){
		remove(count - 1,a);
	}
}

template <class List_entry>
void List<List_entry>::traverse(void (*visit)(List_entry &))
{
	for (int i = 0; i < count; i++){
		(*visit)(set_position(i)->entry);
	}
}

template <class List_entry>
Error_code List<List_entry>::retrieve(int position, List_entry &x) const
{
	if (position < 0 || position >= count) return range_error;
	x = set_position(position)->entry;
	return success;
}

template <class List_entry>
Error_code List<List_entry>::replace(int position, const List_entry &x)
{
	if (position < 0 || position >= count) return range_error;
	set_position(position)->entry = x;
	return success;
}

template <class List_entry>
Error_code List<List_entry>::remove(int position, List_entry &x)
{
	if (position < 0 || position >= count) return range_error;
	Node<List_entry>* old_pointer = set_position(position);
	if (position == 0) head = old_pointer->next;
	else {
		Node<List_entry>* linker = set_position(position - 1);
		linker->next = old_pointer->next;
	}
	delete old_pointer;
	return success;
}

template <class List_entry>
Error_code List<List_entry>::insert(int position, const List_entry &x)
/* Post: If the List is not full and 0 <= position <= n, where n is the number of entries in
         the List, the function succeeds: Any entry formerly at position and all later
         entries have their position numbers increased by 1, and x is inserted at 
         position of the List.
         Else: The function fails with a diagnostic error code. */
{
	if (position < 0 || position > count)
	  return range_error;
	Node<List_entry> *new_node, *previous, *following;
	if (position > 0){
		previous = set_position(position - 1);
		following = previous->next;
	}
	else following = head;
	new_node = new Node<List_entry>(x,following);
	if (new_node == NULL) return overflow;
	if (position == 0) head = new_node;
	else previous->next = new_node;
	count++;
	return success;
}

template <class List_entry>
List<List_entry>::~List()
{
	
}

template <class List_entry>
List<List_entry>::List(const List<List_entry> &copy)
{
	Node<List_entry> *new_copy, *original_node = copy.head;
	if (original_node == NULL) head = NULL;
	else{
		head = new_copy = new Node<List_entry>(original_node->entry);
		while (original_node->next != NULL){
			original_node = original_node->next;
			new_copy->next = new Node<List_entry>(original_node->entry);
			new_copy = new_copy->next;
		}
	}
}

template <class List_entry>
void List<List_entry>::operator=(const List<List_entry> &copy)
{
	Node<List_entry> *new_head, *new_copy, *original_node = copy.head;
	if (original_node == NULL) new_head = NULL;
	else{
		new_copy = new_head = new Node<List_entry>(original_node->entry);
		while (original_node->next != NULL){
			original_node = original_node->next;
			new_copy->next = new Node<List_entry>(original_node->entry);
			new_copy = new_copy->next;
		}
	}
	clear();
	head = new_head;
}

template <class List_entry>
Node<List_entry>* List<List_entry>::set_position(int position) const
/* Pre:  position is a valid position in the List; 0 <= position < count.
   Post: Returns a pointer to the Node in position. */
{
	Node<List_entry>* q = head;
	for (int i = 0; i < position; i++) q = q->next;
	return q;
}


#endif
