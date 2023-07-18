#pragma once
#include <vector>
#include <stdio.h>

struct node {
	int data;
	node* left = nullptr;
	node* right = nullptr;
};

class CompleteBTree
{
public:
	CompleteBTree(int len);
	node* create(std::vector<int> nums, int index);
	void preTraverse(node* root);
private:
	int mLen;
};