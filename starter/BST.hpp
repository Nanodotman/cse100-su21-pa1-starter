#ifndef BST_HPP
#define BST_HPP
#include "BSTNode.hpp"
#include "BSTIterator.hpp"
#include <iostream>
using namespace std;

//hello

template<typename Data>
class BST {

   protected:

      /** Pointer to the root of this BST, or 0 if the BST is empty */
      BSTNode<Data>* root;

      /** Number of Data items stored in this BST. */
      unsigned int isize;

      /** Height of this BST. */
      unsigned int iheight;

   public:

      /** define iterator as an aliased typename for BSTIterator<Data>. */
      typedef BSTIterator<Data> iterator;

      /** Default constructor.
        * Initialize an empty BST.
        */
      BST() : root(0), isize(0), iheight(-1) {  }


      /** Default destructor.
        * Delete every node in this BST.
        */
      virtual ~BST() {
         deleteAll(root);
      }

      /** Given a reference to a Data item, insert a copy of it in this BST.
       *  Return  true if the item was added to this BST
       *  as a result of this call to insert,
       *  false if an item equal to this one was already in this BST.
       *  Note: This function should use only the '<' operator when comparing
       *  Data items. (should not use ==, >, <=, >=)  For the reasoning
       *  behind this, see the assignment writeup.
       *  TODO
       */
      virtual bool insert(const Data& item) {
         //cout << "inserting: " << item << endl;
         BSTNode<Data>* current = this->root;

         BSTNode<Data>* newNode = new BSTNode<Data>(item);
         unsigned int currentHeight = 0;

         while (current != NULL) {
            //cout << current->data << endl;
            if (!(current->data < item || item < current->data)) {
               //cout << "not inserting equal values" << endl;
               delete(newNode);
               return false;
            }

            if (item < current->data){
               currentHeight++;
               if (current->left == NULL) {
                  // update iheight
                  //cout << "inserting item " << item << " as left child of " << current->data << endl;
                  if (currentHeight > iheight) {
                     iheight = currentHeight;
                  }
                  
                  // add node
                  newNode->parent = current;
                  current->left = newNode;
                  isize++;
                  return true;
               }
               current = current->left;
            } else {
               currentHeight++;
               if (current->right == NULL) {
                  // update iheight
                  //cout << "inserting item " << item << " as right child of " << current->data << endl;
                  if (currentHeight > iheight) {
                     iheight = currentHeight;
                  }
                  
                  // add node
                  newNode->parent = current;
                  current->right = newNode;
                  isize++;
                  return true;
               }
               current = current->right;
            }
         }

         // only for root
         this->root = newNode;
         iheight = 0;
         isize++;
         //cout << "root: " << this->root->data << endl;
         return true;
      }


      /** Find a Data item in the BST.
       *  Return an iterator pointing to the item, or pointing past
       *  the last node in the BST if not found.
       *  Note: This function should use only the '<' operator when comparing
       *  Data items. (should not use ==, >, <=, >=).  For the reasoning
       *  behind this, see the assignment writeup.
       *  TODO
       */
      virtual iterator find(const Data& item) const {
         //BSTNode<Data>* current = this->root;
         iterator itr = begin();    // Initialized iterator

         while (*itr < item || item < *itr) {
            itr++;
            if (itr == end()) {
               return end();
            }
         }

         return itr;
      }


      /** Return the number of items currently in the BST.
       *  TODO 
       */
      unsigned int size() const {
         return this->isize;
      }

      /** Return the height of the BST.
       * The height of an empty tree is -1 and the height of a tree
       * with only one node is 0.
       *  TODO  
       */
      unsigned int height() const {
         return this->iheight;
      }


      /** Return true if the BST is empty, else false.
       */
      bool empty() const {
         return isize == 0;
      }

      /** Return an iterator pointing to the first item in the BST (not the root).
       */
      iterator begin() const {
         return BST::iterator(first(root));
      }

      /** Return an iterator pointing past the last item in the BST.
       */
      iterator end() const {
         return typename BST<Data>::iterator(0);
      }


      /** Inorder traverse BST, print out the data of each node in ascending order.
       * Implementing inorder and deleteAll base on the pseudo code is an easy way to get started.
       * Pseudo Code:
       * if current node is null: return;
       * recursively traverse left sub-tree
       * print current node data
       * recursively traverse right sub-tree
       * TODO
       */
      void inorder() const {
         BSTNode<Data>* current = this->root;
         
         if (current == NULL){
            return;
         }     
         current->left.inorder();
         cout << current->data << endl;       // print node data
         current->right.inorder();
      }


   private:

      /** Find the first element of the BST
       *  TODO 
       */ 
      static BSTNode<Data>* first(BSTNode<Data>* root) {
         BSTNode<Data>* current = root;
         
         while (current->left != NULL) {
            current = current->left;
         }
         
         return current;
      }

      /** do a postorder traversal, deleting nodes
       *   TODO 	
       */
      static void deleteAll(BSTNode<Data>* n) {
         /* Pseudo Code:
            if current node is null: return;
            recursively delete left sub-tree
            recursively delete right sub-tree
            delete current node
            */
         
         BSTNode<Data>* current = n;
         
         if (current == NULL) {
            return;
         }     
         deleteAll(current->left);
         deleteAll(current->right);
         delete(current);      // delete current node  
      }


};


#endif //BST_HPP
