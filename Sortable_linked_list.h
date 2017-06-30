#ifndef SORTABLE_LINKED_LIST_H
#define SORTABLE_LINKED_LIST_H

#include "Linked_list.h"
template<class Record>
class Sortable_list:public List<Record>{
	public:
		void insertion_sort();
                void merge_sort();
        private:
		void recursive_merge_sort(Node<Record>* &sub_list);
		Node<Record>* divide_from(Node<Record>* sub_list);
		Node<Record>* merge(Node<Record>* first, Node<Record>* second);
	
};

template<class Record>
void Sortable_list<Record>::insertion_sort()
/* Post: The entries of the Sortable_list have been rearranged so that the keys in
         all the entries are sorted into nondecresing order.
   Uses: Methods for the class Record. The linked List implementation of Chapter 6. */
{
	Node<Record> *first_unsorted,  // the first unsorted node to be inserted
	             *last_sorted,     // tail of the sorted sublist
	             *current,         // used to traverse the sorted sublist
	             *trailing;        // one position behind current
	if (List<Record>::head != NULL){        // Otherwise, the empty list is already sorted.
		last_sorted = List<Record>::head;   // The first node alone makes a sorted sublist.
		while (last_sorted->next != NULL){
			first_unsorted = last_sorted->next;
			if (first_unsorted->entry < List<Record>::head->entry){
			    //  Insert *first_unsorted at the head of the sorted list:
			    last_sorted->next = first_unsorted->next;
			    first_unsorted->next = List<Record>::head;
			    List<Record>::head = first_unsorted;	
			}
			else{
				//  Search the sorted sublist to insert *first_unsorted:
				trailing = List<Record>::head;
				current = trailing->next;
				while (first_unsorted->entry > current->entry){
					trailing = current;
					current  = trailing->next;
				} 
				// *first_unsorted now belongs between *trailings and *current.
				if (first_unsorted == current)
				  last_sorted = first_unsorted; //  already in right position
				else{
					last_sorted->next = first_unsorted->next;
					first_unsorted->next = current;
					trailing->next = first_unsorted;
				}
			}
		}
	}
}

template <class Record>
void Sortable_list<Record>::merge_sort()
/* Post: The entries of the sortable list have been rearranged so that their keys are
         sorted into nondecreasing order.
   Uses: The linked List implementation of Chapter 6 and recursive_merge_sort. */
{
	recursive_merge_sort(List<Record>::head);
}

template <class Record>
void Sortable_list<Record>::recursive_merge_sort(Node<Record>* &sub_list)
/* Post: The nodes referenced by sub_lsit have been rearranged so that their keys
         are sorted into nondecreasing order. The pointer parameter sub_list is
         reset to point at the node containing the smallest key.
   Uses: The linked List implementation of Chapter 6; the functions divide_from,
         merge, and recursive_merge_sort. */
{
	if (sub_list != NULL && sub_list->next != NULL){
		Node<Record>* second_half = divide_from(sub_list);
		recursive_merge_sort(sub_list);
		recursive_merge_sort(second_half);
		sub_list = merge(sub_list, second_half);
	}
}

template <class Record>
Node<Record>* Sortable_list<Record>::divide_from(Node<Record>* sub_list)
/* Post: The list of nodes referenced by sub_list has been reduced to its first half,
         and a pointer to the first node in the second half of the sublist is returned.
         If the sublist has an odd number of entries, then its first half will be one
         entry larger than its second.
   Uses: The linked List implementation of Chapter 6. */
{
	Node<Record> *position,  //  traverses the entire list
	             *midpoint,  //  moves at half speed of position to midpoint
	             *second_half;
	if ((midpoint = sub_list) == NULL) return NULL;  // List is empty.
	position = midpoint->next;
	while (position != NULL) {   //  Move position twice for midpoint's one move.
	    position = position->next;
	    if (position != NULL) {
	    	midpoint = midpoint->next;
	    	position = position->next;
		}
	}
	second_half = midpoint->next;
	midpoint->next = NULL;
	return second_half;
}

template <class Record>
Node<Record>* Sortable_list<Record>::merge(Node<Record>* first, Node<Record>* second)
/* Pre:  first and second point to ordered lists of nodes.
   Post: A pointer to an ordered list of nodes is returned. The ordered list contains
         all entries that were referenced by first and second. The original lists of 
         nodes referedced by first and second are no longer available.
   Uses: Methods for Record class; the linked List implementation of Chapter 6. */
{
	Node<Record>* last_sorted;  //  points to the last node of sorted list
	Node<Record> combined;      //  dummy first node, points to merged list
	last_sorted = &combined;
	while (first != NULL && second != NULL) {  //  Attach node with smaller key
	    if (first->entry <= second->entry) {
	    	last_sorted->next = first;
	    	last_sorted = first;
	    	first = first->next;     //  Advance to the next unmerged node.
		}
		else {
			last_sorted->next = second;
			last_sorted = second;
			second = second->next;
		}
	}
	//  After one list ends, attach the remainder of the other.
	if (first == NULL)
	  last_sorted->next = second;
	else
	  last_sorted->next = first;
	return combined.next;
}
#endif
