#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include "utility.h"

enum Balance_factor{left_higher, equal_height, right_higher};

template <class Entry>
struct Binary_node{
	//  data members:
	Entry data;
	Binary_node<Entry> *left;
	Binary_node<Entry> *right;
	//  constructors:
	Binary_node();
	Binary_node(const Entry &x);
	//  virtual methods:
	virtual void set_balance(Balance_factor b);
	virtual Balance_factor get_balance() const;
};

template <class Entry>
Binary_node<Entry>::Binary_node()
{
	left = NULL;
	right = NULL;
}

template <class Entry>
Binary_node<Entry>::Binary_node(const Entry &x)
{
	left = NULL;
	right = NULL;
	data = x;
}

template <class Entry>
void Binary_node<Entry>::set_balance(Balance_factor b)
{
}

template <class Entry>
Balance_factor Binary_node<Entry>::get_balance() const
{
	return equal_height;
}

template<class Entry>
class Binary_tree{
	public:
		Binary_tree();                                                 
		bool empty() const;
		void preorder(void (*visit)(Entry &));
		void inorder(void (*visit)(Entry &));
		void postorder(void (*visit)(Entry &));
		int size() const;                                              
		void clear();                                               
		int height() const;                                             
		void insert(const Entry&);                                      
		Binary_tree(const Binary_tree<Entry> &original);
		Binary_tree& operator=(const Binary_tree<Entry> &original);
		~Binary_tree();
		void print() const;
	protected:
		// traverse auxiliary
		void recursive_inorder(Binary_node<Entry>* sub_root, void (*visit)(Entry &));
		void recursive_preorder(Binary_node<Entry>* sub_root, void (*visit)(Entry &));
		void recursive_postorder(Binary_node<Entry>* sub_root, void (*visit)(Entry &));
		
		// size auxiliary          
		int recursive_size(Binary_node<Entry>* sub_root) const;
		
		// clear auxiliary         
		void recursive_clear(Binary_node<Entry>* &sub_root);
	
		// height auxiliary        
		int recursive_height(Binary_node<Entry>* sub_root) const;
		
		// insert auxiliary    
		void recursive_insert(const Entry& x, Binary_node<Entry>* &sub_root);
		
		// copy constructor and assignment operator auxiliary
		void copy_left_sub_tree(Binary_node<Entry>* new_copy, Binary_node<Entry>* original_node);
		void copy_right_sub_tree(Binary_node<Entry>* new_copy, Binary_node<Entry>* original_node);
		
		// print auxiliary
		void recursive_print(Binary_node<Entry>* sub_root) const;
		
		Binary_node<Entry>* root;
}; 






/*------------------------------------------methods--------------------------------------------*/

template <class Entry>
Binary_tree<Entry>::Binary_tree()
/* Post: An empty binary tree has been created. */
{
	root = NULL;
}

template <class Entry>
bool Binary_tree<Entry>::empty() const
/* Post: A result of true is returned if the binary tree is empty. Otherwise, false is returned. */
{
	return root == NULL;
}

template <class Entry>
void Binary_tree<Entry>::inorder(void(*visit)(Entry &))
/* Post: The tree has been traversed in inorder sequence.
   Uses: The function recursive_inorder. */
{
	recursive_inorder(root, visit);
}

template <class Entry>
void Binary_tree<Entry>::preorder(void(*visit)(Entry &))
/* Post: The tree has been traversed in preorder sequence.
   Uses: The function recursive_preorder. */
{
	recursive_preorder(root,visit);
}

template <class Entry>
void Binary_tree<Entry>::postorder(void(*visit)(Entry &))
/* Post: The tree has been traversed in postorder sequence.
   Uses: The function recursive_postorder. */
{
	recursive_postorder(root,visit);
}

template <class Entry>
int Binary_tree<Entry>::size() const
{
	if (root == NULL) return 0;
	return 1 + recursive_size(root->left) + recursive_size(root->right);
}

template <class Entry>
void Binary_tree<Entry>::clear()
{
	if (root == NULL)  return ;
	recursive_clear(root->left);
	recursive_clear(root->right);
	delete root;
	root = NULL;
}

template <class Entry>
int Binary_tree<Entry>::height() const
{
	if (!root)
     return -1;
   else
     return 1 + max(recursive_height(root->left), recursive_height(root->right));
}

template <class Entry>
void Binary_tree<Entry>::insert(const Entry& x)
{	
	if (root == NULL) root = new Binary_node<Entry>(x);
	else{
		if (recursive_height(root->left) <= recursive_height(root->right)) recursive_insert(x,root->left);
		else recursive_insert(x,root->right);
	}
}

template <class Entry>
Binary_tree<Entry>::Binary_tree(const Binary_tree<Entry> &original)
{
	Binary_node<Entry> *new_copy, *original_node = original.root;
	if (original_node == NULL) root = NULL;
	else{
		root = new_copy = new Binary_node<Entry>(original_node->data);
		if (original_node->left != NULL) copy_left_sub_tree(new_copy, original_node);
		if (original_node->right != NULL) copy_right_sub_tree(new_copy, original_node);
	}
}

template <class Entry>
Binary_tree<Entry>& Binary_tree<Entry>::operator=(const Binary_tree<Entry> &original)
{
	Binary_node<Entry> *new_root, *new_copy, *original_node = original.root;
	if (original_node == NULL) new_root = NULL;
	else{
		new_root = new_copy = new Binary_node<Entry>(original_node->data);
		if (original_node->left != NULL) copy_left_sub_tree(new_copy, original_node);
		if (original_node->right != NULL) copy_right_sub_tree(new_copy, original_node);
	}
	clear();
	root = new_root;
}

template <class Entry>
Binary_tree<Entry>::~Binary_tree()
{
	clear();
}


template <class Entry>
void Binary_tree<Entry>::print() const
{
	if (root == NULL) return ;
	cout << "(" << root->data << ":";
	recursive_print(root->left);
	cout << ",";
	recursive_print(root->right);
	cout << ")" << endl;
}



/*-----------------------------------auxiliary functions----------------------------------------*/


// traverse auxiliary
template <class Entry>
void Binary_tree<Entry>::recursive_inorder(Binary_node<Entry>* sub_root,
                                           void (*visit)(Entry &))
/* Pre:  sub_root is either NULL or points to a subtree of the Binary_tree.
   Post: The subtree has been traversed in inorder sequence.
   Uses: The function recursive_inorder recursively */
{
	if (sub_root != NULL){
		recursive_inorder(sub_root->left, visit);
		(*visit)(sub_root->data);
		recursive_inorder(sub_root->right, visit);
	}
}

template <class Entry>
void Binary_tree<Entry>::recursive_preorder(Binary_node<Entry>* sub_root,
                                           void (*visit)(Entry &))
/* Pre:  sub_root is either NULL or points to a subtree of the Binary_tree.
   Post: The subtree has been traversed in preorder sequence.
   Uses: The function recursive_preorder recursively */
{
	if (sub_root != NULL){
		(*visit)(sub_root->data);
		recursive_preorder(sub_root->left, visit);
		recursive_preorder(sub_root->right, visit);
	}
}

template <class Entry>
void Binary_tree<Entry>::recursive_postorder(Binary_node<Entry>* sub_root,
                                           void (*visit)(Entry &))
/* Pre:  sub_root is either NULL or points to a subtree of the Binary_tree.
   Post: The subtree has been traversed in postorder sequence.
   Uses: The function recursive_postorder recursively */
{
	if (sub_root != NULL){
		recursive_postorder(sub_root->left, visit);
		recursive_postorder(sub_root->right, visit);
		(*visit)(sub_root->data);
	}
}


// size auxliliary
template <class Entry>
int Binary_tree<Entry>::recursive_size(Binary_node<Entry>* sub_root) const
{
	if (sub_root == NULL) return 0;
	return 1 + recursive_size(sub_root->left) + recursive_size(sub_root->right);
}


// clear auxliliary
template <class Entry>
void Binary_tree<Entry>::recursive_clear(Binary_node<Entry>* &sub_root)
{
	if (sub_root == NULL) {
		return;
	}
	recursive_clear(sub_root->left);
	recursive_clear(sub_root->right);
	delete sub_root;
}


// copy constructor and assignment operator auxliliary
template <class Entry>
void Binary_tree<Entry>::copy_left_sub_tree(Binary_node<Entry>* new_copy, Binary_node<Entry>* original_node)
{
	original_node = original_node->left;
	new_copy->left = new Binary_node<Entry>(original_node->data);
	new_copy = new_copy->left;
	if (original_node->left != NULL) copy_left_sub_tree(new_copy, original_node);
	if (original_node->right != NULL) copy_right_sub_tree(new_copy, original_node);
}

template <class Entry>
void Binary_tree<Entry>::copy_right_sub_tree(Binary_node<Entry>* new_copy, Binary_node<Entry>* original_node)
{
	original_node = original_node->right;
	new_copy->right = new Binary_node<Entry>(original_node->data);
	new_copy = new_copy->right;
	if (original_node->left != NULL) copy_left_sub_tree(new_copy, original_node);
	if (original_node->right != NULL) copy_right_sub_tree(new_copy, original_node);
}


// height auxliliary
template <class Entry>
int Binary_tree<Entry>::recursive_height(Binary_node<Entry>* sub_root) const
{
	if (!sub_root)
     return -1;
   else
     return 1 + max(recursive_height(sub_root->left), recursive_height(sub_root->right));
}


// insert auxliliary
template <class Entry>
void Binary_tree<Entry>::recursive_insert(const Entry& x, Binary_node<Entry>* &sub_root)
{
	if (sub_root == NULL) sub_root = new Binary_node<Entry>(x);
	else{
		if (recursive_height(sub_root->left) <= recursive_height(sub_root->right)) recursive_insert(x,sub_root->left);
		else recursive_insert(x,sub_root->right);
	}
}


// print auxiliary
template <class Entry>
void Binary_tree<Entry>::recursive_print(Binary_node<Entry>* sub_root) const
{
	if (sub_root == NULL) return;
	if (sub_root->right == NULL && sub_root->left == NULL){
		cout << sub_root->data;
		return ;
	}
	cout << "(" << sub_root->data << ":";
	recursive_print(sub_root->left);
	cout << ",";
	recursive_print(sub_root->right);
	cout << ")";
}
#endif
