//
// Created by ansucato on 11/27/19.
//

#ifndef DATASTRUCTURES_HEAP_HPP
#define DATASTRUCTURES_HEAP_HPP

#include <iostream>
#include "DynamicCircularArray.hpp"

namespace DataStructures
{
  template<typename keyType, typename valueType>
  class Heap
  {
  public:
    Heap();
    Heap(const keyType *t_key, const valueType *t_value, int t_size);
    Heap(Heap &copy);
    Heap<keyType, valueType>& operator=(Heap rhs);
    ~Heap();
    
    keyType peakKey();
    valueType peakValue();
    keyType extractMin();
    void insert(keyType t_key, valueType t_value);
    void printKey();
    int length();
    
    bool isValid(int t_index);
  
  protected:
    class Node
    {
    public:
      keyType key;
      valueType value;
      
      Node() = default;
      
      Node(keyType t_key, valueType t_value)
              : key(t_key),
                value(t_value)
      {}
    };
    
    DynamicCircularArray<Node> _store;
    int _heapSize;
    keyType _errorKey;
    valueType _errorValue;
    
    int parent(int t_index);
    int leftChild(int t_index);
    int rightChild(int t_index);
    keyType getKey(int t_index);
    
    void minHeapifyDown(int t_index);
    void minHeapifyUp(int t_index);
  
  private:
  
  };
  
  /// \brief Initializes empty heap
  template<typename keyType, typename valueType>
  Heap<keyType, valueType>::Heap()
          : _heapSize(0)
  {
  }
  
  /// \brief Initializes heap with t_size key value nodes
  /// \param t_key - Array of keys to initialize heap with
  /// \param t_value - Array of values to initialize heap with
  /// \param t_size - number of entries in arrays to initialize heap
  template<typename keyType, typename valueType>
  Heap<keyType, valueType>::Heap(const keyType *t_key, const valueType *t_value, const int t_size)
          : _heapSize(t_size)
  {
    // build unordered dynamic array of nodes
    for (int i = 0; i < t_size; i++)
    {
      Node newNode(t_key[i], t_value[i]);
      _store.addEnd(newNode);
    }
    
    // run minHeapifyDown on all internal nodes of tree
    for (int i = (t_size / 2) - 1; i >= 0; i--)
    {
      minHeapifyDown(i);
    }
  }
  
  template<typename keyType, typename valueType>
  Heap<keyType, valueType>::Heap(Heap &copy)
          : _store(copy._store),
            _heapSize(copy._heapSize)
  {
  }
  
  
  /// \brief Destructor for class
  template<typename keyType, typename valueType>
  Heap<keyType, valueType>::~Heap()
  {
//    for (int i = 0; i < _store.length(); i++)
//    {
//      delete _store[i];
//    }
  }
  
  template<typename keyType, typename valueType>
  keyType Heap<keyType, valueType>::peakKey()
  {
    if (_heapSize < 1)
    {
      // TODO: find alternative (nullptr)
      return -1;
    }
    return getKey(0);
  }
  
  template<typename keyType, typename valueType>
  valueType Heap<keyType, valueType>::peakValue()
  {
    if (_heapSize < 1)
    {
      return nullptr;
    }
    return _store[0].value;
  }
  
  template<typename keyType, typename valueType>
  int Heap<keyType, valueType>::parent(const int t_index)
  {
    return (t_index - 1) / 2;
  }
  
  template<typename keyType, typename valueType>
  int Heap<keyType, valueType>::leftChild(const int t_index)
  {
    return (t_index * 2) + 1;
  }
  
  template<typename keyType, typename valueType>
  int Heap<keyType, valueType>::rightChild(const int t_index)
  {
    return (t_index * 2) + 2;
  }
  
  template<typename keyType, typename valueType>
  void Heap<keyType, valueType>::insert(const keyType t_key, const valueType t_value)
  {
    _heapSize++;
    Node newNode(t_key, t_value);
    _store.addEnd(newNode);
    minHeapifyUp(_heapSize - 1);
  }
  
  template<typename keyType, typename valueType>
  void Heap<keyType, valueType>::minHeapifyDown(const int t_index)
  {
    const int i = t_index;
    const int l = leftChild(t_index);
    const int r = rightChild(t_index);
    int smallest = i;
    
    if (l < _heapSize && getKey(l) < getKey(i))
    {
      smallest = l;
    }
    if (r < _heapSize && getKey(r) < getKey(smallest))
    {
      smallest = r;
    }
    
    if (smallest != i)
    {
      std::swap(_store[i], _store[smallest]);
      minHeapifyDown(smallest);
    }
  }
  
  template<typename keyType, typename valueType>
  void Heap<keyType, valueType>::printKey()
  {
    for (int i = 0; i < _heapSize; i++)
    {
      std::cout << getKey(i) << std::endl;
    }
  }
  
  template<typename keyType, typename valueType>
  void Heap<keyType, valueType>::minHeapifyUp(const int t_index)
  {
    const int i = t_index;
    const int p = parent(t_index);
    
    if (i < _heapSize && getKey(i) < getKey(p))
    {
      std::swap(_store[i], _store[p]);
      minHeapifyUp(p);
    }
  }
  
  template<typename keyType, typename valueType>
  keyType Heap<keyType, valueType>::getKey(int t_index)
  {
    return _store[t_index].key;
  }
  
  template<typename keyType, typename valueType>
  int Heap<keyType, valueType>::length()
  {
    return _heapSize;
  }
  
  template<typename keyType, typename valueType>
  bool Heap<keyType, valueType>::isValid(const int t_index)
  {
    if (t_index > _heapSize)
    {
      return true;
    }
    
    const int i = t_index;
    const int l = leftChild(t_index);
    const int r = rightChild(t_index);
   
    if (l < _heapSize && getKey(l) < getKey(i))
    {
      return false;
    }
    if (r < _heapSize && getKey(r) < getKey(i))
    {
      return false;
    }
    if (!isValid(l) || !isValid(r))
    {
      return false;
    }
    
    return true;
  }
  
  template<typename keyType, typename valueType>
  keyType Heap<keyType, valueType>::extractMin()
  {
    keyType minKey = getKey(0);
    
    std::swap(_store[0], _store[_heapSize - 1]);
    _heapSize--;
    minHeapifyDown(0);
    
    return minKey;
  }
  
  template<typename keyType, typename valueType>
  Heap<keyType, valueType> &Heap<keyType, valueType>::operator=(Heap rhs)
  {
    _store = rhs._store;
    _heapSize = rhs._heapSize;
    return *this;
  }
}


#endif //DATASTRUCTURES_HEAP_HPP
