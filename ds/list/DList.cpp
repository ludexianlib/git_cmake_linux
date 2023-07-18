#include "DList.h"
#include <stdio.h>

DList::DList()
{
	head = new node;
	tail = new node;
	head->data = tail->data = -1;

	head->next = tail;
	tail->front = head;

	head->front = tail;
	tail->next = head;
}

DList::~DList()
{
	node* s;
	node* p = head->next;
	while (p->data != -1)
	{
		s = p;
		p = p->next;
		delete s;
	}
	delete head;
	delete tail;
}

void DList::push_front(int key)
{
	node* p = new node;
	p->data = key;

	p->next = head->next;
	p->front = head;
	head->next->front = p;
	head->next = p;
}

void DList::push_back(int key)
{
	node* p = new node;
	p->data = key;

	p->next = tail;
	p->front = tail->front;
	tail->front->next = p;
	tail->front = p;
}

void DList::remove(int key)
{
	node* p = head->next;
	while (p->data != key)
	{
		if (p->data == -1) {
			printf("不存在%d元素的值.\n", key);
			return;
		}
		p = p->next;
	}

	node* pre = p->front;
	node* next = p->next;

	pre->next = next;
	next->front = pre;

	p->front = p->next = nullptr;
	delete p;
	p = nullptr;
}

void DList::tranverse()
{
	node* p = head->next;
	int i = 1;
	while (p->data != -1)
	{
		printf("元素%d的值: %d\n", i++, p->data);
		p = p->next;
	}
}
