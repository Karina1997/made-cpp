//
// Created by Карина Зайнуллина on 29/11/2019.
//


#include <vector>
#include <map>
#include <list>
#include <queue>
#include "Huffman.h"

using namespace std;

class Node {
public:
    int a = 0;
    char c = -1;
    Node *left = nullptr, *right = nullptr;
    Node(Node *left, Node *right) : left(left), right(right) {a = left->a + right->a;}

    Node(int a, char c) : a(a), c(c) {}

    bool operator < (Node * node){
        return this->a < node->a;
    }
};

void BuildTable(Node &root, map<char, vector<bool>> &table, vector<bool> &code) {
    if (root.left != nullptr) {
        code.push_back(false);
        BuildTable(*root.left, table, code);
    }

    if (root.right != nullptr) {
        code.push_back(true);
        BuildTable(*root.right, table, code);
    }

    if (root.left == nullptr && root.right == nullptr) table[root.c] = code;

    code.pop_back();
}

Node *buildTree(map<byte, int> *freq) {
    list<Node *> t;
    for (auto & itr : *freq) {
        Node *p = Node(itr.first, itr.second);
        t.push_back(p);
    }

    while (t.size() != 1) {
        t.sort();

        Node *SonL = t.front();
        t.pop_front();
        Node *SonR = t.front();
        t.pop_front();

        Node *parent = new Node(SonL, SonR);
        t.push_back(parent);
    }

    return t.front();
}

void deleteTree(Node* root)
{
    if (root == nullptr)
        return;

    queue<Node *> q;
    q.push(root);
    while (!q.empty())
    {
        Node* node = q.front();
        q.pop();

        if (node->left != nullptr)
            q.push(node->left);
        if (node->right != nullptr)
            q.push(node->right);

        delete node;
    }
}

void readLong(IInputStream &compressed, ulong &total) {
    byte val = 0;

    compressed.Read(val);
    total = ((unsigned int) val) << 24;

    compressed.Read(val);
    total |= ((unsigned int) val) << 16;

    compressed.Read(val);
    total |= ((unsigned int) val) << 8;

    compressed.Read(val);
    total |= ((unsigned int) val);
}

void writeLong(IOutputStream &compressed, ulong &total) {
    compressed.Write((byte) ((total & 0xFF000000) >> 24));
    compressed.Write((byte) ((total & 0x00FF0000) >> 16));
    compressed.Write((byte) ((total & 0x0000FF00) >> 8));
    compressed.Write((byte) ((total & 0X000000FF)));
}

void writeData(IOutputStream &compressed, vector<byte> &outBuffer) {
    for (byte bp: outBuffer) {
        compressed.Write(bp);
    }
}

void writeFrequencies(IOutputStream &compressed, map<byte, int> &m) {
    ulong size = m.size();
    writeLong(compressed, size);
    for (auto const &x : m) {
        compressed.Write(x.first);
        compressed.Write(x.second >> 24);
        compressed.Write(x.second >> 16);
        compressed.Write(x.second >> 8);
        compressed.Write(x.second);
    }
}

void readFrequencies(IInputStream &compressed, map<byte, int> &m) {
    ulong size = 0;
    readLong(compressed, size);
    byte key = 0;
    byte value = 0;
    for (ulong i = 0; i < size; i++) {
        compressed.Read(key);

        compressed.Read(value);
        int v = int((unsigned char) (value) << 24);
        compressed.Read(value);
        v = v | (unsigned char) (value) << 16;
        compressed.Read(value);
        v = v | (unsigned char) (value) << 8;
        compressed.Read(value);
        v = v | (unsigned char) (value);

        m[key] = v;
    }
}

void Encode(IInputStream &original, IOutputStream &compressed) {
    vector<byte> inBuffer;
    map<byte, int> m;
    byte c = -1;
    while (original.Read(c)) {
        m[c]++;
        inBuffer.push_back(c);
    }

    Node *root = buildTree(&m);
    map<char, vector<bool>> table;
    vector<bool> code;
    BuildTable(*root, table, code);
    deleteTree(root);

    vector<byte> outBuffer;
    ulong totalBits = 0;
    int count = 0;
    byte buf = 0;
    for (byte ch : inBuffer) {
        vector<bool> x = table[ch];
        for (int n = 0; n < x.size(); n++) {
            totalBits++;
            buf = buf | x[n] << (7 - count);
            count++;
            if (count == 8) {
                outBuffer.push_back(buf);
                count = 0;
                buf = 0;
            }
        }
    }
    if (count != 0) {
        outBuffer.push_back(buf);
    }


    writeLong(compressed, totalBits);
    writeFrequencies(compressed, m);
    writeData(compressed, outBuffer);
}

void Decode(IInputStream &compressed, IOutputStream &original) {
    ulong totalBits = 0;
    map<byte, int> m;

    readLong(compressed, totalBits);
    readFrequencies(compressed, m);

    Node *root = buildTree(&m);
    map<char, vector<bool>> table;
    vector<bool> code;
    BuildTable(*root, table,code);
    deleteTree(root);

    Node *p = root;
    int count = 0;
    byte next;
    bool hasNext = compressed.Read(next);
    while (hasNext && totalBits > 0) {
        totalBits--;
        bool b = next & (1 << (7 - count));
        if (b) p = p->right; else p = p->left;
        if (p->left == nullptr && p->right == nullptr) {
            original.Write(p->c);
            p = root;
        }
        count++;
        if (count == 8) {
            count = 0;
            hasNext = compressed.Read(next);
        }
    }
}
