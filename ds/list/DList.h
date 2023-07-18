#pragma once

class DList
{
	// 双向循环链表
public:
	struct node
	{
		int data;
		node* front;
		node* next;
	};

	DList();
	~DList();
	void push_front(int key);
	void push_back(int key);
	void remove(int key);
	void tranverse();

private:
	node* head = nullptr;
	node* tail = nullptr;
};

