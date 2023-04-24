//
// Created by Frederick.H on 2023/4/23.
//

#ifndef CACHE__LRU_H_
#define CACHE__LRU_H_

#include <list>
#include <unordered_map>

class LruCache {
 public:
  explicit LruCache(int capacity) : capacity_(capacity), len_(0) {}
  LruCache(const LruCache&) = delete;
  LruCache& operator=(const LruCache&) = delete;
  ~LruCache() {}
  int Get(int key);
  int Peek(int key);
  void Put(int key, int value);
  bool Del(int key);
  int PopBack();
  int len() { return len_; }

 private:
  std::list<std::pair<int, int>> items_;
  std::unordered_map<int, std::list<std::pair<int, int>>::iterator> index_;
  int capacity_;
  int len_;
};

#endif  // CACHE__LRU_H_
