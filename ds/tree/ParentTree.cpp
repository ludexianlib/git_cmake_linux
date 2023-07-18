#include "ParentTree.h"
#include <stdio.h>

ParentTree::ParentTree()
	: curSize(0),
	  maxSize(5)
{
}

ParentTree::~ParentTree()
{
	for (int i = 0; i < curSize; i++) {
		delete mNode[i];
	}
}

void ParentTree::init(int key)
{
	if (curSize != 0) {
		printf("�Ѿ��������ڵ�.\n");
		return;
	}
	node* root = new node;
	root->data = key;
	root->parent = -1;

	mNode[curSize++] = root;
}

void ParentTree::insert(int key, int parent)
{
	if (curSize == 0) {
		printf("δ�������ڵ�.\n");
		return;
	}

	if (curSize == maxSize) {
		printf("�ڵ�������.\n");
		return;
	}

	int parentData = find(parent);
	if (parentData == -1) {
		printf("û�иø��ڵ�.\n");
		return;
	}

	node* p = new node;
	p->data = key;
	p->parent = parentData;
	mNode[curSize++] = p;
}

int ParentTree::find(int parent)
{
	for (int i = 0; i < curSize; i++) {
		if (mNode[i]->data == parent) {
			return mNode[i]->data;
		}
	}
	return -1;
}
