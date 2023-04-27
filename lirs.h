//
// Created by Frederick.H on 2023/4/25.
//

#ifndef CACHE__LIRS_H_
#define CACHE__LIRS_H_

#include <list>
#include <map>

#include "lib.h"

enum LirsType {
  LIR = 101,
  HIR,
  NHIR,
};

struct LirsNode {
  int key;
  int value;
  LirsType type;
  std::list<LirsNode*>::iterator s;
  std::list<LirsNode*>::iterator q;

  LirsNode(int key, int value, std::list<LirsNode*>::iterator ends,
           std::list<LirsNode*>::iterator endq)
      : key(key), value(value), s(ends), q(endq), type(LIR) {}
  LirsNode(int key, int value, std::list<LirsNode*>::iterator ends,
           std::list<LirsNode*>::iterator endq, LirsType type)
      : key(key), value(value), s(ends), q(endq), type(type) {}
  void SetType(LirsType type) { type = type; }
};

class Lirs {
 public:
  Lirs(int capacity)
      : capacity_(capacity),
        size_(0),
        s_size_(0.99 * capacity),
        q_size_(0.1 * capacity) {}
  Lirs(int capacity, int s, int q)
      : capacity_(capacity), size_(0), s_size_(s), q_size_(q) {}
  ~Lirs() {
    for (auto it = map_.begin(); it != map_.end(); ++it) {
      delete (it->second);
    }
  }

  bool Put(int key, int value);

  int Get(int key, int value = INVALID);

  void Pruning();

 private:
  int capacity_;
  int size_;
  int q_size_;
  int s_size_;
  std::list<LirsNode*> s_, q_;
  std::map<int, LirsNode*> map_;

  void MoveToTop(LirsNode* p, bool to_s = true);

  void Push(LirsNode* p, bool to_s);

  void Pop(LirsNode* p, bool from_s);

  void Bottom();

  void RemoveOne();
};

#endif  // CACHE__LIRS_H_
