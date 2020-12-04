#pragma once
#include <iterator>
#include <memory>
#include <iostream>
#include <queue>


template <typename T>
class BinaryTree {

private:
	class Node {
	public:
		Node() : _data(T()) {}
		explicit Node(const T& value) : _data(value) {}

		friend class BinaryTree;
	private:
		T _data;
		std::shared_ptr<Node> _left;
		std::shared_ptr<Node> _right;
	};

public:
	BinaryTree() {}

	void push(T data) {
		auto newNode = std::make_shared<Node>(data);

		if (_root == nullptr) {
			_root = newNode;
			return;
		}

		std::queue<Node*> q;
		q.push(_root.get());

		while (!q.empty())
		{
			auto currentNode = q.front();
			q.pop();

			if (currentNode->_left == nullptr) {
				currentNode->_left = newNode;
				return;
			}
			else {
				q.push(currentNode->_left.get());
			}

			if (currentNode->_right == nullptr) {
				currentNode->_right = newNode;
				return;
			}
			else {
				q.push(currentNode->_right.get());
			}
		}
	}

	void printTraversal(Node* node) {
		if (node == NULL)
			return;
		printTraversal(node->_left.get());
		std::cout << node->_data << " ";
		printTraversal(node->_right.get());
	}

	void printTraversal() {
		if (_root == NULL)
			return;
		printTraversal(_root->_left.get());
		std::cout << _root->_data << " ";
		printTraversal(_root->_right.get());
	}

private:

	std::shared_ptr<Node> _root;
};