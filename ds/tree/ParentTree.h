#pragma once

class ParentTree
{
	// Ë«Ç×±íÊ¾·¨
public:
	struct node {
		int data;
		int parent;
	};

	ParentTree();
	~ParentTree();
	void init(int key);
	void insert(int key, int parent);
	int find(int parent);
private:
	int curSize;
	int maxSize;
	node* mNode[5];
};