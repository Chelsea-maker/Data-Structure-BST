#include<iostream>
#include<vector>
using namespace std;

struct Node {
	int data;
	Node* lchild;
	Node* rchild;
};

//创建新结点
Node* newNode(int val)
{
	Node* node = new Node;
	node->data = val;
	node->lchild = node->rchild = nullptr;
	return node;
}

//二叉查找树的查找操作
bool search(Node* root, const int& val)
{
	if (root == nullptr) return false;
	if (root->data == val) {
		return true;
	}
	else if (root->data > val) return search(root->lchild, val);
	else return search(root->rchild, val);
}

//二叉查找树的插入操作
void insert(Node*& root, const int& val)
{
	if (root == nullptr) {
		root = newNode(val);
	}
	else if (root->data == val) {
		return;
	}
	else if (root->data > val) {
		insert(root->lchild, val);
	}
	else {
		insert(root->rchild, val);
	}
}

//二叉查找树的建立
Node* create(vector<int>& data)
{
	Node* root = nullptr;
	for (auto& iter : data) {
		insert(root, iter);
	}
	return root;
}

//传入的是左孩子的结点，找到左子树的最大值
Node* GetLeftMax(Node* root)
{
	while (root != nullptr && root->rchild != nullptr) {
		root = root->rchild;
	}
	return root;
}

//传入的是有孩子的结点，找到右子树的最小值
Node* GetRightMin(Node* root)
{
	while (root != nullptr && root->lchild != nullptr) {
		root = root->lchild;
	}
	return root;
}

//二叉查找树的删除
void deleteNode(Node*& root, int& val)
{
	if (root == nullptr) return;
	if (root->data > val) {
		deleteNode(root->lchild, val);
	}
	else if (root->data < val) {
		deleteNode(root->rchild, val);
	}
	else {
		if (root->lchild == nullptr && root->rchild == nullptr) {
			delete root;
			root = nullptr;
		}
		else if (root->lchild != nullptr) {
			Node* pre = GetLeftMax(root->lchild);
			root->data = pre->data;
			deleteNode(root->lchild, pre->data);
		}
		else if (root->rchild != nullptr) {
			Node* post = GetRightMin(root->rchild);
			root->data = post->data;
			deleteNode(root->rchild, post->data);
		}
	}
}

int main()
{
	vector<int> data = { 2,5,7,9,10 };
	Node* root = create(data);
	cout << "Search result: " << (search(root, 9) ? "Found" : "Not found") << endl;
	return 0;
}