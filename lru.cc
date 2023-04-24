//
// Created by Frederick.H on 2023/4/23.
//

#include "lru.h"

#include "lib.h"

int LruCache::Get(int key) {
  if (index_.find(key) != index_.end()) {
    auto item = index_[key];
    auto value = item->second;
    items_.erase(item);
    items_.push_front(std::make_pair(key, value));
    index_[key] = items_.begin();
    return value;
  }
  return NONE;
}

int LruCache::Peek(int key) {
  if (index_.find(key) != index_.end()) {
    return index_[key]->second;
  }
  return NONE;
}

void LruCache::Put(int key, int value) {
  if (index_.find(key) != index_.end()) {
    auto item = index_[key];
    items_.erase(item);
    items_.push_front(std::make_pair(key, value));
  } else {
    if (len_ == capacity_) {
      auto old_key = items_.back().first;
      items_.pop_back();
      index_.erase(old_key);
      items_.push_front(std::make_pair(key, value));
      index_.insert(std::make_pair(key, items_.begin()));
    } else {
      items_.push_front(std::make_pair(key, value));
      index_.insert(std::make_pair(key, items_.begin()));
      len_++;
    }
  }
}

bool LruCache::Del(int key) {
  if (index_.find(key) != index_.end()) {
    auto it = index_[key];
    items_.erase(it);
    index_.erase(key);
    len_--;
    return true;
  }
  return false;
}

int LruCache::PopBack() {
  auto it = items_.back();
  int key = it.first;
  items_.pop_back();
  index_.erase(key);
  len_--;
  return key;
}