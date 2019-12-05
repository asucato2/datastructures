//
// Created by ansucato on 12/3/19.
//

#include <gtest/gtest.h>
#include "DataStructures/BHeap.hpp"

TEST(BHeapTest, DefaultConstructorTest)
{
  DataStructures::BHeap<int, int> a;
  DataStructures::BHeap<int, std::string> b;
  DataStructures::BHeap<std::string, int*> c;
  DataStructures::BHeap<int*, std::string*> d;
}

TEST(BHeapTest, PrintKeyTest)
{
  DataStructures::BHeap<int, std::string> a;
  a.insert(1, std::to_string(1));
  a.printKey();
}

