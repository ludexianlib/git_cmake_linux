#pragma once

struct HTNode
{
    int weight;
    int parent;
    int lchild;
    int rchild;
};

class Huffman
{
public:
    Huffman(int w[], int n);
    ~Huffman();

private:
    HTNode* bt;
};