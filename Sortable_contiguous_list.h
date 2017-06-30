#ifndef SORTABLE_CONTIGUOUS_LIST_H
#define SORTABLE_CONTIGUOUS_LIST_H

#include "list.h"

template<class Record>
class Sortable_list:public List<Record>{
	public:
		void insertion_sort();
		void selection_sort();
		void shell_sort();
		void quick_sort();
		void heap_sort();
    private:
    	int max_key(int low, int high);                               // selection_sort auxiliary
    	void swap(int low, int high);                                 // selection_sort & quick_sort auxiliary
    	void sort_interval(int start, int increment);                 // shell_sort auxiliary
    	void recursive_quick_sort(int low, int high);                 // quick_sort auxiliary
    	int partition(int low, int high);                             // quick_sort auxiliary
    	void insert_heap(const Record &current, int low, int high);   // heap_sort auxiliary
    	void build_heap();                                            // heap_sort auxiliary
};




/* ------------------------------------- sorting methods ---------------------------------------- */

template<class Record>
void Sortable_list<Record>::insertion_sort()
/* Post: The entries of the Sortable_list have been rearranged so that the keys in
         all the entries are sorted into nondecreasing order.
   Uses: Methods for the class Record; the contiguous List implementation of Chap-
         ter 6 */
{
	int first_unsorted;           // position of first unsorted entry
	int position;                 // searches sorted part of list
	Record current;               // holds the entry temporarily removed from list
	for (first_unsorted = 1; first_unsorted < List<Record>::count; first_unsorted++){
		if (List<Record>::entry[first_unsorted] < List<Record>::entry[first_unsorted - 1]){
			position = first_unsorted;
			current = List<Record>::entry[first_unsorted];    // Pull unsorted entry out of the list.
			do{            // Shift all entries until the proper position is found.
			    List<Record>::entry[position] = List<Record>::entry[position - 1];
			    position--;                 // Position is empty.
			}while (position > 0 && List<Record>::entry[position - 1] > current);
			List<Record>::entry[position] = current;
		}
	}
}

template<class Record>
void Sortable_list<Record>::selection_sort()
/* Post: The entries of the Sortable_list have been rearranged so that the keys in
         all the entries are sorted into nondecreasing order.
   Uses: max_key, swap. */
{
	for (int position = List<Record>::count - 1; position > 0; position--){
		int max = max_key(0, position);
		swap(max, position);
	}
}

template<class Record>
void Sortable_list<Record>::shell_sort()
/* Post: The entries of the Sortable_list have been rearranged so that the keys in
         all the entries are sorted into nondecreasing order.
   Uses: sort_interval. */
{
	int increment,         // spacing of entries in sublist 
	    start;             // starting point of sublist
	increment = List<Record>::count;
	do {
		increment = increment/3 + 1;
		for (start = 0; start < increment; start++)
		  sort_interval(start, increment);     // modified insertion sort
	}while (increment > 1);
}

template<class Record>
void Sortable_list<Record>::quick_sort()
/* Post: The entries of the Sortable_list have been rearranged so that the keys in
         all the entries are sorted into nondecreasing order.
   Uses: The contiguous List implementation of Chapter 6, recursive_quick_sort. */
{
	recursive_quick_sort(0, List<Record>::count - 1);
}

template<class Record>
void Sortable_list<Record>::heap_sort()
/* Post: The entries of the Sortable_list have been rearranged so that the keys are
         sorted into nondecreasing order.
   Uses: The contiguous List implementation of Chapter 6, build_heap, and insert_heap. */
{
	Record current;             // temporary storage for moving entries.
	int last_unsorted;          // Entries beyond last_unsorted have been sorted.
	build_heap();               // First phase:Turn the list into a heap.
	for (last_unsorted = List<Record>::count - 1; last_unsorted > 0; last_unsorted--){
		current = List<Record>::entry[last_unsorted];      // Extract last entry from the list.
		List<Record>::entry[last_unsorted] = List<Record>::entry[0];    // Move top of heap to the end.
		insert_heap(current, 0, last_unsorted - 1);          // Restore the heap.
	}
}

/* ------------------------------------------ auxiliary functions ------------------------------------------- */

template<class Record>
int Sortable_list<Record>::max_key(int low, int high)
/* Pre:  low and high are valid positions in the Sortable_list and low <= high.
   Post: The position of the entry between low and high with the largest key is
         returned.
   Uses: The class Record. The contiguous List implementation of Chapter 6. */
{
	int largest, current;
	largest = low;
	for (current = low + 1; current <= high; current++){
		if (List<Record>::entry[largest] < List<Record>::entry[current])  largest = current;
	}
	return largest;
}

template<class Record>
void Sortable_list<Record>::swap(int low, int high)
/* Pre:  low and high are valid positions in the Sortable_list.
   Post: The entry at position low is swapped with the entry at position high.
   Uses: The contiguous List implementation of Chapter 6. */
{
	Record temp;
	temp = List<Record>::entry[low];
	List<Record>::entry[low] = List<Record>::entry[high];
	List<Record>::entry[high] = temp;
}

template<class Record>
void Sortable_list<Record>::sort_interval(int start, int increment)
{
	int first_unsorted;          
	int position;                
	Record current;               
	for (first_unsorted = start + 1; first_unsorted < List<Record>::count; first_unsorted += increment){
		if (List<Record>::entry[first_unsorted] < List<Record>::entry[first_unsorted - 1]){
			position = first_unsorted;
			current = List<Record>::entry[first_unsorted];   
			do{           
			    List<Record>::entry[position] = List<Record>::entry[position - 1];
			    position--;                
			}while (position > 0 && List<Record>::entry[position - 1] > current);
			List<Record>::entry[position] = current;
		}
	}
}

template<class Record>
void Sortable_list<Record>::recursive_quick_sort(int low, int high)
/* Pre:  low and high are valid positions in the Sortable_list.
   Post: The entries of the Sortable_list have been rearranged so that their keys
         are sorted into nondecreasing order.
   Uses: The contiguous List implementation of Chapter 6, recursive_quick_sort,
         and partition. */
{
	int pivot_position;
	if (low < high){            // Otherwise, no sorting is needed.
		pivot_position = partition(low, high);
		recursive_quick_sort(low, pivot_position - 1);
		recursive_quick_sort(pivot_position + 1, high);
	}
}

template<class Record>
int Sortable_list<Record>::partition(int low, int high)
/* Pre:  low and high are valid positions of the Sortable_list, with low <= high.
   Post: The center (or left center) entry in the range between indices low and
         high of the Sortable_list has been chosen as a pivot. All entries of the
         Sortable_list between indices low and high, inclusive, have been rear-
         ranged so that those with keys less than the pivot come before the pivot
         and the remaining entries come after the pivot. The final position of the
         pivot is returned.
   Uses: swap(int i, int j)(interchanges entries in positions i and j of a Sortable_list),
         the contiguous List implementation of Chapter 6, and methods for the 
		 class Record. */
{
	Record pivot;
	int i,                    // used to scan through the list
	    last_small;           // position of the last key less than pivot
	swap(low, (low + high)/2);
	pivot = List<Record>::entry[low];       // First entry is now pivot..
	last_small = low;
	for (i = low + 1; i <= high; i++)
	/* At the beginning of each iteration of this loop, we have the following conditions:
	           If low < j <= last_small then entry[i].key < pivot.
	           If last_small < j < i then entry[j].key >= pivot. */
	if (List<Record>::entry[i] < pivot){
		last_small = last_small + 1;
		swap(last_small, i);  // Move large entry to right and small to left.
	}
	swap(low, last_small);    // Put the pivot into its proper position.
	return last_small;
 } 

template<class Record>
void Sortable_list<Record>::insert_heap(const Record &current, int low, int high)
/* Pre:  The entries of the Sortable_list between indices low + 1 and high, inclusive,
         room a heap. The entry in position low will be discarded.
   Post: The entry current will be inserted into the Sortable_list, and the entries
         rearranged so that the indices between low and high inclusive, room a heap.
   Uses: The class Record, and the contiguous List implementation of chapter 6. */
{
	int large;             // position of child of entry[low] with the larger key
	large = 2 * low + 1;   // large is now the left child of low
	while (large <= high){
		if (large < high && List<Record>::entry[large] < List<Record>::entry[large + 1])
		  large++;         // large is now the child of low with the largest key
		if (current >= List<Record>::entry[large])
		  break;           // current belongs in position low
		else{         // Promote entry[large] and move down the tree.
		    List<Record>::entry[low] = List<Record>::entry[large];
		    low = large;
			large = 2 * low + 1;
		}
	}
	List<Record>::entry[low] = current;
}

template<class Record>
void Sortable_list<Record>::build_heap()
/* Post: The entries of the Sortable_list have been rearranged so that it becomes a heap.
   Uses: The contiguous List implementation of Chapter 6, and insert_heap. */
{
    int low;        // All entries beyond the position low form a heap. 
    for (low = List<Record>::count / 2 - 1; low >= 0; low--){
    	Record current = List<Record>::entry[low];
    	insert_heap(current, low, List<Record>::count - 1);
	}
}

#endif
