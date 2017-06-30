#ifndef ORDERED_LIST_TEMPLATE_VER_H
#define ORDERED_LIST_TEMPLATE_VER_H

#include "list.h"
template<class Record>
class Ordered_list:public List<Record>{
	public:
		Error_code insert(const Record &data);
		Error_code insert(int position, const Record &data);
		Error_code replace(int position, const Record &data);
};

template<class Record>
Error_code Ordered_list<Record>::insert(const Record &data)
/* Post: If the Ordered_list is not full, the function succeeds: The Record data is
         inserted into the list, following the last entry of the list with a strictly
         lesser key (or in the first list position if no list element has a lesser key).
         Else: the function fails with the diagnostic Error_code overflow. */
{
	int position;
	for (position = 0; position < List<Record>::count; position++){
		Record list_data;
		List<Record>::retrieve(position, list_data);
		if (data < list_data) break;
	}
	return List<Record>::insert(position, data);
}

template<class Record>
Error_code Ordered_list<Record>::insert(int position, const Record &data)
/* Post: If the Ordered_list is not full, 0 <= position <= n, where n is the number of 
         entries in the list, and the Record data can be inserted at position in the
         list, without disturbing the list order, then the function succeeds: Any entry
         formerly in position and all later entries have their position numbers 
         increased by 1 and data is inserted at position of the List.
         Else: the function fails with a diagnostic Error_code. */
{
	Record list_data;
	if (position > 0){
		List<Record>::retrieve(position - 1, list_data);
		if (data < list_data)  return fail;
	}
	if (position < List<Record>::count){
		List<Record>::retrieve(position, list_data);
		if (data > list_data)  return fail;
	}
	return List<Record>::insert(position, data);
}

template<class Record>
Error_code Ordered_list<Record>::replace(int position, const Record &data)
{
	if (position < 0 || position >= List<Record>::count) return range_error;
	if (position == 0 || position == List<Record>::count - 1){
		if (List<Record>::count == 1) {
			List<Record>::entry[position] = data;
			return success;
		}
		if (position == 0 && data > List<Record>::entry[position + 1]) return fail;
		if (position == List<Record>::count - 1 && data < List<Record>::entry[position - 1]) return fail;
		List<Record>::entry[position] = data;
		return success;
	}
	if (data < List<Record>::entry[position - 1] || data > List<Record>::entry[position + 1]) return fail;
	List<Record>::entry[position] = data;
	return success;
}

#endif
