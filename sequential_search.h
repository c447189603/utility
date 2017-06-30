#ifndef SEQUENTIAL_SEARCH_H
#define SEQUENTIAL_SEARCH_H

Error_code sequential_search(const List<Record> &the_list,
                             const Key &target, int &position)
/* Post: If an entry in the_list has key equal to target, then return success and the 
         output parameter position locates such an entry within the list.
         Otherwise return not_present and position becomes invalid. */
{
	int s = the_list.size();
	for (position = 0; position < s; position++){
		Record data;
		the_list.retrieve(position, data);
		if (data == target) return success;
	}
	
	return not_present;
}

#endif

