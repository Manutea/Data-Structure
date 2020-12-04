#include <iostream>
#include <forward_list>

#include "LinkedList.h"
#include "DoubleLinkedList.h"
#include "BinaryTree.h"

int main()
{
    LinkedList<int> linkedList;
    for (auto i = 0; i < 10; i++)
        linkedList.pushFront(i);
    
    for (auto it = linkedList.begin(); it != linkedList.end(); it++)
        std::cout << *it << " ";
    std::cout << std::endl;

    DoubleLinkedList<int> doubleLinkedList;
    for (auto i = 0; i < 11; i++)
        doubleLinkedList.pushFront(i);
    
    doubleLinkedList.print();
    doubleLinkedList.reverse();
    doubleLinkedList.print();

    BinaryTree<int> binaryTree;
    binaryTree.push(0);
    binaryTree.push(1);
    binaryTree.push(2);
    binaryTree.push(3);
    binaryTree.push(4);

    binaryTree.printTraversal();
}