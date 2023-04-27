//
// Created by Frederick.H on 2023/4/25.
//

#include "lirs.h"

bool Lirs::Put(int key, int value) {
  if (map_.find(key) != map_.end()) {
    auto node_p = map_[key];
    if (!VALID(node_p->value)) {
      size_++;
    }
    // TODO: ? problem
    Get(key, value);
    return true;
  }

  // S is not FULL, so just input it as LIR
  auto* p = new LirsNode(key, value, s_.end(), q_.end());
  Push(p, true);
  ++size_;

  // S is FULL, so just input it as HIR
  if (size_ > s_size_) {
    // if (s_.size() > s_size_) {
    p->type = HIR;
    Push(p, false);
  }

  return true;
}

int Lirs::Get(int key, int value) {
  if (map_.find(key) == map_.end()) {
    return NONE;
  }
  auto p = map_[key];
  if (p->type == LIR) {
    MoveToTop(p);
  } else if (p->type == HIR) {
    if (p->s != s_.end()) {
      p->type = LIR;
      MoveToTop(p);
      Pop(p, false);
      Bottom();
    } else {
      Push(p, true);
      MoveToTop(p, false);
    }
  } else {
    // NHIR
    RemoveOne();
    p->value = value;
    if (p->s != s_.end()) {
      p->type = LIR;
      MoveToTop(p);
      Bottom();
    } else {
      p->type = HIR;
      Push(p, true);
      Push(p, false);
    }
  }

  Pruning();
  return p->value;
}

void Lirs::Pruning() {
  while (!s_.empty() && s_.back()->type != LIR) {
    s_.back()->s = s_.end();
    s_.pop_back();
  }
}

void Lirs::MoveToTop(LirsNode* p, bool to_s) {
  Pop(p, to_s);
  Push(p, to_s);
}

void Lirs::Push(LirsNode* p, bool to_s) {
  if (to_s) {
    s_.push_front(p);
    p->s = s_.begin();
  } else {
    q_.push_front(p);
    p->q = q_.begin();
  }

  if (map_.find(p->key) == map_.end()) {
    map_[p->key] = p;
  }
}

void Lirs::Pop(LirsNode* p, bool from_s) {
  if (from_s) {
    s_.erase(p->s);
    p->s = s_.end();
  } else {
    q_.erase(p->q);
    p->q = q_.end();
  }
}

void Lirs::Bottom() {
  auto bottom = s_.back();
  if (bottom->type == LIR) {
    bottom->type = HIR;
    if (bottom->q != q_.end()) {
      Pop(bottom, false);
    }
    Push(bottom, false);
  }
}

void Lirs::RemoveOne() {
  auto p_node = q_.back();
  q_.pop_back();
  p_node->q = q_.end();
  if (VALID(p_node->value)) {
    p_node->value = INVALID;
    size_--;
  }
  if (p_node->s != s_.end()) {
    p_node->type = NHIR;
  } else {
    map_.erase(p_node->key);
    delete p_node;
  }
}