#pragma once

struct BTSNode
{
    int data;
    BTSNode* lchild;
    BTSNode* rchild;
};

// 二叉查找树(Binary Sort Tree)
void SearchBST(BTSNode* T, int key, BTSNode* &ret)
{
    if (T == nullptr || (key == T->data))
    {
        if (T == nullptr)
            return; // 查找失败
        else
            ret = T; // 查找成功
    }
    else if (key < T->data)
        SearchBST(T->lchild, key, ret);
    else
        SearchBST(T->rchild, key, ret);    
}
