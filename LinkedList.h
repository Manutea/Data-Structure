#pragma once
#include <iterator>
#include <memory>
#include <iostream>


template <typename T>
class LinkedList
{

private:
    class Node
    {
    public:
        Node() : _data(T()) {}
        explicit Node(const T& value) : _data(value) {}

        friend class LinkedList;
    private:
        T _data;
        std::unique_ptr<Node> _next;
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

    LinkedList() {}

    LinkedList(const LinkedList<T> &_list){
        Node* root = _list._head.get();

        std::unique_ptr<Node> newHead = nullptr;
        Node* pnewHead = nullptr;

        while (root) {
            auto temp = std::make_unique<Node>(root->_data);
            if (newHead == nullptr) {
                newHead = std::move(temp);
                pnewHead = newHead.get();
            }
            else {
                pnewHead->_next = std::move(temp);
                pnewHead = pnewHead->_next.get();
            }
            root = root->_next.get();
        }
        _head = std::move(newHead);
    }

    void pushBack(const T& value)
    {
        if (_head)
        {
            auto currentNode = _head.get();

            while (currentNode->_next != nullptr)
            {
                currentNode = currentNode->_next.get();
            }

            currentNode->_next = std::make_unique<Node>(value);
        }
        else
        {
            _head = std::make_unique<Node>(value);
        }
    }

    void pushFront(const T& value)
    {
        auto currentNode = std::make_unique<Node>(value);

        if (_head)
        {
            currentNode->_next = std::move(_head);
            _head = std::move(currentNode);
        }
        else
        {
            _head = std::move(currentNode);
        }
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

    void clear() {
        while (_head) {
            _head = std::move(_head->_next);
        }
    }

    void popFront() {
        if (_head == nullptr) {
            return;
        }

        auto temp = std::move(_head);
        _head = std::move(temp->_next);
    }

    void reverse() {
        LinkedList tmp;
        auto root = _head.get();
        while (root) {
            tmp.pushFront(root->_data);
            root = root->_next.get();

        }
        clear();
        _head = std::move(tmp._head);
    }

    Iterator begin()
    {
        return Iterator(_head.get());
    }

    Iterator end()
    {
        return Iterator(nullptr);
    }

    ~LinkedList() {
        clear();
    }

private:
    std::unique_ptr<Node> _head;
};

