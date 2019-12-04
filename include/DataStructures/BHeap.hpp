//
// Created by ansucato on 12/2/19.
//

#ifndef DATASTRUCTURES_BHEAP_HPP
#define DATASTRUCTURES_BHEAP_HPP

#include <iostream>
#include "DynamicCircularArray.hpp"
#include "Heap.hpp"

namespace DataStructures
{
  template<typename keyType, typename valueType>
  class BHeap
  {
  public:
    BHeap();
    
    void printKey() const;
    void merge(BHeap<keyType, valueType> h2);
    void insert(const keyType t_key, const valueType t_value);
  
  protected:
    struct Node
    {
      keyType key;
      valueType value;
      int degree;
      Node *parent;
      Node *child; // left child
      Node *sibling; // right sibling
    };
    
    Node *_head;
    void initializeNode(Node *t_node, const keyType t_key, const valueType t_value, const int t_degree);
    void mergeSameDegreeTrees(Node *a, Node *b);
    void BTreePrintKey(const Node *t_head) const;
  };
  
  template<typename keyType, typename valueType>
  BHeap<keyType, valueType>::BHeap()
          : _head(nullptr)
  {
  }
  
  /// \brief Simple function to initialize node
  /// \param t_node - Node to initialize
  /// \param t_key  - value to set key
  /// \param t_value  - value to set value
  /// \param t_degree - value to set degree
  template<typename keyType, typename valueType>
  void BHeap<keyType, valueType>::initializeNode(BHeap::Node *t_node,
                                                 const keyType t_key,
                                                 const valueType t_value,
                                                 const int t_degree)
  {
    t_node->key = t_key;
    t_node->value = t_value;
    t_node->degree = t_degree;
    t_node->parent = nullptr;
    t_node->sibling = nullptr;
    t_node->child = nullptr;
  }
  
  template<typename keyType, typename valueType>
  void BHeap<keyType, valueType>::merge(BHeap<keyType, valueType> h1)
  {
  
  }
  
  template<typename keyType, typename valueType>
  void BHeap<keyType, valueType>::mergeSameDegreeTrees(BHeap::Node *a, BHeap::Node *b)
  {
    Node *small, *large;
    if (a->key <= b->key)
    {
      small = a;
      large = b;
    }
    else
    {
      small = b;
      large = a;
    }

    large->sibling = small->child;
    large->parent = small;
    small->child = large;
    
    small->degree++;
  }
  
  template<typename keyType, typename valueType>
  void BHeap<keyType, valueType>::printKey() const
  {
    Node *curr = _head;
    while (curr != nullptr)
    {
      std::cout << "B" << curr->degree << std::endl;
      std::cout << curr->key;
      BTreePrintKey(curr->child);
      std::cout << std::endl;
    }
  }
  
  template<typename keyType, typename valueType>
  void BHeap<keyType, valueType>::BTreePrintKey(const BHeap::Node *t_head) const
  {
    while (t_head != nullptr)
    {
      std::cout << ", " << t_head->key;
      BTreePrintKey(t_head->child);
      BTreePrintKey(t_head->sibling);
    }
  }
}

#endif //DATASTRUCTURES_BHEAP_HPP
