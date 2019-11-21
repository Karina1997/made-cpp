//
// Created by Карина Зайнуллина on 11/11/2019.
//


#include <queue>
#include "BinaryTree.h"

void BinaryTree::addLeave(int value) {
    Node *node = new Node(value);
    Node *currentNode = root;
    Node *prevNode = nullptr;
    while (currentNode != nullptr) {
        prevNode = currentNode;
        if (currentNode->getValue() > value) {
            currentNode = currentNode->getLeftChild();
        } else {
            currentNode = currentNode->getRightChild();
        }
    }

    if (prevNode == nullptr) {
        root = node;
    } else if (prevNode->getValue() > value) {
        prevNode->setLeftChild(node);
    } else {
        prevNode->setRightChild(node);
    }
}

std::string BinaryTree::inOrderTraversal() {
        std::stack<Node> stack;
        Node *currentNode = root;
        std::string str;

        while (currentNode != nullptr || !stack.empty()) {
            if (currentNode != nullptr) {
                stack.push(*currentNode);
                currentNode = currentNode->getLeftChild();
            } else {
                currentNode = &stack.top();
                stack.pop();
                str += std::to_string(currentNode->getValue()) + " ";
                currentNode = currentNode->getRightChild();
            }
        }
        return str;
}

BinaryTree::~BinaryTree() {
    deleteTree(root);
    root = nullptr;
}

void BinaryTree::deleteTree(Node* root)
{
    if (root == nullptr)
        return;

    std::queue<Node *> q;
    q.push(root);
    while (!q.empty())
    {
        Node* node = q.front();
        q.pop();

        if (node->getLeftChild() != nullptr)
            q.push(node->getLeftChild());
        if (node->getRightChild() != nullptr)
            q.push(node->getRightChild());

       delete node;
    }
}

int binaryTreeMain() {
    BinaryTree binaryTree;
    int size;
    std::cin >> size;
    int numberToAdd;
    for (int i = 0; i < size; ++i) {
        std::cin >> numberToAdd;
        binaryTree.addLeave(numberToAdd);
    }

    std::cout << binaryTree.inOrderTraversal();
}
