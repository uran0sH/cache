//
// Created by Frederick.H on 2023/4/23.
//

#ifndef CACHE__LRU_H_
#define CACHE__LRU_H_

#include <list>
#include <unordered_map>

class LRUCache {
 public:
  explicit LRUCache(int capacity) : capacity_(capacity), count_(0) {}
  LRUCache(const LRUCache&) = delete;
  LRUCache& operator=(const LRUCache&) = delete;
  ~LRUCache() {}
  bool get(int key, int& value);
  void put(int key, int value);

 private:
  std::list<std::pair<int, int>> items_;
  std::unordered_map<int, std::list<std::pair<int, int>>::iterator> index_;
  int capacity_;
  int count_;

  int remove(int key) {}
  void push_front(std::pair<int, int> item) {}
};

#endif  // CACHE__LRU_H_
