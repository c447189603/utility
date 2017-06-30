#ifndef RECURSIVE_BINARY_SEARCH_2_TEMPLATE_VER_H
#define RECURSIVE_BINARY_SEARCH_2_TEMPLATE_VER_H

#include "Ordered_list_template_ver.h"
template<class Record>
Error_code recursive_binary_2(const Ordered_list<Record> &the_list, const Key &target,
                              int bottom, int top, int &position)
/* Pre:  The indices bottom to top define the range in the list to search for the target.
   Post: If a Record in the range from bottom to top in the_list has key equal to target,
         then position locates one such entry, and a code of success is returned.
         Otherwise, not_present is returned, and position is undefined.
   Uses: recursive_binary_2, together with methods from the classes Ordered_list and
         Record. */
{
	Record data;
	if (bottom <= top){
		int mid = (bottom + top) / 2;
		the_list.retrieve(mid, data);
		if (data == target){
			position = mid;
			return success;
		}
		else if (data < target)  return recursive_binary_2(the_list, target, mid + 1, top, position);
		else                     return recursive_binary_2(the_list, target, bottom, mid - 1, position);
	}
	else {
		position = -1;
		return not_present;
	}
}

template<class Record>
Error_code run_recursive_binary_2(const Ordered_list<Record> &the_list,
                                  const Key &target, int &position)
{
	return recursive_binary_2(the_list, target, 0, the_list.size() - 1, position);
}

#endif
