//
// Created by Frederick.H on 2023/4/23.
//

#include <gtest/gtest.h>
#include "../lru.h"

// Demonstrate some basic assertions.
TEST(LruTest, Insert) {
  LRUCache cache(3);
  cache.put(1, 1);
  int result;
  EXPECT_TRUE(cache.get(1, result));
  EXPECT_EQ(1, result);
  cache.put(2, 2);
  cache.put(3, 3);
  cache.put(4, 4);
  EXPECT_FALSE(cache.get(1, result));
  EXPECT_TRUE(cache.get(4, result));
  EXPECT_EQ(4, result);
  EXPECT_TRUE(cache.get(3, result));
  EXPECT_EQ(3, result);
  cache.put(5, 5);
  EXPECT_FALSE(cache.get(2, result));
}