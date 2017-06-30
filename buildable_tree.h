#ifndef BUILDABLE_TREE_H
#define BUILDABLE_TREE_H

#include "search_tree.h"
#include "list.h"

template<class Record>
class Buildable_tree:public Search_tree<Record>{
	public:
		Error_code build_tree(const List<Record> &supply);
	private:                        //  Add auxiliary function prototypes here.
	    void build_insert(int count, const Record &new_data, List<Binary_node<Record>*> &last_node);
		Binary_node<Record>* find_root(List<Binary_node<Record>*> &last_node);
        void connect_trees(const List<Binary_node<Record>*> &last_node);
};

template<class Record>
Error_code Buildable_tree<Record>::build_tree(const List<Record>&supply)
/*Post:If the entries of supply are in increasing order, a code of success is returned
       and the Search_tree is built out of these entries as a balanced tree. Otherwise,
       a code of fail is returned and a balanced tree is constructed from the longest
       increasing sequence of entries at the start of supply.
  Uses:The methods of class List and the functions build_insert, connect_subtrees, and
       find_root*/
{
	Error_code ordered_data=success;       //  Set this to fail if keys do not increase.
	int count=0;                           //  number of entries inserted so far
	Record x, last_x;
	List<Binary_node<Record>*>last_node;   //  pointers to last nodes on each level
	Binary_node<Record>*none=NULL;
	last_node.insert(0,none);              //  permanently NULL(for children of leaves)
	while (supply.retrieve(count, x)==success){
		if (count > 0 && x <= last_x){
			ordered_data = fail;
			break;
		}
		build_insert(++count, x, last_node);
		last_x = x;
	}
	Binary_tree<Record>::root = find_root(last_node);
	connect_trees(last_node);
	return ordered_data;       //  Report any data-ordering problems back to client.
}

template<class Record>
void Buildable_tree<Record>::build_insert(int count,
                             const Record &new_data,
							 List<Binary_node<Record>*> &last_node)
/*Post:A new node, containing the Record new_data, has been inserted as the rightmost
       node of a partially completed binary search tree. The level of this new node is
       one more than the highest power of 2 that divides count.
  Uses:Methods of class List*/
{
	int level;       //  level of new node above the leaves, counting inclusively
	for (level = 1; count % 2 == 0; level++)
	  count /= 2;    //  Use count to calculate level of next_node.
	Binary_node<Record> *next_node = new Binary_node<Record>(new_data),
	                    *parent;  //  one level higher in last_node
	last_node.retrieve(level-1, next_node->left);
	if (last_node.size() <= level)
	  last_node.insert(level, next_node);
	else
	  last_node.replace(level, next_node);
    if (last_node.retrieve(level+1, parent) == success && parent->right == NULL)
      parent->right = next_node;
}

template<class Record>
Binary_node<Record>* Buildable_tree<Record>::find_root(
                     List<Binary_node<Record>*> &last_node)
/*Pre:  The list last_node contains pointers to the last node on each occupied level
        of the binary search tree.
  Post: A pointer to the root of the newly created binary search tree is returned.
  Uses: Methods of class List */
{
	Binary_node<Record> *high_node;
	last_node.retrieve(last_node.size()-1, high_node);
	  //  Find root in the highest occupied level in last_node.
	return high_node;
}

template<class Record>
void Buildable_tree<Record>::connect_trees(
   const List<Binary_node<Record>*> &last_node)
/*Pre:  The nearly-completed binary search tree has been initialized. The List
        last_node has been initialized and contains links to the last node on each
        level of the tree.
  Post: The final links have been added to complete the binary search tree.
  Uses: Methods of class List*/
{
	Binary_node<Record> *high_node, //  from last_node with NULL right child
	                    *low_node;
	                        //  candidate for right child of high_node
	int high_level = last_node.size() - 1,
	    low_level;
	while (high_level > 2){   //  Nodes on levels 1 and 2 are already OK.
	    last_node.retrieve(high_level, high_node);
	    if (high_node->right != NULL)
	      high_level--;       //  Search down for highest dangling node.
	    else{                 //  Case: undefined right tree
	        low_level = high_level;
	        do{               //  Find the highest entry not in the left subtree.
	            last_node.retrieve(--low_level, low_node);
			}while (low_node != NULL && low_node->data < high_node->data);
			high_node->right = low_node;
			high_level = low_level;
		}
	}
}

#endif
