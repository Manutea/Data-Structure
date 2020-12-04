#pragma once
#include <iterator>
#include <memory>
#include <iostream>


template <typename T>
class DoubleLinkedList
{

private:
    class Node
    {
    public:
        Node() : _data(T()) {}
        explicit Node(const T& value) : _data(value) {}

        friend class DoubleLinkedList;
    private:
        T _data;
        std::shared_ptr<Node> _next;
        std::shared_ptr<Node> _prev;
    };

public:
    class Iterator
    {
    public:
        Iterator() noexcept :
            _currentNode(_head.get()) { }

        Iterator(Node* _Node) noexcept :
            _currentNode(_Node) { }

        Iterator& operator=(Node* _Node)
        {
            _currentNode = _Node;
            return *this;
        }

        Iterator& operator++()
        {
            if (_currentNode)
                _currentNode = _currentNode->_next.get();
            return *this;
        }

        Iterator operator++(int)
        {
            Iterator iterator = *this;
            ++* this;
            return iterator;
        }

        Iterator& operator--()
        {
            if (_currentNode)
                _currentNode = _currentNode->_prev.get();
            return *this;
        }

        Iterator operator--(int)
        {
            Iterator iterator = *this;
            --* this;
            return iterator;
        }

        bool operator!=(const Iterator& iterator)
        {
            return _currentNode != iterator._currentNode;
        }

        int operator*()
        {
            return _currentNode->_data;
        }

    private:
        Node* _currentNode;
    };

public:

    DoubleLinkedList() {}

    void pushFront(const T& value) {
        auto newNode = std::make_shared<Node>(value);

        if (_head) {
            newNode->_next = _head;
            _head->_prev = newNode;
            _head = newNode;
        }
        else {
            _head = newNode;
            if (!_tail)
                _tail = _head;
        }
    }

    void pushBack(const T& value) {
        auto newNode = std::make_shared<Node>(value);

        if (_tail) {
            newNode->_prev = _tail;
            _tail->_next = newNode;
            _tail = newNode;
        }
        else {
            _tail = newNode;
            if (!_head)
                _head = _tail;
        }
    }

    void clear() {
        while (_head) {
            auto temp = _head;
            _head = temp->_next;
            if (_head)
                _head->_prev = nullptr;
        }
    }

    void popFront() {
        if (_head == nullptr) {
            return;
        }

        auto temp = _head;
        _head = temp->_next;
        _head->_prev = nullptr;
    }

    void popBack() {
        if (_tail == nullptr) {
            return;
        }

        auto temp = _tail;
        _tail = temp->_prev;
        _tail->_next = nullptr;
    }

    void print()
    {
        auto head = _head.get();
        while (head) {
            std::cout << head->_data << " ";
            head = head->_next.get();
        }
        std::cout << std::endl;
    }

    void printBack()
    {
        auto tail = _tail.get();
        while (tail) {
            std::cout << tail->_data << " ";
            tail = tail->_prev.get();
        }
        std::cout << std::endl;
    }

    void reverse() {

        auto tmpHead = _head.get();
        auto tmpTail = _tail.get();

        for (auto it = begin(); it != end(); it++) {
            T tmpData = tmpHead->_data;
            tmpHead->_data = tmpTail->_data;
            tmpTail->_data = tmpData;

            if(tmpHead->_next.get() == tmpTail)
                break;

            tmpHead = tmpHead->_next.get();
            tmpTail = tmpTail->_prev.get();

            if (tmpHead == tmpTail)
                break;
        }
    }

    Iterator begin()
    {
        return Iterator(_head.get());
    }

    Iterator end()
    {
        return Iterator(nullptr);
    }

    Iterator rbegin()
    {
        return Iterator(_tail.get());
    }

    Iterator rend()
    {
        return Iterator(nullptr);
    }

    ~DoubleLinkedList() {
        clear();
    }

private:
    std::shared_ptr<Node> _head;
    std::shared_ptr<Node> _tail;
};