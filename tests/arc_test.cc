//
// Created by Frederick.H on 2023/4/24.
//

#include <gtest/gtest.h>
#include "../arc.h"

TEST(ArcTest, Insert) {
  Arc arc(2);
  arc.Put(1, 1);
  arc.Put(2, 2);
  arc.Put(3, 3);
  EXPECT_EQ(NONE, arc.Get(1));
  arc.Put(1, 1);
  arc.Put(2, 2);
  arc.Put(3, 3);
  EXPECT_EQ(NONE, arc.Get(1));
  EXPECT_EQ(2, arc.Get(2));
  EXPECT_EQ(3, arc.Get(3));
}