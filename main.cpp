#include<iostream>
#include<vector>
using namespace std;

struct Node {
	int data;
	Node* lchild;
	Node* rchild;
};

//�����½��
Node* newNode(int val)
{
	Node* node = new Node;
	node->data = val;
	node->lchild = node->rchild = nullptr;
	return node;
}

//����������Ĳ��Ҳ���
bool search(Node* root, const int& val)
{
	if (root == nullptr) return false;
	if (root->data == val) {
		return true;
	}
	else if (root->data > val) return search(root->lchild, val);
	else return search(root->rchild, val);
}

//����������Ĳ������
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

//����������Ľ���
Node* create(vector<int>& data)
{
	Node* root = nullptr;
	for (auto& iter : data) {
		insert(root, iter);
	}
	return root;
}

//����������ӵĽ�㣬�ҵ������������ֵ
Node* GetLeftMax(Node* root)
{
	while (root != nullptr && root->rchild != nullptr) {
		root = root->rchild;
	}
	return root;
}

//��������к��ӵĽ�㣬�ҵ�����������Сֵ
Node* GetRightMin(Node* root)
{
	while (root != nullptr && root->lchild != nullptr) {
		root = root->lchild;
	}
	return root;
}

//�����������ɾ��
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