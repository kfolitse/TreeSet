/**************************************************************************
 
 
 
 
 *****************************************************************************/

#ifndef TREESET_H
#define TREESET_H

#include <memory>

//template <typename T >
class TreeSet {
    private:  
        /*
         * Binary Search Tree Node structure.
         * left node and right declared as smart pointers.
         */
       // template <typename T >
        struct Node{
            int key ; /* key of the node.*/
            std::shared_ptr<Node> left ; /* Left child aka left sub-tree. */
            std::shared_ptr<Node> right; /* Right child aka right sub tree.*/
            
            /* 
             * Constructor-
             * @param: x, key of the node;
             */
            Node(const int x):key(x),left(nullptr),right(nullptr){}
            
            /* Copy-constructor 
             * @param: node, the node.
             * 
             */
            Node(const Node &node);
            
            /*
             * Copy-assignment
             * @param: node, the right hand side of the assignment.
             */
            Node& operator=(const Node &rhs);
            
        };
        
        std::shared_ptr<Node> root; /* Tree root */
        /*
         * Search a node in the tree, starting from the root.
         * @param: key , the key of the node
         * Returns the pointer to the node if node or null pointer.
         */
        std::shared_ptr<Node> search (int key) const;
        
        /*  Returns the number of nodes in the tree, starting from the root.*/
        int size (const std::shared_ptr<Node> &node) const;
        
        /* Returns the successor of a node*/ 
        std::shared_ptr<Node> successor(const std::shared_ptr<Node> &curr);

        /* In-order traversal */
        void inorderTravesal(const std::shared_ptr<Node>  &n) const;
        bool sanity_check(std::shared_ptr<Node> n, int minval, int maxval);
        
        
        public:
        /* Default constructor initialize empty set. */
        TreeSet();

        /* Copy-constructor */
        TreeSet(const TreeSet &tree);

        /* Copy-assignment */
        TreeSet& operator= (const TreeSet &tree);
        
        /* Move-Constructor */
        TreeSet(TreeSet &&tree);
        
        /* Move-Assignment */
        TreeSet& operator=(TreeSet &&tree);

        /* Returns the number of elements in the set. */
        int size () const;

        /* 
         * Adds elements to the set.
         * Returns true if the element value is not in the set. 
         * and false if the element already appears in the set.
         * 
         */
        bool add(int key);

        /* 
         * Deletes an element from the set.
         * Returns true if value appears in the set and it is removed,
         * and false if value is not in the set.
         */
        bool del(int key);

        /*
         * Returns true if value is in the set
         * and false if not.
         */
        bool contains (int key);
        /*
         * In-order traversal */
        void inorderTravesal() const;
        
         
};


#endif /* TREESET_H */

