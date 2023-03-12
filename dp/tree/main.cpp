#include "BinaryTree.h"
#include "LinkQueue.h"
#include "Huffman.h"

int main(int argc, char* argv)
{
    // BinaryTree t;
    // t.PreOrderTraverse();
    // t.InOrderTraverse();
    // t.LevelOrderTraverse();

    int weight[8] = {29, 7, 8, 14, 23, 11, 5 ,3};
    Huffman h(weight, 8);

    return 0;
}