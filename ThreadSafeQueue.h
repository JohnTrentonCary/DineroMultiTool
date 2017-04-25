#pragma once

#include <mutex>
#include <queue>

template <class T>
class ThreadSafeQueue
{
private:
    std::mutex protectMyQueue;
    std::queue<T> myQueue;

public:
    void Enqueue(T &value)
    {
        //lock this scope.
        std::lock_guard<std::mutex> guard(protectMyQueue);
        //put item in queue.
        myQueue.push(value);
    }

    bool Dequeue(T &value)
    {
        //lock this scope.
        std::lock_guard<std::mutex> guard(protectMyQueue);
        //check if queue is empty;
        if (myQueue.empty())
            return false;

        value = myQueue.front();
        myQueue.pop();
        return true;
    }
};
