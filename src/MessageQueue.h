#ifndef MESSAGE_QUEUE_H
#define MESSAGE_QUEUE_H

#include <mutex>
#include <deque>
#include <condition_variable>

template <class T>
class MessageQueue
{
public:
    void send(T&& msg) {
        // perform modification under the lock
        std::lock_guard<std::mutex> uLock(_mutex);
        _queue.push_back(std::move(msg));
        //std::cout << "send: " << _queue.size() << "\n";
        _condition.notify_one();
    }

    T receive() {
        std::unique_lock<std::mutex> uLock(_mutex);
        _condition.wait(uLock, [this] { return !_queue.empty(); });

        T msg = std::move(_queue.back());
        _queue.pop_back();
        //std::cout << "receive: " << _queue.size() << "\n";
        return msg;
    }

private:
    std::deque<T> _queue;
    std::condition_variable _condition;
    std::mutex _mutex;
};

#endif
