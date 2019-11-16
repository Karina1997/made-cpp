//
// Created by Карина Зайнуллина on 14/11/2019.
//

#ifndef MADE_CPP_SPLAYTREE_H
#define MADE_CPP_SPLAYTREE_H

class SplayTree {
private:
    struct Node {
        int key;
        int number = 0;
        Node *Left = nullptr;
        Node *Right = nullptr;
        Node *Parent = nullptr;

        explicit Node(int length) : key(length) {}

        Node *grandParent() { return Parent->Parent; }
    };


    static void rightRotate(Node *);

    static void leftRotate(Node *);

    void splay(Node *);

    Node *root = nullptr;

public:
    int insert(int val);

    bool remove(int val);

    Node *find(int val);
};


#endif //MADE_CPP_SPLAYTREE_H
