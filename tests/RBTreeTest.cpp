//
// Created by ansucato on 10/15/19.
//

#include "gtest/gtest.h"
#include "DataStructures/RBTree.hpp"

TEST(RBTreeTest, ConstructorTest)
{
  DataStructures::RBTree<int, std::string> a;
  DataStructures::RBTree<int, int> b;
  DataStructures::RBTree<int*, std::string> c;
  DataStructures::RBTree<int, std::string*> d;
}

TEST(RBTreeTest, SearchTest)
{
  DataStructures::RBTree<int, std::string> a;
  a.search(5);
}

TEST(RBTreeTest, InsertTest)
{
  const int SIZE = 10;
  DataStructures::RBTree<int, std::string> a;
  for (int i = 0; i < SIZE; i++)
  {
    a.insert(i, std::to_string(i));
  }
  a.preorder();
  a.inorder();
  a.postorder();
  
  DataStructures::RBTree<int, std::string> b, c;
  a.split(4, b, c);
}