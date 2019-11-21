//
// Created by Карина Зайнуллина on 11/11/2019.
//

#ifndef MADE_CPP_BINARYTREE_H
#define MADE_CPP_BINARYTREE_H

#include <iostream>
#include <stack>

class BinaryTree {
private:
    class Node {
    private:
        Node *leftChild = nullptr;
        Node *rightChild = nullptr;
        int value;
    public:
        explicit Node(int value) : value(value) {}


        int getValue() { return value; }

        Node *getLeftChild() const {
            return leftChild;
        }

        Node *getRightChild() const {
            return rightChild;
        }

        void setLeftChild(Node *leftChild) {
            Node::leftChild = leftChild;
        }

        void setRightChild(Node *rightChild) {
            Node::rightChild = rightChild;
        }
    };


    Node *root = nullptr;

    static void deleteTree(Node* node);

public:
    void addLeave(int value);

    std::string inOrderTraversal();

    virtual ~BinaryTree();
};

#endif //MADE_CPP_BINARYTREE_H
