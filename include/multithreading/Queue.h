/**
 * single producer, single consumer lock free queue
 * circular buffer
 */

#include <vector>
#include <atomic>
#include <optional>

namespace prism {

template<typename T>
class Queue {

public:
    Queue(int capacity = 50) 
        : buffer(capacity + 1), front(0), back(0), capacity(capacity + 1)
    {}

    // producer push
    template<typename U>
    bool try_push(U&& item) {
        int next = (front + 1) % capacity;
        if (next == back) {
            return false;
        }
        buffer[front] = std::forward<U>(item);
        front = next;
        return true;
    }

    // consumer pop
    std::optional<T> try_pop() {
        if (front == back) {
            // empty
            return std::nullopt;
        }
        T item = std::move(buffer[back]);
        back = (back + 1) % capacity;
        return item;
    }

    // check if empty
    bool empty() const {
        return front == back;
    }

    // check if full
    bool full() const {
        return ((front + 1) % capacity) == back;
    }

private:
    std::vector<T> buffer;
    std::atomic<int> front, back;
    int capacity;


};

}