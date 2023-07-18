#pragma once

class ChileTree
{
public:
	struct node
	{
		int data;
		node* next;
	};

	ChileTree();
	~ChileTree();
	void init(int key);
	void insert(int key, int parent);
	int find(int parent);
private:
	int size;
	node* mNode[8];
};