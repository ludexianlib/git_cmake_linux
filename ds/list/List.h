#pragma once

class List
{
public:
	struct node
	{
		int data;
		node* next;
	};

	List();
	~List();
	void push_front(int key);
	void push_back(int key);
	void remove(int key);
	void tranverse();

private:
	node* head = nullptr;
};