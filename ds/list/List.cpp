#include "List.h"
#include <stdio.h>

List::List()
{
	node* s = new node;
	s->data = -1;
	s->next = nullptr;
	head = s;
}

List::~List()
{
	node* p;
	while (head != nullptr)
	{
		p = head;
		head = head->next;
		delete p;
	}
}

void List::push_front(int key)
{
	node* s = new node;
	s->data = key;

	s->next = head->next;
	head->next = s;
}

void List::push_back(int key)
{
	node* s = new node;
	s->data = key;

	node* p = head;
	while (p->next != nullptr)
		p = p->next;

	s->next = p->next;
	p->next = s;
}

void List::remove(int key)
{
	node* p = head;			// 两个先后指针
	node* s = head->next;

	while (s != nullptr && s->data != key)
	{
		p = s;
		s = s->next;
	}

	if (s == nullptr) {
		printf("不存在值为%d的元素.\n", key);
		return;
	}

	p->next = s->next;
	s->next = nullptr;
	delete s;
}

void List::tranverse()
{
	node* p = head->next;

	int i = 1;
	while (p != nullptr)
	{
		printf("元素%d的值: %d\n", i++, p->data);
		p = p->next;
	}
}
