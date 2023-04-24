//
// Created by Frederick.H on 2023/4/24.
//

#include "arc.h"

bool Arc::Put(int key, int value) {
  // key in t1
  if (t1_.Peek(key) != NONE) {
    t1_.Del(key);
    t2_.Put(key, value);
    return true;
  }

  // key in t2
  if (t2_.Peek(key) != NONE) {
    t2_.Put(key, value);
    return true;
  }

  int b1_len = b1_.len();
  int b2_len = b2_.len();
  int delta = 1;

  if (b1_.Peek(key) != NONE) {
    if (b2_len > b1_len) {
      delta = b2_len / b1_len;
    }
    p_ = std::min(capacity_, p_ + delta);
    if (t1_.len() + t2_.len() > capacity_) {
      Replace(false);
    }
    b1_.Del(key);
    t2_.Put(key, value);
    return true;
  } else if (b2_.Peek(key) != NONE) {
    if (b1_len > b2_len) {
      delta = b1_len / b2_len;
    }
    p_ = std::max(0, p_ - delta);
    if (t1_.len() + t2_.len() >= capacity_) {
      Replace(true);
    }
    b2_.Del(key);
    t2_.Put(key, value);
    return true;
  }

  // add to t1.
  if (t1_.len() + t2_.len() >= capacity_) {
    Replace(false);
  }

  if (b1_.len() > capacity_ - p_) {
    b1_.PopBack();
  }

  if (b2_.len() > p_) {
    b2_.PopBack();
  }
  t1_.Put(key, value);
  return true;
}

int Arc::Get(int key) {
  int value = t1_.Peek(key);
  if (value != NONE) {
    t1_.Del(key);
    t2_.Put(key, value);
    return value;
  }

  value = t2_.Get(key);
  if (value != NONE) {
    return value;
  }
  return NONE;
}

/// @param flag: true is that x is in b2.
void Arc::Replace(bool flag) {
  int t1_len = t1_.len();
  if (t1_len > 0 && (t1_len > p_ || (t1_len == p_ && flag))) {
    int key = t1_.PopBack();
    b1_.Put(key, INVALID);
  } else {
    int key = t2_.PopBack();
    b2_.Put(key, INVALID);
  }
}

int Arc::Peek(int key) {
  int value = t1_.Peek(key);
  if (value != NONE) {
    //    sta_.Hit(value);
    return value;
  }

  value = t2_.Peek(key);
  //  sta_.Hit(value);
  return value;
}