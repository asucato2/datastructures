//
// Created by ansucato on 11/27/19.
//

#include <gtest/gtest.h>
#include "DataStructures/Heap.hpp"
#include <random>
#include <vector>


TEST(HeapTest, DefaultConstructorTest)
{
  DataStructures::Heap<int, std::string> a;
  DataStructures::Heap<std::string, int> b;
  DataStructures::Heap<int, int*> c;
  DataStructures::Heap<int*, std::string> d;
}

TEST(HeapTest, ConstructorTest)
{
  // 1    2    3  4  5    6
  // Hi there how is it going
  int size = 10;
//  int keys[] = {5,2,3,6,1,4};
  int keys[] = {5,8,1,2,9,4,3,6,7,0};

  std::string values[] = {"it", "there", "how", "going?", "Hi", "is", "", "", "", ""};
  DataStructures::Heap<int, std::string> a(keys, values, size);
  EXPECT_EQ(a.length(), 10);
  EXPECT_EQ(a.isValid(0), 1);
  a.printKey();
}

TEST(HeapTest, CopyConstructorTest)
{
  const int SIZE = 99999;
  DataStructures::Heap<int, std::string> a;
  for (int i = 0; i < SIZE; i++)
  {
    a.insert(SIZE - i, std::to_string(i));
  }
  
  DataStructures::Heap<int, std::string> b = a;
  EXPECT_EQ(b.length(), a.length());
  EXPECT_EQ(b.peakValue(), a.peakValue());
  EXPECT_EQ(b.extractMin(), a.peakKey());
  EXPECT_NE(b.peakKey(), a.peakKey());
}

TEST(HeapTest, AssignmentOperatorTest)
{
  const int SIZE = 99999;
  DataStructures::Heap<int, std::string> a;
  for (int i = 0; i < SIZE; i++)
  {
    a.insert(SIZE - i, std::to_string(i));
  }
  
  DataStructures::Heap<int, std::string> b;
  b = a;
  EXPECT_EQ(b.length(), a.length());
  EXPECT_EQ(b.peakValue(), a.peakValue());
  EXPECT_EQ(b.extractMin(), a.peakKey());
  EXPECT_NE(b.peakKey(), a.peakKey());
}

TEST(HeapTest, InsertTest)
{
  const int SIZE = 1000;
  DataStructures::Heap<int, std::string> a;
  for (int i = 0; i < SIZE; i++)
  {
    a.insert(SIZE - i, std::to_string(i));
  }
  EXPECT_EQ(a.isValid(0), 1);
  EXPECT_EQ(a.length(), SIZE);
}

TEST(HeapTest, ExtractMinTest)
{
  const int SIZE = 1000;
  const int EXTRACTSIZE = 11;
  DataStructures::Heap<int, std::string> a;
  for (int i = 0; i < SIZE; i++)
  {
    a.insert(SIZE - i, std::to_string(i));
  }
  EXPECT_EQ(a.isValid(0), 1);
  EXPECT_EQ(a.length(), SIZE);
  for (int i = 0; i < EXTRACTSIZE; i ++)
  {
    int minVal = a.peakKey();
    EXPECT_EQ(minVal, a.extractMin());
  }
  EXPECT_EQ(a.length(), SIZE - EXTRACTSIZE);
}

TEST(HeapTest, PeakValueTest)
{
  const int SIZE = 1000;
  DataStructures::Heap<int, std::string> a;
  for (int i = 0; i < SIZE; i++)
  {
    a.insert(SIZE - i, std::to_string(i));
    EXPECT_EQ(a.peakValue(), std::to_string(i));
  }
}
