#pragma once

#include <chrono>
#include <condition_variable>
#include <deque>
#include <mutex>
#include <optional>

template <typename TItem> class thread_safe_queue_t {
public:
  using queue_t = std::deque<TItem>;

  void push(TItem item) {
    std::lock_guard<std::mutex> lk(m_mutex);
    m_queue.emplace_back(std::move(item));
    m_cv.notify_one();
  }

  auto pop() -> std::optional<TItem> {
    std::unique_lock<std::mutex> lk(m_mutex);
    if (!m_cv.wait_for(lk, std::chrono::seconds(1),
                       [this] { return !m_queue.empty(); })) {
      return std::nullopt;
    }

    auto item = std::make_optional(m_queue.front());
    m_queue.pop_front();
    return item;
  }

private:
  queue_t m_queue;
  std::mutex m_mutex;
  std::condition_variable m_cv;
};
