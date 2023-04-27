//
// Created by Frederick.H on 2023/4/27.
//

#include <gtest/gtest.h>
#include "../lirs.h"

TEST(LirsTest, Insert) {
  Lirs lirs(10);
  for (int i = 0; i < 10; i++) {
    lirs.Put(i, i);
  }
  lirs.Put(2, 2);
  ASSERT_EQ(2, lirs.Get(2));
  lirs.Put(11, 11);
  ASSERT_EQ(3, lirs.Get(3));
}