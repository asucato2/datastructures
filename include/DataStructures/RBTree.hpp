//
// Created by ansucato on 11/11/19.
//

#ifndef DATASTRUCTURES_RBTREE_HPP
#define DATASTRUCTURES_RBTREE_HPP

#include <iostream>
#include <list>

namespace DataStructures
{
  template<typename keyType, typename valueType>
  class RBTree
  {
  public:
    RBTree();
    RBTree(const keyType *t_key, const valueType *t_value, const int t_size);
    ~RBTree();
  
    void insert(const keyType t_key, const valueType t_value);
    int remove(const keyType t_key);
    valueType *search(const keyType t_key) const;
    int rank(const keyType t_key) const;
    int size() const;
    keyType select(const int t_pos) const;
    void split(const keyType t_key, RBTree<keyType, valueType> &T1, RBTree<keyType, valueType> &T2);
    
    void preorder() const;
    void inorder() const;
    void postorder() const;
  
  
  private:
    struct Node
    {
      keyType key;
      valueType value;
      int weight;
      enum class Color
      {
        black = 0, red
      } color; // color of link above node
      Node *leftChild;
      Node *rightChild;
    };
    Node *_root;
    
    inline void initializeNode(Node *t_node, const keyType t_key, const valueType t_value, const typename Node::Color t_color);
    inline bool isRed(Node *t_node) const;
    
    Node *rotateLeft(Node *t_head);
    Node *rotateRight(Node *t_head);
    Node *colorFlip(Node *t_head);
    Node *insertHelper(Node *t_head, const keyType t_key, const valueType t_value);
    Node *fixup(Node* t_head);
    Node *moveRedRight(Node* t_head);
    Node *moveRedLeft(Node* t_head);
    Node *deleteMin(Node* t_head);
    Node *deleteNode(Node* t_head, const keyType t_key);
    Node *leanRight(Node* t_head);
    
    void preorderTreeWalk(const Node *t_head) const;
    void inorderTreeWalk(const Node *t_head) const;
    void postorderTreeWalk(const Node *t_head) const;
    int treeSize(const Node *t_target) const;
    void treeDelete(Node *t_root);
    Node* treeMin(Node *t_root) const;
    Node* treeMax(const Node *t_root) const;
    void inorderTreeWalkList(const Node *t_head, std::list<Node> nodes);
  };
  
  template<typename keyType, typename valueType>
  RBTree<keyType, valueType>::RBTree()
          : _root(nullptr)
  {
  }
  
  template<typename keyType, typename valueType>
  RBTree<keyType, valueType>::RBTree(const keyType *t_key, const valueType *t_value, const int t_size)
          : _root(nullptr)
  {
    for (int i = 0; i < t_size; i++)
    {
      insert(t_key[i], t_value[i]);
    }
  }
  
  template<typename keyType, typename valueType>
  RBTree<keyType, valueType>::~RBTree()
  {
    treeDelete(_root);
  }
  
  template<typename keyType, typename valueType>
  bool RBTree<keyType, valueType>::isRed(RBTree::Node *t_node) const
  {
    if (t_node == nullptr)
    {
      return false;
    }
    return t_node->color == Node::Color::red;
  }
  
  template<typename keyType, typename valueType>
  void RBTree<keyType, valueType>::insert(const keyType t_key, const valueType t_value)
  {
    _root = insertHelper(_root, t_key, t_value);
    _root->color = Node::Color::black;
  }
  
  template<typename keyType, typename valueType>
  valueType *RBTree<keyType, valueType>::search(const keyType t_key) const
  {
    Node *curNode = _root;
    while (curNode != nullptr)
    {
      if (t_key == curNode->key)
      {
        return &curNode->value;
      }
      else if (t_key < curNode->key)
      {
        curNode = curNode->leftChild;
      }
      else
      {
        curNode = curNode->rightChild;
      }
    }
    return nullptr;
  }
  
  template<typename keyType, typename valueType>
  void RBTree<keyType, valueType>::initializeNode(RBTree::Node *t_node,
                                                  const keyType t_key,
                                                  const valueType t_value,
                                                  const typename RBTree::Node::Color t_color)
  {
    t_node->key = t_key;
    t_node->value = t_value;
    t_node->color = t_color;
    t_node->weight = 1;
    t_node->leftChild = nullptr;
    t_node->rightChild = nullptr;
  }
  
  template<typename keyType, typename valueType>
  typename RBTree<keyType, valueType>::Node *RBTree<keyType, valueType>::rotateLeft(RBTree::Node *t_head)
  {
    Node *x = t_head->rightChild;
    t_head->rightChild = x->leftChild;
    x->leftChild = t_head;
    x->color = x->leftChild->color;
    x->leftChild->color = Node::Color::red;
    
    t_head->weight = treeSize(t_head->leftChild) + treeSize(t_head->rightChild) + 1;
    x->weight = treeSize(x->leftChild) + treeSize(x->rightChild) + 1;
    return x;
  }
  
  template<typename keyType, typename valueType>
  typename RBTree<keyType, valueType>::Node *RBTree<keyType, valueType>::rotateRight(RBTree::Node *t_head)
  {
    Node *x = t_head->leftChild;
    t_head->leftChild = x->rightChild;
    x->rightChild = t_head;
    x->color = x->rightChild->color;
    x->rightChild->color = Node::Color::red;
  
    t_head->weight = treeSize(t_head->leftChild) + treeSize(t_head->rightChild) + 1;
    x->weight = treeSize(x->leftChild) + treeSize(x->rightChild) + 1;
    return x;
  }
  
  template<typename keyType, typename valueType>
  typename RBTree<keyType, valueType>::Node *RBTree<keyType, valueType>::colorFlip(RBTree::Node *t_head)
  {
    if (isRed(t_head))
    {
      t_head->color = Node::Color::black;
    }
    else
    {
      t_head->color = Node::Color::red;
    }
    
    if (isRed(t_head->leftChild))
    {
      t_head->leftChild->color = Node::Color::black;
    }
    else
    {
      t_head->leftChild->color = Node::Color::red;
    }
    
    if (isRed(t_head->rightChild))
    {
      t_head->rightChild->color = Node::Color::black;
    }
    else
    {
      t_head->rightChild->color = Node::Color::red;
    }
    
    return t_head;
  }
  
  template<typename keyType, typename valueType>
  typename RBTree<keyType, valueType>::Node *RBTree<keyType, valueType>::insertHelper(RBTree::Node *t_head,
                                                                                      const keyType t_key,
                                                                                      const valueType t_value)
  {
    Node *head = t_head;
    
    // Insert at bottom
    if (head == nullptr)
    {
      Node *newNode = new Node;
      initializeNode(newNode, t_key, t_value, Node::Color::red);
      return newNode;
    }
  
  
    // BST insert
    if (t_key == head->key)
    {
      head->value = t_value;
    }
    else if (t_key < head->key)
    {
      head->weight++;
      head->leftChild = insertHelper(head->leftChild, t_key, t_value);
    }
    else
    {
      head->rightChild = insertHelper(head->rightChild, t_key, t_value);
      head->weight++;
    }
  
    // fix right leaning reds on the way up
    if (isRed(head->rightChild))
    {
      head = rotateLeft(head);
    }
  
    // fix two reds in a row on the way up
    if (isRed(head->leftChild) && isRed(head->leftChild->leftChild))
    {
      head = rotateRight(head);
    }
    
    // Split 4-nodes on the way down
    if (isRed(head->leftChild) && isRed(head->rightChild))
    {
      colorFlip(head);
    }
    return head;
  }
  
  template<typename keyType, typename valueType>
  void RBTree<keyType, valueType>::preorder() const
  {
    preorderTreeWalk(_root);
    std::cout << std::endl;
  }
  
  template<typename keyType, typename valueType>
  void RBTree<keyType, valueType>::inorder() const
  {
    inorderTreeWalk(_root);
    std::cout << std::endl;
  }
  
  template<typename keyType, typename valueType>
  void RBTree<keyType, valueType>::postorder() const
  {
    postorderTreeWalk(_root);
    std::cout << std::endl;
  }
  
  template<typename keyType, typename valueType>
  void RBTree<keyType, valueType>::preorderTreeWalk(const Node *t_head) const
  {
    if (t_head == nullptr)
    {
      return;
    }
    std::cout << t_head->key << " ";
    preorderTreeWalk(t_head->leftChild);
    preorderTreeWalk(t_head->rightChild);
  }
  
  template<typename keyType, typename valueType>
  void RBTree<keyType, valueType>::inorderTreeWalk(const RBTree::Node *t_head) const
  {
    if (t_head == nullptr)
    {
      return;
    }
    inorderTreeWalk(t_head->leftChild);
    std::cout << t_head->key << " ";
    inorderTreeWalk(t_head->rightChild);
  }
  
  template<typename keyType, typename valueType>
  void RBTree<keyType, valueType>::postorderTreeWalk(const RBTree::Node *t_head) const
  {
    if (t_head == nullptr)
    {
      return;
    }
    postorderTreeWalk(t_head->leftChild);
    postorderTreeWalk(t_head->rightChild);
    std::cout << t_head->key << " ";
  }
  
  template<typename keyType, typename valueType>
  int RBTree<keyType, valueType>::rank(const keyType t_key) const
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
  int RBTree<keyType, valueType>::treeSize(const Node *t_target) const
  {
    if (t_target == nullptr)
    {
      return 0;
    }
  
    return t_target->weight;
  }
  
  template<typename keyType, typename valueType>
  int RBTree<keyType, valueType>::size() const
  {
    return treeSize(_root);
  }
  
  template<typename keyType, typename valueType>
  void RBTree<keyType, valueType>::treeDelete(RBTree::Node *t_root)
  {
    if (t_root != nullptr)
    {
      treeDelete(t_root->leftChild);
      treeDelete(t_root->rightChild);
      delete t_root;
    }
  }
  
  template<typename keyType, typename valueType>
  keyType RBTree<keyType, valueType>::select(const int t_pos) const
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
  
  template<typename keyType, typename valueType>
  void
  RBTree<keyType, valueType>::split(const keyType t_key, RBTree<keyType, valueType> &T1, RBTree<keyType, valueType> &T2)
  {
//    std::list<Node> nodes;
//    keyType keys[size()];
//    valueType values[size()];
//
//    inorderTreeWalkList(_root, nodes);
//    for (int i = 0; i < size(); i++)
//    {
//      Node curNode;
//      curNode = nodes.front();
//      nodes.pop_front();
//      keys[i] = curNode.key;
//      values[i] = curNode.value;
//    }
//
//    int splitIndex = 0;
//    while (t_key <= keys[splitIndex])
//    {
//      splitIndex++;
//    }
//
//    for (int i = 0; i < splitIndex + 1; i++)
//    {
//      T1.insert(keys[i], values[i]);
//    }
//    for (int i = splitIndex+1; i < size(); i++)
//    {
//      T2.insert(keys[i], values[i]);
//    }
  }
  
  template<typename keyType, typename valueType>
  int RBTree<keyType, valueType>::remove(const keyType t_key)
  {
    if (search(t_key) == nullptr)
    {
      return 0;
    }
    
    _root = deleteNode(_root, t_key);
    _root->color = Node::Color::black;
    return 1;
  }
  
  template<typename keyType, typename valueType>
  typename RBTree<keyType, valueType>::Node *RBTree<keyType, valueType>::treeMin(Node *t_root) const
  {
    if (t_root == nullptr)
    {
      return nullptr;
    }
  
    Node *curNode = t_root;
    while (curNode->leftChild != nullptr)
    {
      curNode = curNode->leftChild;
    }
    return curNode;
  }
  
  template<typename keyType, typename valueType>
  typename RBTree<keyType, valueType>::Node *RBTree<keyType, valueType>::treeMax(const RBTree::Node *t_root) const
  {
    if (t_root == nullptr)
    {
      return nullptr;
    }
  
    Node *curNode = t_root;
    while (curNode->rightChild != nullptr)
    {
      curNode = curNode->rightChild;
    }
    return curNode;
  }
  
  template<typename keyType, typename valueType>
  typename RBTree<keyType, valueType>::Node *RBTree<keyType, valueType>::fixup(RBTree::Node *t_head)
  {
    // Rotate-left right-leaning reds
    if (isRed(t_head->rightChild))
    {
      t_head = rotateLeft(t_head);
    }
    // rotate-right red-red pairs
    if (isRed(t_head->leftChild) && isRed(t_head->leftChild->leftChild))
    {
      t_head = rotateRight(t_head);
    }
    //split 4-nodes
    if (isRed(t_head->leftChild) && isRed(t_head->rightChild))
    {
      colorFlip(t_head);
    }
    return t_head;
  }
  
  template<typename keyType, typename valueType>
  typename RBTree<keyType, valueType>::Node *RBTree<keyType, valueType>::moveRedRight(RBTree::Node *t_head)
  {
    colorFlip(t_head);
    if (isRed(t_head->leftChild->leftChild))
    {
      t_head = rotateRight(t_head);
      colorFlip(t_head);
    }
    return t_head;
  }
  
  template<typename keyType, typename valueType>
  typename RBTree<keyType, valueType>::Node *RBTree<keyType, valueType>::deleteMin(RBTree::Node *t_head)
  {
    // remove node on bottom level (h must be red)
    if (t_head->leftChild == nullptr)
    {
      return nullptr;
    }
    // push red link down if necessary
    if (!isRed(t_head->leftChild) && !isRed(t_head->leftChild->leftChild))
    {
      t_head = moveRedRight(t_head);
    }
    // move down one level
    t_head->weight--;
    t_head->leftChild = deleteMin(t_head->leftChild);
    // fix right leaning red links and eliminate 4-nodes on the way up
    return fixup(t_head);
  }
  
  template<typename keyType, typename valueType>
  typename RBTree<keyType, valueType>::Node *RBTree<keyType, valueType>::moveRedLeft(RBTree::Node *t_head)
  {
    colorFlip(t_head);
    if (isRed(t_head->rightChild->leftChild))
    {
      t_head->rightChild = rotateRight(t_head->rightChild);
      t_head = rotateRight(t_head);
      colorFlip(t_head);
    }
    return t_head;
  }
  
  template<typename keyType, typename valueType>
  typename RBTree<keyType, valueType>::Node *RBTree<keyType, valueType>::deleteNode(RBTree::Node *t_head, keyType t_key)
  {
    Node* head = t_head;
    // node to be deleted is on left
    if (t_key < head->key)
    {
      // push red right if necessary
      if (!isRed(head->leftChild) && !isRed(head->leftChild->leftChild))
      {
        head = moveRedRight(head);
      }
      // move down on left child
      head->leftChild = deleteNode(head->leftChild, t_key);
    }
    else // node to be deleted is on right
    {
      // rotate to push red right
      if (isRed(head->leftChild))
      {
        head = rotateRight(head);
      }
      // equal (at bottom): delete node
      if (t_key == head->key && head->rightChild == nullptr)
      {
        return nullptr;
      }
      // push red right if necessary
      if (!isRed(head->rightChild) && !isRed(head->rightChild->leftChild))
      {
        head = moveRedRight(head);
      }
      // equal (not at bottom)
      if (t_key == head->key)
      {
        // replace current node w successor and delete
        Node *successor = treeMin(head->rightChild);
        head->key = successor->key;
        head->value = successor->value;
        successor->weight = head->weight - 1;
        head->rightChild = deleteMin(head->rightChild);
      }
      else
      {
        // move down on right child
        head->rightChild = deleteNode(head->rightChild, t_key);
      }
    }
    // fix right leaning red links and eliminate 4-nodes on the way up
    return fixup(head);
  }
  
  template<typename keyType, typename valueType>
  void RBTree<keyType, valueType>::inorderTreeWalkList(const RBTree::Node *t_head, std::list<Node> node)
  {
    if (t_head == nullptr)
    {
      return;
    }
    inorderTreeWalkList(t_head->leftChild, node);
    node.push_back(*t_head);
    inorderTreeWalkList(t_head->rightChild, node);
  }
}
#endif //DATASTRUCTURES_RBTREE_HPP
