//
// Created by Frederick.H on 2023/4/24.
//

#ifndef CACHE__ARC_H_
#define CACHE__ARC_H_

#include "lib.h"
#include "lru.h"

class Arc {
 public:
  explicit Arc(int capacity)
      : capacity_(capacity),
        p_(0),
        t1_(capacity),
        b1_(capacity),
        t2_(capacity),
        b2_(capacity) {}

  bool Put(int key, int value);
  int Get(int key);
  int Peek(int key);
  void Replace(bool flag);
  int len() { return t1_.len() + t2_.len(); }

  Arc(const Arc&) = delete;
  Arc& operator=(const Arc&) = delete;
  ~Arc() {}

 private:
  int capacity_;
  int p_;
  LruCache t1_, b1_, t2_, b2_;
};

#endif  // CACHE__ARC_H_
