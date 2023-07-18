#include "ChileTree.h"
#include <stdio.h>

ChileTree::ChileTree() : size(0)
{
}

ChileTree::~ChileTree()
{
}

void ChileTree::init(int key)
{
	node* p = new node;
	p->data = key;
	p->next = nullptr;
	mNode[size++] = p;
}

void ChileTree::insert(int key, int parent)
{
	if (size == 0) {
		printf("未创建根节点.\n");
		return;
	}
	// 所有节点在数组中按顺序排列
	node* s = new node;
	s->data = key;
	s->next = nullptr;
	mNode[size++] = s;

	int parentIndex = find(parent);
	if (parentIndex == -1) {
		printf("未找到父节点.\n");
		return;
	}

	// 设置父节点
	node* p = new node;
	p->data = key;
	p->next = mNode[parentIndex]->next;
	mNode[parentIndex]->next = p;

}

int ChileTree::find(int parent)
{
	for (int i = 0; i < size; i++) {
		if (mNode[i]->data == parent) {
			return i;
		}
	}
	return -1;
}
