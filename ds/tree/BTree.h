#pragma once

struct node
{
	int data;
	node* left;
	node* right;
};

class BTree
{
public:
	

	BTree(int key);
	~BTree();
	void insert(int key, int parent);
	void find(int parent, node* t);
	void pre_show(node* t);	// 先序遍历
	void mid_show(node* t);	// 中序遍历
	void aft_show(node* t);	// 后序遍历
	void lev_show(node* t); // 层次遍历
	void destroy(node* t);
	node* getRoot();

private:
	node* root = nullptr;
	node* temp = nullptr;
};

class Solution {
private:

    void traversal(TreeNode* cur, vector<int>& path, vector<string>& result) {
        path.push_back(cur->val);
        // 这才到了叶子节点
        if (cur->left == NULL && cur->right == NULL) {
            string sPath;
            for (int i = 0; i < path.size() - 1; i++) {
                sPath += to_string(path[i]);
                sPath += "->";
            }
            sPath += to_string(path[path.size() - 1]);
            result.push_back(sPath);
            return;
        }
        if (cur->left) {
            traversal(cur->left, path, result);
            path.pop_back(); // 回溯
        }
        if (cur->right) {
            traversal(cur->right, path, result);
            path.pop_back(); // 回溯
        }
    }

public:
    vector<string> binaryTreePaths(TreeNode* root) {
        vector<string> result;
        vector<int> path;
        if (root == NULL) return result;
        traversal(root, path, result);
        return result;
    }
};