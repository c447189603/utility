#ifndef RECURSIVE_BINARY_SEARCH_1_TYPEDEF_VER_H
#define RECURSIVE_BINARY_SEARCH_1_TYPEDEF_VER_H

#include "Ordered_list_typedef_ver.h"
Error_code recursive_binary_1(const Ordered_list &the_list, const Key&target,
                              int bottom, int top, int &position)
/* Pre:  The indices bottom tp top define the range in the list to search for the target.
   Post: If a Record in the range of locations from bottom to top in the_list has key
         equal to target, then position locates one such entry and a code of success is
         returned. Otherwise, the Error_code of not_present is returned and position
         becomes undefined.
   Uses: recursive_binary_1 and methods of the classes List and Record. */
{
	Record data;
	if (bottom < top){       // List has more than one entry.
		int mid = (bottom + top) / 2;
		the_list.retrieve(mid, data);
		if (data < target)  return recursive_binary_1(the_list, target, mid+1, top, position);    // Reduce to top half of list.
		else  return recursive_binary_1(the_list, target, bottom, mid, position);    // Reduce to bottom half of list.
	}
	else if(top < bottom)  return not_present;    // List is empty.
	else {
		position = bottom;
		the_list.retrieve(bottom, data);
		if (data == target) return success;
		else {
			position = -1;
			return not_present;
		}
	}
}

Error_code run_recursive_binary_1(const Ordered_list &the_list,
                                  const Key &target, int &position)
{
	return recursive_binary_1(the_list, target, 0, the_list.size() - 1, position);
}
 
#endif
