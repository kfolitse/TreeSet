/****************************************************************************
 * 
 * 
 * 
 * 
 * 
 ******************************************************************************/
#include<iostream>

#include "treeset.h"
using namespace std;
#include <memory>

/* Node Copy-constructor */

TreeSet::Node::Node(const Node &node):
    key(node.key), left(nullptr), right(nullptr) { 
    if (node.left){
        this->left =  make_shared<Node>(*node.left);
    }
    if (node.right){
        this->right =  make_shared<Node>(*node.right);
    }  
}
/* Node Copy-assignment */
TreeSet::Node& TreeSet::Node::operator =(const Node& rhs){
   if (this == &rhs) {
        return *this;
    }
    this->key = rhs.key;  
    std::shared_ptr<Node> temp =  nullptr;
    if (rhs.left){
        temp =  make_shared<Node>(*rhs.left);
    }
    this->left = temp;
    
    temp =  nullptr;
    if (rhs.right){
        temp =  make_shared<Node>(*rhs.right);
    }
    this->right = temp;
    return *this; 
}
/* Helper function to count the number of nodes in the tree */
int TreeSet::size(const std::shared_ptr<Node> &curr) const {
    if (curr == nullptr) {
        return 0;
    }
    else {
        return size(curr->left) + size(curr->right) + 1;
    }
}
/* Tree default constructor */
TreeSet::TreeSet(){}

/* Tree copy-constructor */
TreeSet::TreeSet(const TreeSet &tree){
    root = make_shared<Node>(*tree.root);    
}

/* Tree copy-assignment */
TreeSet& TreeSet::operator=(const TreeSet &rhs){
    if(this == &rhs ){
        return *this;
    }
    this->root = make_shared<Node>(*rhs.root);
    /* Return the object itself. */
    return *this; //   
}
/* Move constructor */
//TreeSet::TreeSet(TreeSet &&tree){}
/* Move-assignment */
//TreeSet& TreeSet::TreeSet(TreeSet &&tree){}

/* Returns the number of element in the tree */
int TreeSet::size () const {
    return size(root);  
}

/* Adds an element to the tree set */
bool TreeSet:: add(int key){
 
    std::shared_ptr<Node > current = root;
    std::shared_ptr<Node > temp = nullptr;
    
    while(current!= nullptr) {
        temp = current;
        if (key > current->key) {
            current = current->right;
        } 
        else if (key < current->key) {
            current = current->left;
        } 
        else if (current->key == key) {
                return false;
            }
    }
    current = std::make_shared<Node>(key);
    
    if (temp == nullptr) {
        root = current;            
    }
    else if (temp->key < current->key) {
        temp->right = current;
    }
    else {
        temp->left = current;
    }
        
    return true;  
}
/* Checks if the tree contains an element with key */
bool TreeSet::contains (int key){
    
    std::shared_ptr<Node> temp = root;
    while (temp != nullptr) {
        if (key > temp->key) {
            temp = temp->right;
        } 
        else if (key < temp->key) {
            temp = temp->left;
        } 
        else {
            return true;
      }
    }
    return false;
}


bool TreeSet::sanity_check(std::shared_ptr<Node> n, int minval, int maxval){ 
    if(n == nullptr) {
        return false;
      } 
    else if (n->key > minval && n->key < maxval ) {
            return sanity_check (n->left,minval,n->key);
            return sanity_check (n->right,n->key, maxval);
      } 
      else {
            cerr << n->key << " not ["<< minval << ", "<< maxval << "]" << endl;
            sanity_check (n->left,minval,n->key);
            sanity_check (n->right,n->key, maxval);
            return false;
            
      }
    return true;
    
}
/* In-order Traversal of the tree  */
void TreeSet::inorderTravesal(const std::shared_ptr<Node> &n) const{
    if (n == nullptr){
	return;
    }
    inorderTravesal(n->left);
    cout << n->key << " ";
    inorderTravesal(n->right);
}

/* Print out the content of the tree - In order printer */
void TreeSet::inorderTravesal () const{
    inorderTravesal(root);
}
/* Search for a node with key */
std::shared_ptr<TreeSet::Node> TreeSet::search ( int key ) const {
    
    std::shared_ptr<Node> curr = root; 
    while (curr != nullptr){
	if (key < curr->key){
            curr = curr->left;
        }
	else if (key > curr->key){
            curr = curr->right;
        }
        else {
            return curr;
        }
    }
    return nullptr;
}
/* Find the successor - minimum value node in sub-tree rooted at curr 
 */
std::shared_ptr<TreeSet::Node> TreeSet::successor(const std::shared_ptr<Node> &node){
    std::shared_ptr<Node> curr = node;
    while(curr->left != nullptr) {
	curr = curr->left;
    }
    return curr;
}

/* Delete a node with a given key */
bool TreeSet::del(int key){  
    // First find the node that we want to delete, starting from the root node;
    std::shared_ptr<Node> curr = root;
    std::shared_ptr<Node> parent = nullptr;
    
    while (curr != nullptr && curr->key != key){
        parent = curr;
	if (key < curr->key){
            curr = curr->left;
        }
	else {
            curr = curr->right;
        }
    }
    // parent will contains the parent the node to be deleted.
    // current the node to be deleted.
    
    if (curr == nullptr){
	return false; // 
    }

    // Case 1: node to be deleted has no children i.e. it is a leaf node  
    if (curr->left == nullptr && curr->right == nullptr) {
	// if node to be deleted is not a root node, then set its
	// parent left/right child to null
	if (curr != root){
            if (parent->left == curr){
		parent->left = nullptr;
            }
            else{
                parent->right = nullptr;
            }
	}
	// if tree has only root node, delete it and set root to null
	else{
            root = nullptr;
        }

    }	
    
    // Case 2: node to be deleted has two children
    else if (curr->left && curr->right){
	// find its in-order successor node
	std::shared_ptr<Node> succ  = successor(curr->right);

	// store successor value
	int v = succ->key;
 
	// Recursively delete the successor. Note that the successor
	// will have at-most one child (right child)
        del(succ->key);
	// Copy the value of successor to current node
	curr->key = v;
    }
    else {
	// find child node
	std::shared_ptr<Node> child = (curr->left)? curr->left: curr->right;

	// if node to be deleted is not a root node, then set its parent
	// to its child
	if (curr != root){
            if (parent->left == curr){
		parent->left = child;
            }
            else {
		parent->right = child;
            }
	}

	// if node to be deleted is root node, then set the root to child
	else{
            root = child;
        }
    }

    return true;

}
//void C::S::func()