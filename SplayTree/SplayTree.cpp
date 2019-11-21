//
// Created by Карина Зайнуллина on 14/11/2019.
//


#include <iostream>
#include <string>
#include <vector>
#include "SplayTree.h"

void SplayTree::rightRotate(Node *z) {
    Node *l = z->Left;
    Node *c = l->Right;
    Node *p = z->Parent;
    if (p != nullptr) {
        if (p->Left == z)
            p->Left = l;
        else
            p->Right = l;
    }
    l->Parent = p;
    l->Right = z;
    z->Parent = l;
    z->Left = c;
    l->number = l->number + z->number + 1;
    if (c != nullptr) {
        c->Parent = z;
    }
}

void SplayTree::leftRotate(Node *z) {
    Node *r = z->Right;
    Node *c = r->Left;
    Node *p = z->Parent;
    if (p != nullptr) {
        if (p->Left == z)
            p->Left = r;
        else
            p->Right = r;
    }
    r->Parent = p;
    r->Left = z;
    z->Parent = r;
    z->Right = c;
    z->number = z->number - 1 - r->number;
    if (c != nullptr) {
        c->Parent = z;
    }
}

void SplayTree::splay(Node *z) {
    if (z == nullptr)
        return;
    while (z->Parent != nullptr) {
        Node *par = z->Parent;
        Node *gPar = z->grandParent();
        if (par->Left == z) {
            if (gPar == nullptr) {
                // zig
                rightRotate(par);
            } else if (gPar->Left == par) {
                // zig-zig
                rightRotate(gPar);
                rightRotate(par);
            } else {
                // zig-zag
                rightRotate(par);
                leftRotate(gPar);
            }
        } else {
            if (gPar == nullptr) {
                // zag
                leftRotate(par);
            } else if (gPar->Right == par) {
                // zag-zag
                leftRotate(gPar);
                leftRotate(par);
            } else {
                // zag-zig
                leftRotate(par);
                rightRotate(gPar);
            }
        }
    }

    root = z;
}

int SplayTree::insert(int val) {
    Node *t = new Node(val);
    if (root == nullptr) {
        root = t;
        return root->number;
    }
    Node *z = root;
    while (true) {
        if (val < z->key) {
            if (z->Left == nullptr) {
                z->Left = t;
                t->Parent = z;
                break;
            } else {
                z = z->Left;
            }
        } else if (z->key < val) {
            z->number += 1;
            if (z->Right == nullptr) {
                z->Right = t;
                t->Parent = z;
                break;
            } else {
                z = z->Right;
            }
        }
    }
    splay(t);
    return t->number;
}

bool SplayTree::remove(int val) {
    Node *z = find(val);
    if (z == nullptr)
        return false;
    Node *t = z->Left;
    if (t == nullptr) {
        root = z->Right;
        root->Parent = nullptr;
    } else {
        root = t;
        Node *newRoot = find(0);
        root = newRoot;
        root->Parent = nullptr;
        root->number = z->number;
        root->Right = z->Right;
        if (root->Right != nullptr) {
            root->Right->Parent = root;
        }
    }
    delete z;
    return true;
}


SplayTree::Node *SplayTree::find(int val) {
    if (root == nullptr)
        return nullptr;
    Node *cur = root;
    while (val != cur->number) {
        if (val > cur->number) {
            val = val - cur->number - 1;
            cur = cur->Left;
        } else {
            cur = cur->Right;
        }
    }

    if (cur != nullptr) {
        splay(cur);
        return cur;
    }
}

int splayTreeMain() {
    int n;
    std::cin >> n;
    int a, b;
    SplayTree s;
    std::vector<int> res;
    for (size_t i = 0; i < n; i++) {
        std::cin >> a >> b;
        if (a == 1) {
            res.push_back(s.insert(b));
        } else {
            if (!s.remove(b)) {
                std::cout << "No such element";
                break;
            }
        }
    }
    for (int re : res)
        std::cout << re << '\n';
}

