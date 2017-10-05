#ifndef QUEUE_H
#define QUEUE_H

#include <QList>
#include <stdexcept>


template <typename T>
class Queue
{
public:
    Queue(int maxSize);
public:
    void push(const T& t) throw(std::out_of_range);
    T&   pop() throw(std::out_of_range);
    bool empty() const;
    bool full() const;
    int  maxSize() const;
    int  size() const;
    T&   head() throw(std::out_of_range);
    bool setMaxSize(int maxSize);
    void clear();
    void expand(int val);

private:
    QList<T> _data;
    int _maxSize;
};

#endif // QUEUE_H

template <typename T>
Queue<T>::Queue(int maxSize)
    : _maxSize(maxSize)
{}

template <typename T>
void Queue<T>::push(const T &t) throw(std::out_of_range) {
    if (full()) {
        throw std::out_of_range("Queue is full.");
    }
    _data.push_back(t);
}

template <typename T>
T& Queue<T>::pop() throw(std::out_of_range) {
    if (empty()) {
        throw std::out_of_range("Queue is empty.");
    }
    T tmp = _data[0];
    _data.removeFirst();
    return tmp;
}

template <typename T>
bool Queue<T>::empty() const {
    return size() == 0;
}

template <typename T>
bool Queue<T>::full() const {
    return size() == maxSize();
}

template <typename T>
int Queue<T>::maxSize() const {
    return _maxSize;
}

template <typename T>
int Queue<T>::size() const {
    return _data.size();
}

template <typename T>
T& Queue<T>::head() throw(std::out_of_range) {
    if (empty()) {
        throw std::out_of_range("Queue is empty.");
    }
    return _data.last();
}

template <typename T>
bool Queue<T>::setMaxSize(int maxSize) {
    if (maxSize < _maxSize) {
        return false;
    }
    _maxSize = maxSize;
}

template <typename T>
void Queue<T>::clear() {
    _data.clear();
}

template <typename T>
void Queue<T>::expand(int val) {
    if (val > 0) {
        _maxSize += val;
    }
}
