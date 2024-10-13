#pragma once

#include <algorithm>
#include <deque>
#include <optional>

#include <absl/time/time.h>
#include <absl/synchronization/mutex.h>

template <typename TItem> class thread_safe_queue_t {
public:
  using queue_t = std::deque<TItem>;

  void push(TItem item) {
    absl::WriterMutexLock lock(&m_mutex);
    m_queue.emplace_back(std::move(item));
  }

  auto pop() -> std::optional<TItem> {
    absl::WriterMutexLock lock(&m_mutex);
    if (!m_mutex.AwaitWithTimeout(
            absl::Condition(
                +[](queue_t *queue) { return !queue->empty(); }, &m_queue),
            absl::Seconds(1))) {
      return std::nullopt;
    }

    auto item = std::make_optional(m_queue.front());
    m_queue.pop_front();
    return item;
  }

private:
  absl::Mutex m_mutex;
  queue_t m_queue;
};

