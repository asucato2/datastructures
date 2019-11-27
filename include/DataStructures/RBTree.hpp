//
// Created by ansucato on 11/11/19.
//

#ifndef DATASTRUCTURES_RBTREE_HPP
#define DATASTRUCTURES_RBTREE_HPP

#include "BinarySearchTree.hpp"

namespace DataStructures
{
  template<typename keyType, typename valueType>
  class RBTree : public BinarySearchTree<keyType, valueType>
  {
  public:
    RBTree();
    RBTree(keyType *t_keys, valueType *t_data, int t_size);
    ~RBTree();
    
    void insert(keyType t_key, valueType t_data);
    int remove(keyType t_key);
    
  protected:
    const bool RED = true;
    const bool BLACK = false;
    
    struct Node : public BinarySearchTree<keyType, valueType>::Node
    {
      bool color;
      
      Node(keyType t_key, valueType t_data, bool t_color)
      : BinarySearchTree<keyType, valueType>::Node(t_key, t_data), color(t_color) {}
    };
  
    bool isRed(Node* t_node);
    bool isBlack(Node* t_node);
    
    void rotateLeft(Node* t_root);
    void rotateRight(Node* t_root);
    void insertFixup(Node* t_node);
    void deleteFixup(Node* t_node);
    void transplant(Node* t_target, Node* t_replacement);
  
  };
  
  template<typename keyType, typename valueType>
  RBTree<keyType, valueType>::RBTree()
  : BinarySearchTree<keyType, valueType>()
  {
  }
  
  template<typename keyType, typename valueType>
  RBTree<keyType, valueType>::RBTree(keyType *t_keys, valueType *t_data, const int t_size)
  {
    for (int i = 0; i < t_size; i++)
    {
      insert(t_keys[i], t_data[i]);
    }
  }
  
  template<typename keyType, typename valueType>
  RBTree<keyType, valueType>::~RBTree()
  {
    this->deleteTree(this->_root);
  }
  
  template<typename keyType, typename valueType>
  void RBTree<keyType, valueType>::insert(const keyType t_key, const valueType t_data)
  {
    Node *newNode = new Node(t_key, t_data, );
    
    Node *curNode = this->_root;
    Node *prevNode = nullptr;
    
    // Find insertion point in tree
    while (curNode != nullptr)
    {
      curNode->weight++;
      prevNode = curNode;
      if (newNode->key < curNode->key)
      {
        curNode = curNode->leftChild;
      }
      else
      {
        curNode = curNode->rightChild;
      }
    }
    
    // link newNode in
    newNode->parent = prevNode;
    if (prevNode == nullptr)
    {
      this->_root = newNode;
    }
    else if (newNode->key < prevNode->key)
    {
      prevNode->leftChild = newNode;
    }
    else
    {
      prevNode->rightChild = newNode;
    }
    
    // Fixup tree
    insertFixup(newNode);
  }
  
  template<typename keyType, typename valueType>
  int RBTree<keyType, valueType>::remove(keyType t_key)
  {
  }
  
  /// \brief - Helper function to rotate subtree left
  /// \param t_root - Root of subtree to rotate
  template<typename keyType, typename valueType>
  void RBTree<keyType, valueType>::rotateLeft(RBTree::Node *t_root)
  {
    // TODO: Add weight manipulation
    Node *root = t_root;
    Node *right = root->rightChild;
    
    // set rights left subtree to roots right subtree
    root->rightChild = right->leftChild;
    if (right->leftChild != nullptr)
    {
      right->leftChild->parent = root;
    }
    
    // link roots parent to right
    right->parent = root->parent;
    if (root->parent == nullptr)
    {
      this->_root = right;
    }
    else if (root->parent->leftChild == root)
    {
      root->parent->leftChild = right;
    }
    else
    {
      root->parent->rightChild = right;
    }
    
    // put root on rights left
    right->leftChild = root;
    root->parent = right;
  }
  
  /// \brief - Helper function to rotate subtree right
  /// \param t_root - Root of subtree to rotate
  template<typename keyType, typename valueType>
  void RBTree<keyType, valueType>::rotateRight(RBTree::Node *t_root)
  {
    //TODO: Add weight manipulation
    Node* root = t_root;
    Node* left = root->leftChild;
    
    // turn lefts right subtree into roots left subtree
    root->leftChild = left->rightChild;
    if (left->rightChild != nullptr)
    {
      left->rightChild->parent = root;
    }
    
    // link roots parents to left
    left->parent = root->parent;
    if (root->parent == nullptr)
    {
      this->_root = left;
    }
    else if (root->parent->leftChild == root)
    {
      root->parent->leftChild = left;
    }
    else
    {
      root->parent->rightChild = left;
    }
    
    // put root on lefts right
    left->rightChild = root;
    root->parent = left;
  }
  
  template<typename keyType, typename valueType>
  void RBTree<keyType, valueType>::insertFixup(Node *t_node)
  {
    Node *newNode = t_node;
  
    while (isRed(newNode->parent))
    {
    }
  }
  
  template<typename keyType, typename valueType>
  bool RBTree<keyType, valueType>::isRed(RBTree::Node *t_node)
  {
    return t_node->color == t_node->red;
  }
  
  template<typename keyType, typename valueType>
  bool RBTree<keyType, valueType>::isBlack(RBTree::Node *t_node)
  {
    return t_node->color == t_node->black;
  }
  
  
}

#endif //DATASTRUCTURES_RBTREE_HPP
