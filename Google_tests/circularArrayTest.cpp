//
// Created by ansucato on 9/9/19.
//

#include <gtest/gtest.h>
#include "../CircularArray_lib/CircularArray.h"
#include <random>

TEST(CircularArray, constructorTest)
{
    CircularArray<int> a(10);
    EXPECT_EQ(a.capacity(), 10);
    EXPECT_EQ(a.length(), 0);

    CircularArray<std::string> b(100);
    EXPECT_EQ(b.capacity(), 100);
    EXPECT_EQ(b.length(), 0);

    CircularArray<float> c(1000000);
    EXPECT_EQ(c.capacity(), 1000000);
    EXPECT_EQ(c.length(), 0);
}


TEST(CircularArray, copyConstructorTest)
{
    CircularArray<int> a(10);
    a.addFront(4);
    a.addFront(3);
    a.addEnd(5);
    a.addEnd(6);
    a.addEnd(7);
    a.addFront(2);
    a.addFront(1);
    a.addFront(0);

    for (int i = 0; i < 8; i++)
    {
        EXPECT_EQ(a[i], i);
    }

    CircularArray<int> b = a;
    EXPECT_EQ(a.capacity(), b.capacity());
    EXPECT_EQ(a.length(), b.length());
    for (int i = 0; i < 8; i++)
    {
        EXPECT_EQ(b[i], i);
    }

    a[5] = 100;
    for (int i = 0; i < 8; i++)
    {
        EXPECT_EQ(b[i], i);
    }
}

TEST(CircularArray, assignmentOperatorTest)
{
    CircularArray<int> a(10);
    a.addFront(4);
    a.addFront(3);
    a.addEnd(5);
    a.addEnd(6);
    a.addEnd(7);
    a.addFront(2);
    a.addFront(1);
    a.addFront(0);

    for (int i = 0; i < 8; i++)
    {
        EXPECT_EQ(a[i], i);
    }

    CircularArray<int> b(1);
    b = a;
    EXPECT_EQ(a.capacity(), b.capacity());
    EXPECT_EQ(a.length(), b.length());
    for (int i = 0; i < 8; i++)
    {
        EXPECT_EQ(b[i], i);
    }

    a[5] = 100;
    for (int i = 0; i < 8; i++)
    {
        EXPECT_EQ(b[i], i);
    }

    // Check self assignment
    b = b;
    for (int i = 0; i < 8; i++)
    {
        EXPECT_EQ(b[i], i);
    }

}

TEST(CircularArray, addBackTest)
{
    CircularArray<int> a(1000000);
    for (int i = 0; i < 1000000; i++)
    {
        a.addEnd(i * 2);
        ASSERT_EQ(a[i], i * 2);
        ASSERT_EQ(a.length(), i + 1);
    }

    CircularArray<std::string> b(1000000);
    EXPECT_EQ(b.length(), 0);
    EXPECT_EQ(b.capacity(), 1000000);
    for (int i = 0; i < 1000000; i++)
    {
        b.addEnd("index_" + std::to_string(i));
        ASSERT_EQ(b[i], "index_" + std::to_string(i));
        ASSERT_EQ(b.length(), i + 1);
    }
}

TEST(CircularArray, addFrontTest)
{
    CircularArray<int> a(1000000);
    for (int i = 0; i < 1000000; i++)
    {
        a.addFront(i * 3);
        ASSERT_EQ(a[0], i * 3);
        ASSERT_EQ(a.length(), i + 1);
    }

    CircularArray<std::string> b(1000000);
    EXPECT_EQ(b.length(), 0);
    EXPECT_EQ(b.capacity(), 1000000);
    for (int i = 0; i < 1000000; i++)
    {
        b.addFront("index_" + std::to_string(i));
        ASSERT_EQ(b[0], "index_" + std::to_string(i));
        ASSERT_EQ(b.length(), i + 1);
    }
}

TEST(CircularArray, lengthTest)
{
    CircularArray<int> a(1000000);
    EXPECT_EQ(a.length(), 0);
    for (int i = 0; i < 1000000; i++)
    {
        a.addEnd(i);
        ASSERT_EQ(a.length(), i + 1);
    }
}

TEST(CircularArray, accessOperatorTest)
{
    CircularArray<int> a(10);
    a.addFront(4);
    a.addFront(3);
    a.addEnd(5);
    a.addEnd(6);
    a.addEnd(7);
    a.addFront(2);
    a.addFront(1);
    a.addFront(0);

    for (int i = 0; i < 8; i++)
    {
        EXPECT_EQ(a[i], i);
    }

    a[20];
}

TEST(CircularArray, delFrontTest)
{
    CircularArray<int> a(10);
    a.addFront(4);
    a.addFront(3);
    a.addEnd(5);
    a.addEnd(6);
    a.addEnd(7);
    a.addFront(2);
    a.addFront(1);
    a.addFront(0);

    for (int i = 0; i < 8; i++)
    {
        EXPECT_EQ(a[i], i);
    }
    EXPECT_EQ(a.length(), 8);

    a.delFront();
    EXPECT_EQ(a.length(), 7);
    EXPECT_EQ(a[0], 1);

    a.delFront();
    EXPECT_EQ(a.length(), 6);
    EXPECT_EQ(a[0], 2);
}

TEST(CircularArray, delEndTest)
{
    CircularArray<int> a(10);
    a.addFront(4);
    a.addFront(3);
    a.addEnd(5);
    a.addEnd(6);
    a.addEnd(7);
    a.addFront(2);
    a.addFront(1);
    a.addFront(0);

    for (int i = 0; i < 8; i++)
    {
        EXPECT_EQ(a[i], i);
    }
    EXPECT_EQ(a.length(), 8);

    a.delEnd();
    EXPECT_EQ(a.length(), 7);
    EXPECT_EQ(a[6], 6);

    a.delEnd();
    EXPECT_EQ(a.length(), 6);
    EXPECT_EQ(a[5], 5);
}


TEST(CircularArray, linearSearchTest)
{
    CircularArray<int> a(1000000);
    for (int i = 0; i < 1000000; i++)
    {
        a.addEnd(i * 3);
    }
    EXPECT_EQ(a.linearSearch(1234 * 3), 1234);
    EXPECT_EQ(a.linearSearch(99999 * 3), 99999);
}

TEST(CircularArray, quickSelect)
{
    CircularArray<int> a(10);
    a.addEnd(15);
    a.addEnd(18);
    a.addEnd(2);
    a.addFront(7);
    a.addEnd(9);
    a.addFront(20);
    a.addFront(4);
    a.addEnd(12);
    a.addEnd(13);
    a.addEnd(19);

    EXPECT_EQ(a.quickSelect(1), 2);
    EXPECT_EQ(a.quickSelect(2), 4);
    EXPECT_EQ(a.quickSelect(5), 12);
    EXPECT_EQ(a.quickSelect(9), 19);
    EXPECT_EQ(a.quickSelect(10), 20);

    EXPECT_EQ(a.quickSelect(50), -1);
}

TEST(CircularArray, stableSort)
{
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(-1000000, 1000000);
    auto randInt = std::bind(distribution, generator);
    CircularArray<int> a(100000);

    for (int i = 0; i < 100000; i++)
    {
        a.addFront(randInt());
    }

    a.stableSort();
    for (int i = 0; i < 100000 - 1; i++)
    {
        ASSERT_TRUE(a[i] <= a[i+1]);
    }
}

TEST(CircularArray, BinarySearchTest)
{
    CircularArray<int> a(1000000);
    for (int i = 0; i < 1000000; i++)
    {
        a.addFront(i * 3);
    }
    a.stableSort();
    EXPECT_EQ(a.binSearch(1*3), 1);
    EXPECT_EQ(a.binSearch(1234 * 3), 1234);
    EXPECT_EQ(a.binSearch(99999 * 3), 99999);
    // does not exist case
    EXPECT_EQ(a.binSearch(2), -1);
}
