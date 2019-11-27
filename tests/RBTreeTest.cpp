//
// Created by ansucato on 10/15/19.
//

#include "gtest/gtest.h"
#include "DataStructures/RBTree.hpp"
#include <string>
#include <iostream>
#include <random>


void swap(int arr[], int i, int j)
{
  int temp = arr[i];
  arr[i] = arr[j];
  arr[j] = temp;
}

TEST(BSTTest, ConstructorTest)
{
  DataStructures::RBTree<int, std::string> a;
  EXPECT_EQ(a.size(), 0);

  DataStructures::RBTree<int, int> b;
  EXPECT_EQ(b.size(), 0);

  DataStructures::RBTree<int, float> c;
  EXPECT_EQ(c.size(), 0);
}

TEST(BSTTest, InsertTest)
{
  DataStructures::RBTree<int, std::string> a;
  a.insert(20, "S 20");
  EXPECT_EQ(a.size(), 1);
  a.insert(30, "S 30");
  EXPECT_EQ(a.size(), 2);
  a.insert(10, "S 10");
  EXPECT_EQ(a.size(), 3);


}

TEST(BSTTest, ConstructorTwoTest)
{
  const int SIZE = 10;

  int keys[SIZE];
  std::string data[SIZE];

  std::default_random_engine generator;
  std::uniform_int_distribution<int> distribution(0, SIZE - 1);
  auto rand = std::bind(distribution, generator);

  for (int i = 0; i < SIZE; i++)
  {
    keys[i] = i;
  }
  for (int i = 0; i < SIZE; i++)
  {
    swap(keys, i, rand());
  }
  for (int i = 0; i < SIZE; i++)
  {
    data[i] = "S " + std::to_string(keys[i]);
  }

  DataStructures::RBTree<int, std::string> a(keys, data, SIZE);
  EXPECT_EQ(a.size(), SIZE);
}

TEST(BSTTest, CopyConstructorTest)
{
  const int SIZE = 10;
  
  int keys[SIZE];
  std::string data[SIZE];
  
  std::default_random_engine generator;
  std::uniform_int_distribution<int> distribution(0, SIZE - 1);
  auto rand = std::bind(distribution, generator);
  
  for (int i = 0; i < SIZE; i++)
  {
    keys[i] = i;
  }
  for (int i = 0; i < SIZE; i++)
  {
    swap(keys, i, rand());
  }
  for (int i = 0; i < SIZE; i++)
  {
    data[i] = "S " + std::to_string(keys[i]);
  }
  
  DataStructures::RBTree<int, std::string> a(keys, data, SIZE);
  
  DataStructures::RBTree<int, std::string> b = a;
  EXPECT_EQ(*a.search(SIZE / 2), *b.search(SIZE / 2));
  a.remove(SIZE / 2);
  EXPECT_EQ(a.search(SIZE / 2), nullptr);
  EXPECT_NE(b.search(SIZE / 2), nullptr);
  EXPECT_EQ(*b.search(SIZE / 2), "S " + std::to_string(SIZE / 2));
}

TEST(BSTTest, AssignmentOperatorTest)
{
  const int SIZE = 10;
  
  int keys[SIZE];
  std::string data[SIZE];
  
  std::default_random_engine generator;
  std::uniform_int_distribution<int> distribution(0, SIZE - 1);
  auto rand = std::bind(distribution, generator);
  
  for (int i = 0; i < SIZE; i++)
  {
    keys[i] = i;
  }
  for (int i = 0; i < SIZE; i++)
  {
    swap(keys, i, rand());
  }
  for (int i = 0; i < SIZE; i++)
  {
    data[i] = "S " + std::to_string(keys[i]);
  }
  
  DataStructures::RBTree<int, std::string> a(keys, data, SIZE);
  
  DataStructures::RBTree<int, std::string> b;
  b.insert(12, "S 12");
  b = a;
  EXPECT_EQ(*a.search(SIZE / 2), *b.search(SIZE / 2));
  a.remove(SIZE / 2);
  EXPECT_EQ(a.search(SIZE / 2), nullptr);
  EXPECT_NE(b.search(SIZE / 2), nullptr);
  EXPECT_EQ(*b.search(SIZE / 2), "S " + std::to_string(SIZE / 2));
}


TEST(BSTTest, SearchTest)
{
  const int SIZE = 10000;

  int keys[SIZE];
  std::string data[SIZE];

  std::default_random_engine generator;
  std::uniform_int_distribution<int> distribution(0, SIZE - 1);
  auto rand = std::bind(distribution, generator);

  for (int i = 0; i < SIZE; i++)
  {
    keys[i] = i;
  }
  for (int i = 0; i < SIZE; i++)
  {
    swap(keys, i, rand());
  }
  for (int i = 0; i < SIZE; i++)
  {
    data[i] = "S " + std::to_string(keys[i]);
  }

  DataStructures::RBTree<int, std::string> a(keys, data, SIZE);

  EXPECT_EQ(*a.search(0), "S 0");
  EXPECT_EQ(*a.search(SIZE / 2), "S " + std::to_string(SIZE / 2));
  EXPECT_EQ(*a.search(SIZE-1), "S " + std::to_string(SIZE - 1));
  EXPECT_EQ(a.search(SIZE), nullptr);
}

TEST(BSTTest, RemoveTest)
{
  const int SIZE = 9999;

  int keys[SIZE];
  std::string data[SIZE];

  std::default_random_engine generator;
  std::uniform_int_distribution<int> distribution(0, SIZE - 1);
  auto rand = std::bind(distribution, generator);

  for (int i = 0; i < SIZE; i++)
  {
    keys[i] = i;
  }
  for (int i = 0; i < SIZE; i++)
  {
    swap(keys, i, rand());
  }
  for (int i = 0; i < SIZE; i++)
  {
    data[i] = "S " + std::to_string(keys[i]);
  }

  DataStructures::RBTree<int, std::string> a(keys, data, SIZE);

  EXPECT_EQ(a.size(), SIZE);
  EXPECT_EQ(*a.search(SIZE / 2), "S " + std::to_string(SIZE / 2));
  EXPECT_EQ(a.remove(SIZE/2), 1);
  EXPECT_EQ(a.search(SIZE/2), nullptr);
  EXPECT_EQ(a.size(), SIZE-1);
  EXPECT_EQ(a.remove(SIZE/2), 0);
}

TEST(BSTTest, RankTest)
{
  const int SIZE = 1000000;
  
  int *keys = new int[SIZE];
  std::string *data = new std::string[SIZE];

  std::default_random_engine generator;
  std::uniform_int_distribution<int> distribution(0, SIZE - 1);
  auto rand = std::bind(distribution, generator);

  for (int i = 0; i < SIZE; i++)
  {
    keys[i] = i;
  }
  for (int i = 0; i < SIZE; i++)
  {
    swap(keys, i, rand());
  }
  for (int i = 0; i < SIZE; i++)
  {
    data[i] = "S " + std::to_string(keys[i]);
  }

  DataStructures::RBTree<int, std::string> a(keys, data, SIZE);

  for (int i = 0; i < SIZE; i++)
  {
    EXPECT_EQ(a.rank(i), i + 1);
  }
  
  DataStructures::RBTree<int, std::string> b = a;
  
  for (int i = 0; i < SIZE; i++)
  {
    EXPECT_EQ(b.rank(i), i + 1);
  }
  
  delete[] keys;
  delete[] data;
}

TEST(BSTTest, SelectTest)
{
  const int SIZE = 999999;
  
  int *keys = new int[SIZE];
  std::string *data = new std::string[SIZE];
  
  std::default_random_engine generator;
  std::uniform_int_distribution<int> distribution(0, SIZE - 1);
  auto rand = std::bind(distribution, generator);
  
  for (int i = 0; i < SIZE; i++)
  {
    keys[i] = i;
  }
  for (int i = 0; i < SIZE; i++)
  {
    swap(keys, i, rand());
  }
  for (int i = 0; i < SIZE; i++)
  {
    data[i] = "S " + std::to_string(keys[i]);
  }
  
  DataStructures::RBTree<int, std::string> a(keys, data, SIZE);
  
  for (int i = 0; i < SIZE; i++)
  {
    EXPECT_EQ(a.select(i + 1), i);
  }
  
  delete[] keys;
  delete[] data;
}