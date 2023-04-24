//
// Created by Frederick.H on 2023/4/23.
//

#include <gtest/gtest.h>
#include "../lru.h"
#include "../lib.h"

// Demonstrate some basic assertions.
TEST(LruTest, Insert) {
  LruCache cache(3);
  cache.Put(1, 1);
  EXPECT_EQ(1, cache.Get(1));
  cache.Put(2, 2);
  cache.Put(3, 3);
  cache.Put(4, 4);
  EXPECT_EQ(NONE, cache.Get(1));
  EXPECT_EQ(4, cache.Get(4));
  EXPECT_EQ(3, cache.Get(3));
  cache.Put(5, 5);
  EXPECT_EQ(NONE, cache.Get(2));
}