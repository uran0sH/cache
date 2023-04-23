//
// Created by Frederick.H on 2023/4/23.
//

#include "lru.h"

bool LRUCache::get(int key, int& value) {
  if (index_.find(key) != index_.end()) {
    auto item = index_[key];
    value = item->second;
    items_.erase(item);
    items_.push_front(std::make_pair(key, value));
    index_[key] = items_.begin();
    return true;
  }
  return false;
}

void LRUCache::put(int key, int value) {
  if (index_.find(key) != index_.end()) {
    auto item = index_[key];
    items_.erase(item);
    items_.push_front(std::make_pair(key, value));
  } else {
    if (count_ == capacity_) {
      auto old_key = items_.back().first;
      items_.pop_back();
      index_.erase(old_key);
      items_.push_front(std::make_pair(key, value));
      index_.insert(std::make_pair(key, items_.begin()));
    } else {
      items_.push_front(std::make_pair(key, value));
      index_.insert(std::make_pair(key, items_.begin()));
      count_++;
    }
  }
}
