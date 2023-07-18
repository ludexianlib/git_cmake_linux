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
		printf("已经创建根节点.\n");
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
		printf("未创建根节点.\n");
		return;
	}

	if (curSize == maxSize) {
		printf("节点树已满.\n");
		return;
	}

	int parentData = find(parent);
	if (parentData == -1) {
		printf("没有该父节点.\n");
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
