#ifndef QUEUE_H
#define QUEUE_H

#include <stdexcept>
#include <iostream>

template <typename T>
class Queue {
public:
    Queue(int size = 10);
    Queue(const Queue<T>& orig);
    ~Queue();
public:
    bool full() const;
    bool empty() const;
    int  size() const;
    int  capacity() const;
    void push(const T& newElem) throw(std::out_of_range);
    T    pop() throw(std::out_of_range);
    T    top() throw(std::out_of_range);
    T*   data();
    void print();
private:
    int _capacity; // емкость очереди
    int _size;     // фактический размер
    T*  _data;     // массив данных
    int _begin;    // указатель на первый элемент очереди
    int _end;      // указатель на конец очереди
};

#endif // QUEUE_H

// конструктор по-умолчанию
template <typename T>
Queue<T>::Queue(int size/* = 10*/)
    : _capacity(size),
      _size(0),
      _data(new T[_capacity]),
      _begin(0),
      _end(0)
{}

// конструктор копирования
template <typename T>
Queue<T>::Queue(const Queue<T>& orig)
    : _capacity(orig._capacity),
      _size(orig._size),
      _data(new T[_capacity]),
      _begin(orig._begin),
      _end(orig._end)
{
    for (int i = 0; i < _size; i++) {
        _data[i] = orig._data[i];
    }
}

// деструктор
template <typename T>
Queue<T>::~Queue() {
    delete [] _data;
}

// пуста ли очередь?
template <typename T>
bool Queue<T>::full() const {
    return _size == _capacity;
}

// полна ли очередь?
template <typename T>
bool Queue<T>::empty() const {
    return _size == 0;
}

// возвращает фактический размер очереди
template <typename T>
int Queue<T>::size() const {
    return _size;
}

// возвращает максимально возможный размер очереди
template <typename T>
int Queue<T>::capacity() const {
    return _capacity;
}

// вставляет элемент в конец очереди
template <typename T>
void Queue<T>::push(const T& newElem) throw(std::out_of_range) {
    // проверка на заполненность
    if (full()) {
        throw std::out_of_range("Queue is full.\n");
    }

    // вставка элемента
    _data[_end++] = newElem;
    ++_size;

    // проверка кругового заполнения очереди
    if (_end == _capacity) {
        _end -= _capacity;
    }
}

// достает элемент из начала очереди
template <typename T>
T Queue<T>::pop() throw(std::out_of_range) {
    if (empty()) {
        throw std::out_of_range("Queue is empty.\n");
    }

    // достаём элемент
    T retValue = _data[_begin++];
    --_size;

    // проверка кругового заполнения очереди
    if (_begin == _capacity) {
        _begin -= _capacity;
    }

    return retValue;
}

// возвращает первый элемент очереди
template <typename T>
T Queue<T>::top() throw(std::out_of_range) {
    if (empty()) {
        throw std::out_of_range("Queue is empty.\n");
    }
    return _end == 0 ? _data[_capacity - 1] : _data[_end - 1];
}

// распечатка очереди
template <typename T>
void Queue<T>::print() {
    if (_size == 0) {
        std::cout << "Queue is empty." << std::endl;
        return;
    }

    // вывод очереди -> 1 2 3 ->
    std::cout << "-> ";
    int size = _size;
    int i = _end ? _end - 1 : _capacity - 1;
    for ( ; size > 0; --size, --i) {
        if (i < 0) {
            i = _capacity - 1;
        }
        std::cout <<  _data[i] << " ";
    }
    std::cout << "->" << std::endl;

    // вывод фактического расположения
    // элементов в массиве
    std::cout << "Array: ";
    for (int i = 0; i < _capacity; i++) {
        std::cout << _data[i] << " ";
    }
    std::cout << std::endl;
}

