#ifndef THREAD_SAFE_QUEUE_H
#define THREAD_SAFE_QUEUE_H

#include <queue>
#include <mutex>

template <typename T>
class thread_safe_queue
{
public:
    thread_safe_queue() = default;

    T pop()
    {
        std::unique_lock<std::mutex> mlock(mutex);

        T val = queue.front();
        queue.pop();
        return val;
    }

    void push(const T& item)
    {
        std::unique_lock<std::mutex>(mutex);
        queue.push(item);
    }

    bool empty() const
    {
        std::unique_lock<std::mutex>(mutex);
        return queue.empty();
    }

    size_t size() const
    {
        std::unique_lock<std::mutex>(mutex);
        return queue.size();
    }

private:
    std::mutex mutex;
    std::queue<T> queue;
};

#endif // THREAD_SAFE_QUEUE_H
