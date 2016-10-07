
#include <iostream>
using namespace std;

//�ڵ�Ķ���
typedef struct BTNode
{
	int data;
	BTNode* rChild;
	BTNode* lChild;
}BiTNode, *BiTree;


//�������Ĵ��������򴴽�������
int CreateBiTree(BiTNode** T)
{
	int ch;
	cin >> ch;
	if (ch==-1)
	{
		*T = nullptr;
		return 0;
	}
	else
	{
		//*T = new BiTNode();
		*T = (BiTNode*)malloc(sizeof(BiTNode));
		if (T==nullptr)
		{
			cout << "failed!\n";
			return 0;
		}
		else
		{
			(*T)->data = ch;
			cout << "�������ӽڵ㣺";
			//cin >> ch;
			CreateBiTree(&(*T)->lChild);
			cout << endl;
			cout << "�������ӽڵ㣺";
			//cin >> ch;
			CreateBiTree(&(*T)->rChild);
		}
	}
	return 1;
}


//�������������
void PreOrderBiTree(BiTNode* T)
{
	if (T == nullptr)
	{
		return;
	}
	else
	{
		cout << T->data<<" ";
		PreOrderBiTree(T->lChild);
		PreOrderBiTree(T->rChild);
	}
}

//�������������
void InOrderBiTree(BiTNode* T)
{
	if (T == nullptr)
	{
		return;
	}
	else
	{
		InOrderBiTree(T->lChild);
		cout << T->data << " ";
		InOrderBiTree(T->rChild);
	}
}

//��������������
void PostOrderBiTree(BiTNode* T)
{
	if (T == nullptr)
	{
		return;
	}
	else
	{
		PostOrderBiTree(T->lChild);
		PostOrderBiTree(T->rChild);
		cout << T->data << " ";
	}
}

//����....

//Ҷ�ӽڵ����
int LeafCount(BiTNode* T)
{
	static int count = 0;
	if (T!=nullptr)
	{
		if (T->lChild==nullptr&&T->rChild==nullptr)
		{
			count++;
		}
		LeafCount(T->lChild);
		LeafCount(T->rChild);
	}
	return count;
}

//�ͻ��˲���
int main()
{
	BiTNode* T;
	int leafCount = 0;
	cout << "�������һ���ڵ��ֵ��-1��ʾû�нڵ㣺\n";
	CreateBiTree(&T);

	cout << "���������������";
	PreOrderBiTree(T);
	cout << endl;

	cout << "���������������";
	InOrderBiTree(T);
	cout << endl;

	cout << "�������������: ";
	PostOrderBiTree(T);
	cout << endl;

	leafCount = LeafCount(T);
	cout << "Ҷ�ӽڵ�ĸ�����" <<leafCount<< endl;


	return 0;
}


