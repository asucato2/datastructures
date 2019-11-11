//
// Created by ansucato on 10/15/19.
//

#ifndef DATASTRUCTURES_BINARYSEARCHTREE_HPP
#define DATASTRUCTURES_BINARYSEARCHTREE_HPP

#include <iostream>

namespace DataStructures
{
  template<typename keyType, typename valueType>
  class BinarySearchTree
  {
  public:
    BinarySearchTree();
    BinarySearchTree(keyType t_key[], valueType t_data[], int t_size);
    BinarySearchTree(BinarySearchTree &t_tree);
    BinarySearchTree& operator= (const BinarySearchTree &rhs);
    ~BinarySearchTree();
    
    void inorder();
    void preorder();
    void postorder();
    
    virtual void insert(keyType t_key, valueType t_data);
    int remove(keyType t_key);
    
    valueType *search(keyType t_key);
    int size();
    int rank(keyType t_key);
    keyType select(int t_pos);
  
  
  protected:
    struct Node
    {
      keyType key;
      valueType data;
      unsigned int weight;
      
      Node *parent;
      Node *leftChild;
      Node *rightChild;
    };
    Node *_root;
    int _size;
    
    Node* treeCopy(Node *t_root);
    void deleteTree(Node *t_root);
    Node *max(Node *t_root);
    Node *min(Node *t_root);
    Node *successor(Node *t_root);
    Node *predecessor(Node *t_root);
    Node *treeSearch(keyType t_key);
    void inorderTreeWalk(Node *t_root);
    void preorderTreeWalk(Node *t_root);
    void postorderTreeWalk(Node *t_root);
    void createNode(Node *t_ptr, keyType t_key, valueType t_data);
    void treeInsert(Node *t_newNode);
    void transplant(Node *t_target, Node *t_replacement);
    int treeSize(Node *t_target);
  };
  
  template<typename keyType, typename valueType>
  BinarySearchTree<keyType, valueType>::BinarySearchTree()
          :
          _root(nullptr),
          _size(0)
  {
  }
  
  template<typename keyType, typename valueType>
  BinarySearchTree<keyType, valueType>::BinarySearchTree(keyType t_key[], valueType t_data[], const int t_size)
          :
          _root(nullptr),
          _size(0)
  {
    for (int i = 0;
         i < t_size;
         i++)
    {
      insert(t_key[i], t_data[i]);
    }
  }
  
  template<typename keyType, typename valueType>
  BinarySearchTree<keyType, valueType>::BinarySearchTree(BinarySearchTree<keyType, valueType> &t_tree)
  {
    _root = treeCopy(t_tree._root);
  }
  
  template<typename keyType, typename valueType>
  BinarySearchTree<keyType, valueType>& BinarySearchTree<keyType, valueType>::operator= (const BinarySearchTree<keyType, valueType> &rhs)
  {
    deleteTree(_root);
    _root = treeCopy(rhs._root);
    return *this;
  }
  
  template<typename keyType, typename valueType>
  BinarySearchTree<keyType, valueType>::~BinarySearchTree()
  {
    deleteTree(_root);
  }
  
  template<typename keyType, typename valueType>
  void BinarySearchTree<keyType, valueType>::deleteTree(Node *t_root)
  {
    if (t_root != nullptr)
    {
      deleteTree(t_root->leftChild);
      deleteTree(t_root->rightChild);
      delete t_root;
    }
  }
  
  template<typename keyType, typename valueType>
  void BinarySearchTree<keyType, valueType>::inorder()
  {
    inorderTreeWalk(_root);
  }
  
  template<typename keyType, typename valueType>
  void BinarySearchTree<keyType, valueType>::preorder()
  {
    preorderTreeWalk(_root);
  }
  
  template<typename keyType, typename valueType>
  void BinarySearchTree<keyType, valueType>::postorder()
  {
    postorderTreeWalk(_root);
  }
  
  template<typename keyType, typename valueType>
  void BinarySearchTree<keyType, valueType>::insert(keyType t_key, valueType t_data)
  {
    Node *newNode = new Node;
    createNode(newNode, t_key, t_data);
    
    if (_size == 0)
    {
      _root = newNode;
      _size++;
    }
    else
    {
      treeInsert(newNode);
    }
  }
  
  template<typename keyType, typename valueType>
  int BinarySearchTree<keyType, valueType>::remove(const keyType t_key)
  {
    Node *targetNode = treeSearch(t_key);
    
    if (targetNode == nullptr)
    {
      return 0;
    }
    
    if (targetNode->leftChild == nullptr)
    {
      transplant(targetNode, targetNode->rightChild);
    }
    else if (targetNode->rightChild == nullptr)
    {
      transplant(targetNode, targetNode->leftChild);
    }
    else
    {
      Node *replacementNode = min(targetNode->rightChild);
      if (replacementNode->parent != targetNode)
      {
        transplant(replacementNode, replacementNode->rightChild);
        replacementNode->rightChild = targetNode->rightChild;
        replacementNode->rightChild->parent = replacementNode;
      }
      transplant(targetNode, replacementNode);
      replacementNode->leftChild = targetNode->leftChild;
      replacementNode->leftChild->parent = replacementNode;
    }
    _size--;
    delete targetNode;
    return 1;
  }
  
  template<typename keyType, typename valueType>
  int BinarySearchTree<keyType, valueType>::size()
  {
    return _size;
  }
  
  template<typename keyType, typename valueType>
  valueType *BinarySearchTree<keyType, valueType>::search(const keyType t_key)
  {
    Node *node = treeSearch(t_key);
    if (node != nullptr)
    {
      return &node->data;
    }
    else
    {
      return nullptr;
    }
  }
  
  template<typename keyType, typename valueType>
  int BinarySearchTree<keyType, valueType>::rank(const keyType t_key)
  {
    Node *curNode = _root;
    int rank = 1;
    
    while (curNode != nullptr)
    {
      if (t_key < curNode->key)
      {
        curNode = curNode->leftChild;
      }
      else if (t_key > curNode->key)
      {
        rank += 1 + treeSize(curNode->leftChild);
        curNode = curNode->rightChild;
      }
      else
      {
        rank += treeSize(curNode->leftChild);
        return rank;
      }
    }
    return 0;
  }
  
  template<typename keyType, typename valueType>
  typename BinarySearchTree<keyType, valueType>::Node* BinarySearchTree<keyType, valueType>::treeCopy(Node *t_root)
  {
    if (t_root == nullptr)
    {
      return nullptr;
    }
    
    Node* newNode = new Node;
    newNode->key = t_root->key;
    newNode->data = t_root->data;
    newNode->weight = t_root->weight;
    newNode->parent = t_root->parent;
    
    newNode->leftChild = treeCopy(t_root->leftChild);
    if (newNode->leftChild != nullptr)
    {
      newNode->leftChild->parent = newNode;
    }
    
    newNode->rightChild = treeCopy(t_root->rightChild);
    if (newNode->rightChild != nullptr)
    {
      newNode->rightChild->parent = newNode;
    }
    return newNode;
  }
  
  template<typename keyType, typename valueType>
  typename BinarySearchTree<keyType, valueType>::Node *
  BinarySearchTree<keyType, valueType>::treeSearch(const keyType t_key)
  {
    Node *curNode = _root;
    while (curNode != nullptr && t_key != curNode->key)
    {
      if (t_key < curNode->key)
      {
        curNode = curNode->leftChild;
      }
      else
      {
        curNode = curNode->rightChild;
      }
    }
    
    if (curNode != nullptr)
    {
      return curNode;
    }
    else
    {
      return nullptr;
    }
  }
  
  template<typename keyType, typename valueType>
  void BinarySearchTree<keyType, valueType>::createNode(Node *t_ptr, keyType t_key, valueType t_data)
  {
    t_ptr->key = t_key;
    t_ptr->data = t_data;
    t_ptr->weight = 1;
    t_ptr->rightChild = nullptr;
    t_ptr->leftChild = nullptr;
    t_ptr->parent = nullptr;
  }
  
  template<typename keyType, typename valueType>
  void BinarySearchTree<keyType, valueType>::treeInsert(Node *t_newNode)
  {
    Node *curNode = _root;
    Node *p = nullptr;
    
    while (curNode != nullptr)
    {
      p = curNode;
      curNode->weight++;
      if (t_newNode->key < curNode->key)
      {
        curNode = curNode->leftChild;
      }
      else
      {
        curNode = curNode->rightChild;
      }
    }
    t_newNode->parent = p;
    
    if (t_newNode->key < p->key)
    {
      p->leftChild = t_newNode;
      _size++;
    }
    else
    {
      p->rightChild = t_newNode;
      _size++;
    }
  }
  
  template<typename keyType, typename valueType>
  void BinarySearchTree<keyType, valueType>::transplant(Node *t_target, Node *t_replacement)
  {
    if (t_target == _root)
    {
      _root = t_replacement;
    }
    else if (t_target == t_target->parent->leftChild)
    {
      t_target->parent->leftChild = t_replacement;
    }
    else
    {
      t_target->parent->rightChild = t_replacement;
    }
    
    if (t_replacement != nullptr)
    {
      t_replacement->parent = t_target->parent;
    }
  }
  
  template<typename keyType, typename valueType>
  void BinarySearchTree<keyType, valueType>::inorderTreeWalk(Node *t_root)
  {
    if (t_root != nullptr)
    {
      inorderTreeWalk(t_root->leftChild);
      std::cout << t_root->key << std::endl;
      inorderTreeWalk(t_root->rightChild);
    }
  }
  
  template<typename keyType, typename valueType>
  void BinarySearchTree<keyType, valueType>::preorderTreeWalk(Node *t_root)
  {
    if (t_root != nullptr)
    {
      std::cout << t_root->key << std::endl;
      preorderTreeWalk(t_root->leftChild);
      preorderTreeWalk(t_root->rightChild);
    }
  }
  
  template<typename keyType, typename valueType>
  void BinarySearchTree<keyType, valueType>::postorderTreeWalk(Node *t_root)
  {
    if (t_root != nullptr)
    {
      postorderTreeWalk(t_root->leftChild);
      postrderTreeWalk(t_root->rightChild);
      std::cout << t_root->key << std::endl;
    }
  }
  
  template<typename keyType, typename valueType>
  typename BinarySearchTree<keyType, valueType>::Node *BinarySearchTree<keyType, valueType>::max(Node *t_root)
  {
    Node *curNode = t_root;
    if (curNode == nullptr)
    {
      return nullptr;
    }
    while (curNode->rightChild != nullptr)
    {
      curNode = curNode->rightChild;
    }
    return curNode;
  }
  
  template<typename keyType, typename valueType>
  typename BinarySearchTree<keyType, valueType>::Node *BinarySearchTree<keyType, valueType>::min(Node *t_root)
  {
    Node *curNode = t_root;
    if (curNode == nullptr)
    {
      return nullptr;
    }
    
    while (curNode->leftChild != nullptr)
    {
      curNode = curNode->leftChild;
    }
    return curNode;
  }
  
  template<typename keyType, typename valueType>
  typename BinarySearchTree<keyType, valueType>::Node *BinarySearchTree<keyType, valueType>::successor(Node *t_root)
  {
    if (t_root->rightChild != nullptr)
    {
      return min(t_root->rightChild);
    }
    
    Node *curNode = t_root;
    Node *p = t_root->parent;
    
    while (p != nullptr && curNode == p->rightChild)
    {
      curNode = p;
      p = p->parent;
    }
    return p;
  }
  
  template<typename keyType, typename valueType>
  typename BinarySearchTree<keyType, valueType>::Node *BinarySearchTree<keyType, valueType>::predecessor(Node *t_root)
  {
    if (t_root->leftChild != nullptr)
    {
      return max(t_root->leftChild);
    }
    
    Node *curNode = t_root;
    Node *p = t_root->parent;
    
    while (p != nullptr && curNode == p->leftChild)
    {
      curNode = p;
      p = p->parent;
    }
    return p;
  }
  
  template<typename keyType, typename valueType>
  int BinarySearchTree<keyType, valueType>::treeSize(Node *t_target)
  {
    if (t_target == nullptr)
    {
      return 0;
    }
    
    return t_target->weight;
  }
  
  template<typename keyType, typename valueType>
  keyType BinarySearchTree<keyType, valueType>::select(const int t_pos)
  {
    Node *curNode = _root;
    int rank = 0;
    
    while (curNode != nullptr)
    {
      int curRank = rank + treeSize(curNode->leftChild) + 1;
      
      if (t_pos < curRank)
      {
        curNode = curNode->leftChild;
      }
      else if (t_pos > curRank)
      {
        rank += treeSize(curNode->leftChild) + 1;
        curNode = curNode->rightChild;
      }
      else
      {
        return curNode->key;
      }
    }
    return 0;
  }
}


#endif //DATASTRUCTURES_BINARYSEARCHTREE_HPP
